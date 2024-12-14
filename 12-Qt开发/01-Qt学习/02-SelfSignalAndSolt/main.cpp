#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("自定义信号和槽");
    w.resize(480,320);
    w.show();
    //widget.cpp
    return a.exec();
}
