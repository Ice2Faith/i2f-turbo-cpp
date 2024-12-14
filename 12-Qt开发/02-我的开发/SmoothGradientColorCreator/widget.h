#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QImage>
#include<QPainter>
#include<QFileDialog>
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
    virtual bool eventFilter(QObject * obj, QEvent *e);
    QImage m_drtImg;

    void drawDisplayWiew();

    QImage SmoothGradientColorToColor(QColor beginColor, QColor endColor,int sizeWidth,int sizeHeight);
};

#endif // WIDGET_H
