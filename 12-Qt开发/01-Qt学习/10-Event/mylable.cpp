#include "mylable.h"
//第二种定时器头
#include<QTimer>
MyLable::MyLable(QWidget *parent) : QLabel(parent)
{
    //改变为追踪鼠标事件,设置之后，鼠标移动也会捕获，不需要按下
    //this->setMouseTracking(true);

    //第一种定时器方式，需要实现虚函数TimerEvent
    //开启定时器，参数：毫秒触发间隔，使用默认值，返回值为ID
    ID_TM_CLASS1= startTimer(1000);
    ID_TM_CLASS2= startTimer(666);

    //第二种定时器，直接使用对象的方式
    //参数，一个Widget
    QTimer * timer=new QTimer(this);
    //参数，毫秒间隔
    timer->start(720);
    //设置信号和槽
    connect(timer,&QTimer::timeout,this,[=](){
        static int num=10000;
        this->setText("Sec-Timer:"+QString::number(num++));
        if(num==10000+100){
            //关闭定时器
            timer->stop();
        }
    });

}

MyLable::~MyLable()
{
    //关闭定时器
    killTimer(ID_TM_CLASS1);
    killTimer(ID_TM_CLASS2);
}

void MyLable::enterEvent(QEvent *)
{
    this->setText("鼠标进入");
}
void MyLable::leaveEvent(QEvent *)
{
    this->setText("鼠标离开");
}
void MyLable::mouseMoveEvent(QMouseEvent * ev)
{
    //此事件只有在鼠标按下状态才会触发，如果需要判断按键，需要使用buttons方法获取，位与获取按键
    //由于widget不追踪鼠标事件，因此需要按下按键
    //Qt中的字符串格式化
    QString str=QString("Pos:%1,%2").arg(ev->x()).arg(ev->y());
    this->setText(str);
}
void MyLable::mouseReleaseEvent(QMouseEvent * ev)
{
    //按键类型是一个枚举
    QString str=QString("Release:%1").arg(ev->button()==Qt::LeftButton?"左键":"右键");
    this->setText(str);
}
void MyLable::timerEvent(QTimerEvent * ev)
{
    static int Id1=0;
    static int Id2=100;
     if(ev->timerId()==ID_TM_CLASS1)
     {
         QString str=QString("Time1:%1").arg(Id1);
         setText(str);
         Id1++;
     }else if (ev->timerId()==ID_TM_CLASS2)
     {
         QString str=QString("Time2:%1").arg(Id2);
         setText(str);
         Id2++;
     }
}
