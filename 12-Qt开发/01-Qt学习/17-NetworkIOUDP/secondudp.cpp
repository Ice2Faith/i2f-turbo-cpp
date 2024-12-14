#include "secondudp.h"
#include "ui_secondudp.h"

SecondUdp::SecondUdp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SecondUdp)
{
    ui->setupUi(this);
    this->setWindowTitle("附属机");
    ui->lineEditTarIP->setText("127.0.0.1");
    ui->lineEditTarPort->setText("12101");
    ui->lineEditListenPort->setText("12100");
    tarUdp=new QUdpSocket(this);

    //bind local port and listen
    tarUdp->bind(ui->lineEditListenPort->text().toInt());
    //send datagram
    connect(ui->pushButtonSend,&QPushButton::clicked,this,[=](){
        tarUdp->writeDatagram(ui->textEditSend->toPlainText().toUtf8(),QHostAddress(ui->lineEditTarIP->text()),ui->lineEditTarPort->text().toInt());
    });
    //receive datagram
    connect(tarUdp,&QUdpSocket::readyRead,this,[=](){
        //use QByteArray avoid free space
       QByteArray arr(tarUdp->pendingDatagramSize(),0);//变长字符数组
        int len=tarUdp->readDatagram(arr.data(),arr.length());
        ui->textEditHistory->append(arr);

    });
}

SecondUdp::~SecondUdp()
{
    delete ui;
}
