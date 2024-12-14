#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->listWidget->addItem("QT List Widget");
    //QListWidgetItem构造支持添加图标等
    ui->listWidget->addItem(new QListWidgetItem("Qt Item",ui->listWidget));
    ui->tableWidget->setColumnCount(20);
    ui->tableWidget->setRowCount(10);
    QStringList headers;
    headers.push_back("标号");
    headers << "姓名"<<"性别"<<"年龄";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    connect(ui->pushButton_UpWnd,&QPushButton::clicked,this,[=](){
       ui->stackedWidget->setCurrentIndex(1);
    });
    connect(ui->pushButton_DownWnd,&QPushButton::clicked,this,[=](){
       ui->stackedWidget->setCurrentWidget(ui->PagePushBtn);
    });
    ui->comboBox->addItem("测试");
    ui->comboBox->addItem("项目");
    ui->label_Pic->setPixmap(QPixmap(":/img/lablepic.png"));
    //动态图片，支持gif格式
//    QMovie movie(":/...");
//    ui->label_Pic->setMovie(&movie);
//    movie.start();
}

Widget::~Widget()
{
    delete ui;
}
