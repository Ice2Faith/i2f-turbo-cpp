#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include"Ice2Feathers.h"
//行数
#define SIZEX 25
//列数
#define SIZEY 30

void wuziqi();
int ifwin(int x,int y);
void printmap();
void newmap();
void computerrand();
void caculset(int cplayerx,int cplayery);
int map[SIZEX+2][SIZEY+2]={0};//定义生成棋盘规模
int max=0;
int cmax=0;
int cx,cy;
int playerx,playery;
int cdirection=5;
int direction=5;//监控已有五子棋长度如果大于3则改变为相应方向数字；具体如下：
/*
5是中心点
789
456
123
对应方向
*/

void main()
{
    system("title 欢乐五子棋 By： IceFeathers");
    int tt=1;
       int k=1;
    while(k==1)
    {
        system("color f5");
        newmap();
        Bitprint("++++++++++++++++++++++++++++++++++++\n",3);
        Bitprint("+                                  +\n",3);
        Bitprint("+        欢迎来到欢乐五子棋        +\n",3);
        Bitprint("+                                  +\n",3);
        Bitprint("+         BY: Ice2Feathers         +\n",3);
        Bitprint("+                                  +\n",3);
        Bitprint("++++++++++++++++++++++++++++++++++++\n\n",3);
        Bitprint("您的棋子： O\t电脑的棋子： @\n\n",3);
        system("pause");
        if(tt==1)
        {
            Bitprint("\n\n\t输入 1 可以自动调整窗口到合适大小哦！！\n",20);
            fflush(stdin);
            char kkk=getchar();
            if(kkk=='1')
            {
                system("mode con cols=120 lines=42");
            }
            tt=0;
        }
        system("cls");
        Sleep(400);
        Bitprint("\n\t正在为您创建棋盘...\n",30);
        Sleep(800);
        Bitprint("\n\t请稍后...\n",30);
        Sleep(800);
        system("cls");
        wuziqi();
        Bitprint("\n\n\t即将为您刷新棋盘！！\n\n",8);
        Sleep(1500);
        system("cls");
        //清空棋盘数据
    }
}

void wuziqi()
{
   srand((unsigned)time(NULL)+rand());
    int kill;
   int k=1;
   while (k==1)
   {

        printmap();
        //获取用户下棋位置代码块
            Bitprint("请输入您下棋的坐标：Y+X\n\n",6);
            printf(">> ");
            fflush(stdin);
            scanf("%d+%d",&playerx,&playery);
            while (playerx>SIZEX||playery>SIZEY||map[playerx][playery]!=0)
            {
            Bitprint("坐标错误！！\n请输入您下棋的坐标：x+y\n\n",4);
            printf(">> ");
            Screentips(-1,"f5");
            fflush(stdin);
            scanf("%d+%d",&playerx,&playery);
            }
            map[playerx][playery]=1;
            system("cls");
            printmap();
            Sleep(800);
            system("cls");
            printmap();
            kill=rand()%100;
            direction=5;
    if(ifwin(playerx,playery)==1)//玩家获胜
    {
                Bitprint("\n\n\t恭喜您!您赢了！！\n",8);
                max=0;//重置最大长度
                system("color 9f");
                k=0;
    }
    else
    if(direction!=5)
    {
        if(kill<=95)
      {
          //预测性放置
        caculset(playerx,playery);
        direction=5;
      }
      else
      {
        computerrand();


      }

    }
    else
    computerrand();


       Bitprint("\t电脑下棋中！！！\n",8);
    Sleep(1500);
   system("cls");
   system("color f5");

                if(ifwin(cx,cy)==1)
                {
                printmap();
                Bitprint("\n\n\t很遗憾！您输了！！\n",8);
                system("color cf");
                max=0;
                cmax=0;
                k=0;
                }


   }

}
void caculset(int cplayerx,int cplayery)
{
             int jbk;
        if(direction==8||cdirection==8)
        {
            jbk=1;
           while(map[cplayerx+jbk][cplayery]!=0)
           {
               jbk++;
           }
           if((cplayerx+jbk<SIZEX+1))
           {
              map[cplayerx+jbk][cplayery]=2;
              cx=cplayerx+jbk;cy=cplayery;
           }
           else
           {
                jbk=1;
                while(map[cplayerx-jbk][cplayery]!=0)
                {
                    jbk++;
                }
                map[cplayerx-jbk][cplayery]=2;
                cx=cplayerx-jbk;cy=cplayery;
           }
        }
        else
        if(direction==9||cdirection==9)
        {
            jbk=1;
           while(map[cplayerx+jbk][cplayery-jbk]!=0)
           {
               jbk++;
           }
           if((cplayerx+jbk<SIZEX+1)&&(cplayery-jbk>0))
           {
              map[cplayerx+jbk][cplayery-jbk]=2;
              cx=cplayerx+jbk;cy=cplayery-jbk;
           }
           else
           {
                jbk=1;
                while(map[cplayerx-jbk][cplayery+jbk]!=0)
                {
                    jbk++;
                }
                map[cplayerx-jbk][cplayery+jbk]=2;
                cx=cplayerx-jbk;cy=cplayery+jbk;
           }
        }
        else
        if(direction==6||cdirection==6)
        {
            jbk=1;
           while(map[cplayerx][cplayery-jbk]!=0)
           {
               jbk++;
           }
           if((cplayery-jbk>0))
           {
              map[cplayerx][cplayery-jbk]=2;
              cx=cplayerx;cy=cplayery-jbk;
           }
           else
           {
                jbk=1;
                while(map[cplayerx][cplayery+jbk]!=0)
                {
                    jbk++;
                }
                map[cplayerx][cplayery+jbk]=2;
                cx=cplayerx;cy=cplayery+jbk;
           }
        }
        else
        if(direction==3||cdirection==3)
        {
           jbk=1;
           while(map[cplayerx-jbk][cplayery-jbk]!=0)
           {
               jbk++;
           }
           if((cplayerx-jbk>0)&&(cplayery-jbk>0))
           {
              map[cplayerx-jbk][cplayery-jbk]=2;
              cx=cplayerx-jbk;cy=cplayery-jbk;
           }
           else
           {
                jbk=1;
                while(map[cplayerx+jbk][cplayery+jbk]!=0)
                {
                    jbk++;
                }
                map[cplayerx+jbk][cplayery+jbk]=2;
                cx=cplayerx+jbk;cy=cplayery+jbk;
           }
        }
        else
        if(direction==2||cdirection==2)
        {
           jbk=1;
           while(map[cplayerx-jbk][cplayery]!=0)
           {
               jbk++;
           }

           if((cplayerx-jbk>0))
           {
              map[cplayerx-jbk][cplayery]=2;
              cx=cplayerx-jbk;cy=cplayery;
           }
           else
           {
                jbk=1;
                while(map[cplayerx+jbk][cplayery]!=0)
                {
                    jbk++;
                }
                map[cplayerx+jbk][cplayery]=2;
                cx=cplayerx+jbk;cy=cplayery;
           }
        }
        else
        if(direction==1||cdirection==1)
        {
          jbk=1;
           while(map[cplayerx-jbk][cplayery+jbk]!=0)
           {
               jbk++;
           }
           if((cplayerx-jbk>0)&&(cplayery+jbk<SIZEY+1))
           {
              map[cplayerx-jbk][cplayery+jbk]=2;
              cx=cplayerx-jbk;cy=cplayery+jbk;
           }
           else
           {
                jbk=1;
                while(map[cplayerx+jbk][cplayery-jbk]!=0)
                {
                    jbk++;
                }
                map[cplayerx+jbk][cplayery-jbk]=2;
                cx=cplayerx+jbk;cy=cplayery-jbk;
           }
        }
        else
        if(direction==4||cdirection==4)
        {
           jbk=1;
           while(map[cplayerx][cplayery+jbk]!=0)
           {
               jbk++;
           }
           if((cplayery+jbk<SIZEY+1))
           {
              map[cplayerx][cplayery+jbk]=2;
              cx=cplayerx;cy=cplayery+jbk;
           }
           else
           {
                jbk=1;
                while(map[cplayerx][cplayery-jbk]!=0)
                {
                    jbk++;
                }
                map[cplayerx][cplayery-jbk]=2;
                cx=cplayerx;cy=cplayery-jbk;
           }
        }
        else
        if(direction==7||cdirection==7)
        {
          jbk=1;
           while(map[cplayerx+jbk][cplayery+jbk]!=0)
           {
               jbk++;
           }

           if((cplayerx+jbk<SIZEX+1)&&(cplayery+jbk<SIZEY+1))
           {
              map[cplayerx+jbk][cplayery+jbk]=2;
              cx=cplayerx+jbk;cy=cplayery+jbk;
           }
           else
           {
                jbk=1;
                while(map[cplayerx-jbk][cplayery-jbk]!=0)
                {
                    jbk++;
                }
                map[cplayerx-jbk][cplayery-jbk]=2;
                cx=cplayerx-jbk;cy=cplayery-jbk;
           }

        }

}

void computerrand()
{
    int ctx,cty;
    int i,j;
    int control=0;
    for (i=0;i<SIZEX+1;i++)
    {
        for (j=1;j<SIZEY+1;j++)
        {
            cdirection=5;
            if(map[i][j]==2)
            {
            ifwin(i,j);
            if(cdirection!=5)
            {
                ctx=i;cty=j;
                control=1;
                break;
            }

            }

        }
        if(control==1)
            break;
    }

        if(control==1)
        {
          caculset(ctx,cty);
          cdirection=5;
          control=0;
        }
        else
        {
            int computerx,computery;
            int add,space;
            //电脑下棋代码块
            add=rand()%2;
            if(max>3)
                max=4;
            space=5-max;
                if(max<3)
               space=5-max-rand()%3;
            if(add==1)
            {
                computerx=rand()%space+1;
                computery=rand()%space+1;
               while(map[playerx+computerx][playery+computery]!=0)
                {
                computerx=rand()%space+1;
                computery=rand()%space+1;
                }

                if((playerx+computerx<SIZEX+1)&&(playery+computery<SIZEY+1))
                {
                  map[playerx+computerx][playery+computery]=2;
                cx=playerx+computerx;cy=playery+computery;
                }
                else
                {
                    map[playerx-computerx][playery-computery]=2;
                    cx=playerx-computerx;cy=playery-computery;
                }

            }
            else
            if(add==0)
            {
                computerx=rand()%space+1;
                computery=rand()%space+1;
               while(map[playerx-computerx][playery-computery]!=0)
                {
                computerx=rand()%space+1;
                computery=rand()%space+1;
                }
                if((playerx+computerx>0)&&(playery+computery>0))
                {
                   map[playerx-computerx][playery-computery]=2;
                cx=playerx-computerx;cy=playery-computery;
                }
                else
                {
                 map[playerx+computerx][playery+computery]=2;
                cx=playerx+computerx;cy=playery+computery;
                }

            }
        }
}

void printmap()
{
       int i,j;//循环控制变量
       Bitprint("----------\n----------------------\n",3);
        //输出棋盘代码块
        //输出辅助坐标线和坐标
         printf("\\ X");
        for(j=1;j<SIZEY+1;j++)
        {
                printf("%2d",j);

        }
        printf("\n");
        printf("Y \\");
                for(j=1;j<SIZEY+1;j++)
        {

                printf(" |");
        }
                printf("\n");
            //输出棋盘内容
        for(i=1;i<SIZEX+1;i++)
        {
            if(i!=0&&i!=SIZEX+1)
            printf("%2d- ",i);
            for(j=1;j<SIZEY+1;j++)
            {
            // printf("%2d ",map[i][j]);
                if(map[i][j]==-1)
                {
                printf("  ");
                }
                else
                if(map[i][j]==0)
                {
                printf(". ");
                }
                else
                if(map[i][j]==1)
                {
                printf("O ");
                }
                else
                if(map[i][j]==2)
                {
                printf("@ ");
                }
            }
            printf("\n");
        }
    Bitprint("---------------------------------\n\n",2);
}

//新棋盘初始化
void newmap()
{
    //初始化棋盘数据
             int i,j;
            for(i=0;i<SIZEX+2;i++)
            {
                for(j=0;j<SIZEY+2;j++)
                {
                map[i][j]=0;
                }
            }
   //初始化棋盘边界

         for(i=0;i<SIZEY+2;i++)
        {
        map[0][i]=-1;
        map[SIZEX+1][i]=-1;
        }
        for(i=0;i<SIZEX+2;i++)
        {
        map[i][0]=-1;
        map[i][SIZEY+1]=-1;
        }


}

//接收下棋点坐标，返回1赢了，返回0没赢
int ifwin(int x,int y)
{
int leftup=1,rightdown=1;//是否向左上方前进和右下方前进
int counter=1;//对已有的五子棋长度计数
int i,j;
int item=map[x][y];//接收和判断是谁下的棋
int renum=0;//返回值数值

//横向扫描
leftup=1,rightdown=1;counter=1;

    for(i=1;i<5;i++)
    {
        if((leftup==1)&&(map[x][y-i]==item))
        {
            counter++;
        if(counter>=3)
        {
            direction=4;
            cdirection=4;
        }

        }
        else
            if(map[x][y-i]!=item)
            leftup=0;

        if((rightdown==1)&&(map[x][y+i]==item))
        {
            counter++;
            if(counter>=3)
            {
              direction=6;
              cdirection=6;
            }

        }
        else
            if(map[x][y+i]!=item)
            rightdown=0;

    }
    if(counter>max)
        max=counter;

            if(counter==5)
                renum=1;


//纵向扫描
leftup=1,rightdown=1;counter=1;

    for(i=1;i<5;i++)
    {
        if((leftup==1)&&(map[x-i][y]==item))
        {
            counter++;
            if(counter>=3)
            {
            direction=8;
            cdirection=8;
            }

        }
        else
            if(map[x-i][y]!=item)
            leftup=0;

        if((rightdown==1)&&(map[x+i][y]==item))
        {
            counter++;
            if(counter>=3)
            {
              direction=2;
              cdirection=2;
            }

        }
        else
            if(map[x+i][y]!=item)
            rightdown=0;

    }
        if(counter>max)
        max=counter;
            if(counter==5)
               renum=1;


//主对角线扫描
leftup=1,rightdown=1;counter=1;

    for(i=1;i<5;i++)
    {
        if((leftup==1)&&(map[x-i][y-i]==item))
        {
            counter++;
            if(counter>=3)
            {
             direction=7;
             cdirection=7;
            }

        }
        else
            if(map[x-i][y-i]!=item)
            leftup=0;

        if((rightdown==1)&&(map[x+i][y+i]==item))
        {
            counter++;
            if(counter>=3)
            {
              direction=3;
              cdirection=3;
            }

        }
        else
            if(map[x+i][y+i]!=item)
            rightdown=0;

    }
        if(counter>max)
        max=counter;
            if(counter==5)
                renum=1;


//副对角线扫描
leftup=1,rightdown=1;counter=1;

    for(i=1;i<5;i++)
    {
        if((leftup==1)&&(map[x-i][y+i]==item))
        {
            counter++;
            if(counter>=3)
            {
             direction=9;
             cdirection=9;
            }

        }
        else
            if(map[x-i][y+i]!=item)
            leftup=0;

        if((rightdown==1)&&(map[x+i][y-i]==item))
        {
            counter++;
            if(counter>=3)
            {
              direction=1;
              cdirection=1;
            }

        }
        else
            if(map[x+i][y-i]!=item)
            rightdown=0;

    }
        if(counter>max)
        max=counter;
            if(counter==5)
                renum=1;
    return renum;
}
