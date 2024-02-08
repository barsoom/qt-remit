#ifndef CONSTANTS_H
#define CONSTANTS_H

class QString;
class QWebEngineProfile;

namespace Constants
{
    QString configPath();
    QString dataPath();
    QWebEngineProfile* webProfile();
};

#endif // CONSTANTS_H
