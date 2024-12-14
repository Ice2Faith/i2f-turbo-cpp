#include<iostream>
using namespace std;
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<conio.h>
#include<windows.h>
typedef int SYM_TYPE;
#define SYM_ADD (1)
#define SYM_SUB (2)
#define SYM_MUL (4)
#define SYM_DIV (8)
#define SYM_MOD (16)
#define SYM_POW (32)
#define SYM_FOUR_ARITH (SYM_ADD|SYM_SUB|SYM_MUL|SYM_DIV)
#define SYM_ALL (SYM_FOUR_ARITH|SYM_MOD|SYM_POW)
class SimpleCalculateExercise
{
public:
    SimpleCalculateExercise(int sum=100,int floor=0,int top=100);
    ~SimpleCalculateExercise();
    void NextExercise();
    char GetSymbol();
    double GetNumFrist();
    double GetNumSecond();
    int GetSumCount();
    int GetRightCount();
    int GetErrorCount();
    bool SetAnswer(double answer);
    void SetCalculType(SYM_TYPE type);
    friend ostream & operator<<(ostream & out,SimpleCalculateExercise & cal);
private:
    char  * a_Symbols;
    short * a_SymMask;
    int     a_SymLen;
    int     s_Top;
    int     s_Floor;
    int     c_SumCount;
    int     c_RightCount;
    int     c_ErrorCount;
    char    m_Symbol;
    double  m_NumFri;
    double  m_NumSec;
    double  m_TrueAnswer;
    double  m_UserAnswer;
};
ostream & operator<<(ostream & out,SimpleCalculateExercise & cal)
{
    out << cal.m_NumFri<<" "<<cal.m_Symbol<<" "<<cal.m_NumSec<<" = ";
    return out;
}
SimpleCalculateExercise::SimpleCalculateExercise(int sum,int floor,int top)
{
    srand((unsigned int)time(NULL));
    c_SumCount=sum;
    c_RightCount=0;
    c_ErrorCount=0;
    s_Top=top;
    s_Floor=floor;
    a_Symbols=(char*)malloc(sizeof(char)*20);
    a_SymMask=(short*)malloc(sizeof(short)*20);
    char dona[]= {"+-*/%^"};
    a_SymLen=6;
    for(int i=0; i<a_SymLen; i++)
    {
        a_Symbols[i]=dona[i];
        a_SymMask[i]=0;
    }
}
SimpleCalculateExercise::~SimpleCalculateExercise()
{
    free(a_Symbols);
    free(a_SymMask);
}
void SimpleCalculateExercise::SetCalculType(SYM_TYPE type)
{
    for(int i=0; i<a_SymLen; i++)
    {
        if(type&(1<<i))
            a_SymMask[i]=1;
    }
    NextExercise();
}
int SimpleCalculateExercise::GetSumCount()
{
    return c_SumCount;
}
int SimpleCalculateExercise::GetRightCount()
{
    return c_RightCount;
}
int SimpleCalculateExercise::GetErrorCount()
{
    return c_ErrorCount;
}
void SimpleCalculateExercise::NextExercise()
{
    int index=rand()%a_SymLen;
    while(a_SymMask[index]==0)
        index=rand()%a_SymLen;
    m_Symbol=a_Symbols[index];

    m_NumFri=rand()%(s_Top-s_Floor)+s_Floor;
    m_NumSec=rand()%(s_Top-s_Floor)+s_Floor;
    if(m_Symbol=='/')
    {
        while(m_NumSec==0)
             m_NumSec=rand()%(s_Top-s_Floor)+s_Floor;
    }
    switch(m_Symbol)
    {
    case '+':
        m_TrueAnswer=m_NumFri+m_NumSec;
        break;
    case '-':
        m_TrueAnswer=m_NumFri-m_NumSec;
        break;
    case '*':
        m_TrueAnswer=m_NumFri*m_NumSec;
        break;
    case '/':
        m_TrueAnswer=m_NumFri/m_NumSec;
        break;
    case '%':
        m_TrueAnswer=(int)m_NumFri%(int)m_NumSec;
        break;
    case '^':
        m_TrueAnswer=pow(m_NumFri,m_NumSec);
        break;
    }
}
char SimpleCalculateExercise::GetSymbol()
{
    return m_Symbol;
}
double SimpleCalculateExercise::GetNumFrist()
{
    return m_NumFri;
}
double SimpleCalculateExercise::GetNumSecond()
{
    return m_NumSec;
}
bool SimpleCalculateExercise::SetAnswer(double answer)
{
    m_UserAnswer=answer;
    if(m_TrueAnswer==m_UserAnswer)
    {
        c_RightCount++;
        return true;
    }
    else
    {
        c_ErrorCount++;
        return false;
    }
}

void mySetTextColor(int BackGroundColor,int ForeColor)
{
    if(ForeColor<0 ||ForeColor>15)
        ForeColor=15;
    if(BackGroundColor<0 ||BackGroundColor>15)
        BackGroundColor=0;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),ForeColor+BackGroundColor*0x10);
}
int main(int argc,char * argv[])
{
    system("color f1");
    system("title 简单数学练习 Dev Ice2Faith");
    while(1)
    {
        mySetTextColor(15,1);
        cout << "请输入挑战题数 >> ";
        mySetTextColor(15,12);
        int sum=0;
        cin>>sum;
        mySetTextColor(15,1);
        cout << "请输入参与运算最小数 >> ";
        mySetTextColor(15,12);
        int down=0;
        cin>>down;
        mySetTextColor(15,1);
        cout << "请输入参与运算最大数 >> ";
        mySetTextColor(15,12);
        int up=0;
        cin>>up;
        mySetTextColor(15,1);
        cout << "请输入运算种类，例如最多：+-*/%^ >> ";
        mySetTextColor(15,12);
        int sym=0;
        char usym[20]= {0};
        cin >> usym;
        for(int i=0; i<6; i++)
        {
            switch(usym[i])
            {
            case '+':
                sym=sym|SYM_ADD;
                break;
            case '-':
                sym=sym|SYM_SUB;
                break;
            case '*':
                sym=sym|SYM_MUL;
                break;
            case '/':
                sym=sym|SYM_DIV;
                break;
            case '%':
                sym=sym|SYM_MOD;
                break;
            case '^':
                sym=sym|SYM_POW;
                break;
            default:
                break;
            }
        }
        SimpleCalculateExercise mycal(sum,down,up);
        mycal.SetCalculType(sym);
        mySetTextColor(15,1);
        cout << ">>>>>>>>>>>>" <<endl;
        for(int i=0; i<mycal.GetSumCount(); i++)
        {
            mySetTextColor(15,5);
            cout <<mycal;
            double answer=0;
            mySetTextColor(15,12);
            cin>>answer;
            if(mycal.SetAnswer(answer))
            {
                mySetTextColor(15,10);
              cout << " True"<<endl;
            }
            else
            {
                mySetTextColor(15,4);
                cout << " False"<<endl;
            }
            mycal.NextExercise();
        }
        mySetTextColor(15,1);
        cout << "练习结束！！"<<endl;
        cout << "正确率："<<mycal.GetRightCount()<<" / "<<mycal.GetSumCount()<<endl;
        mySetTextColor(15,0);
        cout << "--------------------------"<<endl;
        cout << "是否重新开始？1：是 else：否 >> "<<endl;
        if(getch()=='1')
            system("cls");
        else
            break;
    }

    return 0;
}
