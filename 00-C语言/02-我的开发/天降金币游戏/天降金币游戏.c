#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
#include"Ice2Feathers.h"

int map[20][30]={0};
int core;
int highcore;
void redhighcore();
void writhighcore();

void main()
{
    system("title Game of Greazing Collection gift By: Ice2Feathers");
    system("color f5");
    system("mode con cols=70 lines=32");
    redhighcore();
    srand((unsigned)time(NULL)+rand());
    puts("----------------------------\n");
    puts("***  欢迎来到冰羽小游戏  ***\n");
    puts("游戏名:     疯狂捡金币      \n");
    puts("----------------------------\n");
    puts("You: &\t Gift: $\t Bomb: @\n");
    printf("Tips:\n\n为最佳体验请切换到英文输入法\n\n>> \n\n");
    system("pause");
    system("cls");
    int gift1,gift2,gift3;
    int gift4,gift5,gift6;
    int boom,boom2;
    int x, y=0,y1=0;
    int upx,upy;
    int upy1;
    char move;
    //user location
    map[19][15] = 1;
    x = 15;
    int k=1;
    int updata=1;
    int openmore;
    while (k==1)
    {
        printf("Core : %d \tHighCore : %d\n\n",core,highcore);
        puts("Left: A\t Right: D \t Quit: *\n");
        //updata gift location
        if(updata==1)
        {
                gift1=rand()%30;
          gift2=rand()%30;
          while(gift1==gift2)
          {
             gift2=rand()%30;
          }
          gift3=rand()%30;
          while(gift3==gift2||gift3==gift1)
          {
             gift3=rand()%30;
          }
          boom=rand()%30;
          while(boom==gift2||boom==gift1||boom==gift3)
          {
             boom=rand()%30;
          }
        y=0;
        }

        if(y==10)
        {
                gift4=rand()%30;
          gift5=rand()%30;
          while(gift4==gift5)
          {
             gift5=rand()%30;
          }
          gift6=rand()%30;
          while(gift6==gift5||gift6==gift4)
          {
             gift6=rand()%30;
          }
          boom2=rand()%30;
          while(boom2==gift4||boom2==gift5||boom2==gift6)
          {
             boom2=rand()%30;
          }
        y1=0;
        openmore=1;
        }

        map[y][gift1]=9;
        map[y][gift2]=9;
        map[y][gift3]=9;
        map[y][boom] = 4;
        map[19][x] = 1;

        if(openmore==1)
        {
        map[y1][gift4]=9;
        map[y1][gift5]=9;
        map[y1][gift6]=9;
        map[y1][boom2] = 4;
        }

        puts("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ");
      //print map
      for (int i = 0; i < 20; i++)
        {
            printf("+ ");
        for (int j = 0; j < 30; j++)
            {
            if (map[i][j] == 0)
            printf("  ");
          else if (map[i][j] == 9)
            printf("$ ");
          else if (map[i][j] == 1)
            printf("& ");
          else if (map[i][j] == 4)
                printf("@ ");
            }
            printf("+ ");
            printf("\n");
        }
        puts("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ");
        //get move char
        if(kbhit()!=0)
        move = getch();
        else
            move='s';
        upx=x;
        if(move=='A'||move=='a')
        {
        	if(x==0)
            x=29;
            else
            x--;
        }
        else
        if(move=='D'||move=='d')
        {
        	if(x==29)
            x=0;
            else
            x++;
        }

         upy=y;
         y++;
         if(openmore==1)
         {
              upy1=y1;
              y1++;
         }

              updata=0;
        //get core add
        if( map[18][x]==9)
        {
             core++;
             Screentips(0,"f5");
        }
        else
           if( map[18][x]==4)
           {
              core--;
              Screentips(-1,"f5");
           }

           if(y==19)
            updata=1;

        //delete front num
        map[19][upx]=0;
        map[upy][gift1]=0;
        map[upy][gift2]=0;
        map[upy][gift3]=0;
        map[upy][boom]=0;
   if(openmore==1)
   {
          map[upy1][gift4]=0;
          map[upy1][gift5]=0;
          map[upy1][gift6]=0;
          map[upy1][boom2]=0;
   }

        Sleep(90);
        system("cls");
        if(core>highcore)
            highcore=core;

        if(move=='*')
            break;

    } // while end
            writhighcore();
            End();
}

void redhighcore()
{
    FILE * stream;
    if(fopen("GHighCore.bas","r")==NULL)
    {
         stream=fopen("GHighCore.bas","w");
       fprintf(stream,"0");
    }
    else
        stream=fopen("GHighCore.bas","r");
    fscanf(stream,"%d",&highcore);
    fclose(stream);
}
void writhighcore()
{
    FILE * stream;
    stream=fopen("GHighCore.bas","w");
    if(core>highcore)
        highcore=core;
    fprintf(stream,"%d",highcore);
    fclose(stream);
}
