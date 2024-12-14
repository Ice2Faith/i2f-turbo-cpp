#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    px=50,py=50;
    connect(ui->pushButtonReflash,&QPushButton::clicked,this,[=](){
        px+=10;
        py+=15;
        if(px>this->width())
            px=0;
        if(py>this->height())
            py=0;
        this->update();//更新窗口，刷新界面，也可以使用repaint（可能造成闪烁）
    });
}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent * pe)
{
    //f1选中的帮助，esc退出帮助回到代码
    QPainter painter(this);//参数：绘图设备
    painter.drawPixmap(0,0,QPixmap(":/bg1.jpg"));
    //draw族函数用于常用基本图形绘制
    painter.setPen(QColor::fromRgb(255,0,0));
    //参数:左上角坐标，宽度和高度
    painter.drawEllipse(px,py,200,400);
    //QRect和QRectF,带F标识float
    painter.drawLine(100,100,200,400);
    QBrush brush(QColor::fromRgb(0,255,255));
    painter.setBrush(brush);
    painter.drawRect(200,200,250,250);
    painter.setBrush(QBrush(QPixmap(":/bg1.jpg")));
    painter.drawEllipse(200,200,400,200);
    painter.setFont(QFont("微软雅黑",48,75,true));
    painter.drawText(px,py,"hello QPainter");
    //其余其他信息，查看帮助文档即可
    //获取窗口的宽和高
    this->width();
    this->height();
}
