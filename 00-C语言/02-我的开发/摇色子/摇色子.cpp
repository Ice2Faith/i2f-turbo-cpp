#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<conio.h>
#include<ctime>
#include<windows.h>
#define COUNT_NUM 5
#define FLASH_TIMES 10
using namespace std;
int main(void)
{
    system("mode con lines=5 cols=50");
    system("title 单人摇骰子 Dev Ice2Faith");
    system("color f5");
    char FontColor[17]= {"0123456789abcdef"};
    char Mind[100];
    while(1)
    {
        system("cls");
        cout << "按任意键开始摇骰子" << endl;
        getch();
        for(int j=0; j<FLASH_TIMES; j++)
        {
            system("cls");
            cout << endl << endl;
            cout << "\t";
            for(int i=0; i<COUNT_NUM; i++)
            {
                srand((unsigned)time(NULL)+rand());
                cout << rand()%6+1 << "\t";
            }
            cout << endl;
            sprintf(Mind,"color %c%c\0",FontColor[rand()%16],FontColor[rand()%16]);
            system(Mind);
            Sleep(80);
        }
        system("color f5");
        cout << endl << "这是您的结果，按任意键继续，\"*\"号结束" << "\a";
        if(getch()=='*')
            break;
    }
    return 0;
}
