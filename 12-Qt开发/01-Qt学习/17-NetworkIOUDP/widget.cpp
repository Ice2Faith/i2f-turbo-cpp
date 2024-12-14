#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("主机");
    ui->lineEditTarIP->setText("127.0.0.1");
    ui->lineEditTarPort->setText("12100");
    ui->lineEditListenPort->setText("12101");
    tarUdp=new QUdpSocket(this);

    //bind local port and listen
    tarUdp->bind(ui->lineEditListenPort->text().toInt());
    //send datagram
    connect(ui->pushButtonSend,&QPushButton::clicked,this,[=](){
        tarUdp->writeDatagram(ui->textEditSend->toPlainText().toUtf8(),QHostAddress(ui->lineEditTarIP->text()),ui->lineEditTarPort->text().toInt());
        //如果需要进行广播时，只需要此处的地址换成广播地址即可，比如整个局域网广播：255.255.255.255，又或者针对某个子网255.255.10.255
        //如果需要进行组播时，比如公用组网：224.0.0.10
            //接受信息时，需要加入组网，tarUdp->joinMulticastGroup(QHostAddress("224.0.0.10"));
            //同时，需要注意协议版本，bind(QHostAddress::AnyIpv4,Port)

    });
    //receive datagram
    connect(tarUdp,&QUdpSocket::readyRead,this,[=](){
        //use QByteArray avoid free space
       QByteArray arr(tarUdp->pendingDatagramSize(),0);//变长字符数组
        int len=tarUdp->readDatagram(arr.data(),arr.length());
        ui->textEditHistory->append(arr);

    });
}

Widget::~Widget()
{
    delete ui;
}
