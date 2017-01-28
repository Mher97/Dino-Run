#-------------------------------------------------
#
# Project created by QtCreator 2016-03-02T15:30:07
#
#-------------------------------------------------

QT       += core gui
QT       +=multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Game
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    widget.cpp

HEADERS  += mainwindow.h \
    widget.h

FORMS    += mainwindow.ui \
    widget.ui
