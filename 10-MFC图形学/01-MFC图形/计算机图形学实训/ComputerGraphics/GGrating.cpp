#include"StdAfx.h"
#include"GGrating.h"
#include<deque>
#include<iterator>
double GGrating::Bernstein(int i, int n, double t)
{
	
	double cni=1,tp=1;
	for(int j=1;j<=i;j++)
	{
		if(n-j+1>0)
			cni*=n-j+1;
		tp*=j;
	}
	cni=cni/tp;
	return cni*pow(t,i)*pow(1-t,n-i);
	
	
}
double GGrating::BezierX(int n, double t, GD2Point points[])
{
	double sum = 0;
	for (int i = 0; i<n ; i++)
	{
		sum += points[i].x*Bernstein(i, n-1, t);
	}
	return sum;
}
double GGrating::BezierY(int n, double t, GD2Point points[])
{
	double sum = 0;
	for (int i = 0; i<n; i++)
	{
		sum += points[i].y*Bernstein(i, n-1 , t);
	}
	return sum;
}
void GGrating::BezierLine(HDC hdc, GD2Point points[], int pointCount,COLORREF color)
{
	int tCount = 20000;
	for (int i = 0; i < tCount; i++)
	{
		int x = (int)BezierX(pointCount, 1.0*i / tCount, points);
		int y = (int)BezierY(pointCount, 1.0*i / tCount, points);
		SetPixelV(hdc,x, y, color);
	}
}
GD3DataGroup* GGrating::CreateBezierSpinYCube(GD2Point ctrlPoints[],int ctrlPointCount,int tCount,int rAngleCount)
{
	//Bezier��ת�壨��Y�ᣩ ��������
	GD2Point * points=new GD2Point[tCount];
	int i;
	for (i = 0; i < tCount; i++)
	{
		points[i].x = (int)BezierX(ctrlPointCount, 1.0*i / tCount, ctrlPoints);
		points[i].y = (int)BezierY(ctrlPointCount, 1.0*i / tCount, ctrlPoints);
	}

	GD3DataGroup* data=new GD3DataGroup();
	long pointc= tCount*rAngleCount,tranglec=0;
	data->allocMemory(pointc,tranglec);
	double PI = GTools::MATH_PI;
	//��������
	for (i = 0; i < tCount; i++)
	{
		for (int j = 0; j < rAngleCount; j++)
		{
			data->pointAt(i*rAngleCount + j).x = points[i].x*cos(2 * PI / rAngleCount* j);
			data->pointAt(i*rAngleCount + j).y = points[i].y;
			data->pointAt(i*rAngleCount + j).z = points[i].x*sin(2 * PI / rAngleCount* j);
		}
	}
	delete[] points;
	return data;
}
GD3DataGroup* GGrating::CreateBezierSpinXCube(GD2Point ctrlPoints[],int ctrlPointCount,int tCount,int rAngleCount)
{
	//Bezier��ת�壨��X�ᣩ ��������
	GD2Point * points=new GD2Point[tCount];
	int i;
	for (i = 0; i < tCount; i++)
	{
		points[i].x = (int)BezierX(ctrlPointCount, 1.0*i / tCount, ctrlPoints);
		points[i].y = (int)BezierY(ctrlPointCount, 1.0*i / tCount, ctrlPoints);
	}

	GD3DataGroup* data=new GD3DataGroup();
	long pointc= tCount*rAngleCount,tranglec=0;
	data->allocMemory(pointc,tranglec);
	double PI = GTools::MATH_PI;
	//��������
	for (i = 0; i < tCount; i++)
	{
		for (int j = 0; j < rAngleCount; j++)
		{
			data->pointAt(i*rAngleCount + j).x = points[i].x;
			data->pointAt(i*rAngleCount + j).y = points[i].y*cos(2 * PI / rAngleCount* j);
			data->pointAt(i*rAngleCount + j).z = points[i].y*sin(2 * PI / rAngleCount* j);
		}
	}
	delete[] points;
	return data;
}

//����PolyLine��ת����Y��
GD3DataGroup* GGrating::CreatePolyLineSpinYCube(GD2Point ctrlPoints[], int ctrlPointCount, int tCount, int rAngleCount)
{
	//PolyLine��ת�壨��X�ᣩ ��������
	GD2Point * points = NULL;
	int i, tidx, eidx;
	double tdidx, trate;
	if (tCount <= 0){
		//PolyLine��ת�壨��X�ᣩ ��������
		tCount = ctrlPointCount;
		points = new GD2Point[tCount];
		int i;
		for (i = 0; i < tCount; i++)
		{
			points[i].x = ctrlPoints[i].x;
			points[i].y = ctrlPoints[i].y;
		}
	}
	else{
		//PolyLine��ת�壨��X�ᣩ ��������
		points = new GD2Point[tCount];
		for (i = 0; i < tCount; i++)
		{
			tdidx = (i*1.0 / tCount)*ctrlPointCount;
			tidx = (int)tdidx;
			trate = tdidx - tidx;
			eidx = tidx + 1;
			if (eidx >= ctrlPointCount){
				eidx = tidx;
			}
			points[i].x = ctrlPoints[tidx].x*trate + ctrlPoints[eidx].x*(1.0 - trate);
			points[i].y = ctrlPoints[tidx].y*trate + ctrlPoints[eidx].y*(1.0 - trate);
		}
	}


	GD3DataGroup* data = new GD3DataGroup();
	long pointc = tCount*rAngleCount, tranglec = 0;
	data->allocMemory(pointc, tranglec);
	double PI = GTools::MATH_PI;
	//��������
	for (i = 0; i < tCount; i++)
	{
		for (int j = 0; j < rAngleCount; j++)
		{
			data->pointAt(i*rAngleCount + j).x = points[i].x*cos(2 * PI / rAngleCount* j);
			data->pointAt(i*rAngleCount + j).y = points[i].y;
			data->pointAt(i*rAngleCount + j).z = points[i].x*sin(2 * PI / rAngleCount* j);
		}
	}
	delete[] points;
	return data;
}

//����PolyLine��ת����X��
GD3DataGroup* GGrating::CreatePolyLineSpinXCube(GD2Point ctrlPoints[], int ctrlPointCount, int tCount, int rAngleCount)
{
	//PolyLine��ת�壨��X�ᣩ ��������
	GD2Point * points = NULL;
	int i, tidx, eidx;
	double tdidx, trate;
	if (tCount <= 0){
		//PolyLine��ת�壨��X�ᣩ ��������
		tCount = ctrlPointCount;
		points = new GD2Point[tCount];
		int i;
		for (i = 0; i < tCount; i++)
		{
			points[i].x = ctrlPoints[i].x;
			points[i].y = ctrlPoints[i].y;
		}
	}
	else{
		//PolyLine��ת�壨��X�ᣩ ��������
		points = new GD2Point[tCount];
		for (i = 0; i < tCount; i++)
		{
			tdidx = (i*1.0 / tCount)*ctrlPointCount;
			tidx = (int)tdidx;
			trate = tdidx - tidx;
			eidx = tidx + 1;
			if (eidx >= ctrlPointCount){
				eidx = tidx;
			}
			points[i].x = ctrlPoints[tidx].x*trate + ctrlPoints[eidx].x*(1.0 - trate);
			points[i].y = ctrlPoints[tidx].y*trate + ctrlPoints[eidx].y*(1.0 - trate);
		}
	}


	GD3DataGroup* data = new GD3DataGroup();
	long pointc = tCount*rAngleCount, tranglec = 0;
	data->allocMemory(pointc, tranglec);
	double PI = GTools::MATH_PI;
	//��������
	for (i = 0; i < tCount; i++)
	{
		for (int j = 0; j < rAngleCount; j++)
		{
			data->pointAt(i*rAngleCount + j).x = points[i].x;
			data->pointAt(i*rAngleCount + j).y = points[i].y*cos(2 * PI / rAngleCount* j);
			data->pointAt(i*rAngleCount + j).z = points[i].y*sin(2 * PI / rAngleCount* j);
		}
	}
	delete[] points;
	return data;
}

// DDA��ֵ΢���㷨��ֱ��
void GGrating::DDALine(HDC hdc, GD2Point p1, GD2Point p2, COLORREF color)
{
	double dk = 1.0*(p2.y - p1.y) / (p2.x - p1.x);
	if (dk > 1.0 || dk<-1.0)
	{
		if (p1.y > p2.y)
		{
			GD2Point t;
			t = p1;
			p1 = p2;
			p2 = t;
		}
		double x = p1.x, y = p1.y, k = 1.0;
		k *= 1.0*(p2.x - p1.x) / (p2.y - p1.y);
		while (y < p2.y)
		{
			SetPixelV(hdc,x + 0.5, y, color);
			x += k;
			y += 1;
		}
	}
	else
	{
		if (p1.x > p2.x)
		{
			GD2Point t;
			t = p1;
			p1 = p2;
			p2 = t;
		}
		double x = p1.x, y = p1.y, k = 1.0;
		k *= 1.0*(p2.y - p1.y) / (p2.x - p1.x);
		while (x < p2.x)
		{
			SetPixelV(hdc,x, y + 0.5, color);
			y += k;
			x += 1;
		}
	}

}

// ������ֱ�߻���
void GGrating::AntialiasLine(HDC hdc, GD2Point p1, GD2Point p2, COLORREF fgc, COLORREF bgc)
{
	double dk = 1.0*(p2.y - p1.y) / (p2.x - p1.x);
	if (dk > 1.0 || dk<-1.0)
	{
		if (p1.y > p2.y)
		{
			GD2Point t;
			t = p1;
			p1 = p2;
			p2 = t;
		}
		double x = p1.x, y = p1.y, k = 1.0;
		k *= 1.0*(p2.x - p1.x) / (p2.y - p1.y);
		while (y < p2.y)
		{
			double e = x - (int)(x);
			SetPixelV(hdc,x + 0.5, y, RGB((fgc & 0xff)*e + (bgc & 0xff)*(1 - e), ((fgc >> 8) & 0xff)*e + ((bgc >> 8) & 0xff)*(1 - e), ((fgc >> 16) & 0xff)*e + ((bgc >> 16) & 0xff)*(1 - e)));
			SetPixelV(hdc,x + 0.5 + 1, y, RGB((fgc & 0xff)*(1 - e) + (bgc & 0xff)*e, ((fgc >> 8) & 0xff)*(1 - e) + ((bgc >> 8) & 0xff)*e, ((fgc >> 16) & 0xff)*(1 - e) + ((bgc >> 16) & 0xff)*e));
			x += k;
			y += 1;
		}
	}
	else
	{
		if (p1.x > p2.x)
		{
			GD2Point t;
			t = p1;
			p1 = p2;
			p2 = t;
		}
		double x = p1.x, y = p1.y, k = 1.0;
		k *= 1.0*(p2.y - p1.y) / (p2.x - p1.x);
		while (x < p2.x)
		{
			double e = y - (int)(y);
			SetPixelV(hdc,x, y + 0.5, RGB((fgc & 0xff)*e + (bgc & 0xff)*(1 - e), ((fgc >> 8) & 0xff)*e + ((bgc >> 8) & 0xff)*(1 - e), ((fgc >> 16) & 0xff)*e + ((bgc >> 16) & 0xff)*(1 - e)));
			SetPixelV(hdc,x, y + 0.5 + 1, RGB((fgc & 0xff)*(1 - e) + (bgc & 0xff)*e, ((fgc >> 8) & 0xff)*(1 - e) + ((bgc >> 8) & 0xff)*e, ((fgc >> 16) & 0xff)*(1 - e) + ((bgc >> 16) & 0xff)*e));
			y += k;
			x += 1;
		}
	}


}

//��������㷨
void GGrating::SeedFillAlgorithm(HDC hdc, GD2Point seed, COLORREF bgc, COLORREF flc)
{
	std::deque<GD2Point> que;
	que.push_back(seed);
	SetPixelV(hdc,seed.x,seed.y, flc);
	int directs[4][2] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
	int directSum = 4;
	while (que.size() != 0)
	{
		for (int i = 0; i < directSum; i++)
		{
			GD2Point tp = que.at(0);
			tp.x += directs[i][0];
			tp.y += directs[i][1];
			if (GetPixel(hdc,tp.x,tp.y) == bgc)
			{
				que.push_back(tp);
				SetPixelV(hdc, tp.x, tp.y, flc);
			}
		}
		que.pop_front();
	}
}
//����������㷨
void GGrating::TrangleFillScanLine(GD2Flat flat, COLORREF fillcolor, HDC hdc)
{
	GD2Point arr[3] = { flat.p1, flat.p2, flat.p3 };
	int i,j;
	for (i = 0; i<3; i++)//��Yֵ�Ӵ�С����
	{
		int swap = 0;
		for (j = 0; j<2; j++)
		{
			if (arr[j].y<arr[j + 1].y)
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
	//��ֹ����б��KΪ������Ϊ0�޷�����
	const double limit = 1e-3;
	int minx=arr[0].x;
	int maxx=arr[0].x;
	for(i=1;i<3;i++)
	{
		if(arr[i].x<minx)
			minx=arr[i].x;
		if(arr[i].x>maxx)
			maxx=arr[i].x;
	}
	if(abs(maxx-minx)<limit)
	{
		for(double st=arr[2].y;st<arr[1].y;st+=1)
		{
			SetPixelV(hdc, (int)minx, (int)st, fillcolor);
		}
		return;
	}
	if(abs(arr[0].y-arr[2].y)<limit)
	{
		for(double st=minx;st<maxx;st+=1)
		{
			SetPixelV(hdc, (int)st, (int)arr[0].y, fillcolor);
		}
		return;
	}
	//�õ������ߵĵ�бʽ���̲���K��B
	//��ߣ�Y��С��Y��󹹳�
	double k1 = (arr[2].y - arr[0].y) / (arr[2].x - arr[0].x);
	double b1 = arr[2].y - k1*arr[2].x;
	//�¶̱ߣ�Y��С�ʹ�С����
	double k2 = (arr[2].y - arr[1].y) / (arr[2].x - arr[1].x);
	double b2 = arr[2].y - k2*arr[2].x;
	//�϶̱ߣ�Y����Y�δ󹹳�
	double k3 = (arr[1].y - arr[0].y) / (arr[1].x - arr[0].x);
	double b3 = arr[0].y - k3*arr[0].x;
	//�Ӵδ�ķָ��߿�ʼͬʱ���ϰ벿�ֺ��°벿�����
	double ly = arr[1].y, hy = arr[1].y; 
	while (1)
	{
		int change=0;
		if(ly >= arr[2].y)
		{
			//���ݶ�ӦY��ֵ���㽻�㣬��������ص�X����
			double lxs = (ly - b1) / k1;
			double lxe = (ly - b2) / k2;
			//��֤XS�������С���յ�XE
			if (lxs>lxe)
			{
				double tp = lxs;
				lxs = lxe;
				lxe = tp;
			}
			if(lxs<minx)
				lxs=minx;
			if(lxe>maxx)
				lxe=maxx;
			while (lxs <= lxe)
			{
				SetPixelV(hdc, (int)lxs, (int)ly, fillcolor);
				lxs += 1;
			}
			ly -= 1;
			change=1;
		}
		 
		if(hy < arr[0].y)
		{
			double hxs = (hy - b1) / k1;
			double hxe = (hy - b3) / k3;
			if (hxs>hxe)
			{
				double tp = hxs;
				hxs = hxe;
				hxe = tp;
			}
			if(hxs<minx)
				hxs=minx;
			if(hxe>maxx)
				hxe=maxx;
			while (hxs <= hxe)
			{
				SetPixelV(hdc, (int)hxs, (int)hy, fillcolor);
				hxs += 1;
			}
			hy += 1;
			change=1;
		}
		if(change==0)
			break;

	}

}