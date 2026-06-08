#ifndef URLROUTER_H
#define URLROUTER_H

#include <QUrl>

class UrlRouter {
public:
    enum class Destination { AcceptInRemit, OpenInGithub, OpenExternal };

    UrlRouter(const QUrl& remitBaseUrl, const QUrl& githubBaseUrl);

    Destination route(const QUrl& url);
    bool isLoggingIn() const;

private:
    QUrl remitBaseUrl_;
    QUrl githubBaseUrl_;
    bool loggingIn_ = false;
};

#endif // URLROUTER_H
