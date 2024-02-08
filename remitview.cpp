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

bool RemitView::handleUrlAndEmitSignals(const QUrl& url) {
    if (url.host() == Settings::githubUrl().host()) {
        emit githubNavigationRequested(url);
        return false;
    }

    if (url.host() != Settings::remitUrl().host()) {
        emit externalNavigationRequested(url);
        return false;
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
