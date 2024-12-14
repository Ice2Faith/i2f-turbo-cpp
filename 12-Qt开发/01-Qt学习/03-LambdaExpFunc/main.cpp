#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
/*
    [函数体外部引用](参数列表)mutable exception -> 返回值类型{函数体}
    常见的：
    [](int v){}
    函数体外部引用：
        =（值传递）
        &（引用传递）
        this（当前类中的变量）
    mutable:
        [a] 相当于 [const a]
        去除值传递进来的[]号内的const限定，使得可改变
    exception:
        决定了是否要抛出异常
    返回值类型：
        []()->int{return 0;};
        如果只有一个return语句，可以不加，如果存在多个return就要添加
        如果不加编译器不能自动类型推到
    示例：
        int a,b;
        [a,&b](){}//对a值传递，b引用传递
    一般使用：[=](...){...}


*/
