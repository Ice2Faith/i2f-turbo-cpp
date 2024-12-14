#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include"Ice2Feathers.h"
    //定义图大小
    int map[20][20]={0};
      //定义分数
   int core=0;
   int highcore;
    void SaveCore();

void redhighcore();
void writhighcore();

void main()
{
    system("title 荒野淘金 By: Ice2Feathers");
    system("color f5");
    system("mode con cols=60 lines=30");
    redhighcore();
    //定义用户初始位置
   int userx=0,usery=0;
   int upuserx,upusery;
   //定义奖励点坐标
   int giftx,gifty;
   //播种种子
   srand((unsigned)time(NULL)+rand());
    puts("----------------------------\n");
    puts("***  欢迎来到冰羽小游戏  ***\n");
    puts("游戏名:      荒野淘金       \n");
    puts("----------------------------\n");
    puts("You:&\tCoin:$\tBrambles:#\n");
    printf("Tips:\n\n为最佳体验请切换到英文输入法\n\n>> \n\n");
    system("pause");
    system("cls");
   char control;
   int eat=1;
    giftx=rand()%20;
    gifty=rand()%20;

    map[giftx][gifty]=9;
    int wallx,wally;
    //设置障碍
       for(int k=0;k<18;k++)
       {
           srand((unsigned)time(NULL)+rand());
           wallx=rand()%20;
            wally=rand()%20;
            while((wallx==0&&wally==0)||(wallx==4&&wally==4))
            {
                srand((unsigned)time(NULL)+rand());
                 wallx=rand()%20;
                wally=rand()%20;
            }
            map[wallx][wally]=4;
       }
       int lon=1;
   //生成奖励点位置
   while(lon==1)
   {
       srand((unsigned)time(NULL)+rand());
       printf("Core: %3d\tHighCore: %3d\n\n",core,highcore);
        puts("Up:W\tDown:S\tLeft:A\tRight:D\tQuit:*");
       if(eat==0)
       {
            giftx=rand()%20;
            gifty=rand()%20;
            while(map[giftx][gifty]==4)
            {
                srand((unsigned)time(NULL)+rand());
                 giftx=rand()%20;
                gifty=rand()%20;
            }
            map[giftx][gifty]=9;
            eat=0;
       }

        map[userx][usery]=1;
        upuserx=userx;
        upusery=usery;
        puts("- - - - - - - - - - - - - - - - - - - - - - ");
        for(int i=0;i<20;i++)
        { printf("+ ");
            for(int j=0;j<20;j++)
                {
                if(map[j][i]==0)
                    printf("  ");
                else
                if(map[j][i]==1)
                    printf("& ");
                else
                if(map[j][i]==9)
                    printf("$ ");
                    else
                if(map[j][i]==4)
                    printf("# ");

                }
                 printf("+ ");
            printf("\n");
        }
        puts("- - - - - - - - - - - - - - - - - - - - - - ");
        //获取移动方向
        if(kbhit()!=0)
        control=getch();
        else
            control='r';
        if(control=='W'||control=='w')
        {
            if(usery==0)
                usery=19;
            else
            usery--;
        }
        else
         if(control=='S'||control=='s')
        {
            if(usery==19)
                   usery=0;
            else
            usery++;
        }
        else
         if(control=='A'||control=='a')
        {
            if(userx==0)
                userx=19;
            else
            userx--;
        }
        else
         if(control=='D'||control=='d')
        {
             if(userx==19)
                   userx=0;
            else
            userx++;
        }
         else
         if(control=='*'||control=='*')
        {
            //退出循环
            lon=0;
        }

        if(map[userx][usery]==4)
        {
            userx=upuserx;
            usery=upusery;
            core--;
            system("color cf");
            Sleep(90);
            system("color f5");
        }

        map[upuserx][upusery]=0;

        if(userx==giftx&&usery==gifty)
        {
            core++;
            eat=0;
            system("color e5");
            Sleep(90);
            system("color f5");
        }
        else
            eat=1;

 if(core>highcore)
        highcore=core;
        srand((unsigned)time(NULL)+rand());
        Sleep(75);
        system("cls");
   }
    writhighcore();
   printf("您当前得分: %d\n\n",core);
   puts("输入 S 可以保存本图战绩");
   fflush(stdin);
   char save=getch();
   if(save=='S'||save=='s')
   {
     SaveCore();
     printf("\n\n已经为您保存地图到文件：\n\n>>\tSaveMapCore.txt\n\n");
     Sleep(500);
   }
    End();
}

void redhighcore()
{
    FILE * stream;
    if(fopen("HHighCore.bas","r")==NULL)
    {
         stream=fopen("HHighCore.bas","w");
       fprintf(stream,"0");
    }
    else
        stream=fopen("HHighCore.bas","r");
    fscanf(stream,"%d",&highcore);
    fclose(stream);
}
void writhighcore()
{
    FILE * stream;
    stream=fopen("HHighCore.bas","w");
    if(core>highcore)
        highcore=core;
    fprintf(stream,"%d",highcore);
    fclose(stream);
}

void SaveCore()
{
    FILE * stream;
    stream=fopen("SaveMapCore.txt","w");
     fprintf(stream,"您的得分： %d\n\n",core);
       fprintf(stream,"\t游戏地图：\n\n");
   fprintf(stream,"- - - - - - - - - - - - - - - - - - - - - - \n");
        for(int i=0;i<20;i++)
        { fprintf(stream,"+ ");
            for(int j=0;j<20;j++)
                {
                //printf("%d ",map[j][i]);
                if(map[j][i]==0)
                    fprintf(stream,"  ");
                else
                if(map[j][i]==1)
                    fprintf(stream,"& ");
                else
                if(map[j][i]==9)
                    fprintf(stream,"$ ");
                    else
                if(map[j][i]==4)
                    fprintf(stream,"# ");

                }
                 fprintf(stream,"+ ");
            fprintf(stream,"\n");
        }
        fprintf(stream,"- - - - - - - - - - - - - - - - - - - - - - \n");
        fclose(stream);
}
