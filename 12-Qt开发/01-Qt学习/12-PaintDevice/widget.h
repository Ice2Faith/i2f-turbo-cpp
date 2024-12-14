#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
/*
QPixmap QImage QPicture全彩色
QBitmap只是黑白色，父类是QPixmap
QPixmap 针对平台做出了优化，保证显示效果效率
QImage 可以在多线程中使用
*/
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
};

#endif // WIDGET_H
