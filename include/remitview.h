#ifndef REMITVIEW_H
#define REMITVIEW_H

#include <QWebEngineView>
#include "urlrouter.h"

class RemitView : public QWebEngineView
{
    Q_OBJECT
public:
    RemitView(QWidget* parent = nullptr);

signals:
    void githubNavigationRequested(const QUrl& url);
    void externalNavigationRequested(const QUrl& url);

private:
    UrlRouter router_;
    bool handleUrlAndEmitSignals(const QUrl& url);

private slots:
    void handleNavigationRequest(QWebEngineNavigationRequest& request);
    void handleNewWindowRequest(QWebEngineNewWindowRequest& request);
};

#endif // REMITVIEW_H
