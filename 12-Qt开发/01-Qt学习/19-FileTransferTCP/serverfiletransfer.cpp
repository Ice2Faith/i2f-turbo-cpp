#include "serverfiletransfer.h"
#include "ui_serverfiletransfer.h"

ServerFileTransfer::ServerFileTransfer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerFileTransfer)
{
    ui->setupUi(this);
    server=new QTcpServer(this);
    ui->lineEditListenIP->setText("127.0.0.1");
    ui->lineEditListenPort->setText("12100");
    this->setWindowTitle("TCP File Transfer Server");
    //开启服务器监听
    connect(ui->pushButtonListen,&QPushButton::clicked,this,[=]()
    {
        server->listen(QHostAddress(ui->lineEditListenIP->text()),ui->lineEditListenPort->text().toInt());
        ui->pushButtonListen->setEnabled(false);
    });
    //接受客户端连接
    connect(server,&QTcpServer::newConnection,this,[=]()
    {
        //这里虽然使用了可以接受多个客户端的客户端链表，但是为了处理方便和理解，不进行复杂设计了
        //接受新的客户端
       client=new QTcpSocket();
       client=server->nextPendingConnection();
       //常规来说需要把接受到的新客户端加入客户端链表
       sockClient.append(client);
       //获取客户端地址信息并输出
       QString ip=client->peerAddress().toString();
       qint16 port=client->peerPort();
       ui->textEditInfo->append(QString("接受到新客户端连接 %1:%2...\n").arg(ip).arg(port));
       //为客户端消息建立信号槽
       connect(client,&QTcpSocket::readyRead,this,[=]()
       {
         QByteArray buffer=client->readAll();
         ui->textEditInfo->append(QString("Client:%1").arg(QString(buffer)));
       });
    });
    //选择文件
    connect(ui->pushButtonSelectFile,&QPushButton::clicked,this,[=]()
    {
        strFileName=QFileDialog::getOpenFileName(this,"请选择发送文件");
        if(strFileName.isEmpty())
        {
            ui->textEditInfo->append("未选择文件！\n");
            return;
        }
        ui->lineEditFileName->setText(strFileName);
        ui->textEditInfo->append(QString("已选择新文件：%0").arg(strFileName));
    });
    //发送文件
    connect(ui->pushButtonSendFile,&QPushButton::clicked,this,[=]()
    {
        ui->textEditInfo->append("正在发送文件："+strFileName);
        //构造文件头并发送
        QByteArray head;
        QFileInfo fi(strFileName);
        //文件头：head#*fileName#*fileSize
        //但是为了处理粘包的数据，因此多加一个分割#*到最后
        head.append(QString("F#*%0#*%1#*").arg(fi.fileName()).arg(fi.size()));
        client->write(head);
        client->flush();
        head.clear();
        //一般来说，为了不会粘包，一般采用延时进行处理，由于这里服务器端和客户端都在一个进程中，不好进行延时，
        //后面讲线程的时候会讲解
        //发送文件内容
        QFile fp(strFileName);
        fp.open(QFile::ReadOnly);
        while(!fp.atEnd())
        {
            QByteArray data= fp.read(4096);
            client->write(data);
        }
        client->flush();
        fp.close();
        ui->textEditInfo->append("文件发送完毕！");
    });
}

ServerFileTransfer::~ServerFileTransfer()
{
    delete ui;
}
