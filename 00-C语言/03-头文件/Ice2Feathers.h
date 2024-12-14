//������ֻ�����
//Ice2Feathersͷ�ļ�����
#ifndef _ICE2FEATHERS_H_
#define _ICE2FEATHERS_H_
/*
//ͷ�ļ�д��
#ifndef _NAME_H_
#define _NAME_H_
//...(������������ʵ��)
#endif

//����ͷ�ļ�
#include"name.h"
�ҵ�ͷ�ļ�
�ŵ���������Ŀ��Դ����һ�µ�λ�ü���
��ͷԤ����
#include "Ice2Feathers.h"
���ÿ���̨���ڴ�С
system("mode con cols=��120 lines=��40");
*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <math.h>
#define TRUE 1
#define FALSE 0
//�Զ��庯������
//------------------------------------------------------------------------------------------------------
//��ͷ˵��,���������ַ���
void Head(char * title);
//��β˵��
void End();
//��Ļ��ʾ��type��-1����0���棬1ͨ����before��֮ǰ����ɫ�磺f5
void Screentips(int type,char * before);
//ָ����Χ���������
int Randnum(int a,int b);
//�����ַ���������,���ʱ���Զ���
void Bitprint(char *p, int between);
//����������ɫ,����1ֻ�ı�ǰ��ɫ��������ɫ;0���ı�
void Randcolor(int k);
//����ת���ַ�����txt,�������ת������������num,����ת��ģʽ:0.ֱ��ת��Ϊ����ֵ��1.ת��Ϊ8����10����16������
int char2int(char * txt,int * num,int mode);
//�����������ԭ�ķ�ʽ���м��ܽ��ܣ����Ĵ�����key�������������溯������
void I2FLOCK(char * data,char * key);
void I2FUNLOCK(char * data,char * key);
//�����ı�һ�У�������������DATA����Կ�������KEY
int LockData(char * DATA,int * KEY);
//�����ı�һ��,������������DATA����Կ����KEY
int UnLockData(char * DATA,int * KEY);
//���ö������������ν���������㻹ԭ����ԭ����м��ܣ����������������Կ����
void Bit_Lock_Unlock_Data(char * data,char * key);
//����ͼ�����
void Giftheart();
//����cmdָ�����ָ��
void Cmd(char *mind);
//����ð��������Ҫ��������
void Maopao(int * num, int len);
//쳲��������У�times:control the number of print.printtotxt: isn't 0 will print to txt
void Fibonacciequence(int times,int printtotxt);
//����е�ֵ��times :between 1-100
double Calculatepi(int times);
//����e��ֵ��times :between 1-100
double Calculate_e(int times);
    //this function receive two string which fist is be searched and second is search;
    //And it will return a type of int data when found data, else return NULL
int * KMP(char * searchedstr,char * findstr);
//it will return the Date(0)/Time(1)/week(2) of present locale time(mode)
int PresentDATE(int mode);
//�������ó��򴰿���ɫ���⣬��ȣ��߶�
void FaceInt(char * color,char * title,int cols,int lines);
//��������תʮ���ƣ�����double���ͣ��������������ַ���txt,�ͽ��Ʊ�ʶoth
double Oth2OTC(char * txt,int oth);
//�ַ�����ȡ���֣�ת��Ϊdouble���ͷ���
double String2Double(char * String);
//------------------------------------------------------------------------------------------------------
//��������תʮ���ƣ�����double���ͣ��������������ַ���txt,�ͽ��Ʊ�ʶoth
double Oth2OTC(char * txt,int oth)
{
    double result=0;
    while(*txt!='.'&&*txt!='\0')
    {
        result*=oth;
        if(*txt>='0'&&*txt<='9')
        result+=(*txt-'0');
        else
        if(*txt>='A'&&*txt<='Z')
            result+=(*txt-'A'+10);
        else
        if(*txt>='a'&&*txt<='z')
            result+=(*txt-'a'+10);
        txt++;
    }
    txt++;
    int i=1;
    while(*txt>='0'&&*txt<='9')
    {

        if(*txt>='0'&&*txt<='9')
        result+=(*txt-'0')*pow(1.0/oth,(double)i++);
        else
        if(*txt>='A'&&*txt<='Z')
        result+=(*txt-'A'+10)*pow(1.0/oth,(double)i++);
            else
        if(*txt>='a'&&*txt<='z')
        result+=(*txt-'a'+10)*pow(1.0/oth,(double)i++);
        txt++;
    }
    return result;
}
//�ַ�����ȡ���֣�ת��Ϊdouble���ͷ���
double String2Double(char * String)
{
    double result=0;
    while(*String<'0'||*String>'9')
        String++;
    while(*String>='0'&&*String<='9')
    {
        result*=10;
        result+=(*String-'0');
        String++;

    }
    if(*String=='.')
    {
        String++;
        int i=1;
        while(*String>='0'&&*String<='9')
        {
            result+=(*String-'0')*pow(0.1,(double)i++);
            String++;
        }
    }

    return result;
}
//�������ó��򴰿���ɫ���⣬��ȣ��߶�
void FaceInt(char * color,char * title,int cols,int lines)
{
	char mind[100];
	sprintf(mind,"color %s\0",color);
	system(mind);
	sprintf(mind,"title %s\0",title);
	system(mind);
	sprintf(mind,"mode con cols=%d lines=%d\0",cols,lines);
	system(mind);
}
//�����������ԭ�ķ�ʽ���м��ܽ��ܣ����Ĵ�����key�������������溯������
void I2FLOCK(char * data,char * key)
{
    int i;
   while(*data!='\0')
   {
       i=0;
        while(*(key+i)!='\0')
        {
            *data=*data^*(key+i);
            i++;
        }
       data++;
   }
}
//�����������ԭ�ķ�ʽ���м��ܽ��ܣ����Ĵ�����key�������������溯������
void I2FUNLOCK(char * data,char * key)
{
    int counter=0;
    int i=0;
    while(*(key+i)!='\0')
    {
        i++;
    }
    counter=i;
    while(*data!='\0')
   {
        i=counter;
        while(i>=0)
        {
            *data=*data^*(key+i);
            i--;
        }
        data++;
   }
}
//------------------------------------------------------------------------------------------------------
//���ö������������ν���������㻹ԭ����ԭ����м��ܽ��ܣ�����һ�������������������������Կ����
void Bit_Lock_Unlock_Data(char * data,char * key)
{
    int sum=0;
    while(*key!='\0')
    {
        sum+=*key;
        key++;
    }
    while(*data!='\0')
    {
        *data=*data^sum;
        data++;
    }
}
//------------------------------------------------------------------------------------------------------
//����ת���ַ�����txt,�������ת������������num,����ת��ģʽ:0.ֱ��ת��Ϊ����ֵ��1.ת��Ϊ8����10����16������
int char2int(char * txt,int * num,int mode)
{
	if(mode==0)
	{
		while(*txt!='\0')
		{
		*num=(int)*txt;
		num++;
		txt++;
		}
	}
	else
	if(mode==1)
	{
	while(*txt!='\0')
		{
		if(*txt>='0'&&*txt<='9')
		{
			*num=(int)(*txt-'0');
			num++;
		}
		else
		if(*txt>='a'&&*txt<='f')
		{
			*num=(int)(*txt-'a'+10);
			num++;
		}
		else
		if(*txt>='A'&&*txt<='F')
		{
			*num=(int)(*txt-'A'+10);
			num++;
		}

		txt++;
		}
	}
	return 1;
}
//------------------------------------------------------------------------------------------------------
//�����ı�һ�У�������������DATA����Կ�������KEY��������ʹ��
int LockData(char * DATA,int * KEY)
{
	srand((unsigned)time(NULL)+rand());
   int i;
	while(*DATA!='\0')
	{
		*KEY=rand()%16+1;
		if(*DATA>=1&&*DATA<=127)
		{
			*DATA-=1;
			while((((*DATA+*KEY)%127+1>=8)&&((*DATA+*KEY)%127+1<=31))||(((*DATA+16-*KEY)%127+1>=8)&&((*DATA+16-*KEY)%127+1<=31))||((*DATA+*KEY)%127+1=='\0')||((*DATA+16-*KEY)%127+1=='\0'))
			{
			*KEY=rand()%16+1;
			}
			*DATA=(*DATA+*KEY)%127+1;
			DATA++;
			*DATA=(*DATA+16-*KEY)%127+1;
			DATA++;

		}
		else
		{
			*DATA+=*KEY;
			DATA++;
			*DATA+=16-*KEY;
			DATA++;
		}

	     KEY++;
	}
	return 1;
}
//�����ı�һ��,������������DATA����Կ����KEY��������ʹ��
int UnLockData(char * DATA,int * KEY)
{
      while(*DATA!='\0')
    {
		if(*DATA>=1&&*DATA<=127)
		{
			*DATA-=1;
			if(*DATA-*KEY<=0)
			{
				*DATA=127-(*KEY-*DATA)+1;
			}
			else
			{
				*DATA=*DATA-*KEY+1;
			}
			DATA++;
			if(*DATA-(16-*KEY+1)<=0)
			{
				*DATA=127-((16-*KEY+1)-*DATA);
			}
			else
			{
				*DATA=*DATA-(16-*KEY+1);
			}
			DATA++;
		}
		else
		{
			*DATA-=*KEY;
			DATA++;
			*DATA-=16-*KEY;
			DATA++;
		}


      KEY++;
	  }
	 return 1;
}
//------------------------------------------------------------------------------------------------------
//��Ļ��ʾ��type��-1����0���棬1ͨ����before��֮ǰ����ɫ�磺f5
void Screentips(int type,char * before)
{
	char beforec[20];
	sprintf(beforec,"color %s",before);
if(type==-1)
{
	system("color cf");
}
else
if(type==0)
{
	system("color e0");
}
else
if(type==1)
{
	system("color 9f");
}
	Sleep(90);
	system(beforec);
}
//------------------------------------------------------------------------------------------------------
//����cmdָ�����ָ��
void Cmd(char *mind)
{
	char cmd[100] = { '\0' };
	int i = 0,j=0;
	while (*(mind + i) != '\0')
	{
		if (*(mind + i) == '\\' || *(mind + i) == '\"')
		{
			cmd[i] = '\\';
			i++;
		}
		cmd[i] = *(mind + i);

		i++;
		j++;
	}
	system(cmd);
}
//------------------------------------------------------------------------------------------------------
//ָ����Χ���������
int Randnum(int a,int b)
{
	int min = b;
	if (a > b)
		a = a - b;
	else
	{
		min = a;
		a = b - a;
	}
	int num[10],randnum;
	srand((unsigned)time(NULL)+rand());
	for (int i = 0; i < 10; i++)
	{
		num[i] = rand() % a;
	}
	randnum = num[rand() % 10]+min;
	return randnum;
}
//------------------------------------------------------------------------------------------------------
//����ͼ�����
void Giftheart()
{
	system("color fc");
	float x, y;
	int nm = 0;
	char colorrun[] = { "14569cd" };
	char cmdcolor[20] = { '\0' };
	int m, ii, jj = 0;
	char Love[] = { "L O V E " };
	for (x = 1.4; x >= -1.4; x -= 0.1) {
		for (y = -2.4; y <= 2.4; y += 0.053) {
			if (pow(x*x + y*y - 1, 3) - x*x*x*y*y <= 0)
			{

				printf("%c", Love[(nm++) % 8]);
				Sleep(5);
			}
			else {
				printf(" ");
			}
			if (jj % 60 == 0)
			{
				m = rand() % 7;
				sprintf(cmdcolor, "color f%c", colorrun[m]);
				system(cmdcolor);
				for (ii = 0; ii < 20; ii++)
				{
					cmdcolor[ii] = '\0';
				}
			}
			jj++;
		}
		printf("\n");
	}
	system("color fc");
}
//------------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------------
//����ð��������Ҫ��������
void Maopao(int * num, int len)
{
	int i, j, change;
	int * p;
	p = num;

	for (i = 0; i < len - 1; i++)//��ʼð������
	{
		for (j = 0; j < len - 1; j++)
		{
			if (*(p + j)>*(p + j + 1))//���������ͽ�����ֵ
			{
				change = *(p + j);
				*(p + j) = *(p + j + 1);
				*(p + j + 1) = change;
			}
		}
	}
}
//------------------------------------------------------------------------------------------------------
//쳲��������У�times:control the number of print.printtotxt: isn't 0 will print to txt
void Fibonacciequence(int times,int printtotxt)
{
	double front=1,behind=1,sum;
	int opentxt=1,control=1;
	FILE * words;
	for(int i=2;i<times;i++)
	{
		sum=front+behind;
		if(control==1)
		{
			printf("%.0f\n%.0f\n",front,behind);
			control=0;
		}
		printf("%.0f\n",sum);
		if (printtotxt!=0)
		{
			if(opentxt==1)
			{
				words=fopen("Fibonacciequence.txt","w");
				fprintf(words,"%.0f\n%.0f\n",front,behind);
				opentxt=0;
			}
			fprintf(words,"%.0f\n",sum);
		}
		front=behind;
		behind=sum;
	}
	if (printtotxt!=0)
	fclose(words);
}
//------------------------------------------------------------------------------------------------------
//����е�ֵ��times :between 1-100
double Calculatepi(int times)
{
	times*=1000000;
	double num=1,newnum,nummo;
	double sum=1;
	for(int i=0;i<=times;i++)
	{

		newnum=num+2;
		nummo=newnum;
		if(i%2==0)
		{
			nummo=0-newnum;

			}
		sum=sum+(1/nummo);
		num=newnum;
	}

	return sum*4;
}
//------------------------------------------------------------------------------------------------------
//����e��ֵ��times :between 1-100
double Calculate_e(int times)
{
    times*=999999999999999;
	double sum=pow((1+1/((double)times)),(double)times);

	return sum;
}
//------------------------------------------------------------------------------------------------------
//KMP���Ӵ��ַ��������������ַ����ʹ������ַ���
int * KMP(char * searchedstr,char * findstr)
{
    //this function receive two string which fist is be searched and second is search;
    //And it will return a type of int data when found data, else return NULL
    //build a space to memory data which from receiver
    char string[4096]={'\0'};
    char find[1024]={'\0'};
    //copy data form receiver and calculate length of data
    strcpy(string,searchedstr);
    strcpy(find,findstr);
    int stringlen=strlen(string);
    int findlen=strlen(find);
    //build some variable to control running
    int i=0,j=0,k=0;;
    int get=0,counter=0;
    //build a data space which type of static to return data
    static int space[100]={0};
    //start run compare find data from string
    //only need cycle the times of string length minus find length
    while(i<=stringlen-findlen)
    {
      j=0;
      //until the time when a char from string and first of a char from find equal to compare them, else jump over
     if(string[i]==find[j])
     {

       while(find[j]!='\0')
       {
           if(string[i]==find[0])
            k=j;
           if(string[i]!=find[j])
           {
                i+=k;
                k=0;
                break;
           }
           else
           {
              i++;
           }
           if(find[j+1]=='\0')
           {
             get=1;
             space[counter]=i-2;
             counter++;
             break;
           }

           j++;
       }
     }
     else
     {
       i++;
     }

    }
//if exist equal string,it will return some data of the space about find text, else return NULL show not found
    if(get==1)
    {
    return space;
    }
    else
        return NULL;

}

//it will return the Date(0)/Time(1)/week(2) of present locale time(mode)
int PresentDATE(int mode)
{
	time_t PresentTime;
	PresentTime=time(NULL);
	struct tm * PresentDate;
	PresentDate=localtime(&PresentTime);
	int pdate,ptime;
    pdate=(PresentDate->tm_year+1900)*10000+(PresentDate->tm_mon+1)*100+PresentDate->tm_mday;
    ptime=(PresentDate->tm_hour)*10000+(PresentDate->tm_min)*100+PresentDate->tm_sec;
    if(mode==0)
	return pdate;
	else
	if(mode==1)
	return ptime;
	else
	if(mode==2)
	return PresentDate->tm_wday;
	else
	return -1;
}
//------------------------------------------------------------------------------------------------------
#endif
