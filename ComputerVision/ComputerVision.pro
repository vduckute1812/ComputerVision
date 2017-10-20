#-------------------------------------------------
#
# Project created by QtCreator 2017-09-13T18:03:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ComputerVision
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += '/local/include/opencv2'
LIBS += `pkg-config --libs opencv`
