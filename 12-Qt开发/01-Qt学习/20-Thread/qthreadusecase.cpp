#include "qthreadusecase.h"
#include "ui_qthreadusecase.h"
/*
使用QT4.7之前的方式实现多线程，继承QThread的方式
*/
QThreadUseCase::QThreadUseCase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QThreadUseCase)
{
    ui->setupUi(this);
    this->setWindowTitle("QThread Case 1");
    timer=new QTimer(this);
    mythread=new MyThread();
    connect(ui->pushButtonStart,&QPushButton::clicked,this,[=]()
    {
        if(timer->isActive()==true)
        {
            return;
        }
        timer->start(500);//每500ms定时处理一次
        mythread->start();//启动子线程
    });
    //定时器处理函数
    connect(timer,&QTimer::timeout,this,[=]()
    {
        static int num=0;
        ui->lcdnumber->display(num++);
    });
    connect(mythread,&MyThread::ProcessDone,timer,&QTimer::stop);
}

QThreadUseCase::~QThreadUseCase()
{
    delete ui;
}
