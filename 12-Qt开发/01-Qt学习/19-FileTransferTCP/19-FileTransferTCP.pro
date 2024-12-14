#-------------------------------------------------
#
# Project created by QtCreator 2020-03-17T17:51:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 19-FileTransferTCP
TEMPLATE = app


SOURCES += main.cpp \
    serverfiletransfer.cpp \
    clientfiletransfer.cpp

HEADERS  += \
    serverfiletransfer.h \
    clientfiletransfer.h

FORMS    += \
    serverfiletransfer.ui \
    clientfiletransfer.ui

QT +=network

CONFIG +=c++11
