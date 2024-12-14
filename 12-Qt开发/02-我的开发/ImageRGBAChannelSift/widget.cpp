#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("Image RGBA Channel Sift Dev Ugex");
    this->setAcceptDrops(true);
    ui->widgetPaintArea->installEventFilter(this);

    ui->checkBoxRed->setChecked(true);
    ui->checkBoxGreen->setChecked(true);
    ui->checkBoxBlue->setChecked(true);
    ui->checkBoxAlpha->setChecked(true);
    ui->checkBoxToGray->setChecked(false);
    QDoubleSpinBox * spins[5]={
        ui->doubleSpinBoxRGBAEnhance,
        ui->doubleSpinBoxRedEnhance,
        ui->doubleSpinBoxGreenEnhance,
        ui->doubleSpinBoxBlueEnhance,
        ui->doubleSpinBoxAlphaEnhance};
    for(int i=0;i<5;i++)
    {
        spins[i]->setRange(0.0,10.0);
        spins[i]->setSingleStep(0.01);
        spins[i]->setDecimals(3);
        spins[i]->setValue(1.0);
    }

    connect(ui->checkBoxRed,&QCheckBox::clicked,this,[=]()
    {
      updateOutputImage();
    });
    connect(ui->checkBoxGreen,&QCheckBox::clicked,this,[=]()
    {
      updateOutputImage();
    });
    connect(ui->checkBoxBlue,&QCheckBox::clicked,this,[=]()
    {
      updateOutputImage();
    });
    connect(ui->checkBoxAlpha,&QCheckBox::clicked,this,[=]()
    {
      updateOutputImage();
    });
    connect(ui->checkBoxToGray,&QCheckBox::clicked,this,[=]()
    {
      updateOutputImage();
    });
    connect(ui->doubleSpinBoxRGBAEnhance,static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,[=](double val)
    {
        for(int i=1;i<5;i++)
        {
            spins[i]->setValue(val);
        }
        updateOutputImage();
    });
    connect(ui->doubleSpinBoxRedEnhance,static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,[=](double)
    {
        updateOutputImage();
    });
    connect(ui->doubleSpinBoxGreenEnhance,static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,[=](double)
    {
        updateOutputImage();
    });
    connect(ui->doubleSpinBoxBlueEnhance,static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,[=](double)
    {
        updateOutputImage();
    });
    connect(ui->doubleSpinBoxAlphaEnhance,static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),this,[=](double)
    {
        updateOutputImage();
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
void Widget::updateOutputImage()
{
    m_drtImg=ImageARGBChannelSift(m_srcImg,
                                  ui->checkBoxRed->checkState()==Qt::Checked,
                                  ui->doubleSpinBoxRedEnhance->value(),
                                  ui->checkBoxGreen->checkState()==Qt::Checked,
                                  ui->doubleSpinBoxGreenEnhance->value(),
                                  ui->checkBoxBlue->checkState()==Qt::Checked,
                                  ui->doubleSpinBoxBlueEnhance->value(),
                                  ui->checkBoxAlpha->checkState()==Qt::Checked,
                                  ui->doubleSpinBoxAlphaEnhance->value(),
                                  ui->checkBoxToGray->checkState()==Qt::Checked);
    ui->widgetPaintArea->update();
}

void Widget::drawDisplayWiew()
{
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
QPixmap Widget::ImageARGBChannelSift(QPixmap & pmap,
                                     bool redChannel,double redEnhance,
                                     bool greenChannel,double greenEnhance,
                                     bool blueChannel,double blueEnhance,
                                     bool alphaChannel,double alphaEnhance,
                                     bool toGray)
{
    bool isOnlyAlpha=!(redChannel||greenChannel||blueChannel);
    QImage srcImg=pmap.toImage();
    int wid=srcImg.width();
    int hei=srcImg.height();
    QImage drtImg(wid,hei,QImage::Format_ARGB32);
    for(int y=0;y<hei;y++)
    {
        for(int x=0;x<wid;x++)
        {
            QRgb srccolor=srcImg.pixel(x,y);
            int alpha=qAlpha(srccolor);
            int drtred=0;
            int drtgreen=0;
            int drtblue=0;
            int drtalpha=255;
            if(isOnlyAlpha)
            {
                int tp=alpha*(alphaEnhance);
                drtred=tp;
                drtgreen=tp;
                drtblue=tp;
                drtalpha=tp;
            }
            else
            {
                drtred=(redChannel?qRed(srccolor):0)*redEnhance;
                drtgreen=(greenChannel?qGreen(srccolor):0)*greenEnhance;
                drtblue=(blueChannel?qBlue(srccolor):0)*blueEnhance;
                drtalpha=(alphaChannel?alpha:255)*alphaEnhance;
            }
            drtred=drtred>255?255:drtred;
            drtgreen=drtgreen>255?255:drtgreen;
            drtblue=drtblue>255?255:drtblue;
            drtalpha=drtalpha>255?255:drtalpha;
            QRgb drtcolor=qRgba(drtred,drtgreen,drtblue,drtalpha);
            if(toGray)
            {
                int drtgray=qGray(drtcolor);
                drtalpha=qAlpha(drtcolor);
                drtcolor=qRgba(drtgray,drtgray,drtgray,drtalpha);
            }
            drtImg.setPixel(x,y,drtcolor);
        }
    }
    return QPixmap::fromImage(drtImg);
}
