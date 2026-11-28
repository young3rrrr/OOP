#ifndef SHAPE_H
#define SHAPE_H

class QPainter;

// Базовий абстрактний клас для графічних фігур
class Shape {
protected:
    long xs1 = 0;
    long ys1 = 0;
    long xs2 = 0;
    long ys2 = 0;

public:
    virtual ~Shape() = default;

    // Встановлення координат фігури
    void Set(long x1, long y1, long x2, long y2);

    // Чисто віртуальний метод відображення фігури
    virtual void Show(QPainter &painter) = 0;
};

// Фігура "Крапка"
class PointShape : public Shape {
public:
    void Show(QPainter &painter) override;
};

// Фігура "Лінія"
class LineShape : public Shape {
public:
    void Show(QPainter &painter) override;
};

// Фігура "Прямокутник"
class RectShape : public Shape {
public:
    void Show(QPainter &painter) override;
};

// Фігура "Еліпс"
class EllipseShape : public Shape {
public:
    void Show(QPainter &painter) override;
};

#endif // SHAPE_H
