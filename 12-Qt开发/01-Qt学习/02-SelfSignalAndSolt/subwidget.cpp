#include "subwidget.h"
#include"widget.h"
SubWidget::SubWidget(QWidget *parent) : QWidget(parent)
{
    m_btn=new QPushButton("返回主界面",this);
    this->resize(480,320);
    this->setWindowTitle("子窗口");
    //使用自定义信号（通知主窗口）
    connect(m_btn,&QPushButton::clicked,this,&SubWidget::ClickBtn);
}
void SubWidget::ClickBtn()
{
    //发送信号
    emit hideSelfV();
    emit hideSelfV("你好");
}

SubWidget::~SubWidget()
{

}

