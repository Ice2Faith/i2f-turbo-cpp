#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<string.h>
#define MAXLINE 1024
#define MAXLEN 1024

char RandList[MAXLINE][MAXLEN];
int ListLen=0;
void InitEn();
void Trim(char * str);
void ReadList(FILE * fin);
void RandOutList();
void RandNumber();
int main(int argc,char * args[])
{
    InitEn();
    FILE * fin=NULL;
    if(argc<2)
    {
        fin=fopen("configure.txt","r");
    }
    else
    {
        fin=fopen(args[1],"r");
    }
    if(fin!=NULL)
    {
        ReadList(fin);
        RandOutList();
        fclose(fin);
    }
    else
    {
        printf("Error! \tNot Find File: configure.txt\n");
        printf("\tOr Not Accept File\n");
        printf("\tPlease input choice item into configure.txt\n");
        printf("\tEvery Line will become a choice item\n");
        RandNumber();
    }
    printf("\nPress any key exit!\n>/ ");
    getch();
    return 0;
}
void InitEn()
{
    system("color f1");
    system("title Random Select dev ZeroFiend");
    srand((unsigned int)time(NULL));
    ListLen=0;
}
void RandNumber()
{
    int minnum=0;
    int maxnum=100;
    printf("Please input min number:\n>/ ");
    scanf("%d",&minnum);
    printf("Please input max number:\n>/ ");
    scanf("%d",&maxnum);
    int count=1;
    printf("Please input Random times:\n>/ ");
    scanf("%d",&count);
    for(int i=0; i<count; i++)
    {
        printf(">> %d:\t %d\n",i+1,rand()%(maxnum-minnum+1)+minnum);
    }
}
void RandOutList()
{
    int count=1;
    printf("Please input Random times:\n>/ ");
    scanf("%d",&count);
    for(int i=0; i<count; i++)
    {
        printf(">> %d:\t %s\n",i+1,RandList[rand()%ListLen]);
    }

}
void Trim(char * str)
{
    int i=0;
    while(str[i]!='\0' && (str[i]==' '||str[i]=='\t'||str[i]=='\n'||str[i]=='\r'))
        i++;
    int j=0;
    while(str[i])
    {
        str[j]=str[i];
        j++;
        i++;
    }
    str[j]=0;
    j--;
    while(i>0 && (str[j]==' '||str[j]=='\t'||str[j]=='\n'||str[j]=='\r'))
    {
        str[j]=0;
         i--;
    }

}
void ReadList(FILE * fin)
{
    while(!feof(fin))
    {
        fgets(RandList[ListLen],MAXLEN-1,fin);
        Trim(RandList[ListLen]);
        if(strlen(RandList[ListLen])>0)
            ListLen++;
        if(ListLen>=MAXLINE)
            break;
    }

}
