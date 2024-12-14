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
    ui->spinBoxMainLevel->setValue(20);
    ui->spinBoxMainRate->setValue(80);
    connect(ui->pushButtonRePaint,&QPushButton::clicked,this,[=](){
        PaintNewSpaceInSpace();
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

void Widget::PaintNewSpaceInSpace()
{
    int wid=ui->widgetPaintArea->width();
    int hei=ui->widgetPaintArea->height();
    map=QPixmap(wid,hei);
    map.fill();
    QPainter painter(&map);
    QRect rect(0,0,wid,hei);
    SpaceInSpace(&painter,rect,QColor(255,125,0),(ui->spinBoxMainRate->value())/100.0,ui->spinBoxMainLevel->value());
}

void Widget::DrawSpaceInSpace()
{
    QPainter rpainter(ui->widgetPaintArea);
    rpainter.drawPixmap(0,0,map);
}

bool Widget::eventFilter(QObject * obj, QEvent * e)
{
    if(ui->widgetPaintArea==obj && e->type()==QEvent::Show)
    {
        PaintNewSpaceInSpace();
    }
    if(ui->widgetPaintArea==obj && e->type()==QEvent::Paint)
    {
        DrawSpaceInSpace();
        return true;
    }
    return QWidget::eventFilter(obj,e);
}

void Widget::SpaceInSpace(QPainter * painter,QRect rect,QColor color,double rate,int level)
{
    QPen pen(color);
    painter->setPen(pen);
    painter->drawRect(rect);
    SpaceInSpaceNext(painter,rect,rate,level-1);
}

void Widget::SpaceInSpaceNext(QPainter * painter,QRect rect,double rate,int level)
{
    if(level==0)
    {
        return;
    }
    double nrate=1.0-rate;
    QRect prect(rect.left()+rect.width()*nrate/2,rect.top()+rect.height()*nrate/2,rect.width()*rate,rect.height()*rate);

    painter->drawRect(prect);
    SpaceInSpaceNext(painter,prect,rate,level-1);
}
