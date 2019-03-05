QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = snake
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    food.cpp \
    gamecontroller.cpp \
    snake.cpp \
    wall.cpp

HEADERS  += mainwindow.h \
    food.h \
    gamecontroller.h \
    constants.h \
    snake.h \
    wall.h

FORMS += \
    mainwindow.ui
