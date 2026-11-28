#include <QApplication>
#include "mainwindow.h"

// Точка входу в програму
int main(int argc, char *argv[]) {
    // Ініціалізація графічного середовища Qt
    QApplication app(argc, argv);

    // Створення та показ головного вікна
    MainWindow w;
    w.show();

    // Запуск головного циклу обробки подій програми
    return app.exec();
}
