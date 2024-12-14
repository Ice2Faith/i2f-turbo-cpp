#ifndef WIDGET_H
#define WIDGET_H
#include<QList>
#include <QWidget>
#include"personrelation.h"
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

    PersonRelation m_pr;
    QList<RelationNode::RelationIndex> list;
    void onClickRealtionBtn(RelationNode::RelationIndex index);
    void onBackRelation();
    void updateResult();
    void ClearAllItem();
};

#endif // WIDGET_H
