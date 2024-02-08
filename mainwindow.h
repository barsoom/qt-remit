#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QWebEngineView>
#include <QWebEngineProfile>

#include "remitview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QSplitter splitter;
    QWebEngineProfile profile;
    RemitView remitView;
    QWebEngineView githubView;

    void connectSignals();

protected slots:
    void openInGithubView(const QUrl& url);
};
#endif // MAINWINDOW_H
