#include "mainwindow.h"

#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Встановлюємо заголовок та розміри головного вікна
    setWindowTitle("Лабораторна робота №2");
    resize(800, 600);

    // Меню "Файл"
    QMenu *fileMenu = menuBar()->addMenu("Файл");
    QAction *actExit = fileMenu->addAction("Вихід");
    connect(actExit, &QAction::triggered, this, &QWidget::close);

    // Меню "Об'єкти" (праворуч від "Файл" та ліворуч від "Довідка")
    objectsMenu = menuBar()->addMenu("Об'єкти");
    QAction *actPoint = objectsMenu->addAction("Крапка");
    QAction *actLine = objectsMenu->addAction("Лінія");
    QAction *actRect = objectsMenu->addAction("Прямокутник");
    QAction *actEllipse = objectsMenu->addAction("Еліпс");

    actPoint->setCheckable(true);
    actLine->setCheckable(true);
    actRect->setCheckable(true);
    actEllipse->setCheckable(true);

    // Підключення вибору фігур до редактора
    connect(actPoint, &QAction::triggered, this, [this]() { editor.StartPointEditor(); });
    connect(actLine, &QAction::triggered, this, [this]() { editor.StartLineEditor(); });
    connect(actRect, &QAction::triggered, this, [this]() { editor.StartRectEditor(); });
    connect(actEllipse, &QAction::triggered, this, [this]() { editor.StartEllipseEditor(); });

    // Оновлення позначки активного пункту при відкритті меню
    connect(objectsMenu, &QMenu::aboutToShow, this, [this]() {
        editor.OnInitMenuPopup(objectsMenu);
    });

    // Меню "Довідка"
    QMenu *helpMenu = menuBar()->addMenu("Довідка");
    QAction *actAbout = helpMenu->addAction("Про програму");
    connect(actAbout, &QAction::triggered, this, &MainWindow::onAboutTriggered);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && event->pos().y() >= menuBar()->height()) {
        editor.OnLBdown(event->pos().x(), event->pos().y());
        update();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        editor.OnMouseMove(event->pos().x(), event->pos().y());
        update();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        editor.OnLBup(event->pos().x(), event->pos().y());
        update();
    }
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    // Заливаємо білим робочу область під меню
    QRect canvasRect = rect();
    canvasRect.setTop(menuBar()->height());
    painter.fillRect(canvasRect, Qt::white);
    painter.setClipRect(canvasRect);

    editor.OnPaint(painter);
}

void MainWindow::onAboutTriggered() {
    QMessageBox::about(this, "Про програму",
                       "Лабораторна робота №2\n"
                       "Графічний редактор об'єктів\n"
                       "Варіант: 26");
}
