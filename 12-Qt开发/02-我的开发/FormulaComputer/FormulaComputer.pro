#-------------------------------------------------
#
# Project created by QtCreator 2021-02-01T09:43:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FormulaComputer
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h \
    AlgoContainer.hpp \
    AlgoString.hpp \
    FormulaCalculator.h

FORMS    += widget.ui

CONFIG +=c++11
