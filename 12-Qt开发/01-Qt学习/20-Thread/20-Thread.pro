#-------------------------------------------------
#
# Project created by QtCreator 2020-03-18T11:06:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 20-Thread
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    qthreadusecase.cpp \
    mythread.cpp \
    qthreadcasetwo.cpp \
    mywork.cpp

HEADERS  += widget.h \
    qthreadusecase.h \
    mythread.h \
    qthreadcasetwo.h \
    mywork.h

FORMS    += widget.ui \
    qthreadusecase.ui \
    qthreadcasetwo.ui

CONFIG +=c++11
