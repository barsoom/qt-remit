#ifndef GITHUBVIEW_H
#define GITHUBVIEW_H

#include <QWebEngineView>

#include "clipboardbridge.h"

class QWebChannel;

class GithubView : public QWebEngineView
{
    Q_OBJECT
public:
    GithubView(QWidget* parent = nullptr);

signals:
    void externalNavigationRequested(const QUrl& url);

private:
    bool handleUrlAndEmitSignals(const QUrl& url);
    void setupClipboardBridge();

    ClipboardBridge clipboardBridge;
    QWebChannel* webChannel;

private slots:
    void handleNavigationRequest(QWebEngineNavigationRequest& request);
    void handleNewWindowRequest(QWebEngineNewWindowRequest& request);
};

#endif // GITHUBVIEW_H
