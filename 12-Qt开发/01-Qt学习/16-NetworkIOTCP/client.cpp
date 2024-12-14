#include "client.h"
#include "ui_client.h"
#include<QHostAddress>
Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    ui->lineEditClientIP->setText("127.0.0.1");
    ui->lineEditClientPort->setText("9966");
    //实例化
    client=new QTcpSocket(this);
    //连接
    client->connectToHost(QHostAddress(ui->lineEditClientIP->text()),ui->lineEditClientPort->text().toInt());
    //接受数据
    connect(client,&QTcpSocket::readyRead,this,[=]{
        QByteArray arr=client->readAll();
        ui->textEditHastory->append(arr);
    });
    //发送数据
    connect(ui->pushButtonSend,&QPushButton::clicked,this,[=](){
        client->write(ui->textEditInput->toPlainText().toUtf8().data());
        ui->textEditHastory->append(ui->textEditInput->toPlainText().toUtf8());
        ui->textEditInput->clear();
    });
}

Client::~Client()
{
    delete ui;
}
