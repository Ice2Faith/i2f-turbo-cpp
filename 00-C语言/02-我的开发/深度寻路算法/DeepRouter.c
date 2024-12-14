#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#define LINES 10
#define COLS 10
typedef struct
{
    int x;
    int y;
} Point;
int DDerec[4][2]=
{
    {0,1}, //right
    {1,0}, //down
    {0,-1}, //left
    {-1,0}, //up
};
typedef struct
{
    int value;
    int find;
    int derec;	//reference for DDerec
} HelpMap;
int Map[LINES][COLS]=
{
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,1,0,0,0,0,1,1,1},
    {1,0,1,0,1,1,0,1,0,1},
    {1,0,0,0,1,0,0,0,0,1},
    {1,0,1,1,1,0,1,0,1,1},
    {1,0,1,0,0,1,1,0,0,1},
    {1,0,1,0,1,1,0,1,0,1},
    {1,0,0,0,1,1,0,1,0,1},
    {1,1,1,0,0,0,0,1,0,1},
    {1,1,1,1,1,1,1,1,1,1},
};
HelpMap Hmap[LINES][COLS];
Point Cur= {1,1},Test= {1,1},End= {8,8};
void InitEnveronment();
void DisplayMap();
void AutoRouter();

typedef struct node
{
    Point point;
    struct node * next;
} STEP;
STEP * Head=NULL;
void OverturnStack();
int StackIsEmpty();
void GetTop(Point * point);
void Pop(Point * point);
void Push(Point point);
void DisplayRoute();
int main()
{
    Head=(STEP *)malloc(sizeof(STEP));
    Head->next=NULL;
    srand((unsigned)time(NULL));
    system("color f1");
    InitEnveronment();
    AutoRouter();
    return 0;
}
void AutoRouter()
{
    Hmap[Cur.x][Cur.y].find=1;
    Push(Cur);
    int jmp=0;
    while(1)
    {
        Test.x=Cur.x;
        Test.y=Cur.y;
        switch(Hmap[Cur.x][Cur.y].derec)
        {
        case 0:
            Hmap[Cur.x][Cur.y].derec++;
            Test.x+=DDerec[0][0];
            Test.y+=DDerec[0][1];
            if(Hmap[Test.x][Test.y].find==0&&Hmap[Test.x][Test.y].value==0)
            {
                Push(Cur);
                //Cur入栈
                Hmap[Test.x][Test.y].find=1;
                Cur.x=Test.x;
                Cur.y=Test.y;
            }
            break;
        case 1:
            Hmap[Cur.x][Cur.y].derec++;
            Test.x+=DDerec[1][0];
            Test.y+=DDerec[1][1];
            if(Hmap[Test.x][Test.y].find==0&&Hmap[Test.x][Test.y].value==0)
            {
                Push(Cur);
                //Cur入栈
                Hmap[Test.x][Test.y].find=1;
                Cur.x=Test.x;
                Cur.y=Test.y;
            }
            break;
        case 2:
            Hmap[Cur.x][Cur.y].derec++;
            Test.x+=DDerec[2][0];
            Test.y+=DDerec[2][1];
            if(Hmap[Test.x][Test.y].find==0&&Hmap[Test.x][Test.y].value==0)
            {
                Push(Cur);
                //Cur入栈
                Hmap[Test.x][Test.y].find=1;
                Cur.x=Test.x;
                Cur.y=Test.y;
            }
            break;
        case 3:
            Test.x+=DDerec[3][0];
            Test.y+=DDerec[3][1];
            if(Hmap[Test.x][Test.y].find==0&&Hmap[Test.x][Test.y].value==0)
            {
                Push(Cur);
                //Cur入栈
                Hmap[Test.x][Test.y].find=1;
                Cur.x=Test.x;
                Cur.y=Test.y;
            }
            if(Hmap[Cur.x][Cur.y].derec==3)
            {
                GetTop(&Cur);
                Pop(&Test);
            }
            break;
        }
        DisplayMap();
        if(Cur.x==End.x&&Cur.y==End.y)
        {
            Push(Cur);
            printf("Router Success!!\n");
            DisplayRoute();
            break;
        }
        if(StackIsEmpty())
        {
            printf("Router Failure!!\n");
            break;
        }

        Sleep(100);
    }
    printf("Click * exit\n");
    char sel='\0';
    while(sel!='*')
        sel=getch();
}
void InitEnveronment()
{
    for(int i=0; i<LINES; i++)
    {
        for(int j=0; j<COLS; j++)
        {
            Hmap[i][j].value=Map[i][j];
            Hmap[i][j].find=0;
            Hmap[i][j].derec=0;
        }
    }
}
void DisplayMap()
{
    system("cls");
    for(int i=0; i<LINES; i++)
    {
        for(int j=0; j<COLS; j++)
        {
            if(i==Cur.x&&j==Cur.y)
                printf("$$");
            else if(Hmap[i][j].value==0)
                printf("  ");
            else if(Hmap[i][j].value==1)
                printf("##");
        }
        printf("\n");
    }
}
void DisplayRoute()
{
    OverturnStack();
    while(!StackIsEmpty())
    {
        Pop(&Test);
        printf("->(%d,%d)",Test.x,Test.y);
        Hmap[Test.x][Test.y].value=9;
    }
    printf("\n");
    for(int i=0; i<LINES; i++)
    {
        for(int j=0; j<COLS; j++)
        {
            if(i==Cur.x&&j==Cur.y)
                printf("$$");
            else if(Hmap[i][j].value==9)
                printf("!!");
            else if(Hmap[i][j].find==1)
                printf("..");
            else if(Hmap[i][j].value==0)
                printf("  ");
            else if(Hmap[i][j].value==1)
                printf("##");
        }
        printf("\n");
    }
}
//------------------------------------------
void Push(Point point)
{
    STEP * p=(STEP *)malloc(sizeof(STEP));
    p->next=NULL;
    p->point.x=point.x;
    p->point.y=point.y;
    p->next=Head->next;
    Head->next=p;
}
void Pop(Point * point)
{
    point->x=Head->next->point.x;
    point->y=Head->next->point.y;
    STEP * p=Head->next;
    Head->next=Head->next->next;
    free(p);
}
void GetTop(Point * point)
{
    point->x=Head->next->point.x;
    point->y=Head->next->point.y;
}
int StackIsEmpty()
{
    if(Head->next==NULL)
        return 1;
    return 0;
}
void OverturnStack()
{
    STEP *f=NULL,* p=Head->next;
    Head->next=NULL;
    while(p)
    {
        f=p;
        p=p->next;
        f->next=Head->next;
        Head->next=f;

    }
}
