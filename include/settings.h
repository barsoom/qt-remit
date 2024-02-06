#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QString>

class Settings
{
public:
    static QString remitBaseUrl();
    static QString remitAuthToken();

private:
    // static facades to QSettings
    static QVariant value(QAnyStringView key, const QVariant& defaultValue);
    static void setValue(QAnyStringView key, const QVariant& value);

    // Singleton necessities
    static QSettings& getInstance();
};

#endif // SETTINGS_H
