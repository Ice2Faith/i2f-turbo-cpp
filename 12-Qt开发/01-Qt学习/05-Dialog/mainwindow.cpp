#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPushButton>
#include<QDebug>
#include<QDialog>
#include<QMessageBox>
#include<QColorDialog>
#include<QFontDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_mod,&QPushButton::clicked,this,[this](){
        QDialog dlg(this);
        dlg.resize(480,320);
        //模态对话框，阻塞
        dlg.exec();   //
    });
    connect(ui->pushButton_antimod,&QPushButton::clicked,this,[this](){
       QDialog *dlg=new QDialog(this);
       //非模态对话框，不阻塞，可能会一闪而过,因此使用new创建，不被析构即可
       dlg->resize(480,320);
       //防止不断new，使用方法进行自动析构
       dlg->setAttribute(Qt::WA_DeleteOnClose);
       dlg->show();
    });
    connect(ui->pushButton_msgbox,&QPushButton::clicked,this,[=](){
        //QMessageBox::information(this,"MsgBox","QMessagebox Class Static Infomation Method");
        //critical错误提示，严重性的，infomation资讯对话框,question询问对话框，warning警告对话框
        //QMessageBox::about(this,"MsgBox","QMessagebox Class Static about Method");
        int ret=QMessageBox::question(this,"选项","是否关闭？",QMessageBox::Yes|QMessageBox::No);
        if(ret==QMessageBox::Yes)
            QMessageBox::information(this,"已选择","点击了Yes");
    });
    connect(ui->pushButton_color,&QPushButton::clicked,this,[=](){
       QColor color= QColorDialog::getColor(Qt::white,this,"ColorChoice");
       qDebug()
       <<color.red()
       <<color.green()
       <<color.blue();

    });
    connect(ui->pushButton_font,&QPushButton::clicked,this,[=](){
        bool  bl=false;
        QFont defFont("Times",12);
        QFont font=QFontDialog::getFont(&bl,defFont,this,"FontChoice");
        if(bl)
        {
            qDebug()
            <<font.family()
            <<font.italic()
            <<font.underline()
            <<font.pointSize()
            <<font.weight()
            <<font.bold();
        }

    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
