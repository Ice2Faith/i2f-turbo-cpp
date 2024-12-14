#include "widget.h"
#include <QApplication>
/*
Event函数和事件过滤器
*/
/*
应用程序QApplication，一个程序只有一个，唯一

消息循环
while(GetMessage(msg))
{
}

事件分发器event()，根据事件类型进行分发，
也可以过滤事件，拦截事件

事件过滤器eventFilter,在消息进入窗口之间就进行过滤，
需要安装事件过滤器，需要在事件过滤函数中对事件进行处理

事件--事件过滤器--事件分发器--事件处理
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
