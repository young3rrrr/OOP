#ifndef DIALOG1_STEP1_H
#define DIALOG1_STEP1_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

// Перший крок діалогового майстра (Робота 1)
class Dialog1Step1 : public QDialog {
    Q_OBJECT

public:
    explicit Dialog1Step1(QWidget *parent = nullptr);

signals:
    // Сигнал запиту переходу до наступного діалогового вікна
    void nextRequested();
};

#endif // DIALOG1_STEP1_H
