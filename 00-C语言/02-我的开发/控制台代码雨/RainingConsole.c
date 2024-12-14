#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<string.h>
#define MAXSIZE 300
typedef struct
{
    int x;
    int y;
} Space;
typedef struct
{
    Space rain[MAXSIZE];
    int len;
} Rain;
void gotoxy(int x, int y);
void RainConsole(int RAINLINES,int RAINCOLS);
int main(int argc,char *argv[])
{
    rename(argv[0],"代码雨.exe");
    system("title 代码雨-控制台 By Ice2Faith");
    printf("请输入代码雨的大小：x y\n>/ ");
    int x,y;
    scanf("%d%d",&x,&y);
    system("cls");
    RainConsole(x,y);
    return 0;
}

void RainConsole(int RAINLINES,int RAINCOLS)
{
    char mind[200]= {"\0"};
    sprintf(mind,"mode con lines=%d cols=%d\0",RAINLINES,RAINCOLS);
    system(mind);
    char ch[MAXSIZE][MAXSIZE]= {"\0"};
    srand((unsigned)time(NULL));
    for(int i=0; i<RAINLINES; i++)
    {
        for(int j=0; j<RAINCOLS; j++)
        {
            ch[i][j]=rand()%(127-32)+32;
        }
    }
    Rain RainAll[MAXSIZE];
    ///////////////////////////////////////////////////////
    while(1)
    {
        int raincount=rand()%(RAINCOLS-1)/4+1;
        for(int i=0; i<raincount; i++)
        {
            RainAll[i].len=rand()%(RAINLINES*3/5)+1;
            int y=rand()%(RAINCOLS)+1;
            int start=rand()%(RAINLINES*2/5);
            for(int j=0; j<RainAll[i].len; j++)
            {
                RainAll[i].rain[j].x=start+j;
                RainAll[i].rain[j].y=y;
            }
        }
        for(int k=0; k<RAINLINES; k++)
        {
            for(int i=0; i<raincount; i++)
            {
                for(int j=0; j<RainAll[i].len; j++)
                {
                    if(RainAll[i].rain[j].x<=RAINLINES)
                    {
                        gotoxy(RainAll[i].rain[j].y,RainAll[i].rain[j].x);
                        printf(" ");
                    }
                    RainAll[i].rain[j].x++;
                    if(RainAll[i].rain[j].x>RAINLINES)
                    {
                        //RainAll[i].rain[j].x=RAINLINES;
                       RainAll[i].len--;
                    }
                }
                for(int m=0;m<RainAll[i].len;m++)
                {
                    if(RainAll[i].rain[m].x<=RAINLINES)
                    {
                        gotoxy(RainAll[i].rain[m].y,RainAll[i].rain[m].x);
                        printf("%c",ch[RainAll[i].rain[m].x][RainAll[i].rain[m].y]);
                    }
                }
            }
            Sleep(60);
        }
    }
    ////////////////////////////////////////////////////////
}

void gotoxy(int x, int y)
{
    COORD go = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), go);
}
