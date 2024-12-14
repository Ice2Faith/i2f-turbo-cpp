#include"StdAfx.h"
#include"GTMFile.h"
#include<stdio.h>

GTMData::GTMData()
{
	this->isLoad = false;
}
GTMData::~GTMData()
{

}
GTMData::GTMData(char * fileName)
{
	loadTMFile(fileName);
}
bool GTMData::loadTMFile(char * fileName)
{
	FILE * tmf = fopen(fileName, "r");
	if (tmf == NULL)
	{
		isLoad = false;
		return false;
	}
	int pointc=0,tranglec=0,temp = 0;
	int i = 0;
	if (3 != fscanf(tmf, "%d %d %d\n", &pointc, &tranglec, &temp))
	{
		fclose(tmf);
		isLoad = false;
		return false;
	}
	this->data.allocMemory(pointc,tranglec);
	for (i = 0; i<this->data.getPointCount(); i++)
	{
		fscanf(tmf, "%lf %lf %lf\n", &this->data.pointAt(i).x, &this->data.pointAt(i).y, &this->data.pointAt(i).z);
	}

	for (i = 0; i<this->data.getTrangleCount(); i++)
	{
		fscanf(tmf, "%d %d %d\n", &this->data.trangleAt(i).p1, &this->data.trangleAt(i).p2, &this->data.trangleAt(i).p3);
	}
	fclose(tmf);
	isLoad = true;
	return true;
}
bool GTMData::saveTMFile(char * fileName)
{
	FILE * tmf = fopen(fileName, "w");
	if (tmf == NULL)
	{
		return false;
	}
	int temp = 0;
	int i = 0;
	fprintf(tmf, "%d %d %d\n", this->data.getPointCount(), this->data.getTrangleCount(), temp);
	for (i = 0; i<this->data.getPointCount(); i++)
	{
		fprintf(tmf, "%lf %lf %lf\n", this->data.pointAt(i).x, this->data.pointAt(i).y, this->data.pointAt(i).z);
	}
	for (i = 0; i<this->data.getTrangleCount(); i++)
	{
		fprintf(tmf, "%d %d %d\n", this->data.trangleAt(i).p1, this->data.trangleAt(i).p2, this->data.trangleAt(i).p3);
	}
	fclose(tmf);
	return true;
}
bool GTMData::isLoadFile()
{
	return this->isLoad;
}
