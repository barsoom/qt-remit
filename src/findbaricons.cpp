#include "findbaricons.h"

#include <QPainter>
#include <QPainterPath>
#include <QPalette>
#include <QPixmap>

namespace {

constexpr int kIconSize = 14;
constexpr qreal kStrokeWidth = 1.4;

QPixmap blankPixmap(qreal dpr) {
    QPixmap pix(QSize(kIconSize, kIconSize) * dpr);
    pix.setDevicePixelRatio(dpr);
    pix.fill(Qt::transparent);
    return pix;
}

QPen strokePen(const QPalette& palette) {
    QPen pen(palette.color(QPalette::WindowText), kStrokeWidth);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    return pen;
}

QIcon paintChevron(const QPalette& palette, bool pointingUp) {
    constexpr qreal cx = kIconSize / 2.0;
    constexpr qreal halfW = 3.0;
    constexpr qreal halfH = 2.0;
    const qreal yTip = pointingUp ? cx - halfH : cx + halfH;
    const qreal yArm = pointingUp ? cx + halfH : cx - halfH;

    QPixmap pix = blankPixmap(2.0);
    QPainter p(&pix);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(strokePen(palette));
    QPainterPath path;
    path.moveTo(cx - halfW, yArm);
    path.lineTo(cx,         yTip);
    path.lineTo(cx + halfW, yArm);
    p.drawPath(path);
    return QIcon(pix);
}

} // namespace

QIcon FindBarIcons::chevronUp(const QPalette& palette) {
    return paintChevron(palette, true);
}

QIcon FindBarIcons::chevronDown(const QPalette& palette) {
    return paintChevron(palette, false);
}

QIcon FindBarIcons::close(const QPalette& palette) {
    constexpr qreal pad = 4.0;
    QPixmap pix = blankPixmap(2.0);
    QPainter p(&pix);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(strokePen(palette));
    p.drawLine(QPointF(pad, pad),
               QPointF(kIconSize - pad, kIconSize - pad));
    p.drawLine(QPointF(kIconSize - pad, pad),
               QPointF(pad, kIconSize - pad));
    return QIcon(pix);
}
