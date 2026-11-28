#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "shape_editor.h"

class QAction;
class QMenu;
class QToolBar;

// Головне вікно програми для Лабораторної роботи №3
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
    // Методи-обробники вибору типу об'єкта та сповіщень Toolbar
    void onPointTriggered();
    void onLineTriggered();
    void onRectTriggered();
    void onEllipseTriggered();
    void OnNotify(QAction *action);
    void onAboutTriggered();

private:
    int canvasTop() const;

    ShapeObjectsEditor editor;
    QMenu *objectsMenu = nullptr;
    QToolBar *toolBar = nullptr;
};

#endif // MAINWINDOW_H
