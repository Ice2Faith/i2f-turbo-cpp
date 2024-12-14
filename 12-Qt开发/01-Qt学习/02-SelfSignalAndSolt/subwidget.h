#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QWidget>
#include<QPushButton>
class SubWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SubWidget(QWidget *parent = 0);
    ~SubWidget();

signals:
    //自定义信号
    void hideSelfV();
    //重载信号槽
    void hideSelfV(QString str);
public slots:

private:
    QPushButton * m_btn;
    void ClickBtn();
};

#endif // SUBWIDGET_H
