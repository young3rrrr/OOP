cmake_minimum_required(VERSION 3.16)
project(Lab2 LANGUAGES CXX)

# Встановлюємо стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Вмикаємо автоматичну генерацію MOC, UIC та RCC для Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Пошук бібліотек Qt Widgets (підтримка Qt6 або Qt5)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Список вихідних файлів проєкту
set(PROJECT_SOURCES
    main.cpp
    mainwindow.h
    mainwindow.cpp
    shape.h
    shape.cpp
    editor.h
    shape_editor.h
    shape_editor.cpp
)

# Створення виконуваного файлу
add_executable(Lab2 ${PROJECT_SOURCES})

# Підключення модуля Widgets до проєкту
target_link_libraries(Lab2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
