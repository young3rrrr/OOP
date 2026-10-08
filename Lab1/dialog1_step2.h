#ifndef DIALOG1_STEP2_H
#define DIALOG1_STEP2_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

// Другий крок діалогового майстра (Робота 1)
class Dialog1Step2 : public QDialog {
    Q_OBJECT

public:
    explicit Dialog1Step2(QWidget *parent = nullptr);

signals:
    // Сигнал повернення до першого кроку
    void backRequested();

    // Сигнал успішного завершення та підтвердження роботи майстра
    void acceptedStep2();
};

#endif // DIALOG1_STEP2_H
