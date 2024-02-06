#include "constants.h"
#include <QStandardPaths>

QString Constants::configPath()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
}

QString Constants::dataPath()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
}
