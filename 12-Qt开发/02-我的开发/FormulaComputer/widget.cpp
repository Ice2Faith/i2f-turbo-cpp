#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->installEventFilter(this);


    initComponent();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initComponent(){
    connect(ui->btnQuateLeft,&QPushButton::clicked,this,[=]{
        appendStr2Input(" ( ");
    });
    connect(ui->btnQuateRight,&QPushButton::clicked,this,[=]{
        appendStr2Input(" ) ");
    });
    connect(ui->btnSqrt,&QPushButton::clicked,this,[=]{
        appendStr2Input(" sqrt ");
    });
    connect(ui->btnLog,&QPushButton::clicked,this,[=]{
        appendStr2Input(" log ");
    });
    connect(ui->btnAdds,&QPushButton::clicked,this,[=]{
        appendStr2Input(" adds ");
    });
    connect(ui->btnMuls,&QPushButton::clicked,this,[=]{
        appendStr2Input(" muls ");
    });
    connect(ui->btnRecip,&QPushButton::clicked,this,[=]{
        appendStr2Input(" recip ");
    });
    connect(ui->btnEpowX,&QPushButton::clicked,this,[=]{
        appendStr2Input(" epow ");
    });
    connect(ui->btnLn,&QPushButton::clicked,this,[=]{
        appendStr2Input(" ln ");
    });
    connect(ui->btnGoldSec,&QPushButton::clicked,this,[=]{
        appendStr2Input(" numgsec ");
    });
    connect(ui->btnDehex,&QPushButton::clicked,this,[=]{
        appendStr2Input(" dehex");
    });
    connect(ui->btnClear,&QPushButton::clicked,this,[=]{
        clearInput();
    });
    connect(ui->btnCompute,&QPushButton::clicked,this,[=]{
        computeResult();
    });
    connect(ui->btnAdd,&QPushButton::clicked,this,[=]{
        appendStr2Input(" + ");
    });
    connect(ui->btnNum7,&QPushButton::clicked,this,[=]{
        appendStr2Input("7");
    });
    connect(ui->btnNum8,&QPushButton::clicked,this,[=]{
        appendStr2Input("8");
    });
    connect(ui->btnNum9,&QPushButton::clicked,this,[=]{
        appendStr2Input("9");
    });
    connect(ui->btnSub,&QPushButton::clicked,this,[=]{
        appendStr2Input(" - ");
    });
    connect(ui->btnNum4,&QPushButton::clicked,this,[=]{
        appendStr2Input("4");
    });
    connect(ui->btnNum5,&QPushButton::clicked,this,[=]{
        appendStr2Input("5");
    });
    connect(ui->btnNum6,&QPushButton::clicked,this,[=]{
        appendStr2Input("6");
    });
    connect(ui->btnMul,&QPushButton::clicked,this,[=]{
        appendStr2Input(" * ");
    });
    connect(ui->btnNum1,&QPushButton::clicked,this,[=]{
        appendStr2Input("1");
    });
    connect(ui->btnNum2,&QPushButton::clicked,this,[=]{
        appendStr2Input("2");
    });
    connect(ui->btnNum3,&QPushButton::clicked,this,[=]{
        appendStr2Input("3");
    });
    connect(ui->btnDiv,&QPushButton::clicked,this,[=]{
        appendStr2Input(" / ");
    });
    connect(ui->btnNum0,&QPushButton::clicked,this,[=]{
        appendStr2Input("0");
    });
    connect(ui->btnDot,&QPushButton::clicked,this,[=]{
        appendStr2Input(".");
    });
    connect(ui->btnBack,&QPushButton::clicked,this,[=]{
        backInput();
    });
    connect(ui->btnMod,&QPushButton::clicked,this,[=]{
        appendStr2Input(" % ");
    });
    connect(ui->btnNumA,&QPushButton::clicked,this,[=]{
        appendStr2Input("A");
    });
    connect(ui->btnNumB,&QPushButton::clicked,this,[=]{
        appendStr2Input("B");
    });
    connect(ui->btnNumC,&QPushButton::clicked,this,[=]{
        appendStr2Input("C");
    });
    connect(ui->btnPow,&QPushButton::clicked,this,[=]{
        appendStr2Input(" ^ ");
    });
    connect(ui->btnNumD,&QPushButton::clicked,this,[=]{
        appendStr2Input("D");
    });
    connect(ui->btnNumE,&QPushButton::clicked,this,[=]{
        appendStr2Input("E");
    });
    connect(ui->btnNumF,&QPushButton::clicked,this,[=]{
        appendStr2Input("F");
    });
    connect(ui->btnNeg,&QPushButton::clicked,this,[=]{
        appendStr2Input(" neg ");
    });
    connect(ui->btnPercent,&QPushButton::clicked,this,[=]{
        appendStr2Input(" per ");
    });
    connect(ui->btnFactorial,&QPushButton::clicked,this,[=]{
        appendStr2Input("!");
    });
    connect(ui->btnAbs,&QPushButton::clicked,this,[=]{
        appendStr2Input(" abs ");
    });
    connect(ui->btnAngle,&QPushButton::clicked,this,[=]{
        appendStr2Input(" angle ");
    });
    connect(ui->btnBitAnd,&QPushButton::clicked,this,[=]{
        appendStr2Input(" and ");
    });
    connect(ui->btnBitOr,&QPushButton::clicked,this,[=]{
        appendStr2Input(" or ");
    });
    connect(ui->btnBitXor,&QPushButton::clicked,this,[=]{
        appendStr2Input(" xor ");
    });
    connect(ui->btnRadian,&QPushButton::clicked,this,[=]{
        appendStr2Input(" radian ");
    });
    connect(ui->btnSin,&QPushButton::clicked,this,[=]{
        appendStr2Input(" sin ");
    });
    connect(ui->btnCos,&QPushButton::clicked,this,[=]{
        appendStr2Input(" cos ");
    });
    connect(ui->btnTan,&QPushButton::clicked,this,[=]{
        appendStr2Input(" tan ");
    });
    connect(ui->btnmPi,&QPushButton::clicked,this,[=]{
        appendStr2Input(" numpi ");
    });
    connect(ui->btnArcSin,&QPushButton::clicked,this,[=]{
        appendStr2Input(" arcsin ");
    });
    connect(ui->btnArcCos,&QPushButton::clicked,this,[=]{
        appendStr2Input(" arccos ");
    });
    connect(ui->btnArcTan,&QPushButton::clicked,this,[=]{
        appendStr2Input(" arctan ");
    });
    connect(ui->btnmE,&QPushButton::clicked,this,[=]{
        appendStr2Input(" nume ");
    });

    connect(ui->btnLmov,&QPushButton::clicked,this,[=]{
        appendStr2Input(" lmov ");
    });
    connect(ui->btnRmov,&QPushButton::clicked,this,[=]{
        appendStr2Input(" rmov ");
    });
    connect(ui->btnMax,&QPushButton::clicked,this,[=]{
        appendStr2Input(" max ");
    });
    connect(ui->btnMin,&QPushButton::clicked,this,[=]{
        appendStr2Input(" min ");
    });
    connect(ui->btnAvg,&QPushButton::clicked,this,[=]{
        appendStr2Input(" avg ");
    });
    connect(ui->btnRecipAdds,&QPushButton::clicked,this,[=]{
        appendStr2Input(" recipadds ");
    });
    connect(ui->btnRecipMuls,&QPushButton::clicked,this,[=]{
        appendStr2Input(" recipmuls ");
    });
    connect(ui->btnMinSum,&QPushButton::clicked,this,[=]{
        appendStr2Input(" minsum ");
    });
    connect(ui->btnMaxFac,&QPushButton::clicked,this,[=]{
        appendStr2Input(" maxfac ");
    });
    connect(ui->btnPerAdd,&QPushButton::clicked,this,[=]{
        appendStr2Input(" peradd ");
    });
    connect(ui->btnPerSub,&QPushButton::clicked,this,[=]{
        appendStr2Input(" persub ");
    });
    connect(ui->btnRand,&QPushButton::clicked,this,[=]{
        appendStr2Input(" rand ");
    });
    connect(ui->btnDayOfMonth,&QPushButton::clicked,this,[=]{
        appendStr2Input(" dayofmonth ");
    });
    connect(ui->btnNot,&QPushButton::clicked,this,[=]{
        appendStr2Input(" not ");
    });
    connect(ui->btnXPowX,&QPushButton::clicked,this,[=]{
        appendStr2Input(" xpowx ");
    });
    connect(ui->btnRandZ,&QPushButton::clicked,this,[=]{
        appendStr2Input(" randz ");
    });
    connect(ui->btnRandF,&QPushButton::clicked,this,[=]{
        appendStr2Input(" randf ");
    });
    connect(ui->btnCeil,&QPushButton::clicked,this,[=]{
        appendStr2Input(" ceil ");
    });
    connect(ui->btnFloor,&QPushButton::clicked,this,[=]{
        appendStr2Input(" floor ");
    });
    connect(ui->btnRound,&QPushButton::clicked,this,[=]{
        appendStr2Input(" round ");
    });
    connect(ui->btnDHead,&QPushButton::clicked,this,[=]{
        appendStr2Input(" dhead ");
    });
    connect(ui->btnFTail,&QPushButton::clicked,this,[=]{
        appendStr2Input(" ftail ");
    });
    connect(ui->btnDayOfYear,&QPushButton::clicked,this,[=]{
        appendStr2Input(" dayofyear ");
    });
    connect(ui->btnKmhToMs,&QPushButton::clicked,this,[=]{
        appendStr2Input(" kmhtoms ");
    });
    connect(ui->btnMsToKmh,&QPushButton::clicked,this,[=]{
        appendStr2Input(" mstokmh ");
    });
    connect(ui->btnFtToCt,&QPushButton::clicked,this,[=]{
        appendStr2Input(" fttoct ");
    });
    connect(ui->btnCtToFt,&QPushButton::clicked,this,[=]{
        appendStr2Input(" cttoft ");
    });
    connect(ui->btnFeibo,&QPushButton::clicked,this,[=]{
        appendStr2Input(" feibo ");
    });

    /////////////////////////////

    connect(ui->btnInQuate,&QPushButton::clicked,this,[=](){
        QString str=ui->edtInput->toPlainText();
        str="( "+str+" ) ";
        ui->edtInput->setPlainText(str);
        computeResult();
    });

    connect(ui->edtInput,&QPlainTextEdit::cursorPositionChanged,this,[=](){
       computeResult();
    });

    ui->spnSrcHex->setMinimum(2);
    ui->spnSrcHex->setMaximum(16);
    ui->spnSrcHex->setValue(10);

    ui->spnDstHex->setMinimum(2);
    ui->spnDstHex->setMaximum(16);
    ui->spnDstHex->setValue(16);


    connect(ui->edtSrcHexNumber,&QLineEdit::returnPressed,this,[=](){
        transferHex(true);
    });

    connect(ui->edtDstHexNumber,&QLineEdit::returnPressed,this,[=](){
        transferHex(false);
    });

    connect(ui->spnSrcHex,static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,[=](int val){
        transferHex(true);
    });
    connect(ui->spnDstHex,static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,[=](int val){
        transferHex(false);
    });

}

void Widget::transferHex(bool isSrc){
    if(isSrc){
        QString srcNum=ui->edtSrcHexNumber->text();
        int srcHex=ui->spnSrcHex->value();
        int dstHex=ui->spnDstHex->value();

        double rNum=FormulaCalculator::hex2Number(srcNum.toUtf8().data(),srcHex);
        QByteArray buf;
        buf.resize(300);
        FormulaCalculator::number2Hex(rNum,buf.data(),dstHex,12);
        QString dstNum=QString("%1").arg(buf.data());

        ui->edtDstHexNumber->setText(dstNum);
    }else{
        QString srcNum=ui->edtDstHexNumber->text();
        int srcHex=ui->spnSrcHex->value();
        int dstHex=ui->spnDstHex->value();

        double rNum=FormulaCalculator::hex2Number(srcNum.toUtf8().data(),dstHex);
        QByteArray buf;
        buf.resize(300);
        FormulaCalculator::number2Hex(rNum,buf.data(),srcHex,12);
        QString dstNum=QString("%1").arg(buf.data());

        ui->edtSrcHexNumber->setText(dstNum);
    }

}

//事件过滤器函数
bool Widget::eventFilter(QObject * obj, QEvent * e)
{
    if(obj==ui->edtInput){
        return true;
    }

    //过滤事件
    switch(e->type())
    {
    case QEvent::KeyRelease:
        if(processKeyEvent((QKeyEvent*)e)==false){
            return QWidget::eventFilter(obj,e);
        }
        break;
    default:
        return QWidget::eventFilter(obj,e);
    }
    return true;

}
bool Widget::processKeyEvent(QKeyEvent * e){
    switch(e->key()){
    case Qt::Key_Space:
    case Qt::Key_Tab:
        computeResult();
        break;
    case Qt::Key_Backspace:
        if(e->modifiers()==Qt::ControlModifier)
            backInput();
        break;
    case Qt::Key_Escape:
        this->setFocus();
        break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
        foucus2TextEdit((QTextEdit *)ui->edtInput);
        break;
    default:
        return false;
    }
    return true;
}

void Widget::foucus2TextEdit(QTextEdit * editor){
    editor->setFocus();
    //移动光标到末尾
    QTextCursor cursor = editor->textCursor();
    cursor.movePosition(QTextCursor::End);
    editor->setTextCursor(cursor);
}

void Widget::appendStr2Input(QString str){
    ui->edtInput->setPlainText(ui->edtInput->toPlainText()+str);
    computeResult();
}
void Widget::computeResult(){
    QString str=ui->edtInput->toPlainText();
    bool isSuccess=false;
    double result=this->caculator.calculate(str.toUtf8().data(),&isSuccess);
    if(isSuccess){
        ui->edtOutput->setPlainText(QString("%1").arg(result));
    }else{
        double last=this->caculator.getLastResult();
        ui->edtOutput->setPlainText(QString("%1 [error]\n%2").arg(last).arg(this->caculator.getLastErrStr()));
    }
}
void Widget::backInput(){
    QString str=ui->edtInput->toPlainText().trimmed();
    int index=str.lastIndexOf(" ");
    if(index>=0){
        QString nstr=str.mid(0,index).trimmed()+" ";
        ui->edtInput->setPlainText(nstr);
    }else if(str.length()>0){
        QString nstr=str.mid(0,str.length()-1).trimmed()+" ";
        ui->edtInput->setPlainText(nstr);
    }
}
void Widget::clearInput(){
    QString str=ui->edtInput->toPlainText();
    if(str.length()==0){
        ui->edtOutput->setPlainText("");
    }
    ui->edtInput->setPlainText("");
}
