#include <QWebEngineNavigationRequest>
#include <QDesktopServices>
#include "mainwindow.h"
#include "constants.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    splitter.addWidget(&remitView);
    splitter.addWidget(&githubView);

    // TODO: Restore & save splitter state using splitter.saveState and splitter.restoreState. Until then, this is a decent starting point
    splitter.setStretchFactor(0, 1);
    splitter.setStretchFactor(1, 2);

    setWindowTitle("Remit");
    setCentralWidget(&splitter);

    connect(
        &remitView, &RemitView::githubNavigationRequested,
        this, &MainWindow::openInGithubView
        );

    connect(
        &remitView, &RemitView::externalNavigationRequested,
        this, &MainWindow::openInDefaultBrowser
        );

    connect(
        &githubView, &GithubView::externalNavigationRequested,
        this, &MainWindow::openInDefaultBrowser
        );
}

void MainWindow::connectSignals() {
}

void MainWindow::openInGithubView(const QUrl& url) {
    if (url != githubView.url())
        githubView.setUrl(url);
}

void MainWindow::openInDefaultBrowser(const QUrl& url) {
    QDesktopServices::openUrl(url);
}
