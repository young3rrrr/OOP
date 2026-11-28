#ifndef SHAPE_EDITOR_H
#define SHAPE_EDITOR_H

#include "editor.h"

class Shape;
class QMenu;
class QPainter;

// Базовий клас редактора графічних фігур
class ShapeEditor : public Editor {
protected:
    // Динамічний масив вказівників на фігури (N = Ж + 100 = 127, Ж mod 3 = 0)
    static constexpr int MAX_SHAPES = 127;
    static Shape **pcshape;
    static int shapeCount;

    int xstart = 0;
    int ystart = 0;
    int xend = 0;
    int yend = 0;
    bool isDrawing = false;

    void addShape(Shape *shape);
    virtual void drawRubber(QPainter &painter);

public:
    ShapeEditor() = default;
    ~ShapeEditor() override = default;

    void OnLBdown(int x, int y) override;
    void OnLBup(int x, int y) override;
    void OnMouseMove(int x, int y) override;
    void OnPaint(QPainter &painter) override;

    // Оновлення стану пунктів меню та кнопок Toolbar
    virtual void OnInitMenuPopup(QMenu *menu);

    static void initShapes();
    static void paintShapes(QPainter &painter);
    static void clearShapes();
};

// Редактор для вводу крапок
class PointEditor : public ShapeEditor {
public:
    void OnLBdown(int x, int y) override;
    void OnLBup(int x, int y) override;
    void OnMouseMove(int x, int y) override;
    void OnInitMenuPopup(QMenu *menu) override;
};

// Редактор для вводу ліній
class LineEditor : public ShapeEditor {
protected:
    void drawRubber(QPainter &painter) override;

public:
    void OnLBup(int x, int y) override;
    void OnInitMenuPopup(QMenu *menu) override;
};

// Редактор для вводу прямокутників
class RectEditor : public ShapeEditor {
protected:
    void drawRubber(QPainter &painter) override;

public:
    void OnLBup(int x, int y) override;
    void OnInitMenuPopup(QMenu *menu) override;
};

// Редактор для вводу еліпсів
class EllipseEditor : public ShapeEditor {
protected:
    void drawRubber(QPainter &painter) override;

public:
    void OnLBup(int x, int y) override;
    void OnInitMenuPopup(QMenu *menu) override;
};

// Клас-інтерфейс модуля редагування об'єктів
class ShapeObjectsEditor {
private:
    ShapeEditor *pse = nullptr;

public:
    ShapeObjectsEditor();
    ~ShapeObjectsEditor();

    // Методи вибору поточного режиму малювання
    void StartPointEditor();
    void StartLineEditor();
    void StartRectEditor();
    void StartEllipseEditor();

    // Поліморфна передача подій поточному редактору
    void OnLBdown(int x, int y);
    void OnLBup(int x, int y);
    void OnMouseMove(int x, int y);
    void OnPaint(QPainter &painter);
    void OnInitMenuPopup(QMenu *menu);
};

#endif // SHAPE_EDITOR_H
