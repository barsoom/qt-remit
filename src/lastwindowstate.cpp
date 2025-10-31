#include "lastwindowstate.h"
#include "constants.h"
#include <QSettings>

namespace LastWindowStatePaths {
    QString splitterLeftWidthPath = "ui/splitter_left_width";
    QString windowGeometryPath = "ui/window_geometry";
}

static QSettings& getGeometryInstance() {
    static QSettings instance(Constants::dataPath() + "/lastWindowGeometry.ini", QSettings::IniFormat);
    return instance;
}

int LastWindowState::splitterLeftWidth() {
    return getGeometryInstance().value(LastWindowStatePaths::splitterLeftWidthPath, -1).toInt();
}

void LastWindowState::setSplitterLeftWidth(int width) {
    getGeometryInstance().setValue(LastWindowStatePaths::splitterLeftWidthPath, width);
}

QByteArray LastWindowState::windowGeometry() {
    return getGeometryInstance().value(LastWindowStatePaths::windowGeometryPath, QByteArray()).toByteArray();
}

void LastWindowState::setWindowGeometry(const QByteArray& geometry) {
    getGeometryInstance().setValue(LastWindowStatePaths::windowGeometryPath, geometry);
}

QString LastWindowState::geometryFilePath() {
    return Constants::dataPath() + "/lastWindowGeometry.ini";
}
