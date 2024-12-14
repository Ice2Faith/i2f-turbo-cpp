#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //加载图片
    bgp.load(":/bgp.png");
    //去除边框
    this->setWindowFlags(Qt::FramelessWindowHint);
    //设置背景透明
    this->setAttribute(Qt::WA_TranslucentBackground);
    //设置窗口逻辑，左键按下拖动窗口，右键单击关闭窗口
    dx=0,dy=0;
}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,bgp);
}
void Widget::mousePressEvent(QMouseEvent * me)
{
    if(me->button()==Qt::LeftButton)
    {
        dx=me->globalX()-this->pos().x();
        dy=me->globalY()-this->pos().y();
    }
    else if(me->button()==Qt::RightButton)
    {
        this->close();
    }
}

void Widget::mouseMoveEvent(QMouseEvent * me)
{
    if(me->buttons()&Qt::LeftButton)
        this->move(me->globalX()-dx,me->globalY()-dy);
}
