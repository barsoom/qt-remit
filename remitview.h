#ifndef REMITVIEW_H
#define REMITVIEW_H

#include <QWebEngineView>

class RemitView : public QWebEngineView
{
    Q_OBJECT
public:
    RemitView(QWidget *parent = nullptr);
    RemitView(QWebEngineProfile *profile, QWidget *parent = nullptr);

signals:
    void githubNavigationRequested(const QUrl& url);
    void externalNavigationRequested(const QUrl& url);

private:
    bool handleUrlAndEmitSignals(const QUrl& url);
    void connectToPageSignals() const;

private slots:
    void handleNavigationRequest(QWebEngineNavigationRequest& request);
    void handleNewWindowRequest(QWebEngineNewWindowRequest& request);
};

#endif // REMITVIEW_H
