#include "mythread.h"

MyThread::MyThread(QObject *parent) : QThread(parent)
{

}

MyThread::~MyThread()
{

}

void MyThread::run()
{
    //模拟操作
    sleep(5);
    //操作完成之后发送一个信号
    emit ProcessDone();
}
