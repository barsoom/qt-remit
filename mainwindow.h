#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>

#include "remitview.h"
#include "githubview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private:
    QSplitter splitter;
    RemitView remitView;
    GithubView githubView;

    void connectSignals();

protected slots:
    void openInGithubView(const QUrl& url);
    void openInDefaultBrowser(const QUrl& url);
};
#endif // MAINWINDOW_H
