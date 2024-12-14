#include "widget.h"
#include"qthreadusecase.h"
#include"qthreadcasetwo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    QThreadUseCase qtrd1;
    qtrd1.show();

    QThreadCaseTwo qtrd2;
    qtrd2.show();
    return a.exec();
}
