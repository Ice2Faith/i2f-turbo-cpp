#include"stdafx.h"
#include"ZBuffer.h"
LPZBufferData MakeZBufferData(int width, int height)
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
void FreeZbufferData(LPZBufferData * data)
{
	if ((*data)->info)
	{
		for (int i = 0; i < (*data)->height; i++)
		{
			free((*data)->info[i]);
		}
		*data = NULL;
	}
}
void InitZBufferData(LPZBufferData zdata, double minDeep, COLORREF bgcolor)
{
	for (int i = 0; i < zdata->height; i++)
	for (int j = 0; j < zdata->width; j++)
	{
		zdata->info[i][j].Deep = minDeep;
		zdata->info[i][j].color = bgcolor;
	}
}
void GetD3FlatExpr(D3Flat flat, double * A, double * B, double * C, double * D)
{
	D3Vector v1, v2;
	GetD3Vector(flat.p1, flat.p2, &v1);
	GetD3Vector(flat.p2, flat.p3, &v2);
	D3NormalLine nl;
	GetD3NormalLine(v1, v2, &nl);
	double pA = nl.x, pB = nl.y, pC = nl.z;
	double pD = -pA*flat.p1.x - pB*flat.p1.y - pC*flat.p1.z;
	*A = pA, *B = pB, *C = pC, *D = pD;
}
D2Flat ZBD3Flat2D2Falt(D3Flat flat)
{
	D2Flat ret;
	ret.p1.x = flat.p1.x;
	ret.p2.x = flat.p2.x;
	ret.p3.x = flat.p3.x;
	ret.p1.y = flat.p1.y;
	ret.p2.y = flat.p2.y;
	ret.p3.y = flat.p3.y;
	return ret;
}
void ZBufferAlgorithm(D3Flat * flat, COLORREF * color, int flatCount, int width, int height, HDC hdc, COLORREF bgcolor)
{
	LPZBufferData zdata = MakeZBufferData(width, height);
	InitZBufferData(zdata, -5000, bgcolor);
	for (int preFlatIndex = 0; preFlatIndex < flatCount; preFlatIndex++)
	{
		double A, B, C, D;
		GetD3FlatExpr(flat[preFlatIndex], &A, &B, &C, &D);
		if (abs(C) < 1e-1)
			continue;
		D2Flat d2f = ZBD3Flat2D2Falt(flat[preFlatIndex]);
		D2Point arr[3] = { 0 };
		arr[0] = d2f.p1;
		arr[1] = d2f.p2;
		arr[2] = d2f.p3;
		for (int i = 0; i < 3; i++)//按Y值从大到小排列
		{
			int swap = 0;
			for (int j = 0; j < 2; j++)
			{
				if (arr[j].y < arr[j + 1].y)
				{
					D2Point tp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = tp;
					swap = 1;
				}
			}
			if (swap == 0)
				break;
		}
		//防止计算斜率K为无穷大无法计算
		const double limit = 1e-3;
		if (abs(arr[2].x - arr[1].x) < limit)
		{
			arr[1].x += 0.3;
		}
		if (abs(arr[2].x - arr[0].x) < limit)
		{
			arr[0].x += 0.3;
		}
		if (abs(arr[1].x - arr[0].x) < limit)
		{
			arr[0].x += 0.3;
		}
		//得到三条线的点斜式方程参数K，B
		int min = 0;
		int max = 0;
		for (int index = 0; index < 3; index++)
		{
			if (arr[index].y < arr[min].y)
				min = index;
			if (arr[index].y>arr[max].y)
				max = index;
		}

		{
			arr[min].y -= 5;
			arr[max].y += 5;
		}

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

		for (double ly = arr[1].y, hy = arr[1].y; ly >= arr[2].y || hy < arr[0].y; ly -= 1, hy += 1)
		{
			//根据对应Y的值计算交点，算出起点和重点X坐标
			double lxs = (ly - b1) / k1;
			double lxe = (ly - b2) / k2;
			double hxs = (hy - b1) / k1;
			double hxe = (hy - b3) / k3;
			//保证XS起点坐标小于终点XE
			if (lxs>lxe)
			{
				double tp = lxs;
				lxs = lxe;
				lxe = tp;
			}
			if (hxs > hxe)
			{
				double tp = hxs;
				hxs = hxe;
				hxe = tp;
			}
			while (1)
			{
				bool change = 0;
				if (lxs <= lxe)
				{
					double Z = -(A*lxs + B*ly + D) / C;
					int hei = (int)ly + height / 2;
					int wid = (int)lxs + width / 2;
					if (hei >= 0 && hei < height
						&&wid >= 0 && wid < width)
					{
						double deep = zdata->info[hei][wid].Deep;
						if (Z>deep)
						{
							zdata->info[hei][wid].Deep = Z;
							zdata->info[hei][wid].color = color[preFlatIndex];
						}
					}
					lxs += 1;
					change = 1;
				}
				if (hxs <= hxe)
				{
					double Z = -(A*hxs + B*hy + D) / C;
					int hei = (int)hy + height / 2;
					int wid = (int)hxs + width / 2;
					if (hei >= 0 && hei < height
						&&wid >= 0 && wid < width)
					{
						double deep = zdata->info[hei][wid].Deep;
						if (Z>deep)
						{
							zdata->info[hei][wid].Deep = Z;
							zdata->info[hei][wid].color = color[preFlatIndex];
						}
					}
					if (wid == 1023)
						wid = wid;
					hxs += 1;
					change = 1;
				}
				if (change == 0)
					break;

			}

		}



	}
	for (int i = 0; i < zdata->height; i++)
	for (int j = 0; j < zdata->width; j++)
	{
		SetPixelV(hdc, j - width / 2, i - height / 2, zdata->info[i][j].color);
	}

	FreeZbufferData(&zdata);
}