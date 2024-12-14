#include "widget.h"
#include <QApplication>
#include"secondudp.h"
/**
 * UDP通信：
 * 无连接的通信
 * QUdpSocket
 * 发送数据报：
 * WriteDatagram()参数：IP Port data
 * 接受数据报：
 * 需要绑定端口（本地端口，监听本地端口）
 * ReadDatagram()参数：无
 *  信号：readyRead()
 *
 * 演示：
 * widget标识服务器端
 * SecondUdp标识客户端
 *
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    SecondUdp s;
    s.show();

    return a.exec();
}
