#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QFileDialog>
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //寻找QAction对象,通过成员UI指针
    //菜单项发送triggered
    connect(ui->actionOpen,&QAction::triggered,this,[this](){
        qDebug() << "Clicked Menu File Open"<<endl;
        //静态方法，打开一个文件
        QString fname=QFileDialog::getOpenFileName(this,
                                                   "Open File",
                                                   "D:\\",
                                                   "Images(*.jpg *.png *.gif);;Files(*.txt *.doc *.docx)");
        qDebug() << fname.toUtf8().data() <<endl;
    });
    connect(ui->actionSave,&QAction::triggered,this,[this](){
        qDebug() << "Clicked Menu File Save"<<endl;
        QString fname=QFileDialog::getSaveFileName(this,
                                                   "Save File",
                                                   "D:\\",
                                                   "All Files(*.*)");
        QMessageBox::information(this,"File Operation","Save File:"+fname);
    });
    connect(ui->pushButton_Login,&QPushButton::clicked,this,[this](){
        qDebug() << "Logining..."<<endl;
        QMessageBox::information(this,"Login","LoginInfo");
    });
    connect(ui->pushButton_Exit,&QPushButton::clicked,this,[this](){
        qDebug() << "Exiting..."<<endl;
        this->close();
    });
    ui->statusBar->addWidget(new QPushButton("Hello",this));
    ui->statusBar->addWidget(new QLabel("Lable",this));
   //为控件添加图标
    ui->actionImgMenu->setIcon(QIcon{":/img/cmt.png"});//可以给路径,资源文件：格式：QIcon{":/cmt.png"}
}

MainWindow::~MainWindow()
{
    delete ui;
}
