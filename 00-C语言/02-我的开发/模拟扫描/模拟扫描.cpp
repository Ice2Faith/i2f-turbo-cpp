#include<iostream>
#include"ConsoleControl.h"

using namespace::std;
void ModelScan(int lines,int cols);
int main(int argc,char *argv[])
{
    ConsoleControl control;
    control.SetConsoleTitle("模拟扫描垃圾");
    control.SleepPrint(30,"过程中可按 * 随时结束运行\n");
    control.SleepPrint(30,"请输入大小：lines cols\n>/ ");
    int l,c;
    scanf("%d%d",&l,&c);
    ModelScan(l,c);

    return 0;
}

void ModelScan(int lines,int cols)
{
    ConsoleControl control;
    int fc[20]= {6,15,15,4,7,4,5,9,12,15,15,15,1,10,11,1,6,15,6};
    int bc[20]= {0,9,11,15,8,0,15,15,7,0,11,8,0,7,0,15,7,11,15};
    srand((unsigned)time(NULL));
    int sel=rand()%19;
    control.SetConsoleColor(fc[sel],bc[sel]);
    control.SetConsoleSize(lines,cols);
    srand((unsigned)time(NULL));
    char chs[1024][1024]= {0};
    for(int i=0; i<1024; i++)
        for(int j=0; j<1024; j++)
            chs[i][j]=rand()%(127-32)+32;

    while(1)
    {
        int trash=rand()%(lines*cols)*1/10;
        for(int t=0; t<trash; t++)
        {
            int tx,ty;
            tx=rand()%lines;
            ty=rand()%cols;
            control.SetGotoxy(tx,ty);
            printf("%c",rand()%(127-32)+32);
        }
        for(int k=0; k<cols; k++)
        {
            for(int i=0; i<lines; i++)
            {

                control.SetGotoxy(i,k+1);
                printf("%c",chs[i][k]);
                if(control.Getchif()=='*')
                    exit(0);
                control.SetGotoxy(i,k);
                printf(" ");

            }
            Sleep(20);
        }
    }
}
