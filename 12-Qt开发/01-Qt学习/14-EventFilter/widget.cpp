#include "widget.h"
#include "ui_widget.h"
#include<QDesktopWidget>
#include<QMessageBox>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    /*
    frameGeometry().topLeft().x();
    获取窗口边框属性，长宽，点坐标等

    QDesktopWidget * wid=QApplication::desktop();
    wid->screenGeometry().top();
    获取桌面窗口，然后即可获取相关信息
    */

    ui->setupUi(this);

    //给控件安装事件过滤器,用自己来给自己做过滤
    ui->label->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}
//事件分发器函数
//返回值为true代表事件被处理过了，不继续向下分发
//为false未被处理，继续向下分发，采用默认处理
bool Widget::event(QEvent * e)
{
    switch(e->type())
    {
    case QEvent::Close:
        QMessageBox::warning(this,"Warnning","window will close");
        break;
    case QEvent::Leave:
        QMessageBox::information(this,"Info","msg leave");

        break;
    case QEvent::MouseButtonPress:
        QMessageBox::information(this,"Info","msg click");

        break;
    default:
        return QWidget::event(e);
    }
    return true;
}
//事件过滤器函数
bool Widget::eventFilter(QObject * obj, QEvent * e)
{
    //判断过滤器
    if(obj==ui->label)
    {
        //过滤事件
        switch(e->type())
        {
        case QEvent::Leave:
           // QMessageBox::information(this,"Info","msg leave");

            break;
        case QEvent::MouseButtonPress:
          //  QMessageBox::information(this,"Info","msg click");

            break;
        default:
            return QWidget::eventFilter(obj,e);
        }
        return true;
    }
}
