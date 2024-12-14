/** Name: RGB万色卡*/
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#define SW_BASE 0
#define SW_LINE 1
#define SW_COL  2
#define SW_FULL 3
typedef int SW_MODE;
void RGBMillionColor(SW_MODE mode)
{
	initgraph(240, 60);
	outtextxy(0, 0, "请稍后");
	IMAGE image(256*16,256*16);
	BeginBatchDraw();
	SetWorkingImage(&image);
	int Rcolor = 0;
	int Gcolor = 0;
	int Bcolor = 0;
	//绘制色块
	for (int lblock = 0; lblock < 16; lblock++)
	{
		for (int cblock = 0; cblock < 16; cblock++)
		{
			for (int Gcolor = 0; Gcolor < 256; Gcolor++)
			{
				for (int Bcolor = 0; Bcolor < 256; Bcolor++)
				{
					putpixel(cblock * 256 + Bcolor, lblock * 256 + Gcolor, RGB(Rcolor,Gcolor,Bcolor));
				}
			}
			Rcolor++;
		}
	}
	int * colors[256 * 16] = { 0 };
	for (int i = 0; i < 256 * 16; i++)
	{
		colors[i] = (int *)malloc(sizeof(int)* 256 * 16);
		for (int j = 0; j < 256 * 16; j++)
		{
			colors[i][j] = getpixel(j,i);
		}
	}
	int tpcolor[256 * 16] = { 0 };
	//横向归并色块
	if (mode & SW_LINE)
	{
		for (int i = 0; i < 256 * 16; i++)
		{
			int space = 0;
			for (int j = 0; j < 256; j++)
			{
				for (int k = 0; k < 16; k++)
				{
					tpcolor[space] = colors[i][j + 256 * k];
					space++;
				}

			}
			for (int j = 0; j < 256 * 16; j++)
			{
				colors[i][j] = tpcolor[j];
			}

		}
	}

	//纵向归并色块
	if (mode & SW_COL)
	{
		for (int i = 0; i < 256 * 16; i++)
		{
			int space = 0;
			for (int j = 0; j < 256; j++)
			{
				for (int k = 0; k < 16; k++)
				{
					tpcolor[space] = colors[j + 256 * k][i];
					space++;
				}

			}

			for (int j = 0; j < 256 * 16; j++)
			{
				colors[j][i] = tpcolor[j];
			}

		}
	}


	
	//保存数据到图片
	for (int i = 0; i < 256 * 16; i++)
	{
		for (int j = 0; j < 256 * 16; j++)
		{
			putpixel(j, i, RGB(colors[i][j] & 0xff, (colors[i][j] >> 8) & 0xff, (colors[i][j] >> 16) & 0xff));
		}
		free(colors[i]);
		colors[i] = 0;
	}
	SetWorkingImage(NULL);
	putimage(0,0,&image);
	EndBatchDraw();
	saveimage("RGBMC.png",&image);
	closegraph();
	system("explorer RGBMC.png");
}

int main(int argc, char * argv[])
{
	printf("\t1.原始色块\n");
	printf("\t2.行分裂块\n");
	printf("\t3.列分裂块\n");
	printf("\t4.细分裂块\n");
	printf("\t0.退出程序\n>/ ");
	char sel = 0;
	while (sel<'0' || sel>'4')
		sel = getch();
	printf("%c\n", sel);
	if (sel == '0')
		exit(0);
	RGBMillionColor((SW_MODE)(sel-1));
	
	return 0;
}