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
    system("title ����ҡ���� Dev Ice2Faith");
    system("color f5");
    char FontColor[17]= {"0123456789abcdef"};
    char Mind[100];
    while(1)
    {
        system("cls");
        cout << "���������ʼҡ����" << endl;
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
        cout << endl << "�������Ľ�����������������\"*\"�Ž���" << "\a";
        if(getch()=='*')
            break;
    }
    return 0;
}
