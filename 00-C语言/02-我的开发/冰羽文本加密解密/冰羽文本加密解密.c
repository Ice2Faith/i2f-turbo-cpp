#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>
int  LOCKER();
int  UNLOCKER();
void help();
//开头说明,给定标题字符串
void Head(char * title);
//结尾说明
void End();
//给定字符串逐个输出,间隔时间自定义
void Bitprint(char *p, int between);
//屏幕提示：type：-1错误，0警告，1通过；before：之前的颜色如：f5
void Screentips(int type,char * before);
//随机控制面板色,参数非零只改变前景色，背景白色
void Randcolor(int mode);
char endch='#';
void main()
{
    int k=0;
    char sel;
    while(k==0)
    {
        endch='#';
        Head("冰羽加密解密程序");
        Bitprint("\n\t请选择：\n\n\t1.加密文本\n\n\t2.解密文本\n\n\t3.查看帮助\n\n\t0.退出程序\n\n----------------------------------------\n\n>> ",6);
        fflush(stdin);
        sel=getch();
        putchar(sel);
        fflush(stdin);
        Sleep(480);
        system("cls");
        if(sel=='1')
        {
            printf("默认结束符为\'%c\',需要修改请输入 \'1\' 进入修改 >> ",endch);
            char change=getch();
            putchar(change);
            if(change=='1')
            {
                printf("\n请输入结束符(ASCII,此处切换为英文输入法): >> ");
                endch=getch();
                putchar(endch);
                printf("\n新结束符为：>> \'%c\'\n",endch);
            }
            LOCKER();
            system("pause");
        }
        else if(sel=='2')
        {
            UNLOCKER();
            system("pause");
        }
        else if(sel=='3')
        {
            help();
            system("pause");
        }
        else if(sel=='0')
        {
            Screentips(0,"f5");
            Bitprint("\n\n\t正在为您退出程序......\n\n>> ",10);
            k=1;
        }
        else
        {
            Screentips(-1,"f5");
            Bitprint("\n\n\t是没有看清楚吗？\n\n\t再来一次！！\n\n>> ",6);
        }

        Sleep(1200);
        system("cls");

    }
    End();
}
int  LOCKER()
{
    char * temp=(char *)malloc(sizeof(char));
    char key[100]= {"Ice2Feathers"};
    FILE * Lock=fopen("LockText.txt","wb");
    Bitprint("\n\n\t请输入您的加密内容：\n\n>> \n",20);
    int LenKey=strlen(key);
    int counter=0;
    *temp=getchar();
    while(*temp!=endch)
    {
        *temp^=key[(counter++)%LenKey];
        counter%=LenKey;
        fwrite(temp,1,sizeof(char),Lock);
        *temp=getchar();
    }
    fclose(Lock);
    printf("\n\n自动保存到 \"LockText.txt\"\n");
    Screentips(1,"f5");
}
int  UNLOCKER()
{
    char * temp=(char *)malloc(sizeof(char));
    char key[100]= {"Ice2Feathers"};
    FILE * Lock=fopen("LockText.txt","rb");
    FILE * UnLock=fopen("UnLockText.txt","w");
    Bitprint("\n\n\t这是您的解密内容：\n\n>> \n",20);
    int LenKey=strlen(key);
    int counter=0;
    while(!feof(Lock))
    {
        if(fread(temp,1,sizeof(char),Lock)==0)
            break;
        *temp^=key[(counter++)%LenKey];
        counter%=LenKey;
        fprintf(UnLock,"%c",*temp);
        printf("%c",*temp);
    }
    fclose(Lock);
    fclose(UnLock);
    printf("\n\n自动保存到 \"UnLockText.txt\"\n");
    Screentips(1,"f5");
}

//开头说明,给定标题字符串
void Head(char * title)
{
    char titlea[100];
    //此处可任意添加输出内容，最多100行
    char headtxt[100][100] =
    {
        "\n----------------------------------------\n",
        "\n\t \n",
        "\n\t By: Ice2Feathers \n",
        "\n----------------------------------------\n"
    };
    sprintf(titlea, "title %s By : Ice2Feathers", title);
    sprintf(headtxt[1], "\n\t %s\n", title);

    system(titlea);
    system("color f5");

    int k = 0, counter = 0;
    while (headtxt[k][0] != '\0')
    {
        counter++;
        k++;
    }
    int i, j;
    for (i = 0; i < counter; i++)
    {

        j = 0;
        while (headtxt[i][j] != '\0')
        {
            printf("%c", headtxt[i][j]);
            Sleep(20);
            j++;
        }
    }
}
//------------------------------------------------------------------------------------------------------
//结尾说明
void End()
{
    printf("\n");
    Sleep(1200);
    Sleep(800);
    system("color f9");
    system("cls");
    //此处可任意添加输出内容，最多100行
    char endtxt[100][100] =
    {
        "\n\n----------------------------------------\n",
        "\n\n\t人生若只如初见!!!\n",
        "\n\tThanks for your used!!!\n",
        "\n\t By: Ice2Feathers \n",
        "\n\n----------------------------------------\n"
    };
    int k = 0, counter = 0;
    while (endtxt[k][0] != '\0')
    {
        counter++;
        k++;
    }
    int i, j;
    for (i = 0; i < counter; i++)
    {
        j = 0;
        while (endtxt[i][j] != '\0')
        {
            printf("%c", endtxt[i][j]);
            Sleep(20);
            j++;
        }
        Randcolor(1);
    }
    system("color 75");
    Sleep(1000);
    system("color 79");
    Sleep(1000);
    system("color 70");
    Sleep(1000);
}
//------------------------------------------------------------------------------------------------------
//给定字符串逐个输出,间隔时间自定义
void Bitprint(char *p, int between)
{
    while(*p!='\0')
    {
        printf("%c",*p);
        p++;
        Sleep(between);
    }
}
//屏幕提示：type：-1错误，0警告，1通过；before：之前的颜色如：f5
void Screentips(int type,char * before)
{
    char beforec[20];
    sprintf(beforec,"color %s",before);
    if(type==-1)
    {
        system("color cf");
    }
    else if(type==0)
    {
        system("color e0");
    }
    else if(type==1)
    {
        system("color 9f");
    }
    Sleep(90);
    system(beforec);
}
//随机控制面板色,参数非零只改变前景色，背景白色
void Randcolor(int mode)
{
    srand((unsigned)time(NULL) + rand());
    int f = rand() % 16, b = rand() % 16;
    char color[] = { "0123456789abcdef" };
    char cmd[100];
    if (mode == 0)
    {
        while (f == b)
            b = rand() % 16;
        sprintf(cmd, "color %c%c", color[f], color[b]);
        system(cmd);
    }
    else
    {
        sprintf(cmd, "color f%c", color[f]);
        system(cmd);
    }
}
void help()
{
    system("cls");
    printf("\n\n");
    printf("\t名称:\t冰羽文本加密解密\n\n");
    printf("\t开发:\tIce2Feathers\n\n");
    printf("\t\t您的加密文本将会保存到 \"LockText.txt\".\n\n");
    printf("\t\t您的解密文本将会保存到 \"UnLockText.txt\".\n\n");
    printf("\t加密:\t输入文本加密，支持多行，默认结束标记并回车： \'#\'.\n\n");
    printf("\t解密:\t从文件解密，文件： \"LockText.txt\".\n\n");
    printf("\t其他:\t中英文混输支持，请不要修改加密文件，否则解密错误\n\n");
    printf("\t\t不常用字符集：~ @ # $ & * { } [ ] .\n\n");
    printf("\t注意:\t新文件将会覆盖旧文件，注意保存！！\n\n\t");
}
