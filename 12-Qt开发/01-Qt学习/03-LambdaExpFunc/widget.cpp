#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_btn=new QPushButton("关闭",this);
    this->resize(480,320);
    //使用Lambda需要在pro文件添加：CONFIG +=c++11
    connect(m_btn,&QPushButton::clicked,this,[=](){
        this->close();
    });
}

Widget::~Widget()
{

}
