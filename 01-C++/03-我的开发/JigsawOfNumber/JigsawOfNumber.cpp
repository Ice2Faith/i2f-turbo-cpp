#include<stdio.h>
#include<iostream>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#define MAXSIZE 100
class ConnectPicture
{
private:
    int step;
    int Lines;
    int Cols;
    int maxblock;
    int maxx,maxy;
    int Map[MAXSIZE][MAXSIZE];
    bool MovePic(int direc);
    int GetKeyDown();
    int Meau();
    void Initial();
    bool IsWin();
    void SetSize(int _lines,int _cols);
    void SetState();
    void DisplayMap();
    int queueinit[2048];
    int queuelen;
    char cribber; /*# open hack mode*/
    int direc[4];
    int antidirec[4];
    bool autorun;
    char hack;
public:
    ConnectPicture();
    void MainGame();
    void Help();
    void OutSuccessQueue();

};

void SetConsoleTextColor(int ForeColor,int BackGroundColor);

int main(int argc,char * argv[])
{
    system("title Jigsaw of Number by Ice2Faith");
    ConnectPicture Game;
    if(argc>1)
        if(strcmp(argv[1],"help")==0)
        {
            system("color 0a");
            Game.Help();
            printf("Tell you a secret:\n");
            printf("Input # can open hack mode when you start game tips \"press any key continue\".\n");
            printf("Then you only need enjoy the game instead of be stroke.\n");
            exit(0);
        }
    while(true)
        Game.MainGame();
    return 0;
}
ConnectPicture::ConnectPicture()
{
    SetSize(5,5);
    step=0;
    Lines=5;
    Cols=5;
    maxblock=24;
    maxx=4;
    maxy=4;
    queuelen=0;
    autorun=false;
    cribber='\0';
    int mdirec[4]= {8,4,5,6};
    int mantidirec[4]= {5,6,8,4};
    for(int i=0; i<4; i++)
    {
        direc[i]=mdirec[i];
        antidirec[i]=mantidirec[i];
    }
}
void ConnectPicture::MainGame()
{
    system("color 0a");
    int sel=Meau();
    if(sel==0)
        exit(0);
    if(sel==2)
    {
        Help();
        return;
    }
    int lines=4,cols=4;
    SetConsoleTextColor(11,0);
    printf("using user-defined size?1 yes,0[else] no\n>/ ");
    if(getch()=='1')
    {
        printf("please input size of jigsaw lines*cols\n>/ ");
        while(scanf("%d*%d",&lines,&cols)!=2);
    }
    SetSize(lines,cols);
    Initial();
    int direc=0;
    printf("press any key continue.");
    hack=getch();
    if(hack=='#')
    {
        SetConsoleTextColor(10,0);
        printf("\nCreator >> You Find the mysterious space.\n");
        printf("Creator >> Input # to open hack mode, input @ to open auto-run mode\n>/ ");
        cribber=getch();
        if(cribber=='@')
            autorun=true;
        if(cribber=='#'||cribber=='@')
        {
            printf("\nCreator >> Mysterious space booting...\n");
            Sleep(800);
        }
        else
            printf("\nyou throw out this chance.\n");

    }
    while(true)
    {
        system("cls");
        if(cribber=='#')
            OutSuccessQueue();
        DisplayMap();
        if(autorun==true)
        {
            direc=antidirec[queueinit[queuelen-1]];
            printf("%d",direc);
            queuelen--;
            Sleep(800);
        }
        else
            direc=GetKeyDown();
        if(direc==-1)
        {
            SetConsoleTextColor(12,0);
            printf("You Suicided!!\n");
            printf("\nPress * key continue.\n");
            while(getch()!='*');
            break;
        }
        if(cribber=='#')
            if(direc==antidirec[queueinit[queuelen-1]])
                queuelen--;
            else
            {
                cribber='0';
                printf("you may be will failure,hack be closed\n");
                getch();
            }
        bool tstep=MovePic(direc);
        if(tstep==true)
            step++;
        if(IsWin())
        {
            system("cls");
            DisplayMap();
            SetConsoleTextColor(10,0);
            printf("You Win!!\n");
            printf("\nPress * key continue.\n");
            while(getch()!='*');
            break;
        }
    }

}
int ConnectPicture::Meau()
{
    system("cls");
    SetConsoleTextColor(11,0);
    printf("-------------------------------\n");
    SetConsoleTextColor(9,0);
    printf("\n\tJigsaw of number\n\n");
    SetConsoleTextColor(10,0);
    printf("\t1.Start\n");
    SetConsoleTextColor(14,0);
    printf("\t2.Help\n");
    SetConsoleTextColor(12,0);
    printf("\t0.exit\n");
    SetConsoleTextColor(11,0);
    printf("-------------------------------\n");
    printf(">/ ");
    char sel='\0';
    while(sel<'0'||sel>'2')
        sel=getch();
    return (int)(sel-'0');
}
void ConnectPicture::OutSuccessQueue()
{
    for(int i=queuelen-1; i>0; i--)
        printf("%d->",antidirec[queueinit[i]]);
    printf("%d\n",antidirec[queueinit[0]]);
}
void ConnectPicture::DisplayMap()
{
    SetConsoleTextColor(11,0);
    printf("Step=%4d\n",step);
    for(int j=0; j<Cols; j++)
    {
        printf("--------");
    }
    printf("\n");
    for(int i=0; i<Lines; i++)
    {
        for(int j=0; j<Cols; j++)
        {
            SetConsoleTextColor(14,0);
            if(Map[i][j]==maxblock)
            {
                SetConsoleTextColor(10,0);
                printf("$$\t");
            }
            else
                printf("%d\t",Map[i][j]);
            SetConsoleTextColor(11,0);
            printf("|");
        }
        printf("\n");
        SetConsoleTextColor(11,0);
        for(int j=0; j<Cols; j++)
        {
            printf("--------");
        }
        printf("\n");
    }
}
void ConnectPicture::SetSize(int _lines,int _cols)
{
    Lines=_lines;
    Cols=_cols;
    maxblock=Lines*Cols-1;
    maxx=Lines-1;
    maxy=Cols-1;
}
void ConnectPicture::Initial()
{
    srand((unsigned)time(NULL));
    int k=0;
    for(int i=0; i<Lines; i++)
    {
        for(int j=0; j<Cols; j++)
        {
            Map[i][j]=k++;
        }
    }
    step=0;
    queuelen=0;
    autorun=false;
    hack='\0';
    cribber='\0';
    SetState();
}
void ConnectPicture::SetState()
{
    int times=(Lines*Cols)*((rand()%150+50)/100)+1;
    int randdirec=0,tp=0;
    for(int i=0; i<times; i++)
    {
        tp=rand()%4;
        while(direc[tp]+direc[randdirec]==10)
            tp=rand()%4;
        while(direc[tp]+direc[randdirec]==13)
            tp=rand()%4;
        randdirec=tp;
        if(MovePic(direc[randdirec])==false)
            i--;
        else
        {
            queueinit[queuelen++]=randdirec;
        }
    }
}
int ConnectPicture::GetKeyDown()
{
    char down='\0';
    down=getch();
    if(down=='8'||down=='w'||down=='W')
        return 8;
    else if(down=='5'||down=='s'||down=='S')
        return 5;
    else if(down=='4'||down=='a'||down=='A')
        return 4;
    else if(down=='6'||down=='d'||down=='D')
        return 6;
    else if(down=='*')
        return -1;
    else
        return 0;
}
bool ConnectPicture::MovePic(int direc)
{
    int temp=0;
    int mx,my;
    if(direc==0)
        return true;
    else if(direc==8)
    {
        if(maxx-1==-1)
            return false;
        mx=maxx-1;
        my=maxy;

    }
    else if(direc==5)
    {
        if(maxx+1==Lines)
            return false;
        mx=maxx+1;
        my=maxy;
    }
    else if(direc==6)
    {
        if(maxy+1==Cols)
            return false;
        mx=maxx;
        my=maxy+1;
    }
    else if(direc==4)
    {
        if(maxy-1==-1)
            return false;
        mx=maxx;
        my=maxy-1;
    }
    temp=Map[maxx][maxy];
    Map[maxx][maxy]=Map[mx][my];
    Map[mx][my]=temp;
    maxx=mx;
    maxy=my;
    return true;
}
bool ConnectPicture::IsWin()
{
    int k=0;
    for(int i=0; i<Lines; i++)
    {
        for(int j=0; j<Cols; j++)
        {
            if( Map[i][j]!=k++)
                return false;
        }
    }
    return true;
}
void ConnectPicture::Help()
{
    char info[20][100]=
    {
        {"\n\t   Help"},
        {"\t  Jigsaw of Number"},
        {"\tyou only need sort this number"},
        {"\tfinally become from 0 to max"},
        {"\tthen you win"},
        {"\tjust like"},
        {"\t0  1  2 "},
        {"\t3  4  $$"},
        {"\tIn game:"},
        {"\tControl by 8/W,5/S,6/D,4/A"},
        {"\t* will break out game"},
    };
    SetConsoleTextColor(14,0);
    for(int i=0; info[i][0]!='\0'; i++)
        printf("%s\n",info[i]);
    SetConsoleTextColor(11,0);
    printf("\nPress * key continue.\n");
    while(getch()!='*');
}
void SetConsoleTextColor(int ForeColor,int BackGroundColor)
{
    if(ForeColor<0 ||ForeColor>15)
        ForeColor=15;
    if(BackGroundColor<0 ||BackGroundColor>15)
        BackGroundColor=0;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),ForeColor+BackGroundColor*0x10);
}
