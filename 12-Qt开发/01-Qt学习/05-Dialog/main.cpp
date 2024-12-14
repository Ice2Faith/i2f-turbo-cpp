#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //QDialog
    /*
     * 模态对话框 非模态对话框
     *
    */
    return a.exec();
}
