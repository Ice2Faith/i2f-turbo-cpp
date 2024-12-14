#ifndef SELFFORM_H
#define SELFFORM_H

#include <QWidget>

namespace Ui {
class SelfForm;
}

class SelfForm : public QWidget
{
    Q_OBJECT

public:
    explicit SelfForm(QWidget *parent = 0);
    ~SelfForm();

    //get set方法
    int getValue();
    void setValue(int value);

private:
    Ui::SelfForm *ui;
};

#endif // SELFFORM_H
