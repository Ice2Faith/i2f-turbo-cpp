#include "widget.h"
#include <QApplication>
/*
文件读写
文件流操作
文件信息
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
