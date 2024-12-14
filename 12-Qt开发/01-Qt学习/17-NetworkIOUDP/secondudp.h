#ifndef SECONDUDP_H
#define SECONDUDP_H

#include <QWidget>
#include<QUdpSocket>
#include<QHostAddress>

namespace Ui {
class SecondUdp;
}

class SecondUdp : public QWidget
{
    Q_OBJECT

public:
    explicit SecondUdp(QWidget *parent = 0);
    ~SecondUdp();

private:
    Ui::SecondUdp *ui;
    QUdpSocket * tarUdp;
};

#endif // SECONDUDP_H
