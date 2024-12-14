#include "widget.h"
#include <QApplication>
/***
 * 自定义控件：
 * 项目，右键，添加新文件，QT，QT设计师界面类，Widget,进行设计即可
 * 导入使用：
 * 添加一个Widget，在其上右键，提升为，输入类名，choose，提升，看到属性类名变了几成功了
 * 容器变形:选中容器，比如widget,右键，变形为
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
