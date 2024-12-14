#-------------------------------------------------
#
# Project created by QtCreator 2019-11-03T14:50:37
#
#-------------------------------------------------
# 类似Makefile，一般情况下不需要自己修改，会自动修改
# 对应当前项目用到的模块，目前用到core和gui 看模块类名上F1
QT       += core gui
# 如果是QT5以上可以不加，widgets写到上面即可，这句话为了兼容以前的版本
# QT5把widgets从GUI中分离出来
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
# 生成的应用程序名称
TARGET = 01-HelloQt
# 指定生成的Makefile类型，针对于app的Makefile，还可以是lib
TEMPLATE = app

# 源文件 \ 换行
SOURCES += main.cpp\
        widget.cpp \
    mybutton.cpp
# 头文件
HEADERS  += widget.h \
    mybutton.h

# C++标准设置，后面Lambda会用
CONFIG +=c++11
