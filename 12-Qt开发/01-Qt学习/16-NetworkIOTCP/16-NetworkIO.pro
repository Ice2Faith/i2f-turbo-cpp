#-------------------------------------------------
#
# Project created by QtCreator 2020-02-04T13:37:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 16-NetworkIO
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    client.cpp

HEADERS  += widget.h \
    client.h

FORMS    += widget.ui \
    client.ui

CONFIG +=c++11

QT +=network
