#ifndef GITHUBVIEW_H
#define GITHUBVIEW_H

#include <QWebEngineView>

class GithubView : public QWebEngineView
{
    Q_OBJECT
public:
    GithubView(QWidget* parent = nullptr);
    GithubView(QWebEngineProfile* profile, QWidget* parent = nullptr);

signals:
    void externalNavigationRequested(const QUrl& url);

private:
    bool handleUrlAndEmitSignals(const QUrl& url);
    void init(); // I forgot how to properly overload constructors to not need this.

private slots:
    void handleNavigationRequest(QWebEngineNavigationRequest& request);
    void handleNewWindowRequest(QWebEngineNewWindowRequest& request);
};

#endif // GITHUBVIEW_H
