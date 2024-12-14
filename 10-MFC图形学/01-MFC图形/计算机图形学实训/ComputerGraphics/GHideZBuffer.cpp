#include"StdAfx.h"
#include"GHideZBuffer.h"
#include<stdlib.h>
#include<math.h>
/*
隐面算法：
对每个面上的所有像素点进行投影到屏幕
选取离视点最近的点作为显示点即可
*/
double GHideZBuffer::D3FlatBlankingAlgorithm(double R, double aAngle, double bAngle, GD3Flat flat)
{
	GD3Vector v1(flat.p1, flat.p2), v2(flat.p2, flat.p3);
	GD3NormalLine nl(v1, v2);
	GD3Point sp;
	sp.ParseSpherical(R, aAngle, bAngle);
	GD3Vector sv(flat.p1, sp);
	return nl.CosRadian(sv);
}



LPZBufferData GHideZBuffer::MakeZBufferData(int width, int height)
{
	LPZBufferData ret = (LPZBufferData)malloc(sizeof(ZBufferData));
	ret->height = height;
	ret->width = width;
	ret->info = (ZBufferItem**)malloc(sizeof(ZBufferItem*)*(ret->height));
	for (int i = 0; i < ret->height; i++)
	{
		ret->info[i] = (ZBufferItem*)malloc(sizeof(ZBufferItem)*(ret->width));
	}
	return ret;
}
void GHideZBuffer::FreeZbufferData(LPZBufferData * data)
{
	if ((*data)->info)
	{
		for (int i = 0; i < (*data)->height; i++)
		{
			free((*data)->info[i]);
		}
		free((*data)->info);
		free((*data));
		*data = NULL;
	}
}
void GHideZBuffer::InitZBufferData(LPZBufferData zdata, double minDeep, COLORREF bgcolor)
{
	for (int i = 0; i < zdata->height; i++)
	for (int j = 0; j < zdata->width; j++)
	{
		zdata->info[i][j].Deep = minDeep;
		zdata->info[i][j].color = bgcolor;
	}
}
void GHideZBuffer::GetD3FlatExpr(GD3Flat flat, double * A, double * B, double * C, double * D)
{
	GD3Vector v1(flat.p1, flat.p2), v2(flat.p2, flat.p3);
	GD3NormalLine nl(v1,v2);
	double pA = nl.x, pB = nl.y, pC = nl.z;
	double pD = -pA*flat.p1.x - pB*flat.p1.y - pC*flat.p1.z;
	*A = pA, *B = pB, *C = pC, *D = pD;
}
GD2Flat GHideZBuffer::ZBD3Flat2D2Falt(GD3Flat flat)
{
	GD2Flat ret;
	ret.p1.x = flat.p1.x;
	ret.p2.x = flat.p2.x;
	ret.p3.x = flat.p3.x;
	ret.p1.y = flat.p1.y;
	ret.p2.y = flat.p2.y;
	ret.p3.y = flat.p3.y;
	return ret;
}
void GHideZBuffer::ZBufferAlgorithm(GD3Flat * flat, COLORREF * color, int flatCount, int width, int height, HDC hdc, COLORREF bgcolor)
{
	LPZBufferData zdata = MakeZBufferData(width, height);
	InitZBufferData(zdata, -5000, bgcolor);
	int i;
	for (int preFlatIndex = 0; preFlatIndex < flatCount; preFlatIndex++)
	{
		double A, B, C, D;
		GetD3FlatExpr(flat[preFlatIndex], &A, &B, &C, &D);
		if (abs(C) < 1e-3)
			continue;
		GD2Flat d2f = ZBD3Flat2D2Falt(flat[preFlatIndex]);
		GD2Point arr[3];
		arr[0] = d2f.p1;
		arr[1] = d2f.p2;
		arr[2] = d2f.p3;
		for (i = 0; i < 3; i++)//按Y值从大到小排列
		{
			int swap = 0;
			for (int j = 0; j < 2; j++)
			{
				if (arr[j].y < arr[j + 1].y)
				{
					GD2Point tp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = tp;
					swap = 1;
				}
			}
			if (swap == 0)
				break;
		}
		//防止计算斜率K为无穷大或为0无法计算
		const double limit = 1e-3;
		int minx = arr[0].x;
		int maxx = arr[0].x;
		for (i = 1; i<3; i++)
		{
			if (arr[i].x<minx)
				minx = arr[i].x;
			if (arr[i].x>maxx)
				maxx = arr[i].x;
		}
		if (abs(maxx - minx)<limit)
		{
			int wid = (int)minx + width / 2;
			if(wid >= 0 && wid < width)//如果计算的坐标宽度不在显示区域，则不计算
			{
				for (double st = arr[2].y; st<arr[1].y; st += 1)
				{
					int hei = (int)st + height / 2;
					if (hei >= 0 && hei < height)//如果计算的高度不在显示区域，则不计算
					{
						double Z = -(A*minx + B*st + D) / C;
						double deep = zdata->info[hei][wid].Deep;
						if (Z>deep)
						{
							zdata->info[hei][wid].Deep = Z;
							zdata->info[hei][wid].color = color[preFlatIndex];
						}
					}
				}
			}
			continue;
		}
		if (abs(arr[0].y - arr[2].y)<limit)
		{
			int hei = (int)arr[0].y + height / 2;
			if (hei >= 0 && hei < height)
			{
				for (double st = minx; st<maxx; st += 1)
				{
					int wid = (int)st + width / 2;
					if (wid >= 0 && wid < width)
					{
						double Z = -(A*st + B*arr[0].y + D) / C;
						double deep = zdata->info[hei][wid].Deep;
						if (Z>deep)
						{
							zdata->info[hei][wid].Deep = Z;
							zdata->info[hei][wid].color = color[preFlatIndex];
						}
					}
				}
			}
			continue;
		}
		//得到三条线的点斜式方程参数K，B
		//最长边，Y最小和Y最大构成
		double k1 = (arr[2].y - arr[0].y) / (arr[2].x - arr[0].x);
		double b1 = arr[2].y - k1*arr[2].x;
		//下短边，Y最小和次小构成
		double k2 = (arr[2].y - arr[1].y) / (arr[2].x - arr[1].x);
		double b2 = arr[2].y - k2*arr[2].x;
		//上短边，Y最大和Y次大构成
		double k3 = (arr[1].y - arr[0].y) / (arr[1].x - arr[0].x);
		double b3 = arr[0].y - k3*arr[0].x;
		//从次大的分割线开始同时对上半部分和下半部分填充

		double ly = arr[1].y, hy = arr[1].y;
		while (1)
		{
			int change = 0;
			if (ly >= arr[2].y)
			{
				int hei = (int)ly + height / 2;
				if(hei >= 0 && hei < height)
				{
					//根据对应Y的值计算交点，算出起点和重点X坐标
					double lxs = (ly - b1) / k1;
					double lxe = (ly - b2) / k2;
					//保证XS起点坐标小于终点XE
					if (lxs>lxe)
					{
						double tp = lxs;
						lxs = lxe;
						lxe = tp;
					}
					if (lxs<minx)
						lxs = minx;
					if (lxe>maxx)
						lxe = maxx;
					while (lxs <= lxe)
					{
						int wid = (int)lxs + width / 2;
						if (wid >= 0 && wid < width)
						{
							double Z = -(A*lxs + B*ly + D) / C;
							double deep = zdata->info[hei][wid].Deep;
							if (Z>deep)
							{
								zdata->info[hei][wid].Deep = Z;
								zdata->info[hei][wid].color = color[preFlatIndex];
							}
						}
						lxs += 1;
					}
				}
				ly -= 1;
				change = 1;
			}

			if (hy < arr[0].y)
			{
				int hei = (int)hy + height / 2;
				if(hei >= 0 && hei < height)
				{
					double hxs = (hy - b1) / k1;
					double hxe = (hy - b3) / k3;
					if (hxs>hxe)
					{
						double tp = hxs;
						hxs = hxe;
						hxe = tp;
					}
					if (hxs<minx)
						hxs = minx;
					if (hxe>maxx)
						hxe = maxx;
					while (hxs <= hxe)
					{
						int wid = (int)hxs + width / 2;
						if (wid >= 0 && wid < width)
						{
							double Z = -(A*hxs + B*hy + D) / C;
							double deep = zdata->info[hei][wid].Deep;
							if (Z>deep)
							{
								zdata->info[hei][wid].Deep = Z;
								zdata->info[hei][wid].color = color[preFlatIndex];
							}
						}
						hxs += 1;
					}
				}
				hy += 1;
				change = 1;
			}
			if (change == 0)
				break;

		}



	}
	for (i = 0; i < zdata->height; i++)
	for (int j = 0; j < zdata->width; j++)
	{
		if(zdata->info[i][j].color==bgcolor) continue;
		SetPixelV(hdc, j - width / 2, i - height / 2, zdata->info[i][j].color);
	}

	FreeZbufferData(&zdata);
}