Calculator::Calculator():Pi(3.1415926535897932384626),IsSingel(0)
{
    Num.top=-1;
    Dona.top=0;
    Dona.dona[0]='=';
    PreStr=String;
    char D[20]= {"+-*/()=^"};
    char Singel[20]= {"%SsCcTtPp!"};
    int ru[20][20]=
    {
        /*+ - * / ( ) = ^*/
        {0,0,0,0,1,1,1,0},//+
        {1,0,0,0,1,1,1,0},//-
        {1,1,0,1,1,1,1,0},//*
        {1,1,1,0,1,1,1,0},///
        {1,1,1,1,1,1,1,1},//(
        {0,0,0,0,9,9,1,0},//)
        {0,0,0,0,1,1,9,0},//=
        {1,1,1,1,1,1,1,0}//^

    };
    for(int i=0; i<20; i++)
    {
        AllDona[i]=D[i];
        SingelDona[i]=Singel[i];
        for(int j=0; j<20; j++)
        {
            Rules[i][j]=ru[i][j];
        }
    }
}
bool Calculator::GetString(char * InString)
{
    char * pre=String;
    bool ExistEqual=false;
    while(*InString)
    {
        if(*InString==' '||*InString=='\t'||*InString=='\n')
            continue;
        if((*InString<'0'||*InString>'9'))
        {
            int k=0;
            for(int i=0; i<20; i++)
            {
                if(SingelDona[i]==*InString)
                    k++;
                if(AllDona[i]==*InString)
                    k++;
            }
            if(k==0)
                return false;
        }
        *(pre++)=*(InString++);
        if(*(InString-1)=='=')
        {
            ExistEqual=true;
            break;
        }
    }
    return ExistEqual;
}
int Calculator::IsNumber(char * String)
{
    if(*String>='0'&&*String<='9')
        return 1;
    else
        return 0;
}
bool Calculator::CalculateMain(char * InString,double * result)
{
    *result=0;
    if(!GetString(InString))
        return false;
    double numr=0,num1=0,num2=0;
    char donar,dona1;
    while(*PreStr)
    {
        if(IsNumber(PreStr))
        {
            istrdouble(PreStr,1,&numr,&PreStr);
            Num.num[++Num.top]=numr;
        }
        else
        {
            istrchar(PreStr,&donar,&PreStr);
            IsSingel=0;
            for(int i=0; i<20; i++)
            {
                if(SingelDona[i]==donar)
                {
                    IsSingel=1;
                    break;
                }
            }
            if(IsSingel)
            {
                Num.num[Num.top]=CalcuSingel(Num.num[Num.top],donar);
                continue;
            }
            if(donar=='(')
            {
                Dona.dona[++Dona.top]=donar;
                continue;
            }
            if(donar==')')
            {
                while(Dona.dona[Dona.top]!='(')
                {
                    CalculPop();
                }
                Dona.top--;
                continue;
            }
            int cmp=CompareDonaTop(donar);
            if(cmp==1)
            {
                Dona.dona[++Dona.top]=donar;
            }
            if(cmp==0)
            {
                CalculPop();
                Dona.dona[++Dona.top]=donar;
            }
            if(cmp==9)
            {
                Dona.top--;
            }
            if(donar=='=')
            {
                Dona.top--;
                while(Num.top!=0)
                {
                    CalculPop();
                }
                break;
            }
        }
    }
    *result=Num.num[Num.top];
    return true;
}
void Calculator::CalculPop()
{
    double num1=0,num2=0;
    char dona1;
    num2=Num.num[Num.top--];
    num1=Num.num[Num.top--];
    dona1=Dona.dona[Dona.top--];
    double presult=Calcu(num1,num2,dona1);
    Num.num[++Num.top]=presult;
}
int Calculator::CompareDonaTop(char predona)
{
    char topdona=Dona.dona[Dona.top];
    int i=0;
    int x=-1,y=0-1;
    while(AllDona[i])
    {
        if(topdona==AllDona[i])
            y=i;
        if(predona==AllDona[i])
            x=i;
        if(x!=-1&&y!=-1)
            break;
        i++;
    }
    return Rules[x][y];
}
double Calculator::Calcu(double a,double b,char k)
{
    double result=0;
    switch(k)
    {
    case '+':
        result=a+b;
        break;
    case '-':
        result=a-b;
        break;
    case '*':
        result=a*b;
        break;
    case '/':
        result=a/b;
        break;
    case '^':
        result=pow(a,b);
        break;
    }
    return result;
}
double Calculator::CalcuSingel(double a,char k)
{
    double result=0;
    switch(k)
    {
    case 'S':
    case 's':
        result=sin((a/360.0)*(2*Pi));
        break;
    case 'C':
    case 'c':
        result=cos((a/360.0)*(2*Pi));
        break;
    case 'T':
    case 't':
        result=tan((a/360.0)*(2*Pi));
        break;
    case '%':
        result=a/100.0;
        break;
    case 'P':
    case 'p':
        result=a*Pi;
        break;
    case '!':
    {
        result=1;
        for(int i=a; i>=1; i--)
            result*=i;
        break;
    }

    }
    return result;
}
int Calculator::istrdouble(char * stream,int counter,double * save,char ** newstrspace)
{
    int i=0;
    double num=0;
    int deline=0;
    while(*stream)
    {
        if(*stream>='0'&&*stream<='9')
        {
            num=0;
            deline=0;
            if(*(stream-1)=='-')
                deline=1;
            while(*stream>='0'&&*stream<='9')
            {
                num*=10;
                num+=(int)(*stream-'0');
                stream++;
            }
            if(*stream=='.')
            {
                stream++;
                double tmp=0.1;
                while(*stream>='0'&&*stream<='9')
                {
                    num+=tmp*(int)(*stream-'0');
                    tmp*=0.1;
                    stream++;
                }
            }/*
            if(deline)
                num=0-num;*/
            *save=num;
            save++;
            i++;
            if(i==counter)
                break;
        }
        else
            stream++;
    }
    *newstrspace=stream;
    return i;
}
int Calculator::istrchar(char * stream,char * save,char ** newstrspace)
{
    *save=*(stream++);
    *newstrspace=stream;
    return (*stream)=='\0'?0:1;
}
void Calculator::HelpText(char * Text)
{
    char Help[4096]= {\
                      "\t\tAbout & Help\n\n\
    Class:\tSimple Science calculator\n\
    Dev:\tIce2Faith\n\
    Date:\tfirst build at 20190106\n\
    class using:\n\
    \t----------------------------------\n\
    \tCalculator Calcu;\n\
    \tchar InString[1024];\n\
    \tdouble result;\n\
    \tbool legal=Calcu.CalculateMain(InString,&result);\n\
    \t----------------------------------\n\
    Running on English IME mode\n\
    support double type number calculate\n\
    support donate:+ - * / ( ) ^ % S/s C/c T/t P/p ! =\n\n\
    Using :\n\n\
    \t^:2^3=8\t\tS/s.C/c.T/t=sin.cos.tan\n\
    \tP/p:3.14..\t!:4!=4*3*2*1\n\
    \t%:3=10*30%\tS/s.C/c.T/t:60s=sin60..\n\n\
    Example:\n\n\
    \t(3+5*2-4/2)+1=\t\t\t12\n\
    \t3+2*5-(2*2-3)=\t\t\t12\n\
    \t60s+60c+60t+4!+10*30%+2p=\t36.3813\n\n\0"\
                     };
    int i=0;
    while(Help[i])
    {
        *(Text++)=Help[i++];
    }
}
