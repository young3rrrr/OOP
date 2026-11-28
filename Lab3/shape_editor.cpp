#include "shape_editor.h"
#include "shape.h"

#include <QAction>
#include <QMenu>
#include <QPainter>
#include <QPen>
#include <QtGlobal>

Shape **ShapeEditor::pcshape = nullptr;
int ShapeEditor::shapeCount = 0;

void ShapeEditor::initShapes() {
    if (!pcshape) {
        pcshape = new Shape *[MAX_SHAPES]{nullptr};
    }
}

void ShapeEditor::addShape(Shape *shape) {
    initShapes();
    if (shapeCount < MAX_SHAPES) {
        pcshape[shapeCount++] = shape;
    } else {
        delete shape;
    }
}

void ShapeEditor::drawRubber(QPainter &) {
}

void ShapeEditor::OnLBdown(int x, int y) {
    xstart = xend = x;
    ystart = yend = y;
    isDrawing = true;
}

void ShapeEditor::OnLBup(int x, int y) {
    xend = x;
    yend = y;
    isDrawing = false;
}

void ShapeEditor::OnMouseMove(int x, int y) {
    if (isDrawing) {
        xend = x;
        yend = y;
    }
}

void ShapeEditor::OnPaint(QPainter &painter) {
    paintShapes(painter);
    if (isDrawing) {
        drawRubber(painter);
    }
}

void ShapeEditor::OnInitMenuPopup(QMenu *menu) {
    if (!menu) return;
    for (QAction *act : menu->actions()) {
        act->setChecked(false);
    }
}

void ShapeEditor::paintShapes(QPainter &painter) {
    if (!pcshape) return;
    for (int i = 0; i < shapeCount; ++i) {
        if (pcshape[i]) {
            pcshape[i]->Show(painter);
        }
    }
}

void ShapeEditor::clearShapes() {
    if (pcshape) {
        for (int i = 0; i < shapeCount; ++i) {
            delete pcshape[i];
            pcshape[i] = nullptr;
        }
        delete[] pcshape;
        pcshape = nullptr;
    }
    shapeCount = 0;
}

// --- PointEditor ---

void PointEditor::OnLBdown(int x, int y) {
    auto *point = new PointShape();
    point->Set(x, y, x, y);
    addShape(point);
}

void PointEditor::OnLBup(int, int) {
}

void PointEditor::OnMouseMove(int, int) {
}

void PointEditor::OnInitMenuPopup(QMenu *menu) {
    if (!menu) return;
    for (QAction *act : menu->actions()) {
        act->setChecked(act->text() == "Крапка");
    }
}

// --- LineEditor ---

void LineEditor::drawRubber(QPainter &painter) {
    // Гумовий слід: пунктирна лінія чорного кольору (Ж mod 4 = 3)
    painter.setPen(QPen(Qt::black, 1, Qt::DashLine));
    painter.drawLine(xstart, ystart, xend, yend);
}

void LineEditor::OnLBup(int x, int y) {
    if (!isDrawing) return;
    ShapeEditor::OnLBup(x, y);

    auto *line = new LineShape();
    line->Set(xstart, ystart, xend, yend);
    addShape(line);
}

void LineEditor::OnInitMenuPopup(QMenu *menu) {
    if (!menu) return;
    for (QAction *act : menu->actions()) {
        act->setChecked(act->text() == "Лінія");
    }
}

// --- RectEditor ---

void RectEditor::drawRubber(QPainter &painter) {
    // Гумовий слід: пунктирна лінія чорного кольору (Ж mod 4 = 3)
    painter.setPen(QPen(Qt::black, 1, Qt::DashLine));
    painter.setBrush(Qt::NoBrush);

    // Увід прямокутника від центру до одного з кутів (Ж mod 2 = 1)
    int x1 = 2 * xstart - xend;
    int y1 = 2 * ystart - yend;
    int x = qMin(x1, xend);
    int y = qMin(y1, yend);
    int w = qAbs(xend - x1);
    int h = qAbs(yend - y1);
    painter.drawRect(x, y, w, h);
}

void RectEditor::OnLBup(int x, int y) {
    if (!isDrawing) return;
    ShapeEditor::OnLBup(x, y);

    // Увід прямокутника від центру до одного з кутів (Ж mod 2 = 1)
    int x1 = 2 * xstart - xend;
    int y1 = 2 * ystart - yend;

    auto *rect = new RectShape();
    rect->Set(x1, y1, xend, yend);
    addShape(rect);
}

void RectEditor::OnInitMenuPopup(QMenu *menu) {
    if (!menu) return;
    for (QAction *act : menu->actions()) {
        act->setChecked(act->text() == "Прямокутник");
    }
}

// --- EllipseEditor ---

void EllipseEditor::drawRubber(QPainter &painter) {
    // Гумовий слід: пунктирна лінія чорного кольору (Ж mod 4 = 3)
    painter.setPen(QPen(Qt::black, 1, Qt::DashLine));
    painter.setBrush(Qt::NoBrush);

    // Увід еліпса по двом протилежним кутам охоплюючого прямокутника (Ж mod 2 = 1)
    int x = qMin(xstart, xend);
    int y = qMin(ystart, yend);
    int w = qAbs(xend - xstart);
    int h = qAbs(yend - ystart);
    painter.drawEllipse(x, y, w, h);
}

void EllipseEditor::OnLBup(int x, int y) {
    if (!isDrawing) return;
    ShapeEditor::OnLBup(x, y);

    // Увід еліпса по двом протилежним кутам охоплюючого прямокутника (Ж mod 2 = 1)
    auto *ellipse = new EllipseShape();
    ellipse->Set(xstart, ystart, xend, yend);
    addShape(ellipse);
}

void EllipseEditor::OnInitMenuPopup(QMenu *menu) {
    if (!menu) return;
    for (QAction *act : menu->actions()) {
        act->setChecked(act->text() == "Еліпс");
    }
}

// --- ShapeObjectsEditor ---

ShapeObjectsEditor::ShapeObjectsEditor() {
    ShapeEditor::initShapes();
}

ShapeObjectsEditor::~ShapeObjectsEditor() {
    delete pse;
    pse = nullptr;
    ShapeEditor::clearShapes();
}

void ShapeObjectsEditor::StartPointEditor() {
    delete pse;
    pse = new PointEditor();
}

void ShapeObjectsEditor::StartLineEditor() {
    delete pse;
    pse = new LineEditor();
}

void ShapeObjectsEditor::StartRectEditor() {
    delete pse;
    pse = new RectEditor();
}

void ShapeObjectsEditor::StartEllipseEditor() {
    delete pse;
    pse = new EllipseEditor();
}

void ShapeObjectsEditor::OnLBdown(int x, int y) {
    if (pse) pse->OnLBdown(x, y);
}

void ShapeObjectsEditor::OnLBup(int x, int y) {
    if (pse) pse->OnLBup(x, y);
}

void ShapeObjectsEditor::OnMouseMove(int x, int y) {
    if (pse) pse->OnMouseMove(x, y);
}

void ShapeObjectsEditor::OnPaint(QPainter &painter) {
    if (pse) {
        pse->OnPaint(painter);
    } else {
        ShapeEditor::paintShapes(painter);
    }
}

void ShapeObjectsEditor::OnInitMenuPopup(QMenu *menu) {
    if (pse) {
        pse->OnInitMenuPopup(menu);
    } else if (menu) {
        for (QAction *act : menu->actions()) {
            act->setChecked(false);
        }
    }
}
