#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include"Ice2Feathers.h"
    //����ͼ��С
    int map[20][20]={0};
      //�������
   int core=0;
   int highcore;
    void SaveCore();

void redhighcore();
void writhighcore();

void main()
{
    system("title ��Ұ�Խ� By: Ice2Feathers");
    system("color f5");
    system("mode con cols=60 lines=30");
    redhighcore();
    //�����û���ʼλ��
   int userx=0,usery=0;
   int upuserx,upusery;
   //���影��������
   int giftx,gifty;
   //��������
   srand((unsigned)time(NULL)+rand());
    puts("----------------------------\n");
    puts("***  ��ӭ��������С��Ϸ  ***\n");
    puts("��Ϸ��:      ��Ұ�Խ�       \n");
    puts("----------------------------\n");
    puts("You:&\tCoin:$\tBrambles:#\n");
    printf("Tips:\n\nΪ����������л���Ӣ�����뷨\n\n>> \n\n");
    system("pause");
    system("cls");
   char control;
   int eat=1;
    giftx=rand()%20;
    gifty=rand()%20;

    map[giftx][gifty]=9;
    int wallx,wally;
    //�����ϰ�
       for(int k=0;k<18;k++)
       {
           srand((unsigned)time(NULL)+rand());
           wallx=rand()%20;
            wally=rand()%20;
            while((wallx==0&&wally==0)||(wallx==4&&wally==4))
            {
                srand((unsigned)time(NULL)+rand());
                 wallx=rand()%20;
                wally=rand()%20;
            }
            map[wallx][wally]=4;
       }
       int lon=1;
   //���ɽ�����λ��
   while(lon==1)
   {
       srand((unsigned)time(NULL)+rand());
       printf("Core: %3d\tHighCore: %3d\n\n",core,highcore);
        puts("Up:W\tDown:S\tLeft:A\tRight:D\tQuit:*");
       if(eat==0)
       {
            giftx=rand()%20;
            gifty=rand()%20;
            while(map[giftx][gifty]==4)
            {
                srand((unsigned)time(NULL)+rand());
                 giftx=rand()%20;
                gifty=rand()%20;
            }
            map[giftx][gifty]=9;
            eat=0;
       }

        map[userx][usery]=1;
        upuserx=userx;
        upusery=usery;
        puts("- - - - - - - - - - - - - - - - - - - - - - ");
        for(int i=0;i<20;i++)
        { printf("+ ");
            for(int j=0;j<20;j++)
                {
                if(map[j][i]==0)
                    printf("  ");
                else
                if(map[j][i]==1)
                    printf("& ");
                else
                if(map[j][i]==9)
                    printf("$ ");
                    else
                if(map[j][i]==4)
                    printf("# ");

                }
                 printf("+ ");
            printf("\n");
        }
        puts("- - - - - - - - - - - - - - - - - - - - - - ");
        //��ȡ�ƶ�����
        if(kbhit()!=0)
        control=getch();
        else
            control='r';
        if(control=='W'||control=='w')
        {
            if(usery==0)
                usery=19;
            else
            usery--;
        }
        else
         if(control=='S'||control=='s')
        {
            if(usery==19)
                   usery=0;
            else
            usery++;
        }
        else
         if(control=='A'||control=='a')
        {
            if(userx==0)
                userx=19;
            else
            userx--;
        }
        else
         if(control=='D'||control=='d')
        {
             if(userx==19)
                   userx=0;
            else
            userx++;
        }
         else
         if(control=='*'||control=='*')
        {
            //�˳�ѭ��
            lon=0;
        }

        if(map[userx][usery]==4)
        {
            userx=upuserx;
            usery=upusery;
            core--;
            system("color cf");
            Sleep(90);
            system("color f5");
        }

        map[upuserx][upusery]=0;

        if(userx==giftx&&usery==gifty)
        {
            core++;
            eat=0;
            system("color e5");
            Sleep(90);
            system("color f5");
        }
        else
            eat=1;

 if(core>highcore)
        highcore=core;
        srand((unsigned)time(NULL)+rand());
        Sleep(75);
        system("cls");
   }
    writhighcore();
   printf("����ǰ�÷�: %d\n\n",core);
   puts("���� S ���Ա��汾ͼս��");
   fflush(stdin);
   char save=getch();
   if(save=='S'||save=='s')
   {
     SaveCore();
     printf("\n\n�Ѿ�Ϊ�������ͼ���ļ���\n\n>>\tSaveMapCore.txt\n\n");
     Sleep(500);
   }
    End();
}

void redhighcore()
{
    FILE * stream;
    if(fopen("HHighCore.bas","r")==NULL)
    {
         stream=fopen("HHighCore.bas","w");
       fprintf(stream,"0");
    }
    else
        stream=fopen("HHighCore.bas","r");
    fscanf(stream,"%d",&highcore);
    fclose(stream);
}
void writhighcore()
{
    FILE * stream;
    stream=fopen("HHighCore.bas","w");
    if(core>highcore)
        highcore=core;
    fprintf(stream,"%d",highcore);
    fclose(stream);
}

void SaveCore()
{
    FILE * stream;
    stream=fopen("SaveMapCore.txt","w");
     fprintf(stream,"���ĵ÷֣� %d\n\n",core);
       fprintf(stream,"\t��Ϸ��ͼ��\n\n");
   fprintf(stream,"- - - - - - - - - - - - - - - - - - - - - - \n");
        for(int i=0;i<20;i++)
        { fprintf(stream,"+ ");
            for(int j=0;j<20;j++)
                {
                //printf("%d ",map[j][i]);
                if(map[j][i]==0)
                    fprintf(stream,"  ");
                else
                if(map[j][i]==1)
                    fprintf(stream,"& ");
                else
                if(map[j][i]==9)
                    fprintf(stream,"$ ");
                    else
                if(map[j][i]==4)
                    fprintf(stream,"# ");

                }
                 fprintf(stream,"+ ");
            fprintf(stream,"\n");
        }
        fprintf(stream,"- - - - - - - - - - - - - - - - - - - - - - \n");
        fclose(stream);
}
