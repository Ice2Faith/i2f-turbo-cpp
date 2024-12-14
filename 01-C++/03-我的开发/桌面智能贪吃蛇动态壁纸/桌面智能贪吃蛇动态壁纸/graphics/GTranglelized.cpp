#include"StdAfx.h"
#include"GTranglelized.h"
void GTeanglelized::SortPointYdesc(GD3DataGroup * dg)
{
	int count = dg->getPointCount();
	for (int i = 0; i < count; i++)
	{
		int max = i;
		for (int j = i; j < count; j++)
		{
			if (dg->pointAt(j).y>dg->pointAt(max).y)
			{
				max = j;
			}
		}
		if (i != max)
		{
			GD3Point tp = dg->pointAt(i);
			dg->pointAt(i) = dg->pointAt(max);
			dg->pointAt(max) = tp;
		}
	}
}
void GTeanglelized::SortDistanceUpper(vector<DTSortStruct> & sdv)
{
	int count = sdv.size();
	int sortCount = count >= 4 ? 4 : count;
	for (int i = 0; i < sortCount; i++)
	{
		
		int min = i;
		for (int j = i; j < count; j++)
		{
			if (sdv[j].distance<sdv[min].distance)
			{
				min = j;
			}
		}
		if (i != min)
		{
			DTSortStruct tp = sdv[i];
			sdv[i] = sdv[min];
			sdv[min] = tp;
		}
	}
}
GD3DataGroup * GTeanglelized::PointsTranglelized(GD3DataGroup * dg)
{
	SortPointYdesc(dg);
	vector<GD3Trangle> trangles;
	int count = dg->getPointCount();
	int i;
	for (i = 0; i < count-1; i++)
	{
		int lowCount = 0;
		vector<DTSortStruct> sdv;
		DTSortStruct self;
		self.distance = -1;
		self.index = i;
		sdv.push_back(self);
		for (int j = i+1; j < count; j++)
		{
			if (dg->pointAt(j).y == dg->pointAt(i).y)
				continue;
			DTSortStruct tps;
			GD3Vector tpv(dg->pointAt(i),dg->pointAt(j));
			tps.distance = tpv.GetModuleLength();
			tps.index = j;
			sdv.push_back(tps);
		}
		SortDistanceUpper(sdv);
		if (sdv.size() >= 4)
		{
			GD3Trangle dt1(sdv[0].index, sdv[1].index, sdv[2].index);
			GD3Trangle dt2(sdv[0].index, sdv[2].index, sdv[3].index);
			GD3Trangle dt3(sdv[0].index, sdv[3].index, sdv[1].index);
			GD3Trangle dt4(sdv[1].index, sdv[2].index, sdv[3].index);
			trangles.push_back(dt1);
			trangles.push_back(dt2);
			trangles.push_back(dt3);
			trangles.push_back(dt4);
		}
		else if (sdv.size() == 3)
		{
			GD3Trangle dt1(sdv[0].index, sdv[1].index, sdv[2].index);
			trangles.push_back(dt1);
		}
		else if (sdv.size() == 2)
		{
			GD3Trangle dt1(sdv[0].index, sdv[1].index, sdv[0].index);
			trangles.push_back(dt1);
		}
		else
		{
			GD3Trangle dt1(sdv[0].index, sdv[0].index, sdv[0].index);
			trangles.push_back(dt1);
		}
	}
	GD3DataGroup * retdg = new GD3DataGroup();
	retdg->allocMemory(count,trangles.size());
	for (i = 0; i < count; i++)
		retdg->pointAt(i) = dg->pointAt(i);
	for (i = 0; i < trangles.size(); i++)
		retdg->trangleAt(i) = trangles[i];
	trangles.clear();
	return retdg;
}