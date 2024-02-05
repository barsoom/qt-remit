#include <QApplication>
#include <QWebEngineView>
#include <QSplitter>
#include <QUrl>
#include "mainwindow.h"
#include "webengineviewwithnavigationsignals.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mainWindow;

    auto *splitter = new QSplitter();
    auto *leftView = new WebEngineViewWithNavigationSignals();
    auto *rightView = new WebEngineViewWithNavigationSignals();

    splitter->addWidget(leftView);
    splitter->addWidget(rightView);

    leftView->setUrl(QUrl("https://example.com"));
    rightView->setUrl(QUrl("https://github.com"));

    splitter->setWindowTitle("Remit");

    mainWindow.setCentralWidget(splitter);

    mainWindow.show();

    return a.exec();
}
