#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPainter>
#include<QPaintEvent>
#include<math.h>
#include<time.h>
#include<QPaintDevice>
#include<QPixmap>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
protected:
    bool eventFilter(QObject *, QEvent *);
    QPixmap map;
    void PaintNewSpaceInSpace();
    void DrawSpaceInSpace();
    void SpaceInSpace(QPainter * painter,QRect rect,QColor color,double rate,int level);
    void SpaceInSpaceNext(QPainter * painter,QRect rect,double rate,int level);
};

#endif // WIDGET_H
