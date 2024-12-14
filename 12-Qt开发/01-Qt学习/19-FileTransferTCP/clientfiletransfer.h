#ifndef WIDGET_H
#define WIDGET_H
/*基于TCP的文件传输*/
#include <QWidget>
#include<QTcpServer>
#include<QTcpSocket>
#include<QHostAddress>
#include<QFileDialog>
#include<QFile>
#include<QFileInfo>
#include<QByteArray>
#include<QList>
#include<QMessageBox>
#include<QDebug>
namespace Ui {
class Widget;
}

class ClientFileTransfer : public QWidget
{
    Q_OBJECT

public:
    explicit ClientFileTransfer(QWidget *parent = 0);
    ~ClientFileTransfer();

private:
    Ui::Widget *ui;
    QTcpSocket * sockClient;
    QString strFileName;
    qint64 iFileSize;
    qint64 iRecvSize;
    bool bIsFile;
    QFile file;
};

#endif // WIDGET_H
