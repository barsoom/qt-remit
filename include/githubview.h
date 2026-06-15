#ifndef GITHUBVIEW_H
#define GITHUBVIEW_H

#include <QWebEngineView>

class GithubView : public QWebEngineView
{
    Q_OBJECT
public:
    GithubView(QWidget* parent = nullptr);

signals:
    void externalNavigationRequested(const QUrl& url);

private:
    bool handleUrlAndEmitSignals(const QUrl& url);

private slots:
    void handleNavigationRequest(QWebEngineNavigationRequest& request);
    void handleNewWindowRequest(QWebEngineNewWindowRequest& request);
};

#endif // GITHUBVIEW_H
