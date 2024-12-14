#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("Image Filter dev Ugex");
    dispalyFilter=true;
    ui->widgetPaintArea->installEventFilter(this);
    filterC=0;
    ui->checkBoxUseFilterColor->setChecked(false);
    hslH=0;
    hslS=0;
    hslL=0;
    ui->SliderHslHue->setRange(-1000,1000);
    ui->SliderHslSaturation->setRange(-1000,1000);
    ui->SliderHslLightness->setRange(-1000,1000);
    ui->SliderHslHue->setValue(0);
    ui->SliderHslSaturation->setValue(0);
    ui->SliderHslLightness->setValue(0);
    imgCompareValue=0;
    ui->SliderImgCompare->setRange(-1000,1000);
    ui->SliderImgCompare->setValue(0);
    ui->checkBoxAtTimeUpdate->setChecked(false);

    UpdateBtnFilterColor();

    connect(ui->pushButtonReadFile,&QPushButton::clicked,this,[=](){
          QString filename=QFileDialog::getOpenFileName(this,"请选择图片：");
          if(filename.isEmpty())
          {
              QMessageBox::warning(this,"文件读取错误","未选择图片文件");
              return;
          }
          ui->lineEditFileName->setText(filename);
          map=QPixmap(filename);
          ReFilterImage();
    });

    connect(ui->pushButtonSaveFile,&QPushButton::clicked,this,[=](){
        QString filename=QFileDialog::getSaveFileName(this,"请选择图片：");
        if(filename.isEmpty())
        {
            QMessageBox::warning(this,"文件保存错误","未选择保存文件");
            return;
        }
        bmap.save(filename);
    });
    connect(ui->pushButtonSelectFilterColor,&QPushButton::clicked,this,[=](){
        QColor  pc=QColorDialog::getColor(filterC,this,"请选择滤镜颜色");
        if(!pc.isValid())
        {
            return;
        }
        filterC=pc.rgba();
        UpdateBtnFilterColor();
        ReFilterImage();
        if(dispalyFilter)
            ui->widgetPaintArea->update();
    });
    connect(ui->pushButtonCompare,&QPushButton::clicked,this,[=](){
        dispalyFilter=!dispalyFilter;
        ui->widgetPaintArea->update();
    });
    connect(ui->pushButtonApply,&QPushButton::clicked,this,[=](){
        ReFilterImage();
        ui->widgetPaintArea->update();
    });
    connect(ui->SliderHslHue,&QSlider::valueChanged,this,[=](int value)
    {
        hslH=value/1000.0;
        if(ui->checkBoxAtTimeUpdate->isChecked()){
            ReFilterImage();
            if(dispalyFilter)
                ui->widgetPaintArea->update();
        }
    });
    connect(ui->SliderHslSaturation,&QSlider::valueChanged,this,[=](int value)
    {
        hslS=value/1000.0;
        if(ui->checkBoxAtTimeUpdate->isChecked()){
            ReFilterImage();
            if(dispalyFilter)
                ui->widgetPaintArea->update();
        }
    });
    connect(ui->SliderHslLightness,&QSlider::valueChanged,this,[=](int value)
    {
        hslL=value/1000.0;
        if(ui->checkBoxAtTimeUpdate->isChecked()){
            ReFilterImage();
            if(dispalyFilter)
                ui->widgetPaintArea->update();
        }
    });
    connect(ui->SliderImgCompare,&QSlider::valueChanged,this,[=](int value)
    {
        imgCompareValue=value/1000.0;
        if(ui->checkBoxAtTimeUpdate->isChecked()){
            ReFilterImage();
            if(dispalyFilter)
                ui->widgetPaintArea->update();
        }
    });
    connect(ui->pushButtonResetArgs,&QPushButton::clicked,this,[=]()
    {
        hslH=0;
        hslS=0;
        hslL=0;
        filterC=0;
        imgCompareValue=0;
        ui->SliderHslHue->setValue(0);
        ui->SliderHslSaturation->setValue(0);
        ui->SliderHslLightness->setValue(0);
        ui->SliderImgCompare->setValue(0);
        UpdateBtnFilterColor();
        ReFilterImage();
        if(dispalyFilter)
            ui->widgetPaintArea->update();
    });
}

Widget::~Widget()
{
    delete ui;
}
void Widget::ReFilterImage()
{
    bmap=ImageFilter(map,filterC,hslH,hslS,hslL,imgCompareValue);
}

void Widget::UpdateBtnFilterColor()
{
    QPalette flterpal = ui->pushButtonSelectFilterColor->palette();
   flterpal.setColor(QPalette::Button,filterC);
   ui->pushButtonSelectFilterColor->setPalette(flterpal);
   ui->pushButtonSelectFilterColor->setAutoFillBackground(true);
   ui->pushButtonSelectFilterColor->setFlat(true);
}

void Widget::DisplayView()
{
    QPainter painter(ui->widgetPaintArea);
    int wid=ui->widgetPaintArea->width();
    int hei=ui->widgetPaintArea->height();
    QPixmap dmap;
    if(dispalyFilter)
        dmap=bmap.scaled(wid,hei,Qt::KeepAspectRatio);
    else
        dmap=map.scaled(wid,hei,Qt::KeepAspectRatio);
    int dx=(wid-dmap.width())/2;
    int dy=(hei-dmap.height())/2;
    painter.drawPixmap(dx,dy,dmap);
}

bool Widget::eventFilter(QObject * obj, QEvent *e)
{
    if(ui->widgetPaintArea==obj)
    {
        if(e->type()==QEvent::Paint)
        {
            DisplayView();
            return true;
        }
    }
    return QWidget::eventFilter(obj,e);
}

QPixmap Widget::ImageFilter(QPixmap & pmap,int filterColor,qreal hslHue,qreal hslSaturation,qreal hslLightness,qreal imgCompare)
{
    QImage img=pmap.toImage();

    int width=img.width();
    int height=img.height();
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            QColor currentColor = QColor(img.pixel(col ,row));
            qreal h=currentColor.hslHueF()+hslHue;
            qreal s=currentColor.hslSaturationF()+hslSaturation;
            qreal l=currentColor.lightnessF()+hslLightness;
            h = h<0?0:(h>1.0?1.0:h);
            s = s<0?0:(s>1.0?1.0:s);
            l = l<0?0:(l>1.0?1.0:l);
            currentColor.setHslF(h,s,l);
            QRgb newColor=filterColor|currentColor.rgba();

            int value=qGray(newColor);
            int dert=128*imgCompare;
            if(value<128){
                dert=0-dert;
            }
            int red=qRed(newColor)+dert;
            int green=qGreen(newColor)+dert;
            int blue=qBlue(newColor)+dert;
            int alpha=qAlpha(newColor)+dert;
            red=red<0?0:(red>255?255:red);
            green=green<0?0:(green>255?255:green);
            blue=blue<0?0:(blue>255?255:blue);
            alpha=alpha<0?0:(alpha>255?255:alpha);

            newColor=qRgba(red,green,blue,alpha);
            img.setPixel(col,row,newColor);

        }
    }

    return QPixmap::fromImage(img);
}
