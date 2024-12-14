#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QTcpServer>//需要添加模块
#include<QTcpSocket>
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

    QTcpServer * server;//监听
    QTcpSocket * sock;//通信
};

#endif // WIDGET_H
