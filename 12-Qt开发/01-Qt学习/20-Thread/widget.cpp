#include "widget.h"
#include "ui_widget.h"
/*
QT多线程编程
    两种实现方式：
        QT4.7之前：比较简单，容易实现
            继承QThread，实现子类
            重写虚函数run()
            需要使用时使用线程对象的start()函数启动线程
            使用信号槽和主线程进行通信
         QT4.7之后，实现起来稍微复杂，但是比较灵活
            connect函数最后一个参数
                默认连接
                队列连接
                直接连接
*/
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("With out Thread");
    timer=new QTimer(this);
    //阻塞主线程模拟
    connect(ui->pushButtonStart,&QPushButton::clicked,this,[=]()
    {
        if(timer->isActive()==true)
        {
            return;
        }
        timer->start(500);//每500ms定时处理一次
        //这里由于线程阻塞，会导致显示的值并不会被定时器更改
        QThread::sleep(5);//阻塞5秒
        timer->stop();
    });
    //定时器处理函数
    connect(timer,&QTimer::timeout,this,[=]()
    {
        static int num=0;
        ui->lcdnumber->display(num++);
    });
}

Widget::~Widget()
{
    delete ui;
}
