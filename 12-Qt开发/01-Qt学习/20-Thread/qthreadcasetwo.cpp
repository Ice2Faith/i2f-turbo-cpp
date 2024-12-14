#include "qthreadcasetwo.h"
#include "ui_qthreadcasetwo.h"

QThreadCaseTwo::QThreadCaseTwo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QThreadCaseTwo)
{
    ui->setupUi(this);
    this->setWindowTitle("QThread Case Two");
    /*
    业务对象，构造的时候不能指定父对象
    业务对象（子线程）不能处理UI窗口主线程的相关类或者对象
    子线程只能处理数据相关的操作，不能涉及UI
    */
    timer=new QTimer(this);
    //子线程类
    pthread=new QThread(this);
    //业务对象
    work=new MyWork();
    //将业务对象移动到子线程
    work->moveToThread(pthread);
    //使得子线程工作
    connect(this,&QThreadCaseTwo::DoWork,work,&MyWork::DoWork);


    //这里使用带有最后一个参数的connect，但是这种方式不能使用Lambda
    connect(ui->pushButtonStart,&QPushButton::clicked,this,&QThreadCaseTwo::ClickStart);
    connect(ui->pushButtonEnd,&QPushButton::clicked,this,&QThreadCaseTwo::ClickEnd);
    connect(timer,&QTimer::timeout,this,&QThreadCaseTwo::TimerOn);
   //接收处理完毕信号
    connect(work,&MyWork::ProcessDown,timer,&QTimer::stop);
    //窗口析构的时候，结束子线程
    connect(this,&QThreadCaseTwo::destroyed,this,&QThreadCaseTwo::CloseThread);

    /*
    connect函数的第五个参数Qt::ConnectionType type：
        默认自动连接
            根据写的程序的类型，是否是多线程，会自动指定为队列和直接方式
        多线程队列连接
            槽函数在信号接收者所在的线程中执行
        单线程直接连接
            槽函数和信号在同一个进程中执行

        总的来说，默认连接就行，Qt自己会处理
    */
}

QThreadCaseTwo::~QThreadCaseTwo()
{
    delete ui;
}
void QThreadCaseTwo::ClickStart()
{
    if(timer->isActive()==true)
        return;
    if(pthread->isRunning())
        return;
    timer->start(500);
    pthread->start();
    //发出信号给工作对象，让它开始工作
    emit DoWork();
}

void QThreadCaseTwo::ClickEnd()
{
    //停止定时器，并设置工作对象的状态
    timer->stop();
    work->SetStopFlag(true);
}
void QThreadCaseTwo::TimerOn()
{
    static int num=0;
    ui->lcdnumber->display(num++);
}
void QThreadCaseTwo::CloseThread()
{
    work->SetStopFlag(true);
    pthread->quit();//退出线程（如果没有做完当前的，则等待一下），也可以用terminate强行终止线程（这种方式不建议）
    pthread->wait();//等待子线程执行完毕，配合quit使用
}
