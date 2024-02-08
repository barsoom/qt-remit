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
        profile.setPersistentStoragePath(Constants::dataPath() + "webProfile");
        profile.setPersistentCookiesPolicy(QWebEngineProfile::AllowPersistentCookies);
        configured = true;
    }

    return &profile;
}

