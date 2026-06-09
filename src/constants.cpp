#include "constants.h"
#include <QStandardPaths>
#include <QWebEngineProfile>

QString Constants::configPath()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
}

QString Constants::dataPath()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
}

QWebEngineProfile* Constants::webProfile() {
    static bool configured = false;
    static QWebEngineProfile profile("RemitProfile", nullptr);

    if(!configured) {
        profile.setPersistentCookiesPolicy(QWebEngineProfile::AllowPersistentCookies);
        profile.setHttpCacheMaximumSize(50 * 1024 * 1024); // 50 MB
        configured = true;
    }

    return &profile;
}

