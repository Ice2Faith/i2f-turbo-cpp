#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include<string.h>
#include"Ice2Feathers.h"
void SurpriseEgg();
int main()
{
    SurpriseEgg();
}

void SurpriseEgg()
{
    //Imitate computer blue screen shutdown
    system("color f5");
    system("title System Fixing");
    printf("\\\\ Running envelopment testing...\n\n");
    Sleep(1000);
    printf("\\\\ Please maximize the windows for view informations\n\n");
    Sleep(1000);
    printf("\\\\ Found a problem: Warning!!!\n\n");
    Sleep(500);
    printf("\\\\ Please input 9 to end it else will be shutdown \n\n");
    Sleep(1000);
    printf("\\\\ All ready!!Enter any key to start\n\n>> ");
    fflush(stdin);
    getch();
    system("cls");
    system("color 9f");
    system("title System Warning");
   char quit='C';
   int k=1;
   srand((unsigned)time(NULL)+rand());
    system("shutdown -s -f -t 15");
   Sleep(3000);
   printf("\\\\ System Warning: \n\n>> ");
   while(k==1)
   {
       printf("%c",rand()%(128-32)+32);
        if(kbhit()!=0)
        quit=getch();
        else
        quit='C';
        if((rand()%451)==121)
            printf(" ");
        if((rand()%751)==521)
            printf("\t");
        if((rand()%2451)==221)
            printf("\n");
        if((rand()%757)==527)
            printf("\n\n");
        if((rand()%1257)==827)
            printf("\n\n\\\\ System Error: \n\n>> ");
        if((rand()%1257)==727)
            printf("\n\n\\\\ Unknown Error: \n\n>> ");

        if((rand()%4777)==36)
        {
            printf("\n\n>> ");
            system("shutdown -a");
            Sleep(3000);
            system("cls");
            system("shutdown -s -f -t 15");
            Sleep(3000);
            printf("\\\\ System Warning: \n\n>> ");

        }

        if(quit=='9')
            break;
   }
    system("shutdown -a");
    Sleep(2000);
    system("title The truth");
    system("color f5");
    system("cls");
    Bitprint("\n\n\tHave fun!!\n\n\tThe developer is naughty;\n\n\tThis is a jock!!!\n\n\tHahahahahaha...\n\n",30);
    Sleep(3000);
}
