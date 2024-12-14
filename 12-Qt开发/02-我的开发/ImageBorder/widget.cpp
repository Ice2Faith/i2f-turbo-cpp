#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("Image Border dev Ugex");
    dispalyBorder=true;
    borderC=QColor(120,120,120);
    backC=QColor(255,255,255);
    ui->widgetPaintArea->installEventFilter(this);
    ui->doubleSpinBoxAllowRate->setDecimals(4);
    ui->doubleSpinBoxAllowRate->setRange(0.0,0.9999);
    ui->doubleSpinBoxAllowRate->setSingleStep(0.01);
    ui->doubleSpinBoxAllowRate->setValue(0.02);
    ui->checkBoxUseBackColor->setChecked(true);
    ui->checkBoxUseBorderColor->setChecked(true);

    UpdateBtnBackColor();

    connect(ui->pushButtonReadFile,&QPushButton::clicked,this,[=](){
          QString filename=QFileDialog::getOpenFileName(this,"请选择图片：");
          if(filename.isEmpty())
          {
              QMessageBox::warning(this,"文件读取错误","未选择图片文件");
              return;
          }
          ui->lineEditFileName->setText(filename);
          map=QPixmap(filename);
          ReBorderImage();
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
    connect(ui->pushButtonSelectBackColor,&QPushButton::clicked,this,[=](){
        QColor  pc=QColorDialog::getColor(backC,this,"请选择背景颜色");
        if(!pc.isValid())
        {
            return;
        }
        backC=pc;
        UpdateBtnBackColor();
        ReBorderImage();
        if(dispalyBorder)
            ui->widgetPaintArea->update();
    });
    connect(ui->pushButtonSelectBorderColor,&QPushButton::clicked,this,[=](){
        QColor  pc=QColorDialog::getColor(borderC,this,"请选择背景颜色");
        if(!pc.isValid())
        {
            return;
        }
        borderC=pc;
        UpdateBtnBackColor();
        ReBorderImage();
        if(dispalyBorder)
            ui->widgetPaintArea->update();
    });
    connect(ui->pushButtonCompare,&QPushButton::clicked,this,[=](){
        dispalyBorder=!dispalyBorder;
        ui->widgetPaintArea->update();
    });
    connect(ui->pushButtonApply,&QPushButton::clicked,this,[=](){
        ReBorderImage();
        ui->widgetPaintArea->update();
    });
    connect(ui->pushButtonTransform,&QPushButton::clicked,this,[=](){
        QMatrix matrix;
        matrix.rotate(90);
       map= map.transformed(matrix);
       ReBorderImage();
       ui->widgetPaintArea->update();
    });
}

Widget::~Widget()
{
    delete ui;
}
void Widget::ReBorderImage()
{
    double allowRate=ui->doubleSpinBoxAllowRate->value();
    bool useBkC=ui->checkBoxUseBackColor->isChecked();
    bool useBdC=ui->checkBoxUseBorderColor->isChecked();
    bmap=ImageBorder(map,allowRate,useBdC,useBkC,borderC,backC);
}

void Widget::UpdateBtnBackColor()
{
    QPalette bkpal = ui->pushButtonSelectBackColor->palette();
   bkpal.setColor(QPalette::Button,backC);
   ui->pushButtonSelectBackColor->setPalette(bkpal);
   ui->pushButtonSelectBackColor->setAutoFillBackground(true);
   ui->pushButtonSelectBackColor->setFlat(true);

   QPalette bdpal = ui->pushButtonSelectBorderColor->palette();
  bdpal.setColor(QPalette::Button,borderC);
  ui->pushButtonSelectBorderColor->setPalette(bdpal);
  ui->pushButtonSelectBorderColor->setAutoFillBackground(true);
  ui->pushButtonSelectBorderColor->setFlat(true);
}

void Widget::DisplayView()
{
    QPainter painter(ui->widgetPaintArea);
    int wid=ui->widgetPaintArea->width();
    int hei=ui->widgetPaintArea->height();
    QPixmap dmap;
    if(dispalyBorder)
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
double Widget::DoubleAbs(double num)
{
    return num<0.0?0.0-num:num;
}

QPixmap Widget::ImageBorder(QPixmap & pmap,double allowRate,bool useBorderColor,bool useBackColor,QColor borderColor,QColor backColor)
{
    QImage img=pmap.toImage();

    const double limit = 1e-9;
    if (allowRate <= limit)
        allowRate = 0.0;
    if (allowRate >= 1.0)
        allowRate = 1.0;
    int width=img.width();
    int height=img.height();
    for (int row = 0; row < height; row++)
    {
        QColor befcolor = QColor(img.pixel(0, row));
        for (int col = 0; col < width; col++)
        {
            QColor nowcolor = QColor(img.pixel(col ,row));
            QColor downcolor = row+1>=height?befcolor:QColor(img.pixel(col ,row+1));
            if (allowRate < limit)
            {
                if (befcolor != nowcolor || downcolor != nowcolor)
                {
                    if (useBorderColor)
                    {
                        img.setPixel(col, row,qRgb(borderColor.red(),borderColor.green(),borderColor.blue()));
                    }
                }
                else
                {
                    if (useBackColor)
                    {
                        img.setPixel(col, row,qRgb(backColor.red(),backColor.green(),backColor.blue()));
                    }
                }
            }
            else
            {
                int befr = befcolor.red();
                int befg = befcolor.green();
                int befb = befcolor.blue();

                int nowr = nowcolor.red();
                int nowg = nowcolor.green();
                int nowb = nowcolor.blue();

                int downr = downcolor.red();
                int downg = downcolor.green();
                int downb = downcolor.blue();

                double familiarRateBef = 0;
                familiarRateBef = DoubleAbs((befr - nowr) / 255.0) + DoubleAbs((befg - nowg) / 255.0) + DoubleAbs((befb - nowb) / 255.0);
                familiarRateBef /= 3.0;

                double familiarRateDown = 0;
                familiarRateDown = DoubleAbs((downr - nowr) / 255.0) + DoubleAbs((downg - nowg) / 255.0) + DoubleAbs((downb - nowb) / 255.0);
                familiarRateDown /= 3.0;


                if (familiarRateBef>allowRate || familiarRateDown>allowRate)
                {
                    if (useBorderColor)
                    {
                        img.setPixel(col, row,qRgb(borderColor.red(),borderColor.green(),borderColor.blue()));
                    }
                }
                else
                {
                    if (useBackColor)
                    {
                        img.setPixel(col, row,qRgb(backColor.red(),backColor.green(),backColor.blue()));
                    }
                }
            }
            befcolor = nowcolor;
        }
    }

    return QPixmap::fromImage(img);
}
