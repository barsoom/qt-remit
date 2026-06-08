#include <QDesktopServices>
#include <QCloseEvent>
#include <QShowEvent>
#include <QStandardPaths>
#include <QWebEngineDownloadRequest>
#include <QWebEnginePage>
#include <QWebEngineProfile>

#include "mainwindow.h"
#include "browserpane.h"
#include "constants.h"
#include "lastwindowstate.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), savedSplitterWidth(-1)
{
    remitView  = new RemitView(this);
    githubView = new GithubView(this);

    auto* remitPane  = new BrowserPane(remitView,  BrowserPane::Style::ProgressOnly, this);
    auto* githubPane = new BrowserPane(githubView, BrowserPane::Style::ProgressOnly,   this);

    splitter.addWidget(remitPane);
    splitter.addWidget(githubPane);

    QByteArray geometry = LastWindowState::windowGeometry();
    if (!geometry.isEmpty()) {
        restoreGeometry(geometry);
    }

    savedSplitterWidth = LastWindowState::splitterLeftWidth();

    splitter.setStretchFactor(0, 1);
    splitter.setStretchFactor(1, 2);

    setWindowTitle("Remit");
    setCentralWidget(&splitter);

    connect(
        remitView, &RemitView::githubNavigationRequested,
        this, &MainWindow::openInGithubView
    );
    connect(
        remitView, &RemitView::externalNavigationRequested,
        this, &MainWindow::openInDefaultBrowser
    );
    connect(
        githubView, &GithubView::externalNavigationRequested,
        this, &MainWindow::openInDefaultBrowser
    );
    connect(
        githubView->page(), &QWebEnginePage::titleChanged,
        this, [this](const QString& t) { setWindowTitle(t.isEmpty() ? "Remit" : t); }
    );
    connect(
        Constants::webProfile(), &QWebEngineProfile::downloadRequested,
        this, &MainWindow::handleDownload
    );
}

void MainWindow::connectSignals() {
}

void MainWindow::openInGithubView(const QUrl& url) {
    if (url != githubView->url())
        githubView->setUrl(url);
}

void MainWindow::openInDefaultBrowser(const QUrl& url) {
    QDesktopServices::openUrl(url);
}

void MainWindow::handleDownload(QWebEngineDownloadRequest* download) {
    download->setDownloadDirectory(
        QStandardPaths::writableLocation(QStandardPaths::DownloadLocation));
    download->accept();
}

void MainWindow::showEvent(QShowEvent* event) {
    QMainWindow::showEvent(event);

    if (savedSplitterWidth > 0) {
        int totalWidth = splitter.width();
        int rightWidth = totalWidth - savedSplitterWidth;
        QList<int> sizes;
        sizes << savedSplitterWidth << rightWidth;
        splitter.setSizes(sizes);
    }
}

void MainWindow::closeEvent(QCloseEvent* event) {
    LastWindowState::setWindowGeometry(saveGeometry());

    QList<int> sizes = splitter.sizes();
    if (!sizes.isEmpty()) {
        LastWindowState::setSplitterLeftWidth(sizes[0]);
    }
    QMainWindow::closeEvent(event);
}
