#ifndef MYWORK_H
#define MYWORK_H

#include <QObject>
#include<QThread>
class MyWork : public QObject
{
    Q_OBJECT
public:
    explicit MyWork(QObject *parent = 0);
    ~MyWork();

signals:
    void ProcessDown();//工作完成信号
public slots:
    void DoWork();//开始工作槽函数
    void SetStopFlag(bool flag);//设置工作状态槽函数
private:
    bool isStop;
};

#endif // MYWORK_H
