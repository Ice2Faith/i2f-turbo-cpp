//人生若只如初见
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include <math.h>
void main()
{
	void head();
	void end();
	void love();

	head();
	system("pause");

	//正文开始
	love();
	
	end();

}


void head()
{
	system("title I LOVE YOU!!! By: Ice2Feathers");
	system("color f5");
	//此处可任意添加输出内容，最多100行
	char headtxt[100][100] =
	{
		"\n----------------------------------------\n",
		"\n\t I LOVE YOU!!! \n",
		"\n\t By: Ice2Feathers \n",
		"\n----------------------------------------\n"
	};
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

void end()
{
	printf("\n");
	system("pause");
	Sleep(800);
	system("color f5");

	system("cls");
	//此处可任意添加输出内容，最多100行
	char endtxt[100][100] =
	{
		"\n\n----------------------------------------\n",
		"\n\n\t人生若只如初见!!!\n",
		"\n\n\t我爱你！！！\n",
		"\n\n\t真的爱你！！！！\n",
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
	}


	Sleep(3000);

}

void love()
{
	system("color fc");
	system("cls");
float x, y;
int i = 0;
char Love[] = { "I LOVE YOU!" };
char lovevow[50][200] =
{ "Hi! Baby,\n\n",
"\tI \twant \tto \ttell \tyou: \n\n",
"\t\tMy lovely queen!\n\n",
"\tI am belong to you, Ice2Feathers.\n\n",
"\tAre you still remember the frist met each other?\n\n",
"\tAt that time, I feeling is you who can company with me all life.\n\n",
"\tBut I not dare say to you!\n\n",
"\tUntill taday, the moon, kinds of flowers, lots of butterfly...arround me.\n\n",
"\tI think, I want you can promise me.\n\n",
"\tI find I love you when I first met you.\n\n",
"\tI was dipped attract by you, I feeling you like fairy from sky, or most light star in night.\n\n",
"\tI fantasy that time that I and you stay with each other, which together see sunrise and sunset.\n\n",
"\tI even wish play on any Scenic area that have lots of butterfly with you!\n\n",
"\tAnd with you see full flash star in sky lay on meadow where on little summit.\n\n",
"\tI want spend the best time on romantic with you!\n\n",
"\tTogether see rainbow at rain after.\n\n",
"\tTogether go through everything brought happy and trouble.\n\n",
"\tForgive me for not warm myself but still want to be your sun.\n\n",
"\tLove you, don't need a reason.\n\n",
"\tMy heart，the bird of the wilderness，has found its sky in your eyes.\n\n",
"\tSoft-hearted is a disease， but you is life．\n\n",
"\tObviously very like, but not close to.\n\n",
"\tHeard some things， obviously irrelevant， but also in the hearts of several bends shui think of you．\n\n",
"\tAnd so on.\n\n",
"\t...\n\n",
"\t其实我想说：\n\n"
};
int  j;
srand((unsigned)time(NULL));
char colorrun[] = { "14569cd" };
char cmdcolor[20] = { '\0' };
int m, ii, jj = 0;
for (i = 0; i < 2; i++)
{

	j = 0;
	while (lovevow[i][j] != '\0')
	{
		printf("%c", lovevow[i][j]);
		Sleep(100);
		j++;
	}
}
Sleep(1000);
for (x = 1.4; x >= -1.4; x -= 0.1) {
for (y = -2.4; y <= 2.4; y += 0.053) {
if (pow(x*x + y*y - 1, 3) - x*x*x*y*y <= 0)
{

printf("%c", Love[(i++)%11]);
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

int k = 0, counter = 0;
while (lovevow[k][0] != '\0')
{
	counter++;
	k++;
}

for (i = 2; i < counter; i++)
{
	
	j = 0;
	while (lovevow[i][j] != '\0')
	{
		printf("%c", lovevow[i][j]);
		Sleep(20);
		j++;
		
		if (jj%20==0)
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
}
system("color fc");
system("pause");
system("cls");
for (x = 1.4; x >= -1.4; x -= 0.1) {
	for (y = -2.4; y <= 2.4; y += 0.053) {
		if (pow(x*x + y*y - 1, 3) - x*x*x*y*y <= 0)
		{

			printf("%c", Love[(i++) % 11]);
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
char heart[] = { "\n\n\t\t做我女朋友好吗？\n\n\n" };
int gh = 0;
while (heart[gh] != '\0')
{
	printf("%c", heart[gh]);
	Sleep(520);
	gh++;
}

}
