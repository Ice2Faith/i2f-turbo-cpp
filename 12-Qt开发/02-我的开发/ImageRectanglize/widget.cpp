#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("Image Rectangle Dev Ugex");
    this->setAcceptDrops(true);
    ui->widgetDisplayArea->installEventFilter(this);

    ui->checkBoxSelfWH->setChecked(false);

    ui->spinBoxWidth->setRange(2,2080);
    ui->spinBoxWidth->setSingleStep(30);
    ui->spinBoxWidth->setValue(720);
    ui->spinBoxHeight->setRange(2,2080);
    ui->spinBoxHeight->setSingleStep(30);
    ui->spinBoxHeight->setValue(480);

    m_selectRectIndex=0;
    m_isRect=false;
    m_isDisplaySrcImg=true;

    connect(ui->pushButtonLoadImage,&QPushButton::clicked,this,[=]()
    {
        QString filename=QFileDialog::getOpenFileName(this,"请选择图片：");
        if(filename.isEmpty())
        {
            QMessageBox::warning(this,"文件读取错误","未选择图片文件");
            return;
        }
        m_selectRectIndex=0;
        m_isRect=false;
        m_isDisplaySrcImg=true;
        ui->lineEditImageFileName->setText(filename);
        m_srcImg=QPixmap(filename);
        ui->widgetDisplayArea->update();
    });

    connect(ui->pushButtonTransFormPicture,&QPushButton::clicked,this,[=]()
    {
        QMatrix matrix;
        matrix.rotate(90);
        if(m_isDisplaySrcImg)
            m_srcImg= m_srcImg.transformed(matrix);
        else
            m_drtImg=m_drtImg.transformed(matrix);
        ui->widgetDisplayArea->update();
    });

    connect(ui->pushButtonReRectanglise,&QPushButton::clicked,this,[=]()
    {
        m_selectRectIndex=0;
        m_isRect=false;
        m_isDisplaySrcImg=true;
        ui->widgetDisplayArea->update();
    });

    connect(ui->pushButtonApplyRect,&QPushButton::clicked,this,[=]()
    {
        if(!m_isRect)
            return;
        int wid=ui->widgetDisplayArea->width();
        int hei=ui->widgetDisplayArea->height();
        QPoint leftTop(m_rect[0].x()*1.0/wid*m_srcImg.width(),m_rect[0].y()*1.0/hei*m_srcImg.height());
        QPoint leftDown(m_rect[1].x()*1.0/wid*m_srcImg.width(),m_rect[1].y()*1.0/hei*m_srcImg.height());
        QPoint rightDown(m_rect[2].x()*1.0/wid*m_srcImg.width(),m_rect[2].y()*1.0/hei*m_srcImg.height());
        QPoint rightTop(m_rect[3].x()*1.0/wid*m_srcImg.width(),m_rect[3].y()*1.0/hei*m_srcImg.height());
        m_drtImg=GraphRect(m_srcImg,leftTop,leftDown,rightTop,rightDown);
        m_isDisplaySrcImg=false;
        ui->widgetDisplayArea->update();
    });

    connect(ui->pushButtonSaveImage,&QPushButton::clicked,this,[=]()
    {
        QString filename=QFileDialog::getSaveFileName(this,"请选择图片：");
        if(filename.isEmpty())
        {
            QMessageBox::warning(this,"文件保存错误","未选择保存文件");
            return;
        }
        m_drtImg.save(filename);
    });

    connect(ui->pushButtonHelp,&QPushButton::clicked,this,[=]()
    {
        QMessageBox::information(this,"使用帮助",
"选择或拖入图片，依次逆时针选取四个点作为校正定位点，\n\
点击确认选区按钮开始校正\n\
（这四个点建议是：左上角->左下角->右下角->右上角），\n\
（当然只要是逆时针选取都行），\n\
显示图像经过拉伸，非实际尺寸\n\
原图像拉伸至铺满选取窗口（非按比例缩放）\n\
校正后图像为按比例缩放\n\
实际校正后大小为选取大小的外接矩形\n\
请以保存后为准");
    });
}

Widget::~Widget()
{
    delete ui;
}
void Widget::dragEnterEvent(QDragEnterEvent *event)
{
    event->setDropAction(Qt::MoveAction);
    event->accept();
}

void Widget::dropEvent(QDropEvent *event)
{
    QString filename = (event->mimeData())->urls().first().toString();
    filename=filename.mid(8);//  去掉头file:///
    m_selectRectIndex=0;
    m_isRect=false;
    m_isDisplaySrcImg=true;
    ui->lineEditImageFileName->setText(filename);
    m_srcImg=QPixmap(filename);
    ui->widgetDisplayArea->update();
}
bool Widget::eventFilter(QObject * obj, QEvent *e)
{
    if(ui->widgetDisplayArea==obj)
    {
        if(e->type()==QEvent::Paint)
        {
            drawDisplayWiew();
            return true;
        }
        if(m_isDisplaySrcImg && e->type()==QEvent::MouseButtonPress)
        {
            QMouseEvent * me = static_cast<QMouseEvent*>(e);
           if (me->button() == Qt::LeftButton)
           {
               m_rect[m_selectRectIndex]=me->pos();
               m_selectRectIndex++;
               if(m_selectRectIndex==4)
               {
                   m_isRect=true;
                   ui->widgetDisplayArea->update();
               }
               else
                   m_isRect=false;
               m_selectRectIndex%=4;
           }
           if(me->button()==Qt::RightButton)
           {
               m_selectRectIndex=0;
           }
        }
    }
    return QWidget::eventFilter(obj,e);
}
void Widget::drawDisplayWiew()
{
    QPainter painter(ui->widgetDisplayArea);
    int wid=ui->widgetDisplayArea->width();
    int hei=ui->widgetDisplayArea->height();
    QPixmap dmap;
    if(m_isDisplaySrcImg)
        dmap=m_srcImg.scaled(wid,hei,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    else
        dmap=m_drtImg.scaled(wid,hei,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    int dx=(wid-dmap.width())/2;
    int dy=(hei-dmap.height())/2;
    painter.drawPixmap(dx,dy,dmap);
    if(m_isDisplaySrcImg)
    {
        if(m_isRect)
        {
            painter.setPen(QColor::fromRgb(255,0,0));
            m_rect[4]=m_rect[0];
            painter.drawPolyline(m_rect,5);
        }
    }
}

////////////////////////////////////////
double Widget::GetDistance(QPoint p1, QPoint p2)
{
    return sqrt(pow(p2.x() - p1.x(), 2.0) + pow(p2.y() - p1.y(), 2.0));;
}
QPoint Widget::GetLineRatePoint(QPoint sp,QPoint ep,double rate)
{
    int dx = ep.x() - sp.x();
    int dy = ep.y() - sp.y();
    return QPoint(sp.x() + dx*rate,sp.y() + dy*rate);
}
QPixmap Widget::GraphRect(QPixmap & bimg, QPoint leftTop, QPoint leftDown, QPoint rightTop, QPoint rightDown)
{
    QImage srcimg=bimg.toImage();
    int minLeft = leftTop.x() < leftDown.x() ? leftTop.x() : leftDown.x();
    int minTop = leftTop.y() < rightTop.y() ? leftTop.y() : rightTop.y();
    int maxRight = rightTop.x() > rightDown.x() ? rightTop.x() : rightDown.x();
    int maxDown = leftDown.y() > rightDown.y() ? leftDown.y() : rightDown.y();
    int wid = maxRight - minLeft;
    int hei = maxDown - minTop;
    if(ui->checkBoxSelfWH->checkState()==Qt::Checked)
    {
        wid=ui->spinBoxWidth->value();
        hei=ui->spinBoxHeight->value();
    }
    else
    {
        ui->spinBoxHeight->setValue(hei);
        ui->spinBoxWidth->setValue(wid);
    }
    QImage drtimg(wid, hei,QImage::Format_RGB888);

    for (int i = 0; i < hei; i++)
    {
        for (int j = 0; j < wid; j++)
        {
            double ratex = j*1.0 /wid;
            double ratey = i*1.0 / hei;
            QPoint toptp = GetLineRatePoint(leftTop,rightTop,ratex);
            QPoint downtp = GetLineRatePoint(leftDown,rightDown,ratex);
            QPoint target = GetLineRatePoint(toptp,downtp,ratey);

            QColor color=QColor(srcimg.pixel( target.x(), target.y()));
            drtimg.setPixel(j, i,qRgb(color.red(),color.green(),color.blue()) );

        }
    }
    return QPixmap::fromImage(drtimg);
}
