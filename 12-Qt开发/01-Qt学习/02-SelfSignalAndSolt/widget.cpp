#include "widget.h"
#include<QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("主界面");
    m_btn=new QPushButton("自定义",this);
    //QT5 版本的信号和槽
    //使用自定义槽函数
    /*
     * 槽函数在QT5中可以是成员，全局，静态，Lambda表达式
     * 需要跟信号函数原型对应，返回值和参数列表都要一致
     * 信号没有返回值，所以返回值为void
     * 参数列表不能多，可以少，可以重载
     */
    connect(m_btn,&QPushButton::pressed,this,&Widget::PressBtn);
    connect(m_btn,&QPushButton::released,this,&Widget::ReleaseBtn);
    //使用自定义信号(SubWidget中)-实现窗口的切换
    m_btnTo=new QPushButton("进入子窗口",this);
    m_btnTo->move(100,100);
    connect(m_btnTo,&QPushButton::clicked,this,&Widget::ClickSwitch);

    //使用重载信号时，需要区分函数原型，使用函数指针解决
    //注意头文件的互相递归包含会引发错误
    void (SubWidget::*funcb)()=&SubWidget::hideSelfV;
    connect(&subw,funcb,this,&Widget::AntiSwitch);

    void (SubWidget::*func)(QString)=&SubWidget::hideSelfV;
    connect(&subw,func,this,&Widget::AntiSwitch2);

    //QT4的信号槽方式
    //connect(subw,SIGNAL(clicked()),this,SOLT(ClickSwitch()));
    //connect(subw,SIGNAL(clicked(QString)),this,SOLT(ClickSwitch(QString)));
    /*两个宏将函数转换为字符串预处理,自动去对应的类里面找，因此不用加类作用域
        QT5废弃的原因：不会去检查重载函数是否存在，不进行错误处理，不报错
    */
    /*
    信号可以和信号连接
    一个信号可以和多个槽连接
    多个信号可以连接一个槽函数
    槽函数可以使用Lambda表达式
    */
}
 void Widget::ClickSwitch()
 {
     this->hide();
     subw.show();
 }
 void Widget::AntiSwitch()
{
     this->show();
     subw.hide();
}
void Widget::AntiSwitch2(QString str)
{
    //QString转换为char *
    //str.toUtf8().data();
    //string转换为char *
    //std::string cstr;
    //cstr.data();
    qDebug() << str;
}

void Widget::ReleaseBtn()
{
    m_btn->setText("自定义");
}
void Widget::PressBtn()
{
    m_btn->setText("按下");
}
Widget::~Widget()
{

}
