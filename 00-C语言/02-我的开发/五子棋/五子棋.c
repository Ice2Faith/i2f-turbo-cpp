#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include"Ice2Feathers.h"
//����
#define SIZEX 25
//����
#define SIZEY 30

void wuziqi();
int ifwin(int x,int y);
void printmap();
void newmap();
void computerrand();
void caculset(int cplayerx,int cplayery);
int map[SIZEX+2][SIZEY+2]={0};//�����������̹�ģ
int max=0;
int cmax=0;
int cx,cy;
int playerx,playery;
int cdirection=5;
int direction=5;//������������峤���������3��ı�Ϊ��Ӧ�������֣��������£�
/*
5�����ĵ�
789
456
123
��Ӧ����
*/

void main()
{
    system("title ���������� By�� IceFeathers");
    int tt=1;
       int k=1;
    while(k==1)
    {
        system("color f5");
        newmap();
        Bitprint("++++++++++++++++++++++++++++++++++++\n",3);
        Bitprint("+                                  +\n",3);
        Bitprint("+        ��ӭ��������������        +\n",3);
        Bitprint("+                                  +\n",3);
        Bitprint("+         BY: Ice2Feathers         +\n",3);
        Bitprint("+                                  +\n",3);
        Bitprint("++++++++++++++++++++++++++++++++++++\n\n",3);
        Bitprint("�������ӣ� O\t���Ե����ӣ� @\n\n",3);
        system("pause");
        if(tt==1)
        {
            Bitprint("\n\n\t���� 1 �����Զ��������ڵ����ʴ�СŶ����\n",20);
            fflush(stdin);
            char kkk=getchar();
            if(kkk=='1')
            {
                system("mode con cols=120 lines=42");
            }
            tt=0;
        }
        system("cls");
        Sleep(400);
        Bitprint("\n\t����Ϊ����������...\n",30);
        Sleep(800);
        Bitprint("\n\t���Ժ�...\n",30);
        Sleep(800);
        system("cls");
        wuziqi();
        Bitprint("\n\n\t����Ϊ��ˢ�����̣���\n\n",8);
        Sleep(1500);
        system("cls");
        //�����������
    }
}

void wuziqi()
{
   srand((unsigned)time(NULL)+rand());
    int kill;
   int k=1;
   while (k==1)
   {

        printmap();
        //��ȡ�û�����λ�ô����
            Bitprint("����������������꣺Y+X\n\n",6);
            printf(">> ");
            fflush(stdin);
            scanf("%d+%d",&playerx,&playery);
            while (playerx>SIZEX||playery>SIZEY||map[playerx][playery]!=0)
            {
            Bitprint("������󣡣�\n����������������꣺x+y\n\n",4);
            printf(">> ");
            Screentips(-1,"f5");
            fflush(stdin);
            scanf("%d+%d",&playerx,&playery);
            }
            map[playerx][playery]=1;
            system("cls");
            printmap();
            Sleep(800);
            system("cls");
            printmap();
            kill=rand()%100;
            direction=5;
    if(ifwin(playerx,playery)==1)//��һ�ʤ
    {
                Bitprint("\n\n\t��ϲ��!��Ӯ�ˣ���\n",8);
                max=0;//������󳤶�
                system("color 9f");
                k=0;
    }
    else
    if(direction!=5)
    {
        if(kill<=95)
      {
          //Ԥ���Է���
        caculset(playerx,playery);
        direction=5;
      }
      else
      {
        computerrand();


      }

    }
    else
    computerrand();


       Bitprint("\t���������У�����\n",8);
    Sleep(1500);
   system("cls");
   system("color f5");

                if(ifwin(cx,cy)==1)
                {
                printmap();
                Bitprint("\n\n\t���ź��������ˣ���\n",8);
                system("color cf");
                max=0;
                cmax=0;
                k=0;
                }


   }

}
void caculset(int cplayerx,int cplayery)
{
             int jbk;
        if(direction==8||cdirection==8)
        {
            jbk=1;
           while(map[cplayerx+jbk][cplayery]!=0)
           {
               jbk++;
           }
           if((cplayerx+jbk<SIZEX+1))
           {
              map[cplayerx+jbk][cplayery]=2;
              cx=cplayerx+jbk;cy=cplayery;
           }
           else
           {
                jbk=1;
                while(map[cplayerx-jbk][cplayery]!=0)
                {
                    jbk++;
                }
                map[cplayerx-jbk][cplayery]=2;
                cx=cplayerx-jbk;cy=cplayery;
           }
        }
        else
        if(direction==9||cdirection==9)
        {
            jbk=1;
           while(map[cplayerx+jbk][cplayery-jbk]!=0)
           {
               jbk++;
           }
           if((cplayerx+jbk<SIZEX+1)&&(cplayery-jbk>0))
           {
              map[cplayerx+jbk][cplayery-jbk]=2;
              cx=cplayerx+jbk;cy=cplayery-jbk;
           }
           else
           {
                jbk=1;
                while(map[cplayerx-jbk][cplayery+jbk]!=0)
                {
                    jbk++;
                }
                map[cplayerx-jbk][cplayery+jbk]=2;
                cx=cplayerx-jbk;cy=cplayery+jbk;
           }
        }
        else
        if(direction==6||cdirection==6)
        {
            jbk=1;
           while(map[cplayerx][cplayery-jbk]!=0)
           {
               jbk++;
           }
           if((cplayery-jbk>0))
           {
              map[cplayerx][cplayery-jbk]=2;
              cx=cplayerx;cy=cplayery-jbk;
           }
           else
           {
                jbk=1;
                while(map[cplayerx][cplayery+jbk]!=0)
                {
                    jbk++;
                }
                map[cplayerx][cplayery+jbk]=2;
                cx=cplayerx;cy=cplayery+jbk;
           }
        }
        else
        if(direction==3||cdirection==3)
        {
           jbk=1;
           while(map[cplayerx-jbk][cplayery-jbk]!=0)
           {
               jbk++;
           }
           if((cplayerx-jbk>0)&&(cplayery-jbk>0))
           {
              map[cplayerx-jbk][cplayery-jbk]=2;
              cx=cplayerx-jbk;cy=cplayery-jbk;
           }
           else
           {
                jbk=1;
                while(map[cplayerx+jbk][cplayery+jbk]!=0)
                {
                    jbk++;
                }
                map[cplayerx+jbk][cplayery+jbk]=2;
                cx=cplayerx+jbk;cy=cplayery+jbk;
           }
        }
        else
        if(direction==2||cdirection==2)
        {
           jbk=1;
           while(map[cplayerx-jbk][cplayery]!=0)
           {
               jbk++;
           }

           if((cplayerx-jbk>0))
           {
              map[cplayerx-jbk][cplayery]=2;
              cx=cplayerx-jbk;cy=cplayery;
           }
           else
           {
                jbk=1;
                while(map[cplayerx+jbk][cplayery]!=0)
                {
                    jbk++;
                }
                map[cplayerx+jbk][cplayery]=2;
                cx=cplayerx+jbk;cy=cplayery;
           }
        }
        else
        if(direction==1||cdirection==1)
        {
          jbk=1;
           while(map[cplayerx-jbk][cplayery+jbk]!=0)
           {
               jbk++;
           }
           if((cplayerx-jbk>0)&&(cplayery+jbk<SIZEY+1))
           {
              map[cplayerx-jbk][cplayery+jbk]=2;
              cx=cplayerx-jbk;cy=cplayery+jbk;
           }
           else
           {
                jbk=1;
                while(map[cplayerx+jbk][cplayery-jbk]!=0)
                {
                    jbk++;
                }
                map[cplayerx+jbk][cplayery-jbk]=2;
                cx=cplayerx+jbk;cy=cplayery-jbk;
           }
        }
        else
        if(direction==4||cdirection==4)
        {
           jbk=1;
           while(map[cplayerx][cplayery+jbk]!=0)
           {
               jbk++;
           }
           if((cplayery+jbk<SIZEY+1))
           {
              map[cplayerx][cplayery+jbk]=2;
              cx=cplayerx;cy=cplayery+jbk;
           }
           else
           {
                jbk=1;
                while(map[cplayerx][cplayery-jbk]!=0)
                {
                    jbk++;
                }
                map[cplayerx][cplayery-jbk]=2;
                cx=cplayerx;cy=cplayery-jbk;
           }
        }
        else
        if(direction==7||cdirection==7)
        {
          jbk=1;
           while(map[cplayerx+jbk][cplayery+jbk]!=0)
           {
               jbk++;
           }

           if((cplayerx+jbk<SIZEX+1)&&(cplayery+jbk<SIZEY+1))
           {
              map[cplayerx+jbk][cplayery+jbk]=2;
              cx=cplayerx+jbk;cy=cplayery+jbk;
           }
           else
           {
                jbk=1;
                while(map[cplayerx-jbk][cplayery-jbk]!=0)
                {
                    jbk++;
                }
                map[cplayerx-jbk][cplayery-jbk]=2;
                cx=cplayerx-jbk;cy=cplayery-jbk;
           }

        }

}

void computerrand()
{
    int ctx,cty;
    int i,j;
    int control=0;
    for (i=0;i<SIZEX+1;i++)
    {
        for (j=1;j<SIZEY+1;j++)
        {
            cdirection=5;
            if(map[i][j]==2)
            {
            ifwin(i,j);
            if(cdirection!=5)
            {
                ctx=i;cty=j;
                control=1;
                break;
            }

            }

        }
        if(control==1)
            break;
    }

        if(control==1)
        {
          caculset(ctx,cty);
          cdirection=5;
          control=0;
        }
        else
        {
            int computerx,computery;
            int add,space;
            //������������
            add=rand()%2;
            if(max>3)
                max=4;
            space=5-max;
                if(max<3)
               space=5-max-rand()%3;
            if(add==1)
            {
                computerx=rand()%space+1;
                computery=rand()%space+1;
               while(map[playerx+computerx][playery+computery]!=0)
                {
                computerx=rand()%space+1;
                computery=rand()%space+1;
                }

                if((playerx+computerx<SIZEX+1)&&(playery+computery<SIZEY+1))
                {
                  map[playerx+computerx][playery+computery]=2;
                cx=playerx+computerx;cy=playery+computery;
                }
                else
                {
                    map[playerx-computerx][playery-computery]=2;
                    cx=playerx-computerx;cy=playery-computery;
                }

            }
            else
            if(add==0)
            {
                computerx=rand()%space+1;
                computery=rand()%space+1;
               while(map[playerx-computerx][playery-computery]!=0)
                {
                computerx=rand()%space+1;
                computery=rand()%space+1;
                }
                if((playerx+computerx>0)&&(playery+computery>0))
                {
                   map[playerx-computerx][playery-computery]=2;
                cx=playerx-computerx;cy=playery-computery;
                }
                else
                {
                 map[playerx+computerx][playery+computery]=2;
                cx=playerx+computerx;cy=playery+computery;
                }

            }
        }
}

void printmap()
{
       int i,j;//ѭ�����Ʊ���
       Bitprint("----------\n----------------------\n",3);
        //������̴����
        //������������ߺ�����
         printf("\\ X");
        for(j=1;j<SIZEY+1;j++)
        {
                printf("%2d",j);

        }
        printf("\n");
        printf("Y \\");
                for(j=1;j<SIZEY+1;j++)
        {

                printf(" |");
        }
                printf("\n");
            //�����������
        for(i=1;i<SIZEX+1;i++)
        {
            if(i!=0&&i!=SIZEX+1)
            printf("%2d- ",i);
            for(j=1;j<SIZEY+1;j++)
            {
            // printf("%2d ",map[i][j]);
                if(map[i][j]==-1)
                {
                printf("  ");
                }
                else
                if(map[i][j]==0)
                {
                printf(". ");
                }
                else
                if(map[i][j]==1)
                {
                printf("O ");
                }
                else
                if(map[i][j]==2)
                {
                printf("@ ");
                }
            }
            printf("\n");
        }
    Bitprint("---------------------------------\n\n",2);
}

//�����̳�ʼ��
void newmap()
{
    //��ʼ����������
             int i,j;
            for(i=0;i<SIZEX+2;i++)
            {
                for(j=0;j<SIZEY+2;j++)
                {
                map[i][j]=0;
                }
            }
   //��ʼ�����̱߽�

         for(i=0;i<SIZEY+2;i++)
        {
        map[0][i]=-1;
        map[SIZEX+1][i]=-1;
        }
        for(i=0;i<SIZEX+2;i++)
        {
        map[i][0]=-1;
        map[i][SIZEY+1]=-1;
        }


}

//������������꣬����1Ӯ�ˣ�����0ûӮ
int ifwin(int x,int y)
{
int leftup=1,rightdown=1;//�Ƿ������Ϸ�ǰ�������·�ǰ��
int counter=1;//�����е������峤�ȼ���
int i,j;
int item=map[x][y];//���պ��ж���˭�µ���
int renum=0;//����ֵ��ֵ

//����ɨ��
leftup=1,rightdown=1;counter=1;

    for(i=1;i<5;i++)
    {
        if((leftup==1)&&(map[x][y-i]==item))
        {
            counter++;
        if(counter>=3)
        {
            direction=4;
            cdirection=4;
        }

        }
        else
            if(map[x][y-i]!=item)
            leftup=0;

        if((rightdown==1)&&(map[x][y+i]==item))
        {
            counter++;
            if(counter>=3)
            {
              direction=6;
              cdirection=6;
            }

        }
        else
            if(map[x][y+i]!=item)
            rightdown=0;

    }
    if(counter>max)
        max=counter;

            if(counter==5)
                renum=1;


//����ɨ��
leftup=1,rightdown=1;counter=1;

    for(i=1;i<5;i++)
    {
        if((leftup==1)&&(map[x-i][y]==item))
        {
            counter++;
            if(counter>=3)
            {
            direction=8;
            cdirection=8;
            }

        }
        else
            if(map[x-i][y]!=item)
            leftup=0;

        if((rightdown==1)&&(map[x+i][y]==item))
        {
            counter++;
            if(counter>=3)
            {
              direction=2;
              cdirection=2;
            }

        }
        else
            if(map[x+i][y]!=item)
            rightdown=0;

    }
        if(counter>max)
        max=counter;
            if(counter==5)
               renum=1;


//���Խ���ɨ��
leftup=1,rightdown=1;counter=1;

    for(i=1;i<5;i++)
    {
        if((leftup==1)&&(map[x-i][y-i]==item))
        {
            counter++;
            if(counter>=3)
            {
             direction=7;
             cdirection=7;
            }

        }
        else
            if(map[x-i][y-i]!=item)
            leftup=0;

        if((rightdown==1)&&(map[x+i][y+i]==item))
        {
            counter++;
            if(counter>=3)
            {
              direction=3;
              cdirection=3;
            }

        }
        else
            if(map[x+i][y+i]!=item)
            rightdown=0;

    }
        if(counter>max)
        max=counter;
            if(counter==5)
                renum=1;


//���Խ���ɨ��
leftup=1,rightdown=1;counter=1;

    for(i=1;i<5;i++)
    {
        if((leftup==1)&&(map[x-i][y+i]==item))
        {
            counter++;
            if(counter>=3)
            {
             direction=9;
             cdirection=9;
            }

        }
        else
            if(map[x-i][y+i]!=item)
            leftup=0;

        if((rightdown==1)&&(map[x+i][y-i]==item))
        {
            counter++;
            if(counter>=3)
            {
              direction=1;
              cdirection=1;
            }

        }
        else
            if(map[x+i][y-i]!=item)
            rightdown=0;

    }
        if(counter>max)
        max=counter;
            if(counter==5)
                renum=1;
    return renum;
}
