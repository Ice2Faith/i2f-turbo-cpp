#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QBitmap>
#include<QImage>
#include<QPainter>
#include<QMouseEvent>
#include<QFileDialog>
#include<QMessageBox>
#include<QPaintDevice>
#include<math.h>
#include<QMimeData>
#include<QMessageBox>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
protected:
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dropEvent(QDropEvent *event);
    virtual bool eventFilter(QObject * obj, QEvent *e);
    QPixmap  m_srcImg;
    QPixmap m_drtImg;
    QPoint m_rect[5];
    bool m_isRect;
    bool m_isDisplaySrcImg;
    int m_selectRectIndex;
    void drawDisplayWiew();
    QPixmap GraphRect(QPixmap & bimg, QPoint leftTop, QPoint leftDown, QPoint rightTop, QPoint rightDown);
    double GetDistance(QPoint p1, QPoint p2);
    QPoint GetLineRatePoint(QPoint sp,QPoint ep,double rate);

private:
    Ui::Widget *ui;

};

#endif // WIDGET_H
