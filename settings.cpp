#include "settings.h"
#include "constants.h"

namespace SettingsPaths {
QString baseUrlPath = "remit/base_url";
QString authTokenPath = "remit/auth_token";
}

QString Settings::remitBaseUrl() {
    return Settings::value(SettingsPaths::baseUrlPath, "https://example.com/").toString();
}

QString Settings::remitAuthToken() {
    return Settings::value(SettingsPaths::authTokenPath, "").toString();
}


QSettings& Settings::getInstance() {
    static QSettings instance(Constants::configPath() + "/config.ini", QSettings::IniFormat);
    return instance;
}

QVariant Settings::value(QAnyStringView key, const QVariant& defaultValue)
{
    if(!getInstance().contains(key)) {
        getInstance().setValue(key, defaultValue);
    }
    return getInstance().value(key);
}

void Settings::setValue(QAnyStringView key, const QVariant& value)
{
    getInstance().setValue(key, value);
}
