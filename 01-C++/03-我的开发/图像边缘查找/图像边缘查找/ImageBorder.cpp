#include<iostream>
#include<cstdio>
#include<graphics.h>
#include<cstdlib>
#include<Windows.h>
#include<math.h>
#include<string.h>
using namespace std;
void GraphFindBorder(int height, int width, double allowRate, int useBorderColor, COLORREF colorBorder, int useBackColor, COLORREF bgcolor);
int main(int argc, char * argv[])
{
	if (argc >= 3)
	{
		COLORREF bdcolor = 0x000000;
		COLORREF bgcolor = 0xffffff;
		double allowRate = 0.01;
		int usebdcolor = 1;
		int usebgcolor = 1;
		if (argc >= 4)
			sscanf(argv[3], "%lf", &allowRate);
		if (argc >= 5)
			sscanf(argv[4],"%d",&usebdcolor);
		if (argc >= 6)
			sscanf(argv[5], "%x", ((int*)&bdcolor));
		if (argc >= 7)
			sscanf(argv[6], "%d", &usebgcolor);
		if (argc >= 8)
			sscanf(argv[7], "%x", ((int*)&bgcolor));
		printf("���ڴ���ͼƬ...\n");
		IMAGE img;
		loadimage(&img, argv[1]);
		SetWorkingImage(&img);
		GraphFindBorder(img.getheight(), img.getwidth(), allowRate,usebdcolor, bdcolor & 0xffffff,usebgcolor, bgcolor & 0xffffff);
		SetWorkingImage(NULL);
		saveimage(argv[2], &img);
		printf("ͼƬ������ϣ��Ѿ�����.(%s)\n",argv[2]);
	}
	else
	{
		printf("ͼ���Ե����--ʹ�ð���--��ʹ�ÿ���̨����\n\
--------------Dev:Ugex.Savelar-------------\n\
����˵����\n\
Դ�ļ��� Ŀ���ļ��� �ݴ���=0.01 ʹ�ñ�Եɫ=1 ��Եɫ=000000 ʹ�ñ���ɫ=1 ����ɫ=ffffff\n\
����Ĭ�ϲ����Ŀ���ȱʡ\n\
ʾ����\n\
people.png people_border.png 0.03 1 000000 1 ffff00\n\
���壺�ݴ���0.03����Եɫ��ɫ������ɫ����ɫ\n\n\
people.png people_border.png 0.02 0\n\
���壺�ݴ���0.02��ʹ��ͼƬ�������ɫ��ߣ�����Ĭ��Ϊ��ɫ\n\n\
people.png people_border.png 0.02 1 0000ff 0\n\
���壺�ݴ���0.02����ԵɫΪ����ɫ������ʹ��ͼƬ������\n\n\
people.png people_border.png 0.03\n\
���壺�ݴ���0.03��Ĭ�ϱ�Ե��ɫ��Ĭ�ϱ�����ɫ\n\n\
��ɫ˵�������̺� ����: 0000ff ��ʶ ����ɫ\n\
ʹ�ñ�Եɫ˵�������ֵ��Ϊ0��ʹ�ã�����ʹ��\n\n\
����ͼƬ����ɫ�����ݴ��ʽ�����ߵ�0.08-0.3\n\
һ��ͼƬ���ݴ��ʿ�����0.01-0.08֮�䳢�ԣ�һ�����0.03-0.05\n\
������鱾����Ƭ���ݴ�����0.04-0.08֮��ȽϺ��ʣ�����Ĭ�ϱ�Ե����ɫ���в����Ч��\n\
����Ǵ�ɫ�޽���ɫ����ɫ�������Եģ��ݴ���ֱ�Ӹ�0�ܺ���\n");
		system("pause");
	}
	return 0;
}
void GraphFindBorder(int height, int width, double allowRate,int useBorderColor,COLORREF colorBorder,int useBackColor, COLORREF bgcolor)
{
	const double limit = 1e-9;
	if (allowRate <= limit)
		allowRate = 0.0;
	if (allowRate >= 1.0)
		allowRate = 1.0;
	for (int row = 0; row < height; row++)
	{
		COLORREF befcolor = getpixel(0, row);
		for (int col = 1; col < width; col++)
		{
			COLORREF nowcolor = getpixel(col ,row);
			COLORREF downcolor = getpixel(col,row+1);
			if (allowRate < limit)
			{
				if (befcolor != nowcolor || downcolor != nowcolor)
				{
					if (useBorderColor!=0)
					{
						putpixel(col, row, colorBorder);
					}
				}
				else
				{
					if (useBackColor!=0)
					{
						putpixel(col, row, bgcolor);
					}
				}
			}
			else
			{
				BYTE befr = GetRValue(befcolor);
				BYTE befg = GetGValue(befcolor);
				BYTE befb = GetBValue(befcolor);

				BYTE nowr = GetRValue(nowcolor);
				BYTE nowg = GetGValue(nowcolor);
				BYTE nowb = GetBValue(nowcolor);

				BYTE downr = GetRValue(downcolor);
				BYTE downg = GetGValue(downcolor);
				BYTE downb = GetBValue(downcolor);

				double familiarRateBef = 0;
				familiarRateBef = abs((befr - nowr) / 255.0) + abs((befg - nowg) / 255.0) + abs((befb - nowb) / 255.0);
				familiarRateBef /= 3.0;

				double familiarRateDown = 0;
				familiarRateDown = abs((downr - nowr) / 255.0) + abs((downg - nowg) / 255.0) + abs((downb - nowb) / 255.0);
				familiarRateDown /= 3.0;
				
				
				if (familiarRateBef>allowRate || familiarRateDown>allowRate)
				{
					if (useBorderColor != 0)
					{
						putpixel(col, row, colorBorder);
					}
				}
				else
				{
					if (useBackColor != 0)
					{
						putpixel(col, row, bgcolor);
					}
				}
			}
			befcolor = nowcolor;
		}
	}
}