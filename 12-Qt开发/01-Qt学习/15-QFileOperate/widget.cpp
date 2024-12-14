#include "widget.h"
#include "ui_widget.h"
//文件访问
#include<QFile>

#include<QFileDialog>//文件选择对话框
#include<QMessageBox>//消息对话框
#include<QTextCodec>//编码解决

//文件流
#include<QTextStream>//平台有关，编码有关
#include<QDataStream>//平台无关

//文件信息操作
#include<QFileInfo>
#include<QDateTime>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
#if 1
    //文件操作
    connect(ui->pushButton,&QPushButton::clicked,this,[=]()
    {
        QString filename=QFileDialog::getOpenFileName(this,"read file","C:\\");
        if(filename.isEmpty())
        {
            QMessageBox::warning(this,"Warnning","not select file");
            return;
        }
        ui->lineEdit->setText(filename);
        //创建文件对象，默认读取文件格式为utf8
        QFile file(filename);
        //打卡文件
       bool succ= file.open(QFile::ReadOnly);//打开方式，QIODevice枚举
        if(!succ)
           {
            QMessageBox::warning(this,"Warnning","open file failure");
            return;
        }
        //读取文件
        QByteArray arr=file.readAll();
        //解决字符集问题
        QTextCodec * codec=QTextCodec::codecForName("gbk");
       QString str=codec->toUnicode(arr);
        ui->textEdit->append(str);

        //关闭文件
        file.close();
        /*
        文件写入：
        QString str;
        file.write(str.toUTF8());//QByteArray
        file.write(char *);
        file.write(char *,int64 count);
        */
        QMessageBox::information(this,"Infomation","read file end");

    });
#else
    //文件流
    connect(ui->pushButton,&QPushButton::clicked,this,[=](){
        QString filename=QFileDialog::getOpenFileName(this,"read file","C:\\");
        if(filename.isEmpty())
        {
            QMessageBox::warning(this,"Warnning","not select file");
            return;
        }
        ui->lineEdit->setText(filename);
        QFile file(filename);
        //打卡文件
       bool succ= file.open(QFile::ReadOnly);//打开方式，QIODevice枚举
        if(!succ)
           {
            QMessageBox::warning(this,"Warnning","open file failure");
            return;
        }
        //创建流
        QTextStream ts(&file);//设置IO设备进行构造,默认按照本地编码解析
        ts.setCodec("gbk");
        QString str=ts.readAll();
        ui->textEdit->append(str);

        file.close();

    });
#endif
    ////////////////////////////////////////////////////
#if 0
    //按照C++流的风格进行读写
    QFile f("1.txt");
    f.open(QFile::WriteOnly);
    QTextStream st(&f);
    st << QString("file write") << 1.258;
    f.close();

    f.open(QFile::ReadOnly);
    st.setDevice(&f);
    QString strb;
    st >> strb;

    f.close();
#else
    //二进制流读写，IO设备，内存块
    QFile f("1.bin");
    //f.setFileName("1.bin");//也可以直接设定，不使用构造
    f.open(QFile::WriteOnly);
    QDataStream st(&f);
    st << QString("file write") << 1.258;
    f.close();
//f.atEnd();//判断文件是否读取完毕

    f.open(QFile::ReadOnly);
    st.setDevice(&f);//设置IO设备
    QString strb;
    float num;
    st >> strb >> num;

    f.close();

    //内存读写
    QPixmap pix(24,36);
    QByteArray arr;//大小是可变的
    QDataStream ms(&arr,QIODevice::ReadWrite);
    ms << pix;
#endif

    /////////////////////////////////////////
#if 1
    //查看文件信息，更多构造查看文档
    QFileInfo fi("a.txt");
    fi.size();//大小，字节
    fi.fileName();//文件名称
    fi.filePath();//文件路径
    fi.absolutePath();//绝对路径
    fi.exists();
    fi.isFile();
    fi.isDir();
    fi.lastModified().toString("yyyy-MM-dd hh:mm:ss");
    fi.completeSuffix();//完整后缀
    fi.suffix();//后缀

#endif
}

Widget::~Widget()
{
    delete ui;
}
