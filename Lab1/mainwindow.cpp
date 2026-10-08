#include "mainwindow.h"
#include "dialog1_step1.h"
#include "dialog1_step2.h"
#include "dialog2_groups.h"

#include <QMenuBar>
#include <QAction>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Встановлюємо заголовок та розміри головного вікна
    setWindowTitle("Лабораторна робота №1");
    resize(500, 300);

    // Створюємо центральний віджет та інформаційну мітку
    auto *central = new QWidget(this);
    statusLabel = new QLabel("Оберіть дію в меню...", this);
    statusLabel->setAlignment(Qt::AlignCenter);

    // Збільшуємо розмір шрифту мітки для наочності
    QFont font = statusLabel->font();
    font.setPointSize(12);
    statusLabel->setFont(font);

    // Додаємо мітку до компонувальника центрального віджета
    auto *layout = new QVBoxLayout(central);
    layout->addWidget(statusLabel);
    setCentralWidget(central);

    // Формуємо головне меню з розділом дій
    QMenu *menu = menuBar()->addMenu("Дії");
    QAction *actWork1 = menu->addAction("Робота1");
    QAction *actWork2 = menu->addAction("Робота2");

    // Підключаємо пункти меню до слотів-обробників
    connect(actWork1, &QAction::triggered, this, &MainWindow::onActionWork1Triggered);
    connect(actWork2, &QAction::triggered, this, &MainWindow::onActionWork2Triggered);
}

// Запуск першого завдання (покроковий майстер)
void MainWindow::onActionWork1Triggered() {
    showStep1();
}

// Відображення першого кроку майстра
void MainWindow::showStep1() {
    // Створюємо діалог лише за потреби (лінива ініціалізація)
    if (!step1Dialog) {
        step1Dialog = new Dialog1Step1(this);
        // За сигналом nextRequested відкриваємо другий крок
        connect(step1Dialog, &Dialog1Step1::nextRequested, this, &MainWindow::showStep2);
    }
    step1Dialog->show();
    step1Dialog->raise();
    step1Dialog->activateWindow();
}

// Відображення другого кроку майстра
void MainWindow::showStep2() {
    if (!step2Dialog) {
        step2Dialog = new Dialog1Step2(this);
        // За сигналом backRequested повертаємо перший крок
        connect(step2Dialog, &Dialog1Step2::backRequested, this, &MainWindow::showStep1);
        // При успішному завершенні виводимо інформацію у вікно
        connect(step2Dialog, &Dialog1Step2::acceptedStep2, this, [this]() {
            statusLabel->setText("Майстер успішно завершено (Робота1).");
        });
    }
    step2Dialog->show();
    step2Dialog->raise();
    step2Dialog->activateWindow();
}

// Запуск другого завдання (вибір групи зі списку)
void MainWindow::onActionWork2Triggered() {
    Dialog2Groups dlg(this);
    // Відкриваємо модальний діалог і очікуємо результат
    if (dlg.exec() == QDialog::Accepted) {
        QString selected = dlg.getSelectedGroup();
        statusLabel->setText("Обрана група: " + selected);
    }
}
