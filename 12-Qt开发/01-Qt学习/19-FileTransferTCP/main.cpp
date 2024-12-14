#include "clientfiletransfer.h"
#include"serverfiletransfer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServerFileTransfer ws;
    ws.show();

    ClientFileTransfer wc;
    wc.show();


    return a.exec();
}
