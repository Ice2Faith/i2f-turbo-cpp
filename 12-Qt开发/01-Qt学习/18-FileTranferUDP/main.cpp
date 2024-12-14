#include "widget.h"
#include <QApplication>
/*
使用Udp协议进行文件传输
步骤：
发送端：
1.transfer file name
2.transfer file size
3.open file
4.read buffer length bytes
5.until read file end
QFileInfo 获取文件相关属性
接收端：
1.get file name
2.get file size
3.create file by name
4.write buffer byts
5.until file length equal size
6.save file

文件传输可能会因为采用UD通信，导致大量丢包，
因此实际上不应该采用，多用于流媒体播放器
}
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientFileTransfer w;
    w.show();

    return a.exec();
}
