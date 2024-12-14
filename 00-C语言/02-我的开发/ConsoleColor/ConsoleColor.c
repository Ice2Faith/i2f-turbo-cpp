#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
void SetGotoxy(int lines,int cols);
void _SetTextColor(int ForeColor,int BackGroundColor);
int main()
{
    system("title Console Color Viewer by Ice2Faith");
    int color[17]={0,8,7,15,4,12,6,14,2,10,11,3,9,1,13,5};
    char ccolor[17]={"087F4C6E2AB391D5"};
    char scolor[17][20]={
    "黑色","灰色","白色","亮白色","红色","淡红色","黄色","淡黄色","绿色","淡绿色","淡浅绿色","浅绿色","淡蓝色","蓝色","淡紫色","紫色"
    };
    system("color 02");
    system("mode con cols=109 lines=45");
        for(int j=0;j<109;j++)
    {
       _SetTextColor(0,color[j%16]);
        printf(" ");
    }
    printf("\n");
    _SetTextColor(2,0);
    printf("-------------------------------------------------------------------------------------------------------------\n");
    printf("Color 字体颜色 背景颜色(字体、背景颜色相同将无法显示字体)\n");
    printf("-------------------------------------------------------------------------------------------------------------\n");
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<16;j++)
        {
            _SetTextColor(color[j],color[i]);
            printf("Color %2d %2d",color[j],color[i]);
            if(j%8==7)
                printf("\n");
                else
                 printf("   ");

        }

    }
    _SetTextColor(2,0);
    printf("-------------------------------------------------------------------------------------------------------------\n");
    printf("色块 颜色号(10进制)/(16进制) 颜色描述\n");
    for(int i=0;i<16;i++)
    {
        _SetTextColor(0,color[i]);
        printf("  ");
        _SetTextColor(color[i],0);
        printf("%2d/%c:%s",color[i],ccolor[i],scolor[i]);
        _SetTextColor(2,0);
        if(i%4==3)
            printf("\n");
        else
            printf("\t\t");
    }
    printf("-------------------------------------------------------------------------------------------------------------\n");
    for(int j=0;j<109;j++)
    {
       _SetTextColor(0,color[j%16]);
        printf(" ");
    }
    printf("\n");
    _SetTextColor(2,0);
    printf("Press any key exit>/ ");
    SetGotoxy(2,95);
    printf("Ice2Faith");
    SetGotoxy(44,21);
    getch();
    return 0;
}
void _SetTextColor(int ForeColor,int BackGroundColor)
{
    if(ForeColor<0 ||ForeColor>15)
        ForeColor=15;
    if(BackGroundColor<0 ||BackGroundColor>15)
        BackGroundColor=0;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),ForeColor+BackGroundColor*0x10);
}
void SetGotoxy(int lines,int cols)
{
    COORD Go = {cols, lines};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Go);
}
