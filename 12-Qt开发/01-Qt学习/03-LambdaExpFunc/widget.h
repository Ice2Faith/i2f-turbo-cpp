#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPushButton>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private:
    QPushButton * m_btn;
};

#endif // WIDGET_H
