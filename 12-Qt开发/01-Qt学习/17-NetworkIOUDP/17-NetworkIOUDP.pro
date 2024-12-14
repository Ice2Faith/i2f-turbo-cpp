#-------------------------------------------------
#
# Project created by QtCreator 2020-02-11T12:04:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 17-NetworkIOUDP
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    secondudp.cpp

HEADERS  += widget.h \
    secondudp.h

FORMS    += widget.ui \
    secondudp.ui

QT +=network

CONFIG +=c++11
