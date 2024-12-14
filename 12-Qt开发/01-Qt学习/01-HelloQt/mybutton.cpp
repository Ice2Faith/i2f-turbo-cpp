#include "mybutton.h"
#include<QDebug>
MyButton::MyButton(QWidget *parent) : QPushButton(parent)
{

}

MyButton::~MyButton()
{
    qDebug() << "自定义按钮析构"; //静态对象，相当于cout
}

