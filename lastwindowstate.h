#ifndef LASTWINDOWSTATE_H
#define LASTWINDOWSTATE_H

#include <QString>
#include <QByteArray>

class LastWindowState {
public:
    static int splitterLeftWidth();
    static void setSplitterLeftWidth(int width);

    static QByteArray windowGeometry();
    static void setWindowGeometry(const QByteArray& geometry);

private:
    static QString geometryFilePath();
};

#endif // LASTWINDOWSTATE_H
