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

	head();

	//随机输出指定进制字符一定时间
	int k = 1;
	int c = 0;
	int timenum;
	int mn = 0;
	srand((unsigned)time(NULL));
	puts("请选择模式：\n\t1.十进制\n\t2.八进制\n\t3.十六进制\n\t4.二进制\n\t5.乱码形式\n\t0.随机模式:\n");
	fflush(stdin);
	char jk = getchar();
	if (jk == '0')
	{
		srand((unsigned)time(NULL));
		mn = rand() % 5 + 1;
		char *puttxts[] = { "", "十进制", "八进制", "十六进制", "二进制","乱码形式" };
		printf("随机模式 : -> %s\n\n", puttxts[mn]);
	}
	char sixteen[] = { "0123456789ABCDEF" };
	puts("您希望输出多少秒？请输入:\n");
	fflush(stdin);
	scanf("%d", &timenum);
	fflush(stdin);
	puts("是否开启智能调速？请输入 1 开启，否则不开启\n");
	char kp = getchar();
	fflush(stdin);
	printf("\n请选择界面颜色，不输入默认当前配色：\n\t1.蓝底白字\n\t2.黑底白字\n\t3.黑底红字\n\t4.绿底黄字\n\n");
	char m = getchar();
	if (m == '1')
		system("color 9f");
	else
	if (m == '2')
		system("color 0f");
	else
	if (m == '3')
		system("color 0c");
	else
	if (m == '4')
		system("color 3e");



	system("cls");
	srand((unsigned)time(NULL));
	while (k == 1)
	{

		if (jk == '1' || mn == 1)
			printf("%-2d", rand() % 10);
		else
		if (jk == '2' || mn == 2)
			printf("%-2d", rand() % 8);
		else
		if (jk == '3' || mn == 3)
			printf("%-2c", sixteen[rand() % 16]);
		else
		if (jk == '4' || mn == 4)
			printf("%-2d", rand() % 2);
		else
		if (jk == '5' || mn == 5)
			printf("%-2c", rand() % (128-33)+33);



		if (kp == '1')
		{
			if (timenum >= 600)
			{
				Sleep(0);
				if (c >= timenum * 1000)
					break;
			}

			else
			if (timenum >= 300 && timenum < 600)
			{
				Sleep(1);
				if (c >= timenum * 1000)
					break;
			}

			else
			if (timenum >= 120 && timenum < 300)
			{
				Sleep(2);
				if (c >= timenum * 1000 / 2)
					break;
			}

			else
			if (timenum >= 30 && timenum < 120)
			{
				Sleep(3);
				if (c >= timenum * 1000 / 3)
					break;
			}
			else
			if (timenum >= 0 && timenum < 30)
			{
				Sleep(4);
				if (c >= timenum * 1000 / 4)
					break;
			}

		}
		else
		{
			Sleep(2);
			if (c == timenum * 1000 / 2)
				break;
		}

		c++;

	}
	puts("\n\n");
	end();

}


void head()
{
	system("title 数据风暴模拟器 By: Ice2Feathers");
	system("color f5");
	//此处可任意添加输出内容，最多100行
	char headtxt[100][100] =
	{
		"\n----------------------------------------\n",
		"\n\t 数据风暴模拟器 \n",
		"\n\t By: Ice2Feathers \n",
		"\n\t 尾巴歌词来自： 《酒僧》\n",
		"\n\t 歌手：           李雨  \n",
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
	system("color 9f");

	system("cls");
	//此处可任意添加输出内容，最多100行
	char endtxt[100][100] =
	{
		"\n\n----------------------------------------\n",
		"\n\n\t人生若只如初见!!!\n",
		"\n\tThanks for your used!!!\n",
		"\n\t By: Ice2Feathers \n",
		"\n\n歌词：\n",
		"\n\t有道是姻缘不尽\n",
		"\n\t来世总会相逢\n",
		"\n\t怎奈却昙花一现\n",
		"\n\t叫人好生心动\n",
		"\n\t脚踏黄土头顶清风\n",
		"\n\t不道苦楚莫问前程\n",
		"\n\t一朝笑人间苍生\n",
		"\n\t一夕夜里挑明灯\n",
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