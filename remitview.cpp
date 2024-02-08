#include "remitview.h"
#include <QWebEngineNavigationRequest>
#include <QWebEngineNewWindowRequest>

RemitView::RemitView(QWidget* parent): QWebEngineView(parent) {
    connectToPageSignals();
}

RemitView::RemitView(QWebEngineProfile* profile, QWidget* parent): QWebEngineView(profile, parent) {
    connectToPageSignals();
}

void RemitView::connectToPageSignals() const {
    connect(page(), &QWebEnginePage::navigationRequested, this, &RemitView::handleNavigationRequest);
    connect(page(), &QWebEnginePage::newWindowRequested, this, &RemitView::handleNewWindowRequest);
}

bool RemitView::handleUrlAndEmitSignals(const QUrl& url) {
    if (url.host() == "github.com") {
        emit githubNavigationRequested(url);
        return false;
    }

    if (url.host() != "ex-remit.herokuapp.com") {
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
