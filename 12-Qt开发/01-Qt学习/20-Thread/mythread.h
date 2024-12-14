#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);
    ~MyThread();

signals:
    void ProcessDone();
public slots:

protected:
    virtual void run();//入口函数，使用start()启动
};

#endif // MYTHREAD_H
