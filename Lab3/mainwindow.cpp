#include "mainwindow.h"

#include <QAction>
#include <QCursor>
#include <QIcon>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QSize>
#include <QToolBar>
#include <QToolTip>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Встановлюємо початковий заголовок та розміри головного вікна
    setWindowTitle("Лабораторна робота №3");
    resize(800, 600);

    // Меню "Файл"
    QMenu *fileMenu = menuBar()->addMenu("Файл");
    QAction *actExit = fileMenu->addAction("Вихід");
    connect(actExit, &QAction::triggered, this, &QWidget::close);

    // Меню "Об'єкти" (праворуч від "Файл" та ліворуч від "Довідка")
    objectsMenu = menuBar()->addMenu("Об'єкти");
    QAction *actPoint = objectsMenu->addAction(QIcon(":/icons/point.png"), "Крапка");
    QAction *actLine = objectsMenu->addAction(QIcon(":/icons/line.png"), "Лінія");
    QAction *actRect = objectsMenu->addAction(QIcon(":/icons/rect.png"), "Прямокутник");
    QAction *actEllipse = objectsMenu->addAction(QIcon(":/icons/ellipse.png"), "Еліпс");

    actPoint->setCheckable(true);
    actLine->setCheckable(true);
    actRect->setCheckable(true);
    actEllipse->setCheckable(true);

    // Текст підказок (tooltips) для кнопок Toolbar
    actPoint->setToolTip("Крапка");
    actLine->setToolTip("Лінія");
    actRect->setToolTip("Прямокутник");
    actEllipse->setToolTip("Еліпс");

    // Створення вікна Toolbar з кнопками, що дублюють підпункти меню "Об'єкти"
    toolBar = addToolBar("Панель інструментів");
    toolBar->setMovable(false);
    toolBar->setIconSize(QSize(24, 24));
    toolBar->addAction(actPoint);
    toolBar->addAction(actLine);
    toolBar->addAction(actRect);
    toolBar->addAction(actEllipse);

    // Підключення методів-обробників вибору фігур
    connect(actPoint, &QAction::triggered, this, &MainWindow::onPointTriggered);
    connect(actLine, &QAction::triggered, this, &MainWindow::onLineTriggered);
    connect(actRect, &QAction::triggered, this, &MainWindow::onRectTriggered);
    connect(actEllipse, &QAction::triggered, this, &MainWindow::onEllipseTriggered);

    // Обробка сповіщень (підказок tooltips) при наведенні на кнопки Toolbar
    connect(actPoint, &QAction::hovered, this, [this, actPoint]() { OnNotify(actPoint); });
    connect(actLine, &QAction::hovered, this, [this, actLine]() { OnNotify(actLine); });
    connect(actRect, &QAction::hovered, this, [this, actRect]() { OnNotify(actRect); });
    connect(actEllipse, &QAction::hovered, this, [this, actEllipse]() { OnNotify(actEllipse); });

    // Оновлення стану активного пункту при відкритті меню
    connect(objectsMenu, &QMenu::aboutToShow, this, [this]() {
        editor.OnInitMenuPopup(objectsMenu);
    });

    // Меню "Довідка"
    QMenu *helpMenu = menuBar()->addMenu("Довідка");
    QAction *actAbout = helpMenu->addAction("Про програму");
    connect(actAbout, &QAction::triggered, this, &MainWindow::onAboutTriggered);
}

int MainWindow::canvasTop() const {
    int top = menuBar()->height();
    if (toolBar && toolBar->isVisible()) {
        top += toolBar->height();
    }
    return top;
}

void MainWindow::onPointTriggered() {
    editor.StartPointEditor();
    editor.OnInitMenuPopup(objectsMenu);
    // Позначка поточного типу об'єкту в заголовку вікна (Ж mod 2 = 1)
    setWindowTitle("Лабораторна робота №3 — Крапка");
}

void MainWindow::onLineTriggered() {
    editor.StartLineEditor();
    editor.OnInitMenuPopup(objectsMenu);
    setWindowTitle("Лабораторна робота №3 — Лінія");
}

void MainWindow::onRectTriggered() {
    editor.StartRectEditor();
    editor.OnInitMenuPopup(objectsMenu);
    setWindowTitle("Лабораторна робота №3 — Прямокутник");
}

void MainWindow::onEllipseTriggered() {
    editor.StartEllipseEditor();
    editor.OnInitMenuPopup(objectsMenu);
    setWindowTitle("Лабораторна робота №3 — Еліпс");
}

void MainWindow::OnNotify(QAction *action) {
    if (action && toolBar) {
        QToolTip::showText(QCursor::pos(), action->toolTip(), toolBar);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && event->pos().y() >= canvasTop()) {
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

    // Заливаємо білим робочу область під меню та панеллю інструментів
    QRect canvasRect = rect();
    canvasRect.setTop(canvasTop());
    painter.fillRect(canvasRect, Qt::white);
    painter.setClipRect(canvasRect);

    editor.OnPaint(painter);
}

void MainWindow::onAboutTriggered() {
    QMessageBox::about(this, "Про програму",
                       "Лабораторна робота №3\n"
                       "Розробка інтерфейсу користувача (Toolbar)\n"
                       "Варіант: 27");
}
