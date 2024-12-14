#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
void MainMeau();    //����˵�
void MainGame2048(int _lines,int _cols);    //��Ҫ���п��ƺ���
void InitialMap(int _lines,int _cols);      //��ʼ��ͼ
void CreateNew();    //�����µ�����
int GetMove();      //��ȡ�ƶ�������߲���
void MoveAndResult(int mov);        //�����ƶ�����
void UpDateHighCore();      //������߳ɼ�
void DisplayMap();      //չʾͼ
int IsDead();       //�ж���Ϸ�Ƿ����
void help();        //��ʾ������Ϣ

void SetConsoleSize(int lines,int cols);        //���ÿ���̨���ڴ�С
void _SetTextColor(int ForeColor,int BackGroundColor);      //���ÿ���״̬������ɫ
void SetGotoxy(int lines,int cols);     //���ÿ���̨���λ��

void ReadFileInfo();        //��ȡ��߳ɼ�
void WritFileInfo();        //д����߳ɼ�
    //��¼��߳ɼ�����ļ���
int hstep=0;
int hcore=0;
int husetime=0;
int hmaxnum=2;
int hmodex=4;
int hmodey=4;
    //����ͼ������ʱ����
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
        printf("��ӭ����");
        _SetTextColor(15,0);
        printf("2");
        _SetTextColor(10,0);
        printf("0");
        _SetTextColor(14,0);
        printf("4");
        _SetTextColor(12,0);
        printf("8");
        _SetTextColor(11,0);
        printf("С��Ϸ");      //�������
        SetGotoxy(2,10);
        _SetTextColor(12,0);
        printf("1.��ʼ��Ϸ");

        SetGotoxy(3,10);
        _SetTextColor(14,0);
        printf("2.�鿴�淨");

        SetGotoxy(4,10);
        _SetTextColor(9,0);
        printf("0.������Ϸ");

        SetGotoxy(5,5);
        _SetTextColor(10,0);
        printf("---------------------------");      //���ѡ��

        SetGotoxy(6,5);
        _SetTextColor(11,0);
        printf(">/ ");
        char sel='\0';
        while(sel<'0'||sel>'2')
            sel=getch();
        printf("%c\n",sel);         //��ȡѡ��
        if(sel=='0')
            break;
        if(sel=='1')
        {
            int _lines=4,_cols=4;
            printf("���� * �޸Ĵ�С��Ĭ��4*4\n>/ ");
            if((getch())=='*')
            {
                printf("�������С������ ��������\n>/ ");
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
            printf("1 ��������Ϸ %d*%d...",_lines,_cols);       //��ȡ����ʱ��С
            printf("tips:��Ϸ������԰� * ��ʱ������Ϸ\n");
            Sleep(1000);
            MainGame2048(_lines,_cols);     //��������
        }
        if(sel=='2')
            help();
    }

}
void MainGame2048(int _lines,int _cols)
{
    InitialMap(_lines,_cols);       //��ʼ��ͼ
    int mov=0;      //�����˶�����
    int result=0;       //�ж���Ϸ�Ƿ����
    while(1)
    {
        system("cls");      //ˢ����Ļ
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
    printf("�� * �˳�\n");
    char endsure='\0';
    while(endsure!='*')
        endsure=getch();
}
void InitialMap(int _lines,int _cols)
{
    system("color 0a");
    runtime=time(NULL);     //��¼��ʼʱ�䣬��������ʱ��
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
    ReadFileInfo();     //���ļ���ȡ��߼�¼
}
void CreateNew()
{
    int hasfull=1;
    for(int i=0; i<lines; i++)
    {
        for(int j=0; j<cols; j++)
        {
            if(Map[i][j]==0)
                hasfull=0;      //�ж��Ƿ����ˣ������Ŵ���
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
    step++;     //��������
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
                    nfind=k;     //��ȡ��һ����Ϊ�����һ����Ϊ��
                if(ffind!=-1&&nfind!=-1)
                {
                    if(ffind!=nfind)
                    {
                        if(Map[ffind][i]==Map[nfind][i])        //������ȡ��������
                        {
                            Map[ffind][i]*=2;
                            if(Map[ffind][i]>maxnum)
                                maxnum=Map[ffind][i];
                            Map[nfind][i]=0;
                            core++;         //��������
                        }
                    }
                }

            }
            int count=0;
            for(int j=0; j<lines; j++)      //���߶���
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
    if(core>hcore)      //�������߼�¼
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
    printf("Now >> Step:%4d Core:%5d Time:%4ds\nMax:%8d\n",step,core,usetime,maxnum);       //�����ʷ��ߺ͵�ǰ����
    _SetTextColor(3,0);
    for(int j=0; j<cols; j++)
    {
        printf("---------");
    }
    printf("\n");
    for(int i=0; i<lines; i++)
    {
        for(int j=0; j<cols; j++)       //��������ʽ��������ɫ����
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
                return 0;       //������ڿյĸ���϶�������
            int up,down,right,left;
            up=i-1;
            down=i+1;
            right=j+1;
            left=j-1;       //�ĸ���������ж�
            while(up>=0&&Map[up][j]==0)
                up--;
            if(Map[up][j]==Map[i][j]&&up!=-1)       //ֻҪһ��������Ժϲ��򲻽���
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
    return 1;       //�ų�����������������϶�������
}
void help()
{
    system("cls");
    system("color 0a");
    SetConsoleSize(35,100);
    printf("-------------------------\n");
    printf("\tHelp & Declare\n");
    printf("\t  ����˵����\n");
    printf("\t      �ϣ�8/w�� �£�5/s�� ��4/a�� �ң�6/d��\n");
    printf("\t  �ļ�(��)˵����\n");
    printf("\t  .hlog�ļ�δ��������ʷ��߼�¼���ı��ļ���Ҳ���ǿ����ü��±���\n");
    printf("\t  048GameLog�ļ��б�����ʷ��߼�¼�ļ�(���������ǵ�����)\n");
    printf("\t  �淨˵����\n");
    printf("\t      ͨ��������������Ӧ��������\n");
    printf("\t      ���̻�������ɷ���\n");
    printf("\t      ���·���ϵ���һ���������ֺ����������ȣ���ô����ӣ�������һ��\n");
    printf("\t  ʾ����4/a��\n");
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
    printf("\t  ��Ϊ��\n");
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
    if(fp!=NULL)        //����ļ���������ж�ȡ
    {
        int thstep=0;
        int thcore=0;
        int thusetime=0;
        int thmaxnum=2;
        int thmodex=4;
        int thmodey=4;
        int count=fscanf(fp,"%d%d%d%d%d%d",&thmodex,&thmodey,&thstep,&thcore,&thusetime,&thmaxnum);
        if(count==6)        //�����ȡ��ȷ��ֵ
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
    fprintf(fp,"Now >> Step:%4d Core:%5d Time:%4ds\nMax:%8d\n",step,core,usetime,maxnum);       //��ʽ���������Ļ���ļ�
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
