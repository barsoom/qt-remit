#include <QSettings>
#include <QUrl>
#include <QUrlQuery>
#include <QWebEngineProfile>

#include "settings.h"
#include "constants.h"

namespace SettingsPaths {
    QString baseUrlPath = "remit/base_url";
    QString authTokenPath = "remit/auth_token";
    QString splitterLeftWidthPath = "ui/splitter_left_width";
    QString windowGeometryPath = "ui/window_geometry";
}


QSettings& getInstance() {
    static QSettings instance(Constants::configPath() + "/config.ini", QSettings::IniFormat);
    return instance;
}

QSettings& getGeometryInstance() {
    static QSettings instance(Constants::dataPath() + "/lastWindowGeometry.ini", QSettings::IniFormat);
    return instance;
}

QUrl Settings::remitUrl() {
    QUrlQuery authQueryParams;
    authQueryParams.addQueryItem("auth_key", value(SettingsPaths::authTokenPath, "").toString());

    auto result = remitBaseUrl();
    result.setQuery(authQueryParams);

    return result;
}

QUrl Settings::remitBaseUrl() {
    return QUrl(value(SettingsPaths::baseUrlPath, "https://example.com/").toString());
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

bool Settings::isConfigured()
{
    QString baseUrl = value(SettingsPaths::baseUrlPath, "https://example.com/").toString();
    QString authToken = value(SettingsPaths::authTokenPath, "").toString();

    return baseUrl != "https://example.com/" && !authToken.isEmpty();
}

void Settings::setRemitBaseUrl(const QString& url)
{
    setValue(SettingsPaths::baseUrlPath, url);
}

void Settings::setAuthToken(const QString& token)
{
    setValue(SettingsPaths::authTokenPath, token);
}
