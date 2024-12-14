#ifndef QTHREADUSECASE_H
#define QTHREADUSECASE_H

#include <QWidget>
#include<QTimer>
#include"mythread.h"
namespace Ui {
class QThreadUseCase;
}

class QThreadUseCase : public QWidget
{
    Q_OBJECT

public:
    explicit QThreadUseCase(QWidget *parent = 0);
    ~QThreadUseCase();

private:
    Ui::QThreadUseCase *ui;
    MyThread * mythread;
    QTimer * timer;
};

#endif // QTHREADUSECASE_H
