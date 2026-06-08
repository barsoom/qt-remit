#include "remitview.h"
#include "constants.h"
#include "settings.h"

#include <QWebEngineNavigationRequest>
#include <QWebEngineNewWindowRequest>

RemitView::RemitView(QWidget* parent):
    QWebEngineView(Constants::webProfile(), parent),
    router_(Settings::remitBaseUrl(), Settings::githubUrl())
{
    connect(page(), &QWebEnginePage::navigationRequested, this, &RemitView::handleNavigationRequest);
    connect(page(), &QWebEnginePage::newWindowRequested, this, &RemitView::handleNewWindowRequest);

    page()->load(Settings::remitUrl());
}

bool RemitView::handleUrlAndEmitSignals(const QUrl& url) {
    switch (router_.route(url)) {
        case UrlRouter::Destination::OpenInGithub:
            emit githubNavigationRequested(url);
            return false;
        case UrlRouter::Destination::OpenExternal:
            emit externalNavigationRequested(url);
            return false;
        case UrlRouter::Destination::AcceptInRemit:
            return true;
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
