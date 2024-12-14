#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPushButton>
#include"subwidget.h"
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private:
    QPushButton * m_btn;
    void ReleaseBtn();
    void PressBtn();
    QPushButton * m_btnTo;
    SubWidget subw;
    void ClickSwitch();
public slots:
      void AntiSwitch();
      void AntiSwitch2(QString str);
};

#endif // WIDGET_H
