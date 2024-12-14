#include "widget.h"
#include"client.h"
#include <QApplication>
/*
Qt IO继承关系
所有IO设备的父类：
QIODevice:
    QBuffer（操作内存空间QByteArray）
    QProcess（进程）
    QFileDevice（文件设备，QT5才有的，从QFile抽象出来的）
    QAbstractSocket
QFileDevice:
    QFile
QAbstractSocket: send --write recv --read
    QTcpSocket
    QUdpSocket
QFile:
    QTemporaryFile
QTcpSocket:
    QSslSocket

通信流程：
    服务器端：
        socket()
        bind()
        listen()
          loop:
            accept()
            recv()/send()
            closeClientSocket()
          end loop
        close()
    客户端：
        socket()
        connect()
        recv()/send()
        close()

Qt中的TCP通信：
    服务器：
        QTCPServer 监听，不是IO设备
        QTcpSocket 通信
        流程：
            监听： server.listen(IP,Port) QTCPServer
            接受信号： newConnection() 槽函数：接受请求
            接受客户端：conn=server.nextPendingConnection() QTcpSocket
            发送数据：conn.write()
    客户端：
        QTcpSocket 通信
        流程：
            连接： client.connectToHost(serverIP,serverPort) QTcpSocket
            接受数据信号：readyRead() 槽函数：readAll()
            关闭连接：disconnectFromHost()
            关闭套接字：close() 关闭IO设备
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    Client c;
    c.show();

    c.move(w.frameGeometry().topRight());
    return a.exec();
}
