#include "dialog1_step1.h"

Dialog1Step1::Dialog1Step1(QWidget *parent) : QDialog(parent) {
    // Налаштування заголовка та початкового розміру вікна
    setWindowTitle("Крок 1");
    resize(300, 150);

    // Створення елементів інтерфейсу першого кроку
    auto *label = new QLabel("Це перший діалог майстра.", this);
    auto *btnNext = new QPushButton("Далі >", this);
    auto *btnCancel = new QPushButton("Відміна", this);

    // Горизонтальне розміщення кнопок у нижній частині діалогу
    auto *btnLayout = new QHBoxLayout();
    btnLayout->addStretch(); // Притискаємо кнопки до правого краю
    btnLayout->addWidget(btnNext);
    btnLayout->addWidget(btnCancel);

    // Основний вертикальний шар розміщення для мітки та панелі кнопок
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(label);
    mainLayout->addStretch();
    mainLayout->addLayout(btnLayout);

    // При натисканні "Далі >" надсилаємо сигнал і закриваємо поточний крок
    connect(btnNext, &QPushButton::clicked, this, [this]() {
        emit nextRequested();
        close();
    });

    // При натисканні "Відміна" скасовуємо діалог
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
}
