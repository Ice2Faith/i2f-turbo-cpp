#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
//绘图头文件
#include<QPainter>
#include<QPaintEvent>
#include<QPaintDevice>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
protected:
    //绘图需要重载绘图响应虚函数，类似OnDraw
    virtual void paintEvent(QPaintEvent *);
    int px,py;
private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
