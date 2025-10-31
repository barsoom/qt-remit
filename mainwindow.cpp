#include <QWebEngineNavigationRequest>
#include <QDesktopServices>
#include <QCloseEvent>
#include <QShowEvent>
#include "mainwindow.h"
#include "constants.h"
#include "lastwindowstate.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), savedSplitterWidth(-1)
{
    splitter.addWidget(&remitView);
    splitter.addWidget(&githubView);

    // Restore window geometry (position and size)
    QByteArray geometry = LastWindowState::windowGeometry();
    if (!geometry.isEmpty()) {
        restoreGeometry(geometry);
    }

    // Load saved splitter width (will be applied in showEvent)
    savedSplitterWidth = LastWindowState::splitterLeftWidth();

    // Set default ratio for initial layout
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

void MainWindow::showEvent(QShowEvent* event) {
    QMainWindow::showEvent(event);

    // Restore saved splitter width after window is shown
    if (savedSplitterWidth > 0) {
        int totalWidth = splitter.width();
        int rightWidth = totalWidth - savedSplitterWidth;
        QList<int> sizes;
        sizes << savedSplitterWidth << rightWidth;
        splitter.setSizes(sizes);
    }
}

void MainWindow::closeEvent(QCloseEvent* event) {
    // Save window geometry (position and size)
    LastWindowState::setWindowGeometry(saveGeometry());

    // Save the width of the left column
    QList<int> sizes = splitter.sizes();
    if (!sizes.isEmpty()) {
        LastWindowState::setSplitterLeftWidth(sizes[0]);
    }
    QMainWindow::closeEvent(event);
}