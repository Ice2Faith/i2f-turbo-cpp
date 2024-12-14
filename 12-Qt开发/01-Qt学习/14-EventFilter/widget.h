#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
protected:
    //事件分发器，重载事件分发，进行事件的过滤拦截操作
   virtual bool event(QEvent *);
    //事件过滤器
   virtual bool eventFilter(QObject *, QEvent *);
};

#endif // WIDGET_H
