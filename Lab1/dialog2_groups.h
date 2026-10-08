#ifndef DIALOG2_GROUPS_H
#define DIALOG2_GROUPS_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

// Діалогове вікно вибору академічної групи (Робота 2)
class Dialog2Groups : public QDialog {
    Q_OBJECT

public:
    explicit Dialog2Groups(QWidget *parent = nullptr);

    // Метод для отримання рядка з назвою обраної групи
    QString getSelectedGroup() const;

private:
    // Віджет зі списком доступних груп
    QListWidget *listWidget;
};

#endif // DIALOG2_GROUPS_H
