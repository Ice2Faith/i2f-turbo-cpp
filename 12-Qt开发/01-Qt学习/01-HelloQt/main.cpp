#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //应用程序类，每个QT程序中有且只有一个，相当于MFC的APP对象
    QApplication a(argc, argv);
    //窗口类，创建出来默认不显示，就是整个窗口
    Widget w;//widget.cpp
    w.show();

    //事件处理--信号和槽(消息和处理函数)
    //一个对象发出一个消息，另一个对象进行消息处理
    //信号和槽其实都是函数，信号只有声明，槽声明定义都需要（回调函数）。

    return a.exec();//后台进行消息循环
}
