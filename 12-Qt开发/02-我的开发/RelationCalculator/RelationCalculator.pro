#-------------------------------------------------
#
# Project created by QtCreator 2020-04-08T20:25:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RelationCalculator
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    personrelation.cpp

HEADERS  += widget.h \
    personrelation.h

FORMS    += widget.ui

CONFIG +=c++11
