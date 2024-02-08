#include <QUrlQuery>
#include "settings.h"
#include "constants.h"

namespace SettingsPaths {
QString baseUrlPath = "remit/base_url";
QString authTokenPath = "remit/auth_token";
}


QSettings& getInstance() {
    static QSettings instance(Constants::configPath() + "/config.ini", QSettings::IniFormat);
    return instance;
}

QUrl Settings::remitUrl() {
    auto baseUrl = Settings::value(SettingsPaths::baseUrlPath, "https://example.com/").toString();
    auto authToken = Settings::value(SettingsPaths::authTokenPath, "").toString();

    QUrlQuery authQueryParams;
    authQueryParams.addQueryItem("auth_key", authToken);

    QUrl result(baseUrl);
    result.setQuery(authQueryParams);

    return result;
}

QUrl Settings::githubUrl() {
    return QUrl("https://github.com/");
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
