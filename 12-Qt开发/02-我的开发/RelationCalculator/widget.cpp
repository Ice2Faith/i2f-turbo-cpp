#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("亲戚称呼计算器 Dev : Ugex Savelar");
    ClearAllItem();
    connect(ui->pushButtonFuqin,&QPushButton::clicked,this,[=]()
    {
        onClickRealtionBtn(RelationNode::FuQin);
    });
    connect(ui->pushButtonMuqin,&QPushButton::clicked,this,[=]()
    {
        onClickRealtionBtn(RelationNode::MuQin);
    });
    connect(ui->pushButtonLaopo,&QPushButton::clicked,this,[=]()
    {
        onClickRealtionBtn(RelationNode::LaoPo);
    });
    connect(ui->pushButtonLaogong,&QPushButton::clicked,this,[=]()
    {
        onClickRealtionBtn(RelationNode::LaoGong);
    });
    connect(ui->pushButtonErzi,&QPushButton::clicked,this,[=]()
    {
        onClickRealtionBtn(RelationNode::ErZi);
    });
    connect(ui->pushButtonNver,&QPushButton::clicked,this,[=]()
    {
        onClickRealtionBtn(RelationNode::NvEr);
    });
    connect(ui->pushButtonGege,&QPushButton::clicked,this,[=]()
    {
        onClickRealtionBtn(RelationNode::GeGe);
    });
    connect(ui->pushButtonDidi,&QPushButton::clicked,this,[=]()
    {
        onClickRealtionBtn(RelationNode::DiDi);
    });
    connect(ui->pushButtonJiejie,&QPushButton::clicked,this,[=]()
    {
        onClickRealtionBtn(RelationNode::JieJie);
    });
    connect(ui->pushButtonMeimei,&QPushButton::clicked,this,[=]()
    {
        onClickRealtionBtn(RelationNode::MeiMei);
    });
    connect(ui->pushButtonYifu,&QPushButton::clicked,this,[=]()
    {
        onClickRealtionBtn(RelationNode::YiFu);
    });
    connect(ui->pushButtonYimu,&QPushButton::clicked,this,[=]()
    {
        onClickRealtionBtn(RelationNode::YiMu);
    });
    connect(ui->pushButtonYizi,&QPushButton::clicked,this,[=]()
    {
        onClickRealtionBtn(RelationNode::YiZi);
    });
    connect(ui->pushButtonYinv,&QPushButton::clicked,this,[=]()
    {
        onClickRealtionBtn(RelationNode::YiNv);
    });
    connect(ui->pushButtonClear,&QPushButton::clicked,this,[=]()
    {
        ClearAllItem();
    });
    connect(ui->pushButtonBack,&QPushButton::clicked,this,[=]()
    {
        onBackRelation();
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onClickRealtionBtn(RelationNode::RelationIndex index)
{
    list.append(index);
    updateResult();
}

void Widget::onBackRelation()
{
    if(!list.isEmpty())
    {
        list.pop_back();
        updateResult();
    }

}

void Widget::updateResult()
{
    QString str="我";
    if(list.length()>0)
    {
        for(int i=0;i<list.size();i++)
        {
            str+="的";
            str+=RelationNode::getIndexName(list.at(i));
        }
    }
    ui->lineEditTips->setText(str);
    ui->lineEditResultName->setText(m_pr.routeRelation(list));
}

void Widget::ClearAllItem()
{
    list.clear();
    updateResult();
}

