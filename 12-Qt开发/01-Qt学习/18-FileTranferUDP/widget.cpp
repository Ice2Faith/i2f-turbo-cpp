#include "widget.h"
#include "ui_widget.h"
ClientFileTransfer::ClientFileTransfer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("UDP File Transfer");
    ui->lineEditListenPort->setText("12100");
    ui->lineEditTarIp->setText("127.0.0.1");
    ui->lineEditTarPort->setText("12101");
    tarUdp=new QUdpSocket(this);
    ListenPort();
    connect(ui->pushButtonListen,&QPushButton::clicked,this,&ClientFileTransfer::ListenPort);
    connect(tarUdp,&QUdpSocket::readyRead,this,&ClientFileTransfer::AcceptFile);
    connect(ui->pushButtonSelectFile,&QPushButton::clicked,this,&ClientFileTransfer::AddFile);
    connect(ui->pushButtonSendFile,&QPushButton::clicked,this,&ClientFileTransfer::SendFile);
}

ClientFileTransfer::~ClientFileTransfer()
{
    delete ui;
}
void ClientFileTransfer::ListenPort()
{
    tarUdp->close();
    tarUdp->bind(QHostAddress::AnyIPv4,ui->lineEditListenPort->text().toInt());
    ui->textEditInfo->append("已开始监听端口："+ui->lineEditListenPort->text()+" 消息");
}

void ClientFileTransfer::AcceptFile()
{
    QByteArray arr(tarUdp->pendingDatagramSize(),0);//变长字符数组
    tarUdp->readDatagram(arr.data(),arr.length());
    if(arr.left(3)=="FH:")
    {
        QList<QByteArray> arrs=arr.split('#');
        fileSize=arrs[1].toInt();
        file=new QFile(".\\"+arrs[2]);
        file->open(QFile::WriteOnly);
        presize=0;
        ui->textEditInfo->append(QString("接受到新文件："+arrs[2]+" 大小：%1").arg(fileSize));
    }else
    {
        presize+=arr.size();
        file->write(arr);
        ui->textEditInfo->append("Size:"+QString::number(presize)+" Length:"+QString::number(fileSize));
        if(presize==fileSize)
        {
            file->close();
            ui->textEditInfo->append("文件已保存！！");
            return;
        }
    }
}

void ClientFileTransfer::AddFile()
{
    QString filename=QFileDialog::getOpenFileName(this,"请选择发送文件");
    if(filename.isEmpty())
    {
        ui->lineEditFileName->setText("");
        return;
    }
    ui->lineEditFileName->setText(filename);
    ui->textEditInfo->append(QString("已选择新文件：%0").arg(filename));
}
void ClientFileTransfer::SendFile()
{
    ui->textEditInfo->append("正在发送文件："+ui->lineEditFileName->text());
    QByteArray head;
    QFileInfo fi(ui->lineEditFileName->text());
    head.append(QString("FH:#%0#%1").arg(fi.size()).arg(fi.fileName()));
    SendDatagramToTarget(head);
    head.clear();
    QFile fp(ui->lineEditFileName->text());
    fp.open(QFile::ReadOnly);
    while(!fp.atEnd())
    {
        QByteArray data= fp.read(4096);
        SendDatagramToTarget(data);
    }
    fp.close();
    ui->textEditInfo->append("文件发送完毕！");
}

void ClientFileTransfer::SendDatagramToTarget(QByteArray arr)
{
   tarUdp->writeDatagram(arr.data(),QHostAddress(ui->lineEditTarIp->text()),ui->lineEditTarPort->text().toInt());
   tarUdp->flush();
}
