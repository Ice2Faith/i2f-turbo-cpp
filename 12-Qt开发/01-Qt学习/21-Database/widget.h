#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QSqlDatabase>
#include<QDebug>
#include<QMessageBox>
#include<QSqlError>
#include<QSqlQuery>
#include<QVariantList>
#include<QSqlTableModel> //数据库的数据模型，和C#SqlTable类似
//显示数据就需要使用视图--QTableView
//qt model - view (MVC-model view control)
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QSqlTableModel * table;
};

#endif // WIDGET_H
