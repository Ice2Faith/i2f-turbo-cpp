#ifndef SERVERFILETRANSFER_H
#define SERVERFILETRANSFER_H

#include <QWidget>
#include<QTcpServer>
#include<QTcpSocket>
#include<QHostAddress>
#include<QFileDialog>
#include<QFile>
#include<QFileInfo>
#include<QByteArray>
#include<QList>
#include<QDebug>
namespace Ui {
class ServerFileTransfer;
}

class ServerFileTransfer : public QWidget
{
    Q_OBJECT

public:
    explicit ServerFileTransfer(QWidget *parent = 0);
    ~ServerFileTransfer();

private:
    Ui::ServerFileTransfer *ui;
    QTcpServer * server;
    QTcpSocket * client;
    QList<QTcpSocket*>  sockClient;
    QString strFileName;
};

#endif // SERVERFILETRANSFER_H
