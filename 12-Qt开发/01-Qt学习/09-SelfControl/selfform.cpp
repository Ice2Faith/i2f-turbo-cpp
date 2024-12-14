#include "selfform.h"
#include "ui_selfform.h"

SelfForm::SelfForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelfForm)
{
    ui->setupUi(this);
    //使得spinbox 和 horizotal slider的同步
    //有重载信号
    void (QSpinBox::*sigValueChange)(int)=&QSpinBox::valueChanged;
    connect(ui->spinBox,sigValueChange,ui->horizontalSlider,&QSlider::setValue);
    //
    connect(ui->horizontalSlider,&QSlider::valueChanged,ui->spinBox,&QSpinBox::setValue);
}

SelfForm::~SelfForm()
{
    delete ui;
}
//添加get set方法给外部调用
int SelfForm::getValue()
{
    return ui->spinBox->value();
}
void SelfForm::setValue(int value)
{
    if(value>=0&&value<=100)
    {
        ui->spinBox->setValue(value);
    }
}
