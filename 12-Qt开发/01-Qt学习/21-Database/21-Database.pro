#-------------------------------------------------
#
# Project created by QtCreator 2020-03-18T12:42:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 21-Database
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

QT += sql

CONFIG +=c++11
