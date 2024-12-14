#include "widget.h"
#include <QApplication>
//使用：QPainter和QPaintDevice在一个Widget上绘图
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
