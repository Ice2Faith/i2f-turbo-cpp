#-------------------------------------------------
#
# Project created by QtCreator 2020-02-11T16:26:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 18-FileTranfer
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

QT +=network

CONFIG +=c++11
