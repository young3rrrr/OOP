#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

// Попереднє оголошення класів діалогів
class Dialog1Step1;
class Dialog1Step2;

// Головне вікно програми для Лабораторної роботи №1
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override = default;

private slots:
    // Слот виклику майстра для завдання 1
    void onActionWork1Triggered();

    // Слот виклику діалогу вибору групи для завдання 2
    void onActionWork2Triggered();

    // Методи керування відображенням кроків майстра
    void showStep1();
    void showStep2();

private:
    // Інформаційна мітка в центрі вікна
    QLabel *statusLabel;

    // Вказівники на екземпляри діалогових вікон
    Dialog1Step1 *step1Dialog = nullptr;
    Dialog1Step2 *step2Dialog = nullptr;
};

#endif // MAINWINDOW_H
