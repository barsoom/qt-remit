#include <QWebEnginePage>
#include <QWebEngineNavigationRequest>
#include <QWebEngineNewWindowRequest>

#include "githubview.h"
#include "settings.h"

GithubView::GithubView(QWidget* parent): QWebEngineView(parent) {
    init();
}

GithubView::GithubView(QWebEngineProfile* profile, QWidget* parent): QWebEngineView(profile, parent) {
    init();
}

void GithubView::init() const {
    connect(
        page(), &QWebEnginePage::newWindowRequested,
        this, &GithubView::handleNewWindowRequest
    );

    connect(
        page(), &QWebEnginePage::navigationRequested,
        this, &GithubView::handleNavigationRequest
    );

    page()->load(Settings::githubUrl());
}

bool GithubView::handleUrlAndEmitSignals(const QUrl& url) {
    if(url.host() == Settings::githubUrl().host())
        return true;

    emit externalNavigationRequested(url);
    return false;
}

void GithubView::handleNavigationRequest(QWebEngineNavigationRequest& request){
    if(handleUrlAndEmitSignals(request.url()))
        request.accept();
    else
        request.reject();
}

void GithubView::handleNewWindowRequest(QWebEngineNewWindowRequest& request){
    if(handleUrlAndEmitSignals(request.requestedUrl()))
        request.openIn(page());
}
