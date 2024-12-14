#include "clientfiletransfer.h"
#include "ui_clientfiletransfer.h"

ClientFileTransfer::ClientFileTransfer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("TCP File Transfer Client");

    sockClient=new QTcpSocket(this);

    ui->lineEditTarIp->setText("127.0.0.1");
    ui->lineEditTarPort->setText("12100");
    //链接服务器
    connect(ui->pushButtonConnect,&QPushButton::clicked,this,[=]()
    {
        QString ip=ui->lineEditTarIp->text();
        qint16 port=ui->lineEditTarPort->text().toInt();
        if(ip.isEmpty() || port==0)
        {
            QMessageBox::critical(this,"错误","IP或Port不能为空");
            return;
        }
        //中断之前的链接
        sockClient->abort();
        //链接新的链接
        sockClient->connectToHost(QHostAddress(ip),port);

    });
    //链接成功消息
    connect(sockClient,&QTcpSocket::connected,this,[=]()
    {
        strFileName="";
        iFileSize=0;
        iRecvSize=0;
        bIsFile=false;

        ui->pushButtonConnect->setEnabled(false);
        ui->textEditInfo->clear();
        ui->textEditInfo->append("链接服务器成功");
    });
    //接受数据消息
    connect(sockClient,&QTcpSocket::readyRead,this,[=]()
    {
        QByteArray buffer=sockClient->readAll();
        if(bIsFile==false)
        {
            bIsFile=true;
            QString msg(buffer);
            //按照约定符号分割，提取第一个到第一个，也就是分割后的下标为1的那一个分割部分
            //对应也就是文件名部分
            strFileName=msg.section("#*",1,1);
            //对应也就是文件大小部分
            iFileSize=msg.section("#*",2,2).toInt();
            iRecvSize=0;

            //创建保存文件
            file.setFileName(strFileName);
            if(file.open(QFile::WriteOnly)==false)
            {
                strFileName="";
                iFileSize=0;
                iRecvSize=0;
                bIsFile=false;
                QMessageBox::critical(this,"错误","文件头信息错误");
                return;
            }

            ui->textEditInfo->append(QString("正在接受文件：%1\n").arg(strFileName));

            //由于存在TCP粘包的问题，因此如果文件数据被粘在文件头后面，需要及时保存
            //按照约定格式构造一个文件头包
            QByteArray head;
            head.append(QString("F#*%0#*%1#*").arg(strFileName).arg(iFileSize));
            //将去除了文件头包的剩余数据写入文件
            qint64 len=file.write(buffer.remove(0,head.size()));
            iRecvSize+=len;
        }
        else
        {
            //不是文件头，那就直接
            qint64 len=file.write(buffer);
            iRecvSize+=len;
        }
        if(iRecvSize==iFileSize)
        {
            //当接收到的大小和发送的文件大小一致的时候，也就是文件发送结束了
            file.close();
            bIsFile=false;
            ui->pushButtonConnect->setEnabled(true);
            sockClient->disconnectFromHost();
            QMessageBox::information(this,"成功","文件接受完毕！");
            ui->textEditInfo->append("文件接受完毕!\n");
        }
    });
    //提供给客户端一个发送信息的通道
    connect(ui->pushButtonSend,&QPushButton::clicked,this,[=]()
    {
        QString str=ui->lineEditMsg->text();
        sockClient->write(str.toUtf8());
        sockClient->flush();
        ui->lineEditMsg->setText("");
    });
}

ClientFileTransfer::~ClientFileTransfer()
{
    delete ui;
}
