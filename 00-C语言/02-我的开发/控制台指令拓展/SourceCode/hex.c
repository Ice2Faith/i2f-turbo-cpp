#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<windows.h>
#define MAXSIZE 1000
typedef int elemtype;
typedef struct
{
    elemtype data[MAXSIZE];
    int top;
} StackList;
StackList * DefultStack()
{
    StackList * p=(StackList *)malloc(sizeof(StackList));
    p->top=-1;
}
int IsEmpty(StackList * S)
{
    return S->top==-1;
}
int IsFull(StackList * S)
{
    return S->top==MAXSIZE-1;
}
int Push(StackList * S,elemtype x)
{
    if(IsFull(S))
        return 0;
    S->data[++S->top]=x;
    return 1;
}
int Pop(StackList * S,elemtype * x)
{
    if(IsEmpty(S))
        return 0;
    *x=S->data[S->top--];
    return 1;
}
char Change[MAXSIZE]= {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwsyz@#\0"};
//十进制转其他进制
void OTC2Other(double num,int oth,int bef)
{
    int otc=(int)num;
    double flo=num-otc;
    int FloNum[MAXSIZE];
    StackList * p;
    p=DefultStack();
    while(otc!=0)
    {
        Push(p,otc%oth);
        otc=(int)otc/oth;
    }
    int i=0;
    while(flo!=0.0&&i<100)
    {
        FloNum[i]=(int)(flo*oth);
        flo=flo*oth-FloNum[i];
        i++;
    }
    FloNum[i]=0;
    FloNum[++i]=-9999;
    printf(">> %2d->%2d >> ",bef,oth);
    i=0;
    while(!IsEmpty(p))
    {
        Pop(p,&otc);
        printf("%c",Change[otc]);
        if(i%4==3)
            printf(" ");
        i++;
    }
    printf(".");
    i=0;
    while(FloNum[i]!=-9999)
    {
        printf("%c",Change[FloNum[i]]);
        if(i%4==3)
            printf(" ");
        i++;
    }
    printf("\n");
    free(p);
}

//其他进制转十进制，返回double类型，传入其他进制字符串txt,和进制标识oth
double Oth2OTC(char * txt,int oth)
{
    double result=0;
    while(*txt!='.'&&*txt!='\0')
    {
        result*=oth;
        if(*txt>='0'&&*txt<='9')
            result+=(*txt-'0');
        else if(*txt>='A'&&*txt<='Z')
            result+=(*txt-'A'+10);
        else if(*txt>='a'&&*txt<='z')
            result+=(*txt-'a'+10);
        txt++;
    }
    txt++;
    int i=1;
    while(*txt>='0'&&*txt<='9')
    {

        if(*txt>='0'&&*txt<='9')
            result+=(*txt-'0')*pow(1.0/oth,(double)i++);
        else if(*txt>='A'&&*txt<='Z')
            result+=(*txt-'A'+10)*pow(1.0/oth,(double)i++);
        else if(*txt>='a'&&*txt<='z')
            result+=(*txt-'a'+10)*pow(1.0/oth,(double)i++);
        txt++;
    }
    return result;
}
void help()
{
    printf("\tsource direct number number ...\n");
    printf("\t\tsource : number's source radix\n");
    printf("\t\tdirect : number's direct radix\n");
    printf("\t\tnumber : number of need to exchange\n");
    printf("\tsuch as:\n");
    printf("\t\thex 10 16 12.125 17.178\n");
    printf("\t\thex 16 2 A.BC\n");
}
int main(int argc,char * argv[])
{
    rename(argv[0],"hex.exe");
    if(argc>1)
    {
        if(argv[1][0]=='?')
        {
            help();
            return 0;
        }
    }
    if(argc<4)
        return 0;
    int bef=10,oth=16;
    double num;
    sscanf(argv[1],"%d",&bef);
    sscanf(argv[2],"%d",&oth);
    if(bef<2||bef>64||oth<2||oth>64)
        return 0;
    for(int i=3;i<argc;i++)
    {
        num=Oth2OTC(argv[i],bef);
        OTC2Other(num,oth,bef);
    }
    return 0;
}


