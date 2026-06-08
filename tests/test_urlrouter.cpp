#include <QTest>
#include "urlrouter.h"

class TestUrlRouter : public QObject {
    Q_OBJECT
private slots:
    void remitUrl_acceptsInRemit();
    void githubUrl_opensInGithub();
    void externalUrl_opensExternal();
    void loginUrl_setsLoggingIn();
    void loginUrlWithQueryAndFragment_setsLoggingIn();
    void whileLoggingIn_allUrlsAccepted();
    void authCallbackWithQueryParams_clearsLoggingIn();
    void afterLogin_routingResumesNormally();
};

static QUrl remitBase() { return QUrl("https://remit.example.com"); }
static QUrl githubBase() { return QUrl("https://github.com"); }

void TestUrlRouter::remitUrl_acceptsInRemit() {
    UrlRouter router(remitBase(), githubBase());
    QCOMPARE(router.route(QUrl("https://remit.example.com/reviews/123")), UrlRouter::Destination::AcceptInRemit);
}

void TestUrlRouter::githubUrl_opensInGithub() {
    UrlRouter router(remitBase(), githubBase());
    QCOMPARE(router.route(QUrl("https://github.com/owner/repo/pull/42")), UrlRouter::Destination::OpenInGithub);
}

void TestUrlRouter::externalUrl_opensExternal() {
    UrlRouter router(remitBase(), githubBase());
    QCOMPARE(router.route(QUrl("https://other.example.com/page")), UrlRouter::Destination::OpenExternal);
}

void TestUrlRouter::loginUrl_setsLoggingIn() {
    UrlRouter router(remitBase(), githubBase());
    QVERIFY(!router.isLoggingIn());
    router.route(QUrl("https://remit.example.com/login"));
    QVERIFY(router.isLoggingIn());
}

// routeMatches strips query/fragment — a login URL with these should still trigger loggingIn
void TestUrlRouter::loginUrlWithQueryAndFragment_setsLoggingIn() {
    UrlRouter router(remitBase(), githubBase());
    router.route(QUrl("https://remit.example.com/login?redirect=/dashboard#main"));
    QVERIFY(router.isLoggingIn());
}

void TestUrlRouter::whileLoggingIn_allUrlsAccepted() {
    UrlRouter router(remitBase(), githubBase());
    router.route(QUrl("https://remit.example.com/login"));

    QCOMPARE(router.route(QUrl("https://github.com/oauth")), UrlRouter::Destination::AcceptInRemit);
    QCOMPARE(router.route(QUrl("https://oauth-provider.example.com/callback")), UrlRouter::Destination::AcceptInRemit);
}

// routeMatches strips query/fragment — auth callback with token params should still clear loggingIn
void TestUrlRouter::authCallbackWithQueryParams_clearsLoggingIn() {
    UrlRouter router(remitBase(), githubBase());
    router.route(QUrl("https://remit.example.com/login"));
    QVERIFY(router.isLoggingIn());

    router.route(QUrl("https://remit.example.com/auth?token=abc&session=xyz"));
    QVERIFY(!router.isLoggingIn());
}

void TestUrlRouter::afterLogin_routingResumesNormally() {
    UrlRouter router(remitBase(), githubBase());
    router.route(QUrl("https://remit.example.com/login"));
    router.route(QUrl("https://remit.example.com/auth?token=abc"));

    QCOMPARE(router.route(QUrl("https://github.com/owner/repo")), UrlRouter::Destination::OpenInGithub);
    QCOMPARE(router.route(QUrl("https://other.com/page")), UrlRouter::Destination::OpenExternal);
}

QTEST_GUILESS_MAIN(TestUrlRouter)
#include "test_urlrouter.moc"
