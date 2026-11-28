#include "shape.h"

#include <QPainter>
#include <QPen>
#include <QtGlobal>

void Shape::Set(long x1, long y1, long x2, long y2) {
    xs1 = x1;
    ys1 = y1;
    xs2 = x2;
    ys2 = y2;
}

void PointShape::Show(QPainter &painter) {
    painter.setPen(QPen(Qt::black, 3));
    painter.drawPoint(xs1, ys1);
}

void LineShape::Show(QPainter &painter) {
    painter.setPen(QPen(Qt::black, 1));
    painter.drawLine(xs1, ys1, xs2, ys2);
}

void RectShape::Show(QPainter &painter) {
    // Чорний контур і рожеве заповнення (Ж = 27: mod 5 = 2, mod 6 = 3)
    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(QColor(255, 182, 193));

    int x = qMin(xs1, xs2);
    int y = qMin(ys1, ys2);
    int w = qAbs(xs2 - xs1);
    int h = qAbs(ys2 - ys1);
    painter.drawRect(x, y, w, h);
}

void EllipseShape::Show(QPainter &painter) {
    // Чорний контур без заповнення (Ж = 27: mod 5 = 2)
    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(Qt::NoBrush);

    int x = qMin(xs1, xs2);
    int y = qMin(ys1, ys2);
    int w = qAbs(xs2 - xs1);
    int h = qAbs(ys2 - ys1);
    painter.drawEllipse(x, y, w, h);
}
