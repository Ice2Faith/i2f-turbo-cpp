#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPainter>
#include<QPaintDevice>
#include<QPixmap>
#include<QImage>
#include<QRgb>
#include<QFileDialog>
#include<QColorDialog>
#include<QMessageBox>
#include<QSlider>
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
    QPixmap map;
    QPixmap bmap;
    bool dispalyFilter;
    QRgb filterC;
    qreal hslH;
    qreal hslS;
    qreal hslL;
    qreal imgCompareValue;
    void ReFilterImage();
    void UpdateBtnFilterColor();
    void DisplayView();
    virtual bool eventFilter(QObject *, QEvent *);
    QPixmap ImageFilter(QPixmap & pmap,int filterColor,qreal hslHue,qreal hslSaturation,qreal hslLightness,qreal imgCompare);
};

#endif // WIDGET_H
