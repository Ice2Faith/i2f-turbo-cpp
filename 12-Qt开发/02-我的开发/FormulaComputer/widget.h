#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QString>
#include<QEvent>
#include<QKeyEvent>
#include<QMessageBox>
#include<QTextEdit>

#include"FormulaCalculator.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:

protected:
    //事件过滤器
   virtual bool eventFilter(QObject *, QEvent *);

private:
    void initComponent();
    void appendStr2Input(QString str);
    void computeResult();
    bool processKeyEvent(QKeyEvent * e);
    void backInput();
    void clearInput();

    void foucus2TextEdit(QTextEdit * editor);
    void transferHex(bool isSrc);

    Ui::Widget *ui;
    FormulaCalculator caculator;
};

#endif // WIDGET_H
