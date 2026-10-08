cmake_minimum_required(VERSION 3.16)
project(Lab1 LANGUAGES CXX)

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
    dialog1_step1.h
    dialog1_step1.cpp
    dialog1_step2.h
    dialog1_step2.cpp
    dialog2_groups.h
    dialog2_groups.cpp
)

# Створення виконуваного файлу
add_executable(Lab1 ${PROJECT_SOURCES})

# Підключення модуля Widgets до проекту
target_link_libraries(Lab1 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
