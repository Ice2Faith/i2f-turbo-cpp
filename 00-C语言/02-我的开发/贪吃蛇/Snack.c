#include "Snack.h"
int Map[X+2][Y+2];
void SnackEattingGmme()
{
    system("title Game Snack of eatting Dev: Ice2Faith Ver: 2.0.0");
    system("color f5");
    system("mode con cols=60 lines=35");
    ReadyAll();
    int result=0;
    char pre='D';
    printf("\twelcome play the game\n\n");
    printf("\tThe Snack of eatting\n\n");
    printf("\tDev:\tIce2Faith\n\n");
    printf("\t@:Snack\t$:Food\t#:Wall\n\n");
    printf("\t&:Gift\t%%:Head\t*:Tail\n\n");
    int speed=150;
    printf("\t需要调节速度(7)请输入 \'+\':\n\n\t");
    if(getch()=='+')
    {
        printf("\t请输入速度1-10：\n\n\t");
        int Sv;
        scanf("%d",&Sv);
        if(Sv>10)
            Sv=10;
        if(Sv<1)
            Sv=1;
        speed=530-Sv*50;
    }
    printf("\tClick Any Key Continue\n\t>/ ");
    getch();
    int AntiMove=0;
    do
    {
        printf("\t--------------------------\n");
        printf("\tControl:\t(*:exit)\n");
        printf("\tW/8:up\t\tS/5:down\n");
        printf("\tA/4:left\tD/6:right\tLast: + %3d\n",LastGet);
        printf("\tcore: %3d\tLength: %3d\tValue: %s\n",core,SnackBody->len,GiftVanul>=40?"SSS":(GiftVanul>=5?" S ":" A "));
        if(kbhit())
            pre=getch();
        AntiMove=0;
        if((pre=='W'||pre=='w'||pre=='8')&&(control=='S'||control=='s'||control=='5')) AntiMove=1;
        if((pre=='A'||pre=='a'||pre=='4')&&(control=='D'||control=='d'||control=='6')) AntiMove=1;
        if((pre=='S'||pre=='s'||pre=='5')&&(control=='W'||control=='w'||control=='8')) AntiMove=1;
        if((pre=='D'||pre=='d'||pre=='6')&&(control=='A'||control=='a'||control=='4')) AntiMove=1;
        if((pre=='8'||pre=='4'||pre=='5'||pre=='6'||pre=='w'||pre=='W'||pre=='a'||pre=='A'||pre=='s'||pre=='S'||pre=='d'||pre=='D')&&AntiMove==0)
        {
            control=pre;
        }
        MoveSnack();
        result=SnackCheak();
        DrewMap();
        DisplayMap();
        printf("\n\t--------------------------\n\t");
        if(result==2)
        {
            if(GiftVanul>=5)
            {
                printf("\n\t--------New Gift Waring--------\n\t");
                Screentips(2,"f5");
            }
            else
            Screentips(1,"f5");
        }
        if(pre=='*')
            Screentips(0,"f5");
        if(!result)
        {
            Screentips(-1,"f5");
            break;
        }
        Sleep(speed);
        system("cls");
    }
    while(pre!='*');
    if(pre!='*')
    printf("\n\tGame Over!\n\n");
    printf("\tClick Any Key Continue\n\t>/ ");
    getch();
}
void DefultMap()	//初始化地图信息
{
    int i,j;
    for(i=0; i<X+2; i++)
    {
        for(j=0; j<Y+2; j++)
        {
            Map[i][j]=0;
        }
    }
    for(i=0; i<X+2; i++)
    {
        Map[i][0]=1;
        Map[i][Y+1]=1;
    }
    for(i=0; i<Y+2; i++)
    {
        Map[0][i]=1;
        Map[X+1][i]=1;
    }
}

void DrewMap()
{
    DefultMap();
    for(int i=0; i<SnackBody->len; i++)
    {
        Map[SnackBody->x[i]][SnackBody->y[i]]=2;
    }
    if(existgift==0)
    {
        CreatGift();
    }
    Map[gift->x][gift->y]=9;
}

void CreatGift()
{
    srand((unsigned)time+rand());
    do
    {
        gift->x=rand()%X+1;
        gift->y=rand()%Y+1;
    }
    while(Map[gift->x][gift->y]!=0);
    existgift=1;
    CountBigGift++;
    if(CountBigGift==BigGiftTimes)
    {
        CountBigGift=0;
        srand((unsigned)time(NULL)+rand());
        BigGiftTimes=rand()%10+3;
        if(rand()%100<30)
            GiftVanul=rand()%25+5;
        else
            GiftVanul=rand()%60+40;
    }
    else
        GiftVanul=rand()%3+1;
}

void DisplayMap()
{
    for(int i=0; i<X+2; i++)
    {
        printf("\t");
        for(int j=0; j<Y+2; j++)
        {

            if((SnackBody->x[0]==i)&&(SnackBody->y[0]==j))
                printf("%% ");
            else if((SnackBody->x[SnackBody->len-1]==i)&&(SnackBody->y[SnackBody->len-1]==j))
                printf("* ");
            else if(Map[i][j]==0)
                printf("  ");
            else if(Map[i][j]==1)
                printf("# ");
            else if(Map[i][j]==2)
                printf("@ ");
            else if(Map[i][j]==9)
                if(GiftVanul<5)
                printf("$ ");
                else
                printf("& ");


        }
        printf("\n");
    }
}

void MoveSnack()
{
    if(control=='W'||control=='w'||control=='8')
    {
        head->x--;
    }
    else if(control=='S'||control=='s'||control=='5')
    {
        head->x++;
    }
    else if(control=='A'||control=='a'||control=='4')
    {
        head->y--;
    }
    else if(control=='D'||control=='d'||control=='6')
    {
        head->y++;
    }
    for(int i=SnackBody->len; i>0; i--)
    {
        SnackBody->x[i]=SnackBody->x[i-1];
        SnackBody->y[i]=SnackBody->y[i-1];
    }
    SnackBody->x[0]=head->x;
    SnackBody->y[0]=head->y;
}

int SnackCheak()
{
    if(Map[head->x][head->y]==1)
        return 0;
    else if(Map[head->x][head->y]==2)
        return 0;
    else if(Map[head->x][head->y]==9)
    {
        core+=GiftVanul;
        LastGet=GiftVanul;
        existgift=0;

        for(int i=SnackBody->len; i>0; i--)
        {
            SnackBody->x[i]=SnackBody->x[i-1];
            SnackBody->y[i]=SnackBody->y[i-1];
        }
        SnackBody->x[0]=head->x;
        SnackBody->y[0]=head->y;
        SnackBody->len++;
        return 2;
    }
    return 1;
}

void ReadyAll()
{
    gift=(space *)malloc(sizeof(space));
    head=(space *)malloc(sizeof(space));
    SnackBody=(Snack *)malloc(sizeof(Snack));
    SnackBody->x[0]=(X+2)/2;
    SnackBody->y[0]=(Y+2)/4;
    head->x=SnackBody->x[0];
    head->y=SnackBody->y[0];
    SnackBody->len=1;
    control='D';
    existgift=0;
    core=0;
    GiftVanul=1;
    CountBigGift=0;
    BigGiftTimes=5;
    LastGet=0;
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
    else if(type==2)
    {
        system("color 20");
    }
    Sleep(90);
    system(beforec);
}























