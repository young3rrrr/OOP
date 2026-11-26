#ifndef EDITOR_H
#define EDITOR_H

class QPainter;

// Базовий абстрактний клас редактора
class Editor {
public:
    virtual ~Editor() = default;

    // Обробники подій миші та перемалювання
    virtual void OnLBdown(int x, int y) = 0;
    virtual void OnLBup(int x, int y) = 0;
    virtual void OnMouseMove(int x, int y) = 0;
    virtual void OnPaint(QPainter &painter) = 0;
};

#endif // EDITOR_H
