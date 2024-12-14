#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //类似MFC的单文档，带有菜单栏，工具栏，状态栏等
    /*
    菜单栏只能有一个，
    工具栏可以有多个，
    状态栏只能有一个，
    */
    MainWindow w;
    w.show();
    //往工具栏添加项：UI设置界面下面的action，选中，托中到工具栏即可，移除相反
    //活动窗口，Dock Widget，类似多窗口
    //状态栏，可以存放所有widget子类窗口，但是只能用代码方式添加
    //添加资源文件：项目名-添加文件-QT-QTresource-名称resource-完成
    //选中resource.qrc右键，open with editor,添加前缀/，添加文件
    //编译资源文件时间会比较长，因为要进行资源文件的二进制拷贝
    //有了资源文件之后，在ui设计界面就可以属性，选择icon进行选择了
    //tooltip属性是在鼠标移动到图片按钮上之后显示的内容
    return a.exec();
}
