#include <stdio.h>
#include <conio.h>  //非阻塞式输入字符，不在需要回车
#include <stdlib.h>  //系统连接定义，system函数
#include <Windows.h>  //延迟输出Sleep函数定义
#include <time.h>  //随机数生成使用需要
#include <math.h>  //Pow函数定义，计算前一个参数的后一个参数次方
#include <string.h>  //strlen函数定义，计算字符串长度

void FlashHeart();
int main()
{
    //system函数指令支持详见：打开cmd(WIN*R输出cmd回车)，键入help 查看全部指令，查看指定指令详细例如：help color
    FlashHeart();
}

void FlashHeart()
{
    system("title FlashHeart Dev: Ice2Faith");  //程序窗口左上角标题定义
    system("color f5");  //程序界面颜色定义
    srand((unsigned)time(NULL)+rand());
    char colorrun[] = { "14569cd" };  //存放随机字体色彩变换用
    char cmdcolor[20] = { '\0' };     //存放system函数命令
    char Text[100] = { "Love Needn't Reason!" };
    printf("欢快之旅即将启程>>>\n\n");
    printf("是否需要自定义填充内容？是请输入 1 否则使用默认\n\n>/ ");
    char user='0';
    user=getch();  //getch函数，只要键盘缓冲区存在字符就直接读取字符，不用回车，不显示读入值
    printf("%c\n",user);
    if(user=='1')
    {
        printf("请输入您的填充内容：\n>/ ");
        gets(Text);
    }
    double x1=1;
    fflush(stdin);
    printf("是否需要自定义心形大小？是请输入 1 否则使用默认\n\n>/ ");
    user='0';
    user=getch();
    if(user=='1')
    {
        printf("请输入您要更改的倍数，默认1,全屏可以试试2：\n>/ ");
        scanf("%lf",&x1);
        if(x1<=0)
            x1=0.1;
    }
    system("cls");  //清屏
    double x,y;
    int i=0,m,len,jj = 0;
    len=strlen(Text);  //计算输出填充文本长度，后面用
    for (x = 1.4; x >= -1.4; x -= 0.1/x1)  //定义X，Y变化范围
    {
        for (y = -2.4; y <= 2.4; y += 0.053/x1)
        {
            if (pow(x*x + y*y - 1, 3) - x*x*x*y*y <= 0)   //如果满足心形函数（X方+Y方-1）的立方-X立方*Y方<=0即在心形线内，输出字符，不在输出空格
            {

                printf("%c", Text[(i++)%len]);
                Sleep(5);
            }
            else
            {
                printf(" ");
            }

            if (jj % 60 == 0)  //JJ为自增变量，如果满足是60的倍数，就随机切换字体颜色
            {
                m = rand() % 7;
                sprintf(cmdcolor, "color f%c\0", colorrun[m]);  //利用sprintf将引号内内容传到cmdcolor数组中，最后\0标志语句结束
                system(cmdcolor);  //调用system函数执行cmdcolor数组内指令
            }
            jj++;

        }
        printf("\n");   //每一行输出结束换行
    }
    char exit='0';
    printf(">/ Input \"*\" Exit the APP\n\n");
    do  //检测用户是否要退出，不退出则循环切换字体颜色
    {
        if(kbhit()!=0)  //kbhit函数用于检测键盘缓冲区是否存在字符，存在返回非0
        exit=getch();   //如果存在字符就读取，不存在就不读，依旧是初始赋值
        m = rand() % 7;
        sprintf(cmdcolor, "color f%c\0", colorrun[m]);
        system(cmdcolor);
        Sleep(35);  //延迟35毫秒，传入1000即为1秒
    }
    while(exit!='*');
}
