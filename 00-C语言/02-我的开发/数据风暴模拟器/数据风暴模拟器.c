//������ֻ�����
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

	//������ָ�������ַ�һ��ʱ��
	int k = 1;
	int c = 0;
	int timenum;
	int mn = 0;
	srand((unsigned)time(NULL));
	puts("��ѡ��ģʽ��\n\t1.ʮ����\n\t2.�˽���\n\t3.ʮ������\n\t4.������\n\t5.������ʽ\n\t0.���ģʽ:\n");
	fflush(stdin);
	char jk = getchar();
	if (jk == '0')
	{
		srand((unsigned)time(NULL));
		mn = rand() % 5 + 1;
		char *puttxts[] = { "", "ʮ����", "�˽���", "ʮ������", "������","������ʽ" };
		printf("���ģʽ : -> %s\n\n", puttxts[mn]);
	}
	char sixteen[] = { "0123456789ABCDEF" };
	puts("��ϣ����������룿������:\n");
	fflush(stdin);
	scanf("%d", &timenum);
	fflush(stdin);
	puts("�Ƿ������ܵ��٣������� 1 ���������򲻿���\n");
	char kp = getchar();
	fflush(stdin);
	printf("\n��ѡ�������ɫ��������Ĭ�ϵ�ǰ��ɫ��\n\t1.���װ���\n\t2.�ڵװ���\n\t3.�ڵ׺���\n\t4.�̵׻���\n\n");
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
	system("title ���ݷ籩ģ���� By: Ice2Feathers");
	system("color f5");
	//�˴����������������ݣ����100��
	char headtxt[100][100] =
	{
		"\n----------------------------------------\n",
		"\n\t ���ݷ籩ģ���� \n",
		"\n\t By: Ice2Feathers \n",
		"\n\t β�͸�����ԣ� ����ɮ��\n",
		"\n\t ���֣�           ����  \n",
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
	//�˴����������������ݣ����100��
	char endtxt[100][100] =
	{
		"\n\n----------------------------------------\n",
		"\n\n\t������ֻ�����!!!\n",
		"\n\tThanks for your used!!!\n",
		"\n\t By: Ice2Feathers \n",
		"\n\n��ʣ�\n",
		"\n\t�е�����Ե����\n",
		"\n\t�����ܻ����\n",
		"\n\t����ȴ꼻�һ��\n",
		"\n\t���˺����Ķ�\n",
		"\n\t��̤����ͷ�����\n",
		"\n\t�������Ī��ǰ��\n",
		"\n\tһ��Ц�˼����\n",
		"\n\tһϦҹ��������\n",
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