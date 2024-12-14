#include "widget.h"
#include"mybutton.h"
//F4来回跳转.cpp .h
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    /*
     * 如果窗口需要依附于另外一个窗口，就应该指定父窗口
     * 一旦指定父窗口之后，就可以不用在进行show，跟随父窗口显示
     * x向右，y向下
    */
    m_btn.setText("按钮1");
    m_btn.setParent(this);
    m_btn.move(*new QPoint(100,100));//new出来的是指针，需要引用
    m_btn.show();
    //F1进入帮助，查看构造
    mp_btn=new QPushButton("按钮2",this);
    mp_btn->move(100,200);//指定位置和大小
    mp_btn->resize(200,50);
    //mp_btn->show();

    //创建自定义按钮对象，F2进入自定义的
    MyButton * mybtn=new MyButton(this);
    mybtn->setText("自定义按钮");

    this->setWindowTitle("第一个QT程序");
    //this->setWindowIcon(QIcon(".\\icon.png"));//设置图片，jpg,png都行
    this->resize(720,480);
    this->setFixedSize(720,480);//设置成固定的尺寸，不可以鼠标在调整

    //按钮点击响应
    //链接对象：进行消息与处理函数的绑定
    //发出信号的对象指针，信号类型，接受信号的对象指针，处理函数
    connect(mp_btn,&QPushButton::clicked,this,&Widget::close);
    //&QPushButton::clicked &类名::名称，取类成员地址
}

Widget::~Widget()
{
    delete mp_btn;//QT中可以内存自动回收，可以不写delete
    //适用于从QObject派生的类，使用了virtual析构原理
    //指定父类，虚析构父类时自动析构子类
    //因此需要以上两个条件
}
