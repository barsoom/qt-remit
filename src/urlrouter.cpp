#include "urlrouter.h"

static bool routeMatches(const QUrl& a, const QUrl& b) {
    static auto options = QUrl::RemoveQuery |
                          QUrl::RemoveFragment |
                          QUrl::RemoveUserInfo |
                          QUrl::StripTrailingSlash;
    return a.matches(b, options);
}

UrlRouter::UrlRouter(const QUrl& remitBaseUrl, const QUrl& githubBaseUrl)
    : remitBaseUrl_(remitBaseUrl), githubBaseUrl_(githubBaseUrl), loggingIn_(false)
{}

UrlRouter::Destination UrlRouter::route(const QUrl& url) {
    if (loggingIn_) {
        auto oauthRedirectUrl = remitBaseUrl_;
        oauthRedirectUrl.setPath("/auth");

        if (routeMatches(url, oauthRedirectUrl))
            loggingIn_ = false;

        return Destination::AcceptInRemit;
    }

    if (url.host() == githubBaseUrl_.host())
        return Destination::OpenInGithub;

    if (url.host() != remitBaseUrl_.host())
        return Destination::OpenExternal;

    auto loginUrl = remitBaseUrl_;
    loginUrl.setPath("/login");
    if (routeMatches(url, loginUrl))
        loggingIn_ = true;

    return Destination::AcceptInRemit;
}

bool UrlRouter::isLoggingIn() const {
    return loggingIn_;
}
