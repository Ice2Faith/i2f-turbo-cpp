#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>
int  LOCKER();
int  UNLOCKER();
void help();
//��ͷ˵��,���������ַ���
void Head(char * title);
//��β˵��
void End();
//�����ַ���������,���ʱ���Զ���
void Bitprint(char *p, int between);
//��Ļ��ʾ��type��-1����0���棬1ͨ����before��֮ǰ����ɫ�磺f5
void Screentips(int type,char * before);
//����������ɫ,��������ֻ�ı�ǰ��ɫ��������ɫ
void Randcolor(int mode);
char endch='#';
void main()
{
    int k=0;
    char sel;
    while(k==0)
    {
        endch='#';
        Head("������ܽ��ܳ���");
        Bitprint("\n\t��ѡ��\n\n\t1.�����ı�\n\n\t2.�����ı�\n\n\t3.�鿴����\n\n\t0.�˳�����\n\n----------------------------------------\n\n>> ",6);
        fflush(stdin);
        sel=getch();
        putchar(sel);
        fflush(stdin);
        Sleep(480);
        system("cls");
        if(sel=='1')
        {
            printf("Ĭ�Ͻ�����Ϊ\'%c\',��Ҫ�޸������� \'1\' �����޸� >> ",endch);
            char change=getch();
            putchar(change);
            if(change=='1')
            {
                printf("\n�����������(ASCII,�˴��л�ΪӢ�����뷨): >> ");
                endch=getch();
                putchar(endch);
                printf("\n�½�����Ϊ��>> \'%c\'\n",endch);
            }
            LOCKER();
            system("pause");
        }
        else if(sel=='2')
        {
            UNLOCKER();
            system("pause");
        }
        else if(sel=='3')
        {
            help();
            system("pause");
        }
        else if(sel=='0')
        {
            Screentips(0,"f5");
            Bitprint("\n\n\t����Ϊ���˳�����......\n\n>> ",10);
            k=1;
        }
        else
        {
            Screentips(-1,"f5");
            Bitprint("\n\n\t��û�п������\n\n\t����һ�Σ���\n\n>> ",6);
        }

        Sleep(1200);
        system("cls");

    }
    End();
}
int  LOCKER()
{
    char * temp=(char *)malloc(sizeof(char));
    char key[100]= {"Ice2Feathers"};
    FILE * Lock=fopen("LockText.txt","wb");
    Bitprint("\n\n\t���������ļ������ݣ�\n\n>> \n",20);
    int LenKey=strlen(key);
    int counter=0;
    *temp=getchar();
    while(*temp!=endch)
    {
        *temp^=key[(counter++)%LenKey];
        counter%=LenKey;
        fwrite(temp,1,sizeof(char),Lock);
        *temp=getchar();
    }
    fclose(Lock);
    printf("\n\n�Զ����浽 \"LockText.txt\"\n");
    Screentips(1,"f5");
}
int  UNLOCKER()
{
    char * temp=(char *)malloc(sizeof(char));
    char key[100]= {"Ice2Feathers"};
    FILE * Lock=fopen("LockText.txt","rb");
    FILE * UnLock=fopen("UnLockText.txt","w");
    Bitprint("\n\n\t�������Ľ������ݣ�\n\n>> \n",20);
    int LenKey=strlen(key);
    int counter=0;
    while(!feof(Lock))
    {
        if(fread(temp,1,sizeof(char),Lock)==0)
            break;
        *temp^=key[(counter++)%LenKey];
        counter%=LenKey;
        fprintf(UnLock,"%c",*temp);
        printf("%c",*temp);
    }
    fclose(Lock);
    fclose(UnLock);
    printf("\n\n�Զ����浽 \"UnLockText.txt\"\n");
    Screentips(1,"f5");
}

//��ͷ˵��,���������ַ���
void Head(char * title)
{
    char titlea[100];
    //�˴����������������ݣ����100��
    char headtxt[100][100] =
    {
        "\n----------------------------------------\n",
        "\n\t \n",
        "\n\t By: Ice2Feathers \n",
        "\n----------------------------------------\n"
    };
    sprintf(titlea, "title %s By : Ice2Feathers", title);
    sprintf(headtxt[1], "\n\t %s\n", title);

    system(titlea);
    system("color f5");

    int k = 0, counter = 0;
    while (headtxt[k][0] != '\0')
    {
        counter++;
        k++;
    }
    int i, j;
    for (i = 0; i < counter; i++)
    {

        j = 0;
        while (headtxt[i][j] != '\0')
        {
            printf("%c", headtxt[i][j]);
            Sleep(20);
            j++;
        }
    }
}
//------------------------------------------------------------------------------------------------------
//��β˵��
void End()
{
    printf("\n");
    Sleep(1200);
    Sleep(800);
    system("color f9");
    system("cls");
    //�˴����������������ݣ����100��
    char endtxt[100][100] =
    {
        "\n\n----------------------------------------\n",
        "\n\n\t������ֻ�����!!!\n",
        "\n\tThanks for your used!!!\n",
        "\n\t By: Ice2Feathers \n",
        "\n\n----------------------------------------\n"
    };
    int k = 0, counter = 0;
    while (endtxt[k][0] != '\0')
    {
        counter++;
        k++;
    }
    int i, j;
    for (i = 0; i < counter; i++)
    {
        j = 0;
        while (endtxt[i][j] != '\0')
        {
            printf("%c", endtxt[i][j]);
            Sleep(20);
            j++;
        }
        Randcolor(1);
    }
    system("color 75");
    Sleep(1000);
    system("color 79");
    Sleep(1000);
    system("color 70");
    Sleep(1000);
}
//------------------------------------------------------------------------------------------------------
//�����ַ���������,���ʱ���Զ���
void Bitprint(char *p, int between)
{
    while(*p!='\0')
    {
        printf("%c",*p);
        p++;
        Sleep(between);
    }
}
//��Ļ��ʾ��type��-1����0���棬1ͨ����before��֮ǰ����ɫ�磺f5
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
    Sleep(90);
    system(beforec);
}
//����������ɫ,��������ֻ�ı�ǰ��ɫ��������ɫ
void Randcolor(int mode)
{
    srand((unsigned)time(NULL) + rand());
    int f = rand() % 16, b = rand() % 16;
    char color[] = { "0123456789abcdef" };
    char cmd[100];
    if (mode == 0)
    {
        while (f == b)
            b = rand() % 16;
        sprintf(cmd, "color %c%c", color[f], color[b]);
        system(cmd);
    }
    else
    {
        sprintf(cmd, "color f%c", color[f]);
        system(cmd);
    }
}
void help()
{
    system("cls");
    printf("\n\n");
    printf("\t����:\t�����ı����ܽ���\n\n");
    printf("\t����:\tIce2Feathers\n\n");
    printf("\t\t���ļ����ı����ᱣ�浽 \"LockText.txt\".\n\n");
    printf("\t\t���Ľ����ı����ᱣ�浽 \"UnLockText.txt\".\n\n");
    printf("\t����:\t�����ı����ܣ�֧�ֶ��У�Ĭ�Ͻ�����ǲ��س��� \'#\'.\n\n");
    printf("\t����:\t���ļ����ܣ��ļ��� \"LockText.txt\".\n\n");
    printf("\t����:\t��Ӣ�Ļ���֧�֣��벻Ҫ�޸ļ����ļ���������ܴ���\n\n");
    printf("\t\t�������ַ�����~ @ # $ & * { } [ ] .\n\n");
    printf("\tע��:\t���ļ����Ḳ�Ǿ��ļ���ע�Ᵽ�棡��\n\n\t");
}
