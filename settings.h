#ifndef SETTINGS_H
#define SETTINGS_H

class QAnyStringView;
class QVariant;
class QWebEngineProfile;
class QUrl;

class Settings
{
public:
    static QUrl remitUrl();
    static QUrl remitBaseUrl();
    static QUrl githubUrl();

    static bool isConfigured();
    static void setRemitBaseUrl(const QString& url);
    static void setAuthToken(const QString& token);

private:
    // static facades to QSettings
    static QVariant value(QAnyStringView key, const QVariant& defaultValue);
    static void setValue(QAnyStringView key, const QVariant& value);
};

#endif // SETTINGS_H
