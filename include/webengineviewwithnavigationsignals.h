#ifndef WEBENGINEVIEWWITHNAVIGATIONSIGNALS_H
#define WEBENGINEVIEWWITHNAVIGATIONSIGNALS_H

#include <QWebEngineView>
#include <QWebEngineProfile>

class WebEngineViewWithNavigationSignals : public QWebEngineView
{
    Q_OBJECT
public:
    WebEngineViewWithNavigationSignals(QWebEngineProfile *profile);
};

#endif // WEBENGINEVIEWWITHNAVIGATIONSIGNALS_H
