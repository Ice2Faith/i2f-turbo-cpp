#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
void MainMeau();    //进入菜单
void MainGame2048(int _lines,int _cols);    //主要运行控制函数
void InitialMap(int _lines,int _cols);      //初始化图
void CreateNew();    //创建新的数字
int GetMove();      //获取移动方向或者操作
void MoveAndResult(int mov);        //进行移动操作
void UpDateHighCore();      //更新最高成绩
void DisplayMap();      //展示图
int IsDead();       //判断游戏是否结束
void help();        //显示帮助信息

void SetConsoleSize(int lines,int cols);        //设置控制台窗口大小
void _SetTextColor(int ForeColor,int BackGroundColor);      //设置控制状态字体颜色
void SetGotoxy(int lines,int cols);     //设置控制台光标位置

void ReadFileInfo();        //读取最高成绩
void WritFileInfo();        //写入最高成绩
    //记录最高成绩输出文件用
int hstep=0;
int hcore=0;
int husetime=0;
int hmaxnum=2;
int hmodex=4;
int hmodey=4;
    //运行图和运行时环境
int Map[100][100];
int lines=0;
int cols=0;
int step=0;
int core=0;
long runtime=0;
int usetime=0;
int maxnum=2;

int main(int argc,char * argv[])
{
    rename(argv[0],"2048Game.exe");
    MainMeau();
    return 0;
}

void MainMeau()
{
    system("title Game2048 by Ice2Faith");
    while(1)
    {
        system("color 0a");
        SetConsoleSize(14,45);
        SetGotoxy(0,5);
        _SetTextColor(10,0);
        printf("---------------------------");
        SetGotoxy(1,8);
        _SetTextColor(11,0);
        printf("欢迎来到");
        _SetTextColor(15,0);
        printf("2");
        _SetTextColor(10,0);
        printf("0");
        _SetTextColor(14,0);
        printf("4");
        _SetTextColor(12,0);
        printf("8");
        _SetTextColor(11,0);
        printf("小游戏");      //输出标题
        SetGotoxy(2,10);
        _SetTextColor(12,0);
        printf("1.开始游戏");

        SetGotoxy(3,10);
        _SetTextColor(14,0);
        printf("2.查看玩法");

        SetGotoxy(4,10);
        _SetTextColor(9,0);
        printf("0.结束游戏");

        SetGotoxy(5,5);
        _SetTextColor(10,0);
        printf("---------------------------");      //输出选择

        SetGotoxy(6,5);
        _SetTextColor(11,0);
        printf(">/ ");
        char sel='\0';
        while(sel<'0'||sel>'2')
            sel=getch();
        printf("%c\n",sel);         //获取选择
        if(sel=='0')
            break;
        if(sel=='1')
        {
            int _lines=4,_cols=4;
            printf("输入 * 修改大小，默认4*4\n>/ ");
            if((getch())=='*')
            {
                printf("请输入大小（行数 列数）：\n>/ ");
                scanf("%d%d",&_lines,&_cols);
            }
            if(_lines<2)
                _lines=2;
            if(_cols<2)
                _cols=2;
            if(_lines>100)
                _lines=100;
            if(_cols>100)
                _cols=100;
            printf("1 秒后进入游戏 %d*%d...",_lines,_cols);       //获取运行时大小
            printf("tips:游戏中你可以按 * 随时结束游戏\n");
            Sleep(1000);
            MainGame2048(_lines,_cols);     //进入运行
        }
        if(sel=='2')
            help();
    }

}
void MainGame2048(int _lines,int _cols)
{
    InitialMap(_lines,_cols);       //初始化图
    int mov=0;      //跟踪运动方向
    int result=0;       //判断游戏是否结束
    while(1)
    {
        system("cls");      //刷新屏幕
        CreateNew();
        DisplayMap();
        mov=GetMove();
        if(mov==-1)
            break;
        MoveAndResult(mov);
        UpDateHighCore();
        if(step>(lines*cols*2))
            if(IsDead()==1)
                break;
        usetime=time(NULL)-runtime;
    }
    WritFileInfo();
    printf("Game Over!\n");
    printf("按 * 退出\n");
    char endsure='\0';
    while(endsure!='*')
        endsure=getch();
}
void InitialMap(int _lines,int _cols)
{
    system("color 0a");
    runtime=time(NULL);     //记录开始时间，用于算总时长
    SetConsoleSize(_lines*2+10,_cols*10);
    lines=_lines;
    cols=_cols;
    srand((unsigned)time(NULL));
    for(int i=0; i<lines; i++)
    {
        for(int j=0; j<cols; j++)
        {
            Map[i][j]=0;
        }
    }
    CreateNew();
    ReadFileInfo();     //从文件读取最高纪录
}
void CreateNew()
{
    int hasfull=1;
    for(int i=0; i<lines; i++)
    {
        for(int j=0; j<cols; j++)
        {
            if(Map[i][j]==0)
                hasfull=0;      //判断是否满了，不满才创建
        }
    }
    if(hasfull==1)
        return;
    int si,sj;
    si=rand()%lines;
    sj=rand()%cols;
    while(Map[si][sj]!=0)
    {
        si=rand()%lines;
        sj=rand()%cols;
    }
    Map[si][sj]=2;
}
int GetMove()
{
    char move='\0';
    move=getch();
    if(move=='w'||move=='8'||move=='W')
        return 8;
    if(move=='s'||move=='5'||move=='S')
        return 5;
    if(move=='a'||move=='4'||move=='A')
        return 4;
    if(move=='d'||move=='6'||move=='D')
        return 6;
    if(move=='*')
        return -1;
    return 0;
}
void MoveAndResult(int mov)
{
    if(mov==0)
        return;
    step++;     //步数增加
    int ffind,nfind;
    if(mov==8)
    {
        for(int i=0; i<cols; i++)
        {
            ffind=-1;
            nfind=-1;
            for(int j=0; j<lines; j++)
            {
                int k=j;
                while(k<lines&&Map[k][i]==0)
                    k++;
                if(k!=lines)
                    ffind=k;
                k++;
                while(k<lines&&Map[k][i]==0)
                    k++;
                if(k!=lines)
                    nfind=k;     //获取第一个不为零和下一个不为零
                if(ffind!=-1&&nfind!=-1)
                {
                    if(ffind!=nfind)
                    {
                        if(Map[ffind][i]==Map[nfind][i])        //两个获取相等则叠加
                        {
                            Map[ffind][i]*=2;
                            if(Map[ffind][i]>maxnum)
                                maxnum=Map[ffind][i];
                            Map[nfind][i]=0;
                            core++;         //分数增加
                        }
                    }
                }

            }
            int count=0;
            for(int j=0; j<lines; j++)      //单边对齐
            {
                if(Map[j][i]!=0)
                {
                    int temp=Map[j][i];
                    Map[j][i]=0;
                    Map[count][i]=temp;
                    count++;
                }

            }

        }
    }
    else if(mov==5)
    {
        for(int i=0; i<cols; i++)
        {
            ffind=-1;
            nfind=-1;
            for(int j=lines; j>=0; j--)
            {
                int k=j;
                while(k>=0&&Map[k][i]==0)
                    k--;
                if(k!=-1)
                    ffind=k;
                k--;
                while(k>=0&&Map[k][i]==0)
                    k--;
                if(k!=-1)
                    nfind=k;
                if(ffind!=-1&&nfind!=-1)
                {
                    if(ffind!=nfind)
                    {
                        if(Map[ffind][i]==Map[nfind][i])
                        {
                            Map[ffind][i]*=2;
                            if(Map[ffind][i]>maxnum)
                                maxnum=Map[ffind][i];
                            Map[nfind][i]=0;
                            core++;
                        }
                    }
                }

            }
            int count=lines-1;
            for(int j=lines-1; j>=0; j--)
            {
                if(Map[j][i]!=0)
                {
                    int temp=Map[j][i];
                    Map[j][i]=0;
                    Map[count][i]=temp;
                    count--;
                }

            }
        }
    }
    else if(mov==4)
    {
        for(int i=0; i<lines; i++)
        {
            ffind=-1;
            nfind=-1;
            for(int j=0; j<cols; j++)
            {
                int k=j;
                while(k<cols&&Map[i][k]==0)
                    k++;
                if(k!=cols)
                    ffind=k;
                k++;
                while(k<cols&&Map[i][k]==0)
                    k++;
                if(k!=cols)
                    nfind=k;
                if(ffind!=-1&&nfind!=-1)
                {
                    if(ffind!=nfind)
                    {
                        if(Map[i][ffind]==Map[i][nfind])
                        {
                            Map[i][ffind]*=2;
                            if(Map[i][ffind]>maxnum)
                                maxnum=Map[i][ffind];
                            Map[i][nfind]=0;
                            core++;
                        }
                    }
                }

            }
            int count=0;
            for(int j=0; j<cols; j++)
            {
                if(Map[i][j]!=0)
                {
                    int temp=Map[i][j];
                    Map[i][j]=0;
                    Map[i][count]=temp;
                    count++;
                }

            }
        }
    }
    else if(mov==6)
    {
        for(int i=0; i<lines; i++)
        {
            ffind=-1;
            nfind=-1;
            for(int j=cols; j>=0; j--)
            {
                int k=j;
                while(k>=0&&Map[i][k]==0)
                    k--;
                if(k!=-1)
                    ffind=k;
                k--;
                while(k>=0&&Map[i][k]==0)
                    k--;
                if(k!=-1)
                    nfind=k;
                if(ffind!=-1&&nfind!=-1)
                {
                    if(ffind!=nfind)
                    {
                        if(Map[i][ffind]==Map[i][nfind])
                        {
                            Map[i][ffind]*=2;
                            if(Map[i][ffind]>maxnum)
                                maxnum=Map[i][ffind];
                            Map[i][nfind]=0;
                            core++;
                        }
                    }
                }

            }
            int count=cols-1;
            for(int j=cols-1; j>=0; j--)
            {
                if(Map[i][j]!=0)
                {
                    int temp=Map[i][j];
                    Map[i][j]=0;
                    Map[i][count]=temp;
                    count--;
                }

            }
        }
    }
}
void UpDateHighCore()
{
    if(core>hcore)      //如果有最高纪录
    {
        hcore=core;
        hstep=step;
        husetime=usetime;
        hmaxnum=maxnum;
        hmodex=lines;
        hmodey=cols;
    }
}
void DisplayMap()
{
    SetGotoxy(0,0);
    _SetTextColor(10,0);
    printf("High>> Step:%4d Core:%5d Time:%4ds\nMax:%8d\n",hstep,hcore,husetime,hmaxnum);
    printf("Now >> Step:%4d Core:%5d Time:%4ds\nMax:%8d\n",step,core,usetime,maxnum);       //输出历史最高和当前分数
    _SetTextColor(3,0);
    for(int j=0; j<cols; j++)
    {
        printf("---------");
    }
    printf("\n");
    for(int i=0; i<lines; i++)
    {
        for(int j=0; j<cols; j++)       //输出表格形式，按照颜色区分
        {
            if(Map[i][j]==0)
            {
                _SetTextColor(3,0);
                printf("        |");
            }
            else
            {
                if(Map[i][j]==2)
                {
                    _SetTextColor(15,0);
                }
                else if(Map[i][j]==4)
                {
                    _SetTextColor(15,0);
                }
                else if(Map[i][j]==8)
                {
                    _SetTextColor(13,0);
                }
                else if(Map[i][j]==16)
                {
                    _SetTextColor(13,0);
                }
                else if(Map[i][j]==32)
                {
                    _SetTextColor(9,0);
                }
                else if(Map[i][j]==64)
                {
                    _SetTextColor(9,0);
                }
                else if(Map[i][j]==128)
                {
                    _SetTextColor(11,0);
                }
                else if(Map[i][j]==256)
                {
                    _SetTextColor(11,0);
                }
                else if(Map[i][j]==512)
                {
                    _SetTextColor(10,0);
                }
                else if(Map[i][j]==1024)
                {
                    _SetTextColor(10,0);
                }
                else if(Map[i][j]==2048)
                {
                    _SetTextColor(14,0);
                }
                else if(Map[i][j]==4096)
                {
                    _SetTextColor(14,0);
                }
                else if(Map[i][j]==8192)
                {
                    _SetTextColor(12,0);
                }
                else
                {
                    _SetTextColor(4,0);
                }
                printf("%8d",Map[i][j]);
                _SetTextColor(3,0);
                printf("|");
            }
        }
        printf("\n");
        for(int j=0; j<cols; j++)
        {
            printf("---------");
        }
        printf("\n");
    }
}
int IsDead()
{
    for(int i=0; i<lines; i++)
    {
        for(int j=0; j<cols; j++)
        {
            if(Map[i][j]==0)
                return 0;       //如果存在空的格则肯定不结束
            int up,down,right,left;
            up=i-1;
            down=i+1;
            right=j+1;
            left=j-1;       //四个方向进行判定
            while(up>=0&&Map[up][j]==0)
                up--;
            if(Map[up][j]==Map[i][j]&&up!=-1)       //只要一个方向可以合并则不结束
                return 0;
            while(down<lines&&Map[down][j]==0)
                down--;
            if(Map[down][j]==Map[i][j]&&down!=lines)
                return 0;
            while(right<cols&&Map[i][right]==0)
                right++;
            if(Map[i][right]==Map[i][j]&&right!=cols)
                return 0;
            while(left>=0&&Map[i][left]==0)
                left--;
            if(Map[i][left]==Map[i][j]&&left!=-1)
                return 0;
        }
    }
    return 1;       //排除所有情况不结束，肯定结束了
}
void help()
{
    system("cls");
    system("color 0a");
    SetConsoleSize(35,100);
    printf("-------------------------\n");
    printf("\tHelp & Declare\n");
    printf("\t  按键说明：\n");
    printf("\t      上（8/w） 下（5/s） 左（4/a） 右（6/d）\n");
    printf("\t  文件(夹)说明：\n");
    printf("\t  .hlog文件未保存了历史最高记录的文本文件，也就是可以用记事本打开\n");
    printf("\t  048GameLog文件夹保存历史最高记录文件(不更改它们的名字)\n");
    printf("\t  玩法说明：\n");
    printf("\t      通过方向键点击，对应滑动方块\n");
    printf("\t      过程会随机生成方块\n");
    printf("\t      如果路径上的下一个方块数字和这个数字相等，那么会相加，并消除一个\n");
    printf("\t  示例：4/a键\n");
    printf("    Step:   9 Core:    4 Time:  13s\n");
    printf("------------------------------------\n");
    printf("       8|       4|       2|       2|\n");
    printf("------------------------------------\n");
    printf("       2|       2|        |        |\n");
    printf("------------------------------------\n");
    printf("        |        |        |       2|\n");
    printf("------------------------------------\n");
    printf("        |        |        |        |\n");
    printf("------------------------------------\n");
    printf("\t  变为：\n");
    printf("    Step:  10 Core:    6 Time: 17s\n");
    printf("------------------------------------\n");
    printf("       8|       4|       4|       2|\n");
    printf("------------------------------------\n");
    printf("       4|        |        |        |\n");
    printf("------------------------------------\n");
    printf("       2|        |        |        |\n");
    printf("------------------------------------\n");
    printf("        |        |        |        |\n");
    printf("------------------------------------\n");
    system("pause");
}

void ReadFileInfo()
{
    char filename[1024]= {0};
    sprintf(filename,"2048GameLog\\Game2048-%d-%d.hlog\0",lines,cols);
    FILE * fp=fopen(filename,"r");
    if(fp!=NULL)        //如果文件存在则进行读取
    {
        int thstep=0;
        int thcore=0;
        int thusetime=0;
        int thmaxnum=2;
        int thmodex=4;
        int thmodey=4;
        int count=fscanf(fp,"%d%d%d%d%d%d",&thmodex,&thmodey,&thstep,&thcore,&thusetime,&thmaxnum);
        if(count==6)        //如果读取正确则赋值
        {
            hstep=thstep;
            hcore=thcore;
            husetime=thusetime;
            hmaxnum=thmaxnum;
            hmodex=thmodex;
            hmodey=thmodey;
        }
        fclose(fp);
        return;
    }

    hstep=0;
    hcore=0;
    husetime=0;
    hmaxnum=2;
    hmodex=4;
    hmodey=4;

}
void WritFileInfo()
{
    char filename[1024]= {0};
    sprintf(filename,"2048GameLog\\Game2048-%d-%d.hlog\0",lines,cols);
    mkdir("2048GameLog");
    FILE * fp=fopen(filename,"w");
    fprintf(fp,"%d %d %d %d %d %d\n",hmodex,hmodey,hstep,hcore,husetime,hmaxnum);
    fprintf(fp,"High>> Step:%4d Core:%5d Time:%4ds\nMax:%8d\n",hstep,hcore,husetime,hmaxnum);
    fprintf(fp,"Now >> Step:%4d Core:%5d Time:%4ds\nMax:%8d\n",step,core,usetime,maxnum);       //格式按照输出屏幕到文件
    for(int j=0; j<cols; j++)
    {
        fprintf(fp,"---------");
    }
    fprintf(fp,"\n");
    for(int i=0; i<lines; i++)
    {
        for(int j=0; j<cols; j++)
        {
            if(Map[i][j]==0)
            {
                fprintf(fp,"        |");
            }
            else
            {
                fprintf(fp,"%8d",Map[i][j]);
                fprintf(fp,"|");
            }
        }
        fprintf(fp,"\n");
        for(int j=0; j<cols; j++)
        {
            fprintf(fp,"---------");
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}

void SetConsoleSize(int lines,int cols)
{
    char mind[1024]= {0};
    if(lines>0 && cols>0)
        sprintf(mind, "mode con lines=%d cols=%d\0", lines, cols);
    else if(lines <=0 && cols>0)
        sprintf(mind, "mode con cols=%d\0", cols);
    else if(lines >0 && cols<=0)
        sprintf(mind, "mode con lines=%d\0", lines);
    else if(lines<=0 && cols<=0)
        return;
    system(mind);
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
