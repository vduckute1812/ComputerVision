#-------------------------------------------------
#
# Project created by QtCreator 2017-09-06T14:36:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    segmentation.cpp \
    findlinkpixel.cpp \
    humoment.cpp \
    traindata.cpp \
    filedata.cpp

HEADERS  += mainwindow.h \
    segmentation.h \
    findlinkpixel.h \
    humoment.h \
    traindata.h \
    filedata.h

FORMS    += mainwindow.ui

INCLUDEPATH += "/usr/local/include"
LIBS += `pkg-config --libs opencv`
