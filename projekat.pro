#-------------------------------------------------
#
# Project created by QtCreator 2017-03-27T15:42:57
#
#-------------------------------------------------

QT       += core gui network
QT += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projekat
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    game.cpp \
    figure.cpp \
    table.cpp \
    button.cpp \
    field.cpp \
    score.cpp \
    robot.cpp \
    potez.cpp \
    server.cpp

HEADERS  += mainwindow.h \
    game.h \
    figure.h \
    table.h \
    button.h \
    field.h \
    score.h \
    robot.h \
    potez.h \
    server.h

FORMS    += mainwindow.ui

RESOURCES += \
    slike.qrc
