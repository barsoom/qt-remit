#include "remitview.h"
#include "constants.h"
#include "settings.h"

#include <QWebEngineNavigationRequest>
#include <QWebEngineNewWindowRequest>

RemitView::RemitView(QWidget* parent): QWebEngineView(Constants::webProfile(), parent) {
    connect(page(), &QWebEnginePage::navigationRequested, this, &RemitView::handleNavigationRequest);
    connect(page(), &QWebEnginePage::newWindowRequested, this, &RemitView::handleNewWindowRequest);

    page()->load((Settings::remitUrl()));
}

bool routeMatches(const QUrl& a, const QUrl& b) {
    static auto options = QUrl::RemoveQuery |
                          QUrl::RemoveFragment |
                          QUrl::RemoveUserInfo |
                          QUrl::StripTrailingSlash;

    return a.matches(b, options);
}

bool RemitView::handleUrlAndEmitSignals(const QUrl& url) {
    if (loggingIn) {
        // During login, we can't redirect to a different profile or a different browser, so:
        // - don't fire navigation-events while we're logging in.
        // - accept all navigation requests, open them in this window
        auto oauthRedirectUrl = Settings::remitBaseUrl();
        oauthRedirectUrl.setPath("/auth");

        if (routeMatches(url, oauthRedirectUrl)) {
            // We're done with logging in after this
            loggingIn = false;
        }

        return true;
    }

    if (url.host() == Settings::githubUrl().host()) {
        emit githubNavigationRequested(url);
        return false;
    }

    if (url.host() != Settings::remitBaseUrl().host()) {
        emit externalNavigationRequested(url);
        return false;
    }

    auto loginUrl = Settings::remitBaseUrl();
    loginUrl.setPath("/login");
    if (routeMatches(url, loginUrl)) {
        loggingIn = true;
    }

    return true;
}

void RemitView::handleNavigationRequest(QWebEngineNavigationRequest& request) {
    if (handleUrlAndEmitSignals(request.url()))
        request.accept();
    else
        request.reject();
}

void RemitView::handleNewWindowRequest(QWebEngineNewWindowRequest& request) {
    if (handleUrlAndEmitSignals(request.requestedUrl()))
        request.openIn(page());
}
