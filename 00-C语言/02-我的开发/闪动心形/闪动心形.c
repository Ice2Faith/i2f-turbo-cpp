#include <stdio.h>
#include <conio.h>  //������ʽ�����ַ���������Ҫ�س�
#include <stdlib.h>  //ϵͳ���Ӷ��壬system����
#include <Windows.h>  //�ӳ����Sleep��������
#include <time.h>  //���������ʹ����Ҫ
#include <math.h>  //Pow�������壬����ǰһ�������ĺ�һ�������η�
#include <string.h>  //strlen�������壬�����ַ�������

void FlashHeart();
int main()
{
    //system����ָ��֧���������cmd(WIN*R���cmd�س�)������help �鿴ȫ��ָ��鿴ָ��ָ����ϸ���磺help color
    FlashHeart();
}

void FlashHeart()
{
    system("title FlashHeart Dev: Ice2Faith");  //���򴰿����ϽǱ��ⶨ��
    system("color f5");  //���������ɫ����
    srand((unsigned)time(NULL)+rand());
    char colorrun[] = { "14569cd" };  //����������ɫ�ʱ任��
    char cmdcolor[20] = { '\0' };     //���system��������
    char Text[100] = { "Love Needn't Reason!" };
    printf("����֮�ü�������>>>\n\n");
    printf("�Ƿ���Ҫ�Զ���������ݣ��������� 1 ����ʹ��Ĭ��\n\n>/ ");
    char user='0';
    user=getch();  //getch������ֻҪ���̻����������ַ���ֱ�Ӷ�ȡ�ַ������ûس�������ʾ����ֵ
    printf("%c\n",user);
    if(user=='1')
    {
        printf("����������������ݣ�\n>/ ");
        gets(Text);
    }
    double x1=1;
    fflush(stdin);
    printf("�Ƿ���Ҫ�Զ������δ�С���������� 1 ����ʹ��Ĭ��\n\n>/ ");
    user='0';
    user=getch();
    if(user=='1')
    {
        printf("��������Ҫ���ĵı�����Ĭ��1,ȫ����������2��\n>/ ");
        scanf("%lf",&x1);
        if(x1<=0)
            x1=0.1;
    }
    system("cls");  //����
    double x,y;
    int i=0,m,len,jj = 0;
    len=strlen(Text);  //�����������ı����ȣ�������
    for (x = 1.4; x >= -1.4; x -= 0.1/x1)  //����X��Y�仯��Χ
    {
        for (y = -2.4; y <= 2.4; y += 0.053/x1)
        {
            if (pow(x*x + y*y - 1, 3) - x*x*x*y*y <= 0)   //����������κ�����X��+Y��-1��������-X����*Y��<=0�����������ڣ�����ַ�����������ո�
            {

                printf("%c", Text[(i++)%len]);
                Sleep(5);
            }
            else
            {
                printf(" ");
            }

            if (jj % 60 == 0)  //JJΪ�������������������60�ı�����������л�������ɫ
            {
                m = rand() % 7;
                sprintf(cmdcolor, "color f%c\0", colorrun[m]);  //����sprintf�����������ݴ���cmdcolor�����У����\0��־������
                system(cmdcolor);  //����system����ִ��cmdcolor������ָ��
            }
            jj++;

        }
        printf("\n");   //ÿһ�������������
    }
    char exit='0';
    printf(">/ Input \"*\" Exit the APP\n\n");
    do  //����û��Ƿ�Ҫ�˳������˳���ѭ���л�������ɫ
    {
        if(kbhit()!=0)  //kbhit�������ڼ����̻������Ƿ�����ַ������ڷ��ط�0
        exit=getch();   //��������ַ��Ͷ�ȡ�������ھͲ����������ǳ�ʼ��ֵ
        m = rand() % 7;
        sprintf(cmdcolor, "color f%c\0", colorrun[m]);
        system(cmdcolor);
        Sleep(35);  //�ӳ�35���룬����1000��Ϊ1��
    }
    while(exit!='*');
}
