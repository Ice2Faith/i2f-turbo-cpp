#include "widget.h"
#include <QApplication>
/***
 * 项目，右键，添加新文件，C++类，选择父类QWidget(所有的父类）
 * 填写类名，完成
 * 界面上，先添加父类控件，提升为，填写派生的子类即可
 *
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
