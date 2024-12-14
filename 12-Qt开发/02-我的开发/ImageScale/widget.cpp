#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("Image Scale Dev Ugex");
    this->setAcceptDrops(true);
    ui->widgetPaintArea->installEventFilter(this);


    ui->spinBoxWidth->setRange(2,40960);
    ui->spinBoxWidth->setSingleStep(30);
    ui->spinBoxWidth->setValue(720);
    ui->spinBoxHeight->setRange(2,40960);
    ui->spinBoxHeight->setSingleStep(30);
    ui->spinBoxHeight->setValue(480);
    ui->checkBoxKeepRate->setChecked(true);
    ui->spinBoxHeight->setEnabled(false);
    ui->spinBoxSmoothLevel->setRange(1,9);
    ui->spinBoxSmoothLevel->setSingleStep(1);
    ui->spinBoxSmoothLevel->setValue(3);
    ui->doubleSpinBoxSmoothRate->setDecimals(3);
    ui->doubleSpinBoxSmoothRate->setRange(0.0,1.0);
    ui->doubleSpinBoxSmoothRate->setSingleStep(0.1);
    ui->doubleSpinBoxSmoothRate->setValue(0.4);

    connect(ui->pushButtonApply,&QPushButton::clicked,this,[=]()
    {
       m_drtImg=ImageScale(m_srcImg,ui->spinBoxWidth->value(),ui->spinBoxHeight->value(),
                           ui->spinBoxSmoothLevel->value(),ui->doubleSpinBoxSmoothRate->value());
       ui->widgetPaintArea->update();
    });

    connect(ui->checkBoxKeepRate,&QCheckBox::clicked,this,[=]()
    {
        if(ui->checkBoxKeepRate->checkState()==Qt::Checked)
            ui->spinBoxHeight->setEnabled(false);
        else
            ui->spinBoxHeight->setEnabled(true);
    });

    connect(ui->spinBoxWidth,static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,[=](int val)
    {
        if(ui->checkBoxKeepRate->checkState()==Qt::Checked)
            ui->spinBoxHeight->setValue(1.0*val/m_srcImg.width()*m_srcImg.height());
    });

    connect(ui->pushButtonOpenImage,&QPushButton::clicked,this,[=]()
    {
        QString filename=QFileDialog::getOpenFileName(this,"请选择图片：");
        if(filename.isEmpty())
        {
            QMessageBox::warning(this,"文件读取错误","未选择图片文件");
            return;
        }

        loadImageFile(filename);
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
    loadImageFile(filename);
}
bool Widget::eventFilter(QObject * obj, QEvent *e)
{
    if(ui->widgetPaintArea==obj)
    {
        if(e->type()==QEvent::Paint)
        {
            drawDisplayWiew();
            return true;
        }

    }
    return QWidget::eventFilter(obj,e);
}
void Widget::loadImageFile(QString filename)
{
    ui->lineEditFileName->setText(filename);
    m_srcImg=QPixmap(filename);
    m_drtImg=m_srcImg;
    ui->widgetPaintArea->update();
}

void Widget::drawDisplayWiew()
{
    ui->spinBoxWidth->setValue(m_drtImg.width());
    ui->spinBoxHeight->setValue(m_drtImg.height());
    if(m_drtImg.isNull())
        return;
    QPainter painter(ui->widgetPaintArea);
    int wid=ui->widgetPaintArea->width();
    int hei=ui->widgetPaintArea->height();
    QPixmap dmap;
    dmap=m_drtImg.scaled(wid,hei,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    int dx=(wid-dmap.width())/2;
    int dy=(hei-dmap.height())/2;
    painter.drawPixmap(dx,dy,dmap);
}
////////////////////////////
QPixmap Widget::ImageScale(QPixmap & pmap,int targetWidth,int targetHeight,int smoothLeavel,double smoothRate)
{
    QImage srcimg=pmap.toImage();
    QImage drtimg(targetWidth,targetHeight,QImage::Format_ARGB32);
    if(smoothLeavel<1)
        smoothLeavel=1;
    if(smoothLeavel>9)
        smoothLeavel=9;
    double befcolorRate=smoothRate-(int)smoothRate;
    double rbefColorRate=1.0-befcolorRate;
    int srcWid=srcimg.width();
    int srcHei=srcimg.height();
    for(int y=0;y<targetHeight;y++)
    {
        double dsrcy=1.0*y/targetHeight*srcHei;
        int isrcy=(int)dsrcy;
        double ratey=dsrcy-isrcy;
        double rratey=1.0-ratey;
        int nisrcy=isrcy+1;
        bool nisrcyOut=nisrcy>=srcHei;
        int bdrty=y-1;
        bool bdrtyOut=bdrty<0;
        for(int x=0;x<targetWidth;x++)
        {
            double dsrcx=1.0*x/targetWidth*srcWid;
            int isrcx=(int)dsrcx;
            double ratex=dsrcx-isrcx;
            double rratex=1.0-ratex;
            int nisrcx=isrcx+1;
            bool nisrcxOut=nisrcx>=srcWid;
            int bdrtx=x-1;
            bool bdrtxOut=bdrtx<0;

            QColor pcenter=QColor(srcimg.pixel(isrcx,isrcy));
            int pcenterR=pcenter.red();
            int pcenterG=pcenter.green();
            int pcenterB=pcenter.blue();
            int pcenterA=pcenter.alpha();

            int red=pcenterR;
            int green=pcenterG;
            int blue=pcenterB;
            int alpha=pcenterA;

            double pcount=1;
            if(smoothLeavel>=2)
            {
                if(!nisrcxOut)
                {
                    QColor pright=QColor(srcimg.pixel(nisrcx,isrcy));
                    red+=pcenterR*rratex+pright.red()*ratex;
                    green+=pcenterG*rratex+pright.green()*ratex;
                    blue+=pcenterB*rratex+pright.blue()*ratex;
                    alpha+=pcenterA*rratex+pright.alpha()*ratex;
                    pcount++;
                }
            }
            if(smoothLeavel>=3)
            {
                if(!nisrcyOut)
                {
                    QColor pdown=QColor(srcimg.pixel(isrcx,nisrcy));
                    red+=pcenterR*rratey+pdown.red()*ratey;
                    green+=pcenterG*rratey+pdown.green()*ratey;
                    blue+=pcenterB*rratey+pdown.blue()*ratey;
                    alpha+=pcenterA*rratey+pdown.alpha()*ratey;
                    pcount++;
                }
            }
            if(smoothLeavel>=4)
            {
                if(!nisrcxOut && !nisrcyOut)
                {
                    double avgratexy=(ratex+ratey)/2;
                    double ravgratexy=1.0-avgratexy;
                    QColor prightdown=QColor(srcimg.pixel(nisrcx,nisrcy));
                    red+=pcenterR*ravgratexy+prightdown.red()*avgratexy;
                    green+=pcenterG*ravgratexy+prightdown.green()*avgratexy;
                    blue+=pcenterB*ravgratexy+prightdown.blue()*avgratexy;
                    alpha+=pcenterA*ravgratexy+prightdown.alpha()*avgratexy;
                    pcount++;
                }
            }
            if(smoothLeavel>=5)
            {
                if(!bdrtxOut)
                {
                    QColor eleft=QColor(drtimg.pixel(bdrtx,y));
                    red+=pcenterR*rbefColorRate+eleft.red()*befcolorRate;
                    green+=pcenterG*rbefColorRate+eleft.green()*befcolorRate;
                    blue+=pcenterB*rbefColorRate+eleft.blue()*befcolorRate;
                    alpha+=pcenterA*rbefColorRate+eleft.alpha()*befcolorRate;
                    pcount++;
                }
            }
            if(smoothLeavel>=6)
            {
                if(!bdrtyOut)
                {
                    QColor eup=QColor(drtimg.pixel(x,bdrty));
                    red+=pcenterR*rbefColorRate+eup.red()*befcolorRate;
                    green+=pcenterG*rbefColorRate+eup.green()*befcolorRate;
                    blue+=pcenterB*rbefColorRate+eup.blue()*befcolorRate;
                    alpha+=pcenterA*rbefColorRate+eup.alpha()*befcolorRate;
                    pcount++;
                }
            }
            if(smoothLeavel>=7)
            {
                if(!bdrtxOut && !bdrtyOut)
                {
                    QColor eleftup=QColor(drtimg.pixel(bdrtx,bdrty));
                    red+=pcenterR*rbefColorRate+eleftup.red()*befcolorRate;
                    green+=pcenterG*rbefColorRate+eleftup.green()*befcolorRate;
                    blue+=pcenterB*rbefColorRate+eleftup.blue()*befcolorRate;
                    alpha+=pcenterA*rbefColorRate+eleftup.alpha()*befcolorRate;
                    pcount++;
                }
            }

            if(smoothLeavel>=8)
            {
                if(!bdrtyOut && !nisrcxOut)
                {
                    QColor erightup=QColor(drtimg.pixel(x+1,bdrty));
                    red+=pcenterR*rbefColorRate+erightup.red()*befcolorRate;
                    green+=pcenterG*rbefColorRate+erightup.green()*befcolorRate;
                    blue+=pcenterB*rbefColorRate+erightup.blue()*befcolorRate;
                    alpha+=pcenterA*rbefColorRate+erightup.alpha()*befcolorRate;
                    pcount++;
                }
            }
            if(smoothLeavel>=9)
            {
                if(isrcx-1>=0 && !nisrcyOut)
                {
                    QColor eleftdown=QColor(srcimg.pixel(isrcx-1,nisrcy));
                    red+=pcenterR*rbefColorRate+eleftdown.red()*befcolorRate;
                    green+=pcenterG*rbefColorRate+eleftdown.green()*befcolorRate;
                    blue+=pcenterB*rbefColorRate+eleftdown.blue()*befcolorRate;
                    alpha+=pcenterA*rbefColorRate+eleftdown.alpha()*befcolorRate;
                    pcount++;
                }
            }

            red=red/pcount;
            green=green/pcount;
            blue=blue/pcount;
            alpha=alpha/pcount;
            drtimg.setPixel(x,y,qRgba(red,green,blue,alpha));
        }
    }
    return QPixmap::fromImage(drtimg);
}
