#ifndef QTHREADCASETWO_H
#define QTHREADCASETWO_H

#include <QWidget>
#include<QTimer>
#include<QThread>
#include"mywork.h"
namespace Ui {
class QThreadCaseTwo;
}

class QThreadCaseTwo : public QWidget
{
    Q_OBJECT

public:
    explicit QThreadCaseTwo(QWidget *parent = 0);
    ~QThreadCaseTwo();
public slots:
    void ClickStart();
    void ClickEnd();
    void TimerOn();
    void CloseThread();
signals:
    void DoWork();
private:
    Ui::QThreadCaseTwo *ui;
    QTimer * timer;
    QThread * pthread;
    MyWork * work;
};

#endif // QTHREADCASETWO_H
