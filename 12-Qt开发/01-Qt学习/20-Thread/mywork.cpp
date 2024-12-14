#include "mywork.h"

MyWork::MyWork(QObject *parent) : QObject(parent)
{
    isStop=false;
}

MyWork::~MyWork()
{

}
void MyWork::DoWork()
{
    while(isStop==false)
    {
        QThread::sleep(5);

    }
    emit ProcessDown();
}

void MyWork::SetStopFlag(bool flag)
{
    isStop=flag;
}

