#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPainter>
#include<QPaintDevice>
#include<QPixmap>
#include<QImage>
#include<QFileDialog>
#include<QColorDialog>
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

private:
    Ui::Widget *ui;

protected:
    QPixmap map;
    QPixmap bmap;
    bool dispalyBorder;
    QColor borderC;
    QColor backC;
    void ReBorderImage();
    void UpdateBtnBackColor();
    double DoubleAbs(double num);
    void DisplayView();
    virtual bool eventFilter(QObject *, QEvent *);
    QPixmap ImageBorder(QPixmap & pmap,double allowRate,bool useBorderColor=true,bool useBackColor=true,QColor borderColor=QColor(40,40,40),QColor backColor=QColor(255,255,255));
};

#endif // WIDGET_H
