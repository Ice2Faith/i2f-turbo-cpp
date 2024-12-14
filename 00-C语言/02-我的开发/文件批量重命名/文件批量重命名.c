#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
#include<time.h>
#define APPNAME "文件批量重命名"
//返回当前时间信息，mode值0日期，1时间，2星期
int PresentDATE(int mode)
{
    time_t PresentTime;
    PresentTime=time(NULL);
    struct tm * PresentDate;
    PresentDate=localtime(&PresentTime);
    int pdate,ptime;
    pdate=(PresentDate->tm_year+1900)*10000+(PresentDate->tm_mon+1)*100+PresentDate->tm_mday;
    ptime=(PresentDate->tm_hour)*10000+(PresentDate->tm_min)*100+PresentDate->tm_sec;
    if(mode==0)
        return pdate;
    else if(mode==1)
        return ptime;
    else if(mode==2)
        return PresentDate->tm_wday;
    else
        return -1;
}
//判断是否是文件，是文件返回1，是文件夹返回0
int IsFIle(char * filename[])
{
    return fopen(filename[0],"r")==NULL?0:1;
}
//显示传入值
void DisplayFile(int argc,char *argv[])
{
    printf(">/ sum: %d\n\n",argc);
    for(int i=0; i<argc; i++)
    {
        printf(">/ %s --> %d\n",argv[i],IsFIle(&argv[i]));
    }

}
//批量重命名方法
int RenameFile(int argc,char *argv[])
{
    char choice='v';
    printf("------------------------------\n\n");
    printf("        文件批量重命名        \n\n");
    printf("        Dev: Ice2Faith        \n\n");
    printf("\t请选择：\n\n");
    printf("\t1.原文件名-日期时间\n\n");
    printf("\t2.原文件名-日期-时间\n\n");
    printf("\t3.原文件名-日期\n\n");
    printf("\t4.原文件名-时间\n\n");
    printf("\t5.原文件名-序号\n\n");
    printf("\t6.新文件名-序号\n\n");
    printf("\t7.新文件名-序号-日期时间\n\n");
    printf("\t8.修改后缀\n\n");
    printf("\t9.注意事项\n\n");
    printf("\t0.取消操作\n\n");
    printf("------------------------------\n\n>/ ");
    while(choice<'0'||choice>'9')
        choice=getch();

    int sel=(int)(choice-'0');
    printf("%d\n",sel);
    if(sel==0)
        return 0;
    if(sel==9)
    {
        system("cls");
        printf("------------------------------\n\n");
        printf("           注意事项           \n\n");
        printf("     请不要改动本程序名       \n\n");
        printf("   否则可能会导致无法使用     \n\n");
        printf("       若误更改，请改回       \n\n");
        printf("    默认名： 文件批量重命名   \n\n");
        printf("------------------------------\n\n");
        Sleep(2000);
        return 0;
    }
    char name[400]= {'\0'};
    char time[400]= {'\0'};
    char before[400]= {'\0'};
    char behind[400]= {'\0'};
    char File[100][1024]= {'\0'};
    char mind[2048]= {'\0'};
    int len,dsp,psp,j,k,con=0;
    int usernum=1;
    char userdefined[400]= {'\0'};
    char after[20]= {'\0'};
    fflush(stdin);
    switch(sel)
    {

    default:
    {
        break;
    }
    case 5:
    {

        printf("请输入初始序号：\n\n>/ ");
        scanf("%d",&usernum);
        break;
    }

    case 6:
    {
        fflush(stdin);
        printf("请输入新文件名：\n\n>/ ");
        gets(userdefined);
        printf("请输入初始序号：\n\n>/ ");
        scanf("%d",&usernum);
        break;
    }

    case 7:
    {
        fflush(stdin);
        printf("请输入新文件名：\n\n>/ ");
        gets(userdefined);
        printf("请输入初始序号：\n\n>/ ");
        scanf("%d",&usernum);
        break;
    }

    case 8:
    {
        printf("请输入后缀：(.XXX)\n\n>/ ");
        fflush(stdin);
        scanf("%s",after);
        break;
    }

    }

    for(int i=0; i<argc; i++)
    {
        //清空数组内容
        for(int b=0; b<400; b++)
        {
            if(name[b]!='\0')
                name[b]='\0';
            if(before[b]!='\0')
                before[b]='\0';
            if(time[b]!='\0')
                time[b]='\0';
            if(behind[b]!='\0')
                behind[b]='\0';
        }
        strcpy(File[i],argv[i]);
        //统计路径长度
        len=0;
        while(File[i][len]!='\0')
            len++;
        //计算文件夹标识符位置
        dsp=0;
        while(File[i][len-dsp]!='\\')
        {
            dsp++;
        }
        dsp=len-dsp+1;
        //计算.的那位置
        psp=0;
        while(File[i][len-psp]!='.')
        {
            if(File[i][len-psp]=='\\')
            {
                psp=0;
                break;
            }
            psp++;
        }
        psp=len-psp;
        //复制小数点以后的后缀进去behind
        j=0;
        while(File[i][psp+j]!='\0')
        {
            behind[j]=File[i][psp+j];
            j++;
        }
        //复制小数点以前的名字进去before
        k=0;
        while(File[i][dsp+k]!='.'&&File[i][dsp+k]!='\0')
        {
            before[k]=File[i][dsp+k];
            k++;
        }
        //如果是本程序的话，跳过
        if(strcmp(before,APPNAME)==0&&strcmp(behind,".exe")==0)
            continue;

        switch(sel)
        {
        case 1:
        {
            sprintf(time,"-%d%d\0",PresentDATE(0),PresentDATE(1));
            strcat(name,before);
            strcat(name,time);
            strcat(name,behind);
            break;
        }

        case 2:
            //合并名称,原名称-日期-时间
        {
            sprintf(time,"-%d-%d\0",PresentDATE(0),PresentDATE(1));
            strcat(name,before);
            strcat(name,time);
            strcat(name,behind);
            break;
        }

        case 3:
        {
            sprintf(time,"-%d\0",PresentDATE(0));
            strcat(name,before);
            strcat(name,time);
            strcat(name,behind);
            break;
        }

        case 4:
        {
            sprintf(time,"-%d\0",PresentDATE(1));
            strcat(name,before);
            strcat(name,time);
            strcat(name,behind);
            break;
        }

        case 5:
        {
            sprintf(time,"-%d",usernum+i);
            strcat(name,before);
            strcat(name,time);
            strcat(name,behind);
            break;
        }

        case 6:
        {
            sprintf(time,"%s-%d",userdefined,usernum+i);
            strcat(name,time);
            strcat(name,behind);
            break;
        }

        case 7:
        {
            sprintf(time,"%s-%d-%d%d",userdefined,usernum+i,PresentDATE(0),PresentDATE(1));
            strcat(name,time);
            strcat(name,behind);
            break;
        }

        case 8:
        {
            if(after[0]!='.')
                sprintf(behind,".%s\0",after);
            else
                sprintf(behind,"%s\0",after);
            strcat(name,before);
            strcat(name,behind);
            break;
        }

        }
        //执行重命名操作
        sprintf(mind,"ren \"%s\" \"%s\"\0",File[i],name);
        system(mind);
    }


}

//主方法
int main(int argc,char *argv[])
{
    system("color f5");
    system("mode con cols=48 lines=38");
    system("title 文件批量重命名 Dev: Ice2Faith");
    RenameFile(argc,&argv[0]);
    return 0;
}

