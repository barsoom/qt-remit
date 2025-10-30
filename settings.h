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

    static int splitterLeftWidth();
    static void setSplitterLeftWidth(int width);

    static QByteArray windowGeometry();
    static void setWindowGeometry(const QByteArray& geometry);

private:
    // static facades to QSettings
    static QVariant value(QAnyStringView key, const QVariant& defaultValue);
    static void setValue(QAnyStringView key, const QVariant& value);
};

#endif // SETTINGS_H
