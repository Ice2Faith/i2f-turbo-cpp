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
#include<QDebug>
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
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dropEvent(QDropEvent *event);
    virtual bool eventFilter(QObject * obj, QEvent *e);
    QPixmap  m_srcImg;
    QPixmap m_drtImg;

    void loadImageFile(QString filename);
    void drawDisplayWiew();
    void updateOutputImage();
    QPixmap ImageARGBChannelSift(QPixmap & pmap,
                                         bool redChannel,double redEnhance,
                                         bool greenChannel,double greenEnhance,
                                         bool blueChannel,double blueEnhance,
                                         bool alphaChannel=false,double alphaEnhance=1,
                                         bool toGray=false);
};

#endif // WIDGET_H
