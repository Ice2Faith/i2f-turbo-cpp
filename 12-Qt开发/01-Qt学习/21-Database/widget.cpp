#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //获取所有驱动名
    //qDebug() << QSqlDatabase::drivers()<<endl;
    //结果如下：("QSQLITE", "QMYSQL", "QMYSQL3", "QODBC", "QODBC3", "QPSQL", "QPSQL7")
    //添加数据库，参数:驱动名,有默认参数不用管了
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL3");
    //设置数据库
    db.setHostName("localhost");//或者给127.0.0.1
    db.setUserName("root");//登录数据库的用户名
    db.setPassword("ltb12315");//设置密码
    db.setDatabaseName("study");//设置访问的数据库名

    if(db.open()==false)
    {
        //需要MySql的相关才能加载驱动DLL文件
        /*
        操作步骤：
        找到MySql下面的MySQL\MySQL Server 8.0\lib\libmysql.dll 和对应的lib
        拷贝到Q弹安装路径下面的目录下：QT\Qt5.4.0\5.4\mingw491_32\bin
        但是如果位数不一样也没作用
        */
        QMessageBox::warning(this,"警告",db.lastError().text());
    }

    //数据库非查询语句
    //添加
    QSqlQuery bquery;
    QString sql="insert into student values('101','linq','man')";
    bool ret=bquery.exec(sql);
    if(ret==false)
        QMessageBox::warning(this,"警告","插入失败");

//    //使用预处理批量进行查询
//    //批处理方式1，ODBC风格
//    QSqlQuery pquery;
//    //准备预处理语句
//    pquery.prepare("insert into student(no,name,sex) values(?,?,?)");
//    //绑定数据,QVariant相当于一个Object，可以放任意类型
//    //注意，绑定数据的顺序就是对应的顺序
//    QVariantList noarguments;
//    noarguments << "101" << "102" <<"103";
//    pquery.addBindValue(noarguments);
//    QVariantList namearguments;
//    namearguments << "zhangsan" << "lisi" <<"wangwu";
//    pquery.addBindValue(namearguments);
//    QVariantList sexarguments;
//    sexarguments << "man" << "woman" <<"man";
//    pquery.addBindValue(sexarguments);
//    //执行批处理
//    ret=pquery.execBatch();
//    if(ret==false)
//        QMessageBox::warning(this,"警告","插入失败");

    //批处理方式2，Oracle风格，推荐使用
    //通配符不在使用问好，而是：:+自定义名称
    //这种方式在绑定数据的时候，可以不用管添加绑定数据的顺序，直接按照自定义名称绑定
    QSqlQuery pquery;
    //准备预处理语句
    pquery.prepare("insert into student(no,name,sex) values(:no,:name,:sex)");
    //绑定数据,QVariant相当于一个Object，可以放任意类型
    QVariantList noarguments;
    noarguments << "101" << "102" <<"103";
    pquery.bindValue(":no",noarguments);
    QVariantList sexarguments;
    sexarguments << "man" << "woman" <<"man";
    pquery.bindValue(":sex",sexarguments);
    QVariantList namearguments;
    namearguments << "zhangsan" << "lisi" <<"wangwu";
    pquery.bindValue(":name",namearguments);

    //执行批处理
    ret=pquery.execBatch();
    if(ret==false)
        QMessageBox::warning(this,"警告","插入失败");

    //数据库查询语句
    QSqlQuery squery;
    squery.exec("select * from student");
    //获取查询语句
    while(squery.next())//指向一条记录
    {
        //squery.value(0).toInt();//获取第一个字段
        squery.value("name").toString();//获取字段名对应的值
        //注意获取到的字符串可能是乱码，因此一般使用：toString().toUtf8().data();

    }

    //使用QSqlTableModel进行数据库数据显示
    //实例化
    table=new QSqlTableModel(this);
    //设置模型
    ui->tableViewData->setModel(table);
    //给model设置数据库表,前提是数据库已经打开了
    table->setTable("student");
    //查询数据,查询之后才会显示数据
    table->select();
    //设置水平表头，可选设置，其实垂直表头设置是无效的，
    //一般是重写他的祖宗类来实现自定义功能QItemModel
    table->setHeaderData(0,Qt::Horizontal,"编号");
    table->setHeaderData(0,Qt::Horizontal,"学号");
    table->setHeaderData(0,Qt::Horizontal,"姓名");
    //在视图上修改将会直接影响到数据库内容，因此常常要设置提交模式
    //设置为用户允许之后提交，不用默认自动提交
    table->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //需要提交的时候，需要使用submitAll进行提交,这是由提交模式决定的，要使用带All的
    table->submitAll();//实际是一个槽函数，因此可以直接连接
    //撤销修改
    table->revertAll();
    table->submitAll();//一般来说撤销修改之后需要进行一次提交，更新数据显示，也可以使用select更新
    //设置过滤条件,毕竟有些行是不需要显示的
    table->setFilter(QString("name like '%%%1%%'").arg("man"));//这里面的内容其实就是select语句的where条件
    table->select();//重新查询显示在视图上
}

Widget::~Widget()
{
    delete ui;
}
