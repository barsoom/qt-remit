#include <QWebEngineNavigationRequest>
#include <QDesktopServices>
#include "mainwindow.h"
#include "constants.h"
#include "settings.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    splitter(),
    profile("RemitProfile", nullptr),
    remitView(&profile),
    githubView(&profile)
{
    profile.setPersistentStoragePath(Constants::dataPath() + "webProfile");
    profile.setPersistentCookiesPolicy(QWebEngineProfile::AllowPersistentCookies);

    splitter.addWidget(&remitView);
    splitter.addWidget(&githubView);

    // TODO: Restore & save splitter state using splitter.saveState and splitter.restoreState. Until then, this is a decent starting point
    splitter.setStretchFactor(0, 1);
    splitter.setStretchFactor(1, 2);

    remitView.setUrl(Settings::remitUrl());
    githubView.setUrl(QUrl("https://github.com"));

    setWindowTitle("Remit");
    setCentralWidget(&splitter);

    connect(
        &remitView, &RemitView::githubNavigationRequested,
        this, &MainWindow::openInGithubView
        );
}

MainWindow::~MainWindow() {}

void MainWindow::connectSignals() {
}

void MainWindow::openInGithubView(const QUrl& url) {
    if (url != githubView.url())
        githubView.setUrl(url);
}
