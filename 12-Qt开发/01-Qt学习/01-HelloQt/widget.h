#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
// QT类习惯，Q开头,没有.h
#include<QPushButton>
//QWidget 所有窗口类的父类
class Widget : public QWidget
{
    //宏，如果使用信号槽就必须添加，类似消息映射宏
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private:
    QPushButton m_btn;
    QPushButton * mp_btn;
};

#endif // WIDGET_H
