#ifndef MYLABLE_H
#define MYLABLE_H

#include <QLabel>
#include<QMouseEvent>
#include<QEvent>
#include<QTimerEvent>
class MyLable : public QLabel
{
    Q_OBJECT
public:
    explicit MyLable(QWidget *parent = 0);
    ~MyLable();

signals:

public slots:

protected://事件函数，重载，仅以鼠标事件为例

    virtual void enterEvent(QEvent *);//鼠标进入
    virtual void leaveEvent(QEvent *);//鼠标离开
    virtual void mouseReleaseEvent(QMouseEvent *);//鼠标释放
    virtual void mouseMoveEvent(QMouseEvent *);//鼠标移动
    virtual void timerEvent(QTimerEvent *);//定时器
    //定时器ID保存
    int ID_TM_CLASS1;
    int ID_TM_CLASS2;
};

#endif // MYLABLE_H
