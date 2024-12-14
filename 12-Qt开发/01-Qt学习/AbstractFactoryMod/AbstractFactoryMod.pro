TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    AbstractFactoryMod.cpp

include(deployment.pri)
qtcAddDeployment()

