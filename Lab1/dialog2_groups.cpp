#include "dialog2_groups.h"
#include <QMessageBox>

Dialog2Groups::Dialog2Groups(QWidget *parent) : QDialog(parent) {
    // Налаштовуємо заголовок і розмір діалогового вікна
    setWindowTitle("Вибір групи");
    resize(300, 260);

    // Створюємо список груп та наповнюємо його даними
    listWidget = new QListWidget(this);
    const QStringList groups = {
        "ІМ-51", "ІМ-52", "ІМ-53", "ІМ-54",
        "ІМ-61", "ІМ-62", "ІМ-63", "ІМ-64"
    };
    listWidget->addItems(groups);

    // Кнопки дій
    auto *btnOk = new QPushButton("Так", this);
    auto *btnCancel = new QPushButton("Відміна", this);

    // Розміщуємо кнопки внизу праворуч
    auto *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(btnOk);
    btnLayout->addWidget(btnCancel);

    // Загальний компонувальник для віджета списку та кнопок
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(listWidget);
    mainLayout->addLayout(btnLayout);

    // Обробка підтвердження вибору
    connect(btnOk, &QPushButton::clicked, this, [this]() {
        // Перевіряємо, чи користувач виділив хоча б один елемент списку
        if (!listWidget->currentItem()) {
            QMessageBox::warning(this, "Попередження", "Оберіть групу зі списку!");
            return;
        }
        accept(); // Закриваємо діалог зі статусом Accepted
    });

    // Обробка натискання кнопки "Відміна"
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);
}

// Повертає текст виділеного елемента або порожній рядок, якщо нічого не вибрано
QString Dialog2Groups::getSelectedGroup() const {
    if (listWidget->currentItem()) {
        return listWidget->currentItem()->text();
    }
    return QString();
}
