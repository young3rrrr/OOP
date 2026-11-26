#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "shape_editor.h"

class QMenu;

// Головне вікно програми для Лабораторної роботи №2
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

protected:
    // Перевизначені обробники подій миші та малювання
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onAboutTriggered();

private:
    ShapeObjectsEditor editor;
    QMenu *objectsMenu = nullptr;
};

#endif // MAINWINDOW_H
