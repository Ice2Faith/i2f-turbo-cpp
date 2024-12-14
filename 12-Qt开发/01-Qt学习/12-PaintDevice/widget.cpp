#include "widget.h"
#include "ui_widget.h"
#include<QPainter>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //在QPixmap中绘图，同样也可以在QBitmap中绘图，只是构造可能不同
    //创建大小图片
    QPixmap img(500,500);
    //填充背景，默认黑色
    img.fill(Qt::white);
    //创建画家，绘制后保存
    QPainter painter(&img);
    painter.drawEllipse(0,0,200,150);
    //img.save(".\\bg.png");
//    painter.save();//保存当前的画笔画刷到栈中
//    painter.restore();//从栈中取出画刷画笔
    //QImage img(300,300,QImage::Format_ARGB32);
//    painter.begin();//重新指定绘图设备，相当于缓冲
//    painter.end();//结束重新绘图
  //  QPicture pic();//保存的是绘图步骤，不是图片，因此使用save方法保存的不是图片
//    pic.load(QPicture文件路径);//通过pic加载picture文件
//    painter.drawPicture(pic);//显示picture
}

Widget::~Widget()
{
    delete ui;
}
