#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
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
//ʮ����ת��������
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
    printf(">>\t%d->%d\t>/ ",bef,oth);
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
    printf("\n\n");
    free(p);
}

//��������תʮ���ƣ�����double���ͣ��������������ַ���txt,�ͽ��Ʊ�ʶoth
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

int main()
{
    system("title ����ת��Pro Dev: Ice2Faith");
    system("color f5");
    system("mode con cols=152 lines=35");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    printf("\t\t\t\t\t\t\t\t����ת��Pro\n\n");
    printf("\t\t\t\t\t\t\t\tDev: Ice2Faith\n\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    printf("���֧��ת������Ϊ64����,����Ϊ�ַ��������У����������\n");
    printf("\n>> ");
    int j=0;
    while(Change[j])
    {
        printf("%c",Change[j]);
        if(j%8==7)
            printf(" ");
        j++;
    }
    printf("\n\n>/ ");
    getch();
    char exit='0';
    int bef,oth;
    double num;
    char txt[100];
    system("cls");
    do
    {
        printf("�����룺��ʽ��\"ԭʼ����-Ŀ�����-ת����ֵ\"�����磺10-16-12.125\n>/ ");
        scanf("%d-%d-%s",&bef,&oth,txt);
        num=0;
        num=Oth2OTC(txt,bef);
        printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
        if(oth>=2&&oth<=64)
            OTC2Other(num,oth,bef);
        else
            printf("��֧��ת��Ϊ %d ����\n\n",oth);
        printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
        printf("�����������ƣ�>/ \n\n");
        OTC2Other(num,2,bef);
        OTC2Other(num,8,bef);
        OTC2Other(num,16,bef);
        OTC2Other(num,3,bef);
        OTC2Other(num,24,bef);
        OTC2Other(num,32,bef);
        OTC2Other(num,64,bef);
        printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
        printf("���� * �˳����������\n");
        exit=getch();
        system("cls");
    }
    while(exit!='*');

    return 0;
}


