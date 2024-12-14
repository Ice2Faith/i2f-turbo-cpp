#include "widget.h"
#include "ui_widget.h"
#include<QFileDialog>
#include<QMessageBox>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("MapBlanket dev Ugex");
    ui->widgetPaintArea->installEventFilter(this);
    ui->spinBoxMainLevel->setValue(5);
    connect(ui->pushButtonRePaint,&QPushButton::clicked,this,[=](){
        PaintNewMapBlanket();
        ui->widgetPaintArea->update();
    });
    connect(ui->pushButtonSave,&QPushButton::clicked,this,[=]{
        QString filename=QFileDialog::getSaveFileName(this,"请输入保存图片的文件名");
        if(filename.isEmpty())
        {
            QMessageBox::warning(this,"Warnning","not select file,operate cancel.");
            return;
        }
        map.save(filename,"PNG");
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::PaintNewMapBlanket()
{
    int wid=ui->widgetPaintArea->width();
    int hei=ui->widgetPaintArea->height();
    map=QPixmap(wid,hei);
    map.fill();
    QPainter painter(&map);
    QRect rect(0,0,wid,hei);
    MapBlanket(&painter,rect,QColor(255,125,0),ui->spinBoxMainLevel->value());
}

void Widget::DrawMapBlanket()
{
    QPainter rpainter(ui->widgetPaintArea);
    rpainter.drawPixmap(0,0,map);
}

bool Widget::eventFilter(QObject * obj, QEvent * e)
{
    if(ui->widgetPaintArea==obj && e->type()==QEvent::Show)
    {
        PaintNewMapBlanket();
    }
    if(ui->widgetPaintArea==obj && e->type()==QEvent::Paint)
    {
        DrawMapBlanket();
        return true;
    }
    return QWidget::eventFilter(obj,e);
}

void Widget::MapBlanket(QPainter * painter,QRect rect,QColor color,int level)
{
    QBrush brush(color);
    painter->setBrush(brush);
    QPen pen(color);
    painter->setPen(pen);
    painter->drawRect(rect);
    QBrush bgbrush(QColor(255,255,255));
    painter->setBrush(bgbrush);
    MapBlanketNext(painter,rect,level-1);
}

void Widget::MapBlanketNext(QPainter * painter,QRect rect,int level)
{
    if(level==0)
    {
        return;
    }
    int wid=rect.width()/3;
    int hei=rect.height()/3;
    QRect prect(rect.left()+wid,rect.top()+hei,wid,hei);
    painter->drawRect(prect);

    QRect tlrect(rect.left(),rect.top(),wid,hei);
    MapBlanketNext(painter,tlrect,level-1);

    QRect tcrect(rect.left()+wid,rect.top(),wid,hei);
    MapBlanketNext(painter,tcrect,level-1);

    QRect trrect(rect.left()+2*wid,rect.top(),wid,hei);
    MapBlanketNext(painter,trrect,level-1);

    QRect clrect(rect.left(),rect.top()+hei,wid,hei);
    MapBlanketNext(painter,clrect,level-1);

    QRect crrect(rect.left()+2*wid,rect.top()+hei,wid,hei);
    MapBlanketNext(painter,crrect,level-1);

    QRect blrect(rect.left(),rect.top()+2*hei,wid,hei);
    MapBlanketNext(painter,blrect,level-1);

    QRect bcrect(rect.left()+wid,rect.top()+2*hei,wid,hei);
    MapBlanketNext(painter,bcrect,level-1);

    QRect brrect(rect.left()+2*wid,rect.top()+2*hei,wid,hei);
    MapBlanketNext(painter,brrect,level-1);

}
