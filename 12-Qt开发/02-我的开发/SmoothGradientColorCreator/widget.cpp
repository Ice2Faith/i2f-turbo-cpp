#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("Smooth Gradient Color Creator Dev Ugex");
    ui->widgetPaintArea->installEventFilter(this);

    QSpinBox * rgbArrSPB[]={ui->spinBoxBGA,ui->spinBoxBGB,ui->spinBoxBGG,ui->spinBoxBGR,
                            ui->spinBoxEDA,ui->spinBoxEDB,ui->spinBoxEDG,ui->spinBoxEDR};
    QSpinBox * szArrSPB[]={ui->spinBoxSZW,ui->spinBoxSZH};
    for(int i=0;i<8;i++)
    {
        if(i<2)
        {
            szArrSPB[i]->setRange(1,4096);
            szArrSPB[i]->setSingleStep(100);
            szArrSPB[i]->setValue(720);
            connect(szArrSPB[i],static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,[=]
            {
                QColor bcolor=QColor(qRgba(ui->spinBoxBGR->value(),ui->spinBoxBGG->value(),ui->spinBoxBGB->value(),ui->spinBoxBGA->value()));
                QColor ecolor=QColor(qRgba(ui->spinBoxEDR->value(),ui->spinBoxEDG->value(),ui->spinBoxEDB->value(),ui->spinBoxEDA->value()));
                m_drtImg=SmoothGradientColorToColor(bcolor,ecolor,ui->spinBoxSZW->value(),ui->spinBoxSZH->value());
                ui->widgetPaintArea->update();
            });
        }
        rgbArrSPB[i]->setRange(0,255);
        rgbArrSPB[i]->setSingleStep(10);
        rgbArrSPB[i]->setValue(0);
        connect(rgbArrSPB[i],static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,[=]
        {
            QColor bcolor=QColor(qRgba(ui->spinBoxBGR->value(),ui->spinBoxBGG->value(),ui->spinBoxBGB->value(),ui->spinBoxBGA->value()));
            QColor ecolor=QColor(qRgba(ui->spinBoxEDR->value(),ui->spinBoxEDG->value(),ui->spinBoxEDB->value(),ui->spinBoxEDA->value()));
            m_drtImg=SmoothGradientColorToColor(bcolor,ecolor,ui->spinBoxSZW->value(),ui->spinBoxSZH->value());
            ui->widgetPaintArea->update();
        });
    }
    ui->spinBoxSZH->setValue(240);
    ui->spinBoxBGB->setValue(255);
    ui->spinBoxEDG->setValue(255);
    ui->spinBoxBGA->setValue(255);
    ui->spinBoxEDA->setValue(255);
     m_drtImg=SmoothGradientColorToColor(QColor(qRgba(0,0,255,255)),QColor(qRgba(0,255,0,255)),720,240);

    connect(ui->pushButtonApply,&QPushButton::clicked,this,[=]()
    {
        QColor bcolor=QColor(qRgba(ui->spinBoxBGR->value(),ui->spinBoxBGG->value(),ui->spinBoxBGB->value(),ui->spinBoxBGA->value()));
        QColor ecolor=QColor(qRgba(ui->spinBoxEDR->value(),ui->spinBoxEDG->value(),ui->spinBoxEDB->value(),ui->spinBoxEDA->value()));
        m_drtImg=SmoothGradientColorToColor(bcolor,ecolor,ui->spinBoxSZW->value(),ui->spinBoxSZH->value());
        ui->widgetPaintArea->update();
    });

    connect(ui->pushButtonSave,&QPushButton::clicked,this,[=]()
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

void Widget::drawDisplayWiew()
{
    if(m_drtImg.isNull())
        return;
    QPainter painter(ui->widgetPaintArea);
    int wid=ui->widgetPaintArea->width();
    int hei=ui->widgetPaintArea->height();
    QImage dmap;
    dmap=m_drtImg.scaled(wid,hei,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    int dx=(wid-dmap.width())/2;
    int dy=(hei-dmap.height())/2;
    painter.drawImage(dx,dy,dmap);
}
QImage Widget::SmoothGradientColorToColor(QColor beginColor, QColor endColor,int sizeWidth,int sizeHeight)
{
    int br = beginColor.red();
    int bg = beginColor.green();
    int bb = beginColor.blue();
    int ba=beginColor.alpha();
    int er = endColor.red();
    int eg = endColor.green();
    int eb = endColor.blue();
    int ea=endColor.alpha();

    int dr = er - br;
    int dg = eg - bg;
    int db = eb - bb;
    int da = ea - ba;


    QImage img(sizeWidth,sizeHeight,QImage::Format_RGBA8888_Premultiplied);

    for (int i = 0; i < sizeWidth; i++)
    {
        int red = i*1.0 / sizeWidth*dr + br;
        int green = i*1.0 / sizeWidth*dg + bg;
        int blue = i*1.0 / sizeWidth*db + bb;
        int alpha = i*1.0 / sizeWidth*da + ba;

        QRgb color=qRgba(red,green,blue,alpha);
        for(int j=0;j<sizeHeight;j++)
        {
            img.setPixel(i,j,color);
        }
    }
    return img;
}
