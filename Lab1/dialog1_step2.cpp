#include "dialog1_step2.h"

Dialog1Step2::Dialog1Step2(QWidget *parent) : QDialog(parent) {
    // Встановлюємо заголовок та розміри другого вікна
    setWindowTitle("Крок 2");
    resize(320, 150);

    // Створення мітки та кнопок керування
    auto *label = new QLabel("Це другий діалог майстра.", this);
    auto *btnBack = new QPushButton("< Назад", this);
    auto *btnOk = new QPushButton("Так", this);
    auto *btnCancel = new QPushButton("Відміна", this);

    // Розміщення кнопок: кнопка "Назад" зліва, кнопки дій ("Так", "Відміна") справа
    auto *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(btnBack);
    btnLayout->addStretch();
    btnLayout->addWidget(btnOk);
    btnLayout->addWidget(btnCancel);

    // Головний вертикальний шар для збирання інтерфейсу
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(label);
    mainLayout->addStretch();
    mainLayout->addLayout(btnLayout);

    // Кнопка "< Назад": надсилаємо запит на повернення назад і закриваємо крок 2
    connect(btnBack, &QPushButton::clicked, this, [this]() {
        emit backRequested();
        close();
    });

    // Кнопка "Так": сигналізуємо про успішне завершення майстра та схвалюємо діалог
    connect(btnOk, &QPushButton::clicked, this, [this]() {
        emit acceptedStep2();
        accept();
    });

    // Кнопка "Відміна": закриття без підтвердження
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
}
