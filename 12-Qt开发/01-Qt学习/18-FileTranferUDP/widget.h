#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QUdpSocket>
#include<QHostAddress>
#include<QFileDialog>
#include<QFile>
#include<QFileInfo>
#include<QByteArray>
#include<QList>
namespace Ui {
class Widget;
}

class ClientFileTransfer : public QWidget
{
    Q_OBJECT

public:
    explicit ClientFileTransfer(QWidget *parent = 0);
    ~ClientFileTransfer();
public slots:
    void AcceptFile();
    void AddFile();
    void SendFile();
    void ListenPort();
private:
    void SendDatagramToTarget(QByteArray arr);
    qint64 fileSize;
    qint64 presize;
    Ui::Widget *ui;
    QUdpSocket * tarUdp;
    QFile * file;
};

#endif // WIDGET_H
