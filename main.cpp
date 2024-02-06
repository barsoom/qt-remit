#include <QApplication>
#include <QWebEngineView>
#include <QSplitter>
#include <QUrl>
#include <QWebEngineProfile>

#include "include/mainwindow.h"
#include "include/constants.h"
#include "include/webengineviewwithnavigationsignals.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mainWindow;
    QSplitter splitter;

    QWebEngineProfile webProfile("RemitProfile", nullptr);
    webProfile.setPersistentStoragePath(Constants::dataPath() + "webProfile");
    webProfile.setPersistentCookiesPolicy(QWebEngineProfile::AllowPersistentCookies);

    WebEngineViewWithNavigationSignals leftView(&webProfile);
    WebEngineViewWithNavigationSignals rightView(&webProfile);

    splitter.addWidget(&leftView);
    splitter.addWidget(&rightView);

    leftView.setUrl(QUrl("https://example.com"));
    rightView.setUrl(QUrl("https://github.com"));

    mainWindow.setWindowTitle("Remit");
    mainWindow.setCentralWidget(&splitter);
    mainWindow.show();

    return a.exec();
}
