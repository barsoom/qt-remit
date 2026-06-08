#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>

#include "remitview.h"
#include "githubview.h"

class QWebEngineDownloadRequest;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

protected:
    void closeEvent(QCloseEvent* event) override;
    void showEvent(QShowEvent* event) override;

private:
    QSplitter splitter;
    RemitView* remitView = nullptr;
    GithubView* githubView = nullptr;
    int savedSplitterWidth;

    void connectSignals();

protected slots:
    void openInGithubView(const QUrl& url);
    void openInDefaultBrowser(const QUrl& url);
    void handleDownload(QWebEngineDownloadRequest* download);
};
#endif // MAINWINDOW_H
