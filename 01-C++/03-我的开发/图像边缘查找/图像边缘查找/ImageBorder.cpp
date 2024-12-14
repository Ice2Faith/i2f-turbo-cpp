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
		printf("正在处理图片...\n");
		IMAGE img;
		loadimage(&img, argv[1]);
		SetWorkingImage(&img);
		GraphFindBorder(img.getheight(), img.getwidth(), allowRate,usebdcolor, bdcolor & 0xffffff,usebgcolor, bgcolor & 0xffffff);
		SetWorkingImage(NULL);
		saveimage(argv[2], &img);
		printf("图片处理完毕，已经保存.(%s)\n",argv[2]);
	}
	else
	{
		printf("图像边缘查找--使用案例--请使用控制台运行\n\
--------------Dev:Ugex.Savelar-------------\n\
参数说明：\n\
源文件名 目标文件名 容错率=0.01 使用边缘色=1 边缘色=000000 使用背景色=1 背景色=ffffff\n\
带有默认参数的可以缺省\n\
示例：\n\
people.png people_border.png 0.03 1 000000 1 ffff00\n\
含义：容错率0.03，边缘色黑色，背景色蓝绿色\n\n\
people.png people_border.png 0.02 0\n\
含义：容错率0.02，使用图片本身的颜色描边，背景默认为白色\n\n\
people.png people_border.png 0.02 1 0000ff 0\n\
含义：容错率0.02，边缘色为纯红色，背景使用图片自身背景\n\n\
people.png people_border.png 0.03\n\
含义：容错率0.03，默认边缘黑色，默认背景白色\n\n\
颜色说明：蓝绿红 例如: 0000ff 标识 纯红色\n\
使用边缘色说明：如果值不为0则使用，否则不使用\n\n\
复杂图片或颜色相差不大，容错率建议提高到0.08-0.3\n\
一般图片，容错率可以在0.01-0.08之间尝试，一般采用0.03-0.05\n\
如果是书本的照片，容错率在0.04-0.08之间比较合适，采用默认边缘背景色会有不错的效果\n\
如果是纯色无渐变色或颜色反差明显的，容错率直接给0很合适\n");
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