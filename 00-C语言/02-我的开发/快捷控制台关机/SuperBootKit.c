#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<windows.h>

char Meau();
void SwitchPower(char sel);
void Bootmind(int mode);
double String2DoublePro(char * String,int * pre);
void Bitprint(char *p, int between);
void Screentips(int type,char * before);
void End();
void Randcolor(int k);

int main()
{
    system("mode con cols=55 lines=40");
    system("color b5");
    Sleep(90);
    int k=1;
    char sel;
    while(k==1)
    {
        system("color f5");
        sel=Meau();
        if(sel=='0')
            k=0;
        else
            SwitchPower(sel);

        Sleep(1200);
        system("cls");
    }
    End();
    return 0;
}
char Meau()
{
    system("title Super Boot Kit By Ice2Feathers");
    Bitprint("------------------------------------------\n\n\t    >> Super Boot Kit <<\n\n------------------------------------------\n",2);
    Bitprint("请选择：\tTips：选择后立即项不可取消\n\n",1);
    Bitprint("\t1.立即关机\n\n",1);
    Bitprint("\t2.立即重启\n\n",1);
    Bitprint("\t3.锁定屏幕\n\n",1);
    Bitprint("\t4.30分钟后关机\n\n",1);
    Bitprint("\t5.1小时后关机\n\n",1);
    Bitprint("\t6.自定义延时关机*\n\n",1);
    Bitprint("\t7.自定义延时重启*\n\n",1);
    Bitprint("\t8.取消计划关机/重启任务*\n\n",1);
    Bitprint("\t9.帮助 & 命令行\n\n",1);
    Bitprint("\t0.退出程序\n\n",1);
    Bitprint("------------------------------------------\n\n>> ",2);
    fflush(stdin);
    char sel;
    do
    {
        sel=getch();
        if(sel<'0'||sel>'9')
            Screentips(0,"f5");
    }
    while(sel<'0'||sel>'9');
    printf("%c\n",sel);
    Screentips(1,"f5");
    Sleep(90);
    return sel;
}

void SwitchPower(char sel)
{
    switch(sel)
    {
    case '1':
    {
        Bitprint("\n一段延迟之后为您关机，请稍后\n\n",15);
        Sleep(1200);
        system("shutdown /s /f /t 0");
        break;
    }
    case '2':
    {
        Bitprint("\n一段延迟之后为您重启，请稍后\n\n",15);
        Sleep(1200);
        system("shutdown /r /f /t 0");
        break;
    }
    case '3':
    {
        Bitprint("\n一段延迟之后为您锁屏，请稍后\n\n",15);
        Sleep(1200);
        system("rundll32 user32.dll,LockWorkStation");
        break;
    }
    case '4':
    {
        Bitprint("\n正在为您执行操作！！\n\n",15);
        Sleep(800);
        system("shutdown /s /f /t 1800");
        break;
    }
    case '5':
    {
        Bitprint("\n正在为您执行操作！！\n\n",15);
        Sleep(800);
        system("shutdown /s /f /t 3600");
        break;
    }
    case '6':
    {
        Bootmind(0);
        break;
    }
    case '7':
    {
        Bootmind(1);
        break;
    }
    case '8':
    {
        Bitprint("\n正在为您执行操作！！\n\n",15);
        system("shutdown /a");
        Sleep(800);
        break;
    }
    case '9':
    {
        Bitprint("\n一段延迟之后为您进入命令行，请稍后\n\n",1);
        Sleep(800);
        system("start cmd /k \"echo Tips: 输入\"Help\"获取帮助及所有命令,输入\"Exit\"退出命令行,输入后回车\"Enter\"开始执行！！----Ice2Feathers\"");
        break;
    }
    }

}

void Bootmind(int mode)
{
    fflush(stdin);
    int num[3]= {0};
    int time=0;
    int pre=0;
    double temp=0;
    char Intime[100];
    Bitprint("\n请输入延迟时间，如3h28s/2h15m20/etc.:\n\n",2);
    gets(Intime);
    while(Intime[pre])
    {
        temp=String2DoublePro(&Intime[pre],&pre);
        if(Intime[pre]=='h'||Intime[pre]=='H')
        {
            time+=(int)(temp*3600);
        }
        else if(Intime[pre]=='m'||Intime[pre]=='M')
        {
            time+=(int)(temp*60);
        }
        else if(Intime[pre]=='s'||Intime[pre]=='S')
        {
            time+=(int)(temp*1);
        }
        else
        {
            time+=(int)(temp*1);
            break;
        }

        pre++;
    }

    char mind[80]= {'\0'};
    if(mode==0)
        sprintf(mind,"shutdown -s -f -t %d",time);
    else if(mode==1)
        sprintf(mind,"shutdown -r -f -t %d",time);

    Screentips(1,"f5");
    Bitprint("\n正在为您执行操作！！\n\n",15);
    system(mind);
    Sleep(800);

}

double String2DoublePro(char * String,int * pre)
{
    double result=0;
    while(*String<'0'||*String>'9')
    {
        String++;
        (*pre)++;
    }

    while(*String>='0'&&*String<='9')
    {
        result*=10;
        result+=(*String-'0');
        String++;
        (*pre)++;

    }
    if(*String=='.')
    {
        String++;
        (*pre)++;
        int i=1;
        while(*String>='0'&&*String<='9')
        {
            result+=(*String-'0')*pow(0.1,(double)i++);
            String++;
            (*pre)++;
        }
    }

    return result;
}
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
void Bitprint(char *p, int between)
{
    while(*p!='\0')
    {
        printf("%c",*p);
        p++;
        Sleep(between);
    }
}
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
