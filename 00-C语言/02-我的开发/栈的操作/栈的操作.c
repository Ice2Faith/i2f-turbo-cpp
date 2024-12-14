#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define MAXSIZE 100
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
void VcantStack(StackList * S)
{
    S->top=-1;
}
int main()
{
    system("color f5");
    system("title ջ�Ļ������� Dev: Ice2Faith");
    printf("---------------------------------\n\n");
    printf("\tջ�Ļ�������\n\n");
    printf("\tDev: Ice2Faith\n\n");
    printf("---------------------------------\n\n");
    printf("���������\n>/ ");
    getch();
    StackList * S=DefultStack();
    int num;
    char exit='c';
    do
    {
        system("cls");
        printf("������Ԫ�ؽ�ջ����-999������\n>/ ");
        scanf("%d",&num);
        while(num!=-999)
        {
            Push(S,num);
            scanf("%d",&num);
        }
        printf("\n\n����Ϊ����ջ��\n>/ ");
        while(Pop(S,&num))
        {
            printf("->%d",num);
        }
        printf("\n\n�˳������� * ���������²��ԣ�\n>/ ");
        exit=getch();
    }while(exit!='*');
    free(S);
    return 0;
}
