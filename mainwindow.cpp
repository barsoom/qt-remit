#include "mainwindow.h"
#include "constants.h"
#include "settings.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    splitter(),
    profile("RemitProfile", nullptr),
    leftView(&profile),
    rightView(&profile)
{
    profile.setPersistentStoragePath(Constants::dataPath() + "webProfile");
    profile.setPersistentCookiesPolicy(QWebEngineProfile::AllowPersistentCookies);

    splitter.addWidget(&leftView);
    splitter.addWidget(&rightView);

    // TODO: Restore & save splitter state using splitter.saveState and splitter.restoreState. Until then, this is a decent starting point
    splitter.setStretchFactor(0, 1);
    splitter.setStretchFactor(1, 2);

    QUrl leftUrl(Settings::remitBaseUrl() + "?auth_key=" + Settings::remitAuthToken());
    leftView.setUrl(leftUrl);
    rightView.setUrl(QUrl("https://github.com"));

    // QObject::connect(&leftView, &QWebEngineView::urlChanged, &rightView, &QWebEngineView::setUrl);

    setWindowTitle("Remit");
    setCentralWidget(&splitter);
}

MainWindow::~MainWindow() {}
