#include "widget.h"
#include "ui_widget.h"
/*
在同一个程序内完成两个顶层窗口
，Weiget窗口作为服务器，Client作为客户端
*/
#include<QHostAddress>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->lineEditServerIP->setText("127.0.0.1");
    ui->lineEditServerPort->setText("9966");
    //实例化
    server=new QTcpServer(this);
    //监听
    server->listen(QHostAddress(ui->lineEditServerIP->text()),ui->lineEditServerPort->text().toInt());
    //接受客户端连接
    connect(server,&QTcpServer::newConnection,this,[=](){
       //accept
        sock=server->nextPendingConnection();
        ui->textEditHastory->append("client linked.");
        connect(sock,&QTcpSocket::readyRead,this,[=]{
            //接受数据
            QByteArray arr=sock->readAll();
            ui->textEditHastory->append(arr);
        });
    });
    //发送数据
    connect(ui->pushButtonSend,&QPushButton::clicked,this,[=]{
        sock->write(ui->textEditInput->toPlainText().toUtf8().data());
        ui->textEditHastory->append(ui->textEditInput->toPlainText().toUtf8());
        ui->textEditInput->clear();
    });
}

Widget::~Widget()
{
    delete ui;
}
