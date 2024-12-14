#include"Sweep.h"
#include<iostream>
using namespace std;
Sweep::Sweep(int line, int col)
{
	srand((unsigned int)time(NULL));
	this->Lines = line;
	this->Cols = col;
	int Sum = this->Lines*this->Cols;
	if (Sum < 30)
		this->BoomCount = Sum * 1 / 5;
	else if (Sum < 100)
		this->BoomCount = Sum * 1 / 7;
	else if (Sum < 500)
		this->BoomCount = Sum * 1 / 12;
	else
		this->BoomCount = Sum * 1 / 17;
	if (this->BoomCount == 0)
		this->BoomCount = 1;
	this->Map = (int*)malloc(sizeof(int)*this->Lines*this->Cols);
	this->BufferLen = 0;
	CleanMap();
	CreateBoom();
	BuildBoomNumber();
	BuildMask();
	this->FlagCount = this->BoomCount;
}

Sweep::~Sweep()
{
	free(this->Map);
}
void Sweep::clear()
{
	this->BufferLen = 0;
	CleanMap();
	CreateBoom();
	BuildBoomNumber();
	BuildMask();
	this->FlagCount = this->BoomCount;
}
int Sweep::GetScore()
{
	int Score = 0;
	for (int i = 0; i < this->Lines; i++)
	{
		for (int j = 0; j < this->Cols; j++)
		{
			if (this->Map[i*this->Cols + j] == 299)
				Score++;
		}
	}
	return Score;
}
int Sweep::GetBoomCount()
{
	return this->BoomCount;
}
int Sweep::GetFlagCount()
{
	return this->FlagCount;
}
void Sweep::DisplayAllBoom()
{
	for (int i = 0; i < this->Lines; i++)
	{
		for (int j = 0; j < this->Cols; j++)
		{
			if (this->Map[i*this->Cols + j] == 99)
				this->Map[i*this->Cols + j] -= 100;
			if (this->Map[i*this->Cols + j] == 199)
				this->Map[i*this->Cols + j] = 299;
		}
	}
}
void Sweep::DisplayNerVecant(int rindex, int cindex)
{
	this->BufferLen = 1;
	int tp = 0;
	this->Buffer[tp].line = rindex;
	this->Buffer[tp].col = cindex;
	while (1)
	{
		if ((BufferLen + 1) % 1024 != tp && this->Map[(this->Buffer[tp].line)*(this->Cols) + (this->Buffer[tp].col)] == 100 && \
			this->Buffer[tp].line - 1 >= 0 && this->Buffer[tp].col >= 0 && this->Buffer[tp].line - 1 <this->Lines && this->Buffer[tp].col <this->Cols &&\
			this->Map[(this->Buffer[tp].line - 1)*(this->Cols) + (this->Buffer[tp].col)] >= 100 && \
			this->Map[(this->Buffer[tp].line - 1)*(this->Cols) + (this->Buffer[tp].col)] < 110)
		{
			this->Buffer[this->BufferLen].line = this->Buffer[tp].line - 1;
			this->Buffer[this->BufferLen].col = this->Buffer[tp].col;
			this->BufferLen++;
		}
		if ((BufferLen + 1) % 1024 != tp && this->Map[(this->Buffer[tp].line)*(this->Cols) + (this->Buffer[tp].col)] == 100 && \
			this->Buffer[tp].line + 1 >= 0 && this->Buffer[tp].col >= 0 && this->Buffer[tp].line + 1 <this->Lines && this->Buffer[tp].col <this->Cols &&\
			this->Map[(this->Buffer[tp].line + 1)*(this->Cols) + (this->Buffer[tp].col)] >= 100&&\
			this->Map[(this->Buffer[tp].line + 1)*(this->Cols) + (this->Buffer[tp].col)] <110)
		{
			this->Buffer[this->BufferLen].line = this->Buffer[tp].line + 1;
			this->Buffer[this->BufferLen].col = this->Buffer[tp].col;
			this->BufferLen++;
		}
		if ((BufferLen + 1) % 1024 != tp && this->Map[(this->Buffer[tp].line)*(this->Cols) + (this->Buffer[tp].col)] == 100 && \
			this->Buffer[tp].line >= 0 && this->Buffer[tp].col - 1 >= 0 && this->Buffer[tp].line <this->Lines && this->Buffer[tp].col - 1 <this->Cols &&\
			this->Map[(this->Buffer[tp].line)*(this->Cols) + (this->Buffer[tp].col - 1)] >= 100&&\
			this->Map[(this->Buffer[tp].line)*(this->Cols) + (this->Buffer[tp].col - 1)] <110)
		{
			this->Buffer[this->BufferLen].line = this->Buffer[tp].line;
			this->Buffer[this->BufferLen].col = this->Buffer[tp].col - 1;
			this->BufferLen++;
		}
		if ((BufferLen + 1) % 1024 != tp && this->Map[(this->Buffer[tp].line)*(this->Cols) + (this->Buffer[tp].col)] == 100 && \
			this->Buffer[tp].line >= 0 && this->Buffer[tp].col + 1 >= 0 && this->Buffer[tp].line <this->Lines && this->Buffer[tp].col + 1 <this->Cols &&\
			this->Map[(this->Buffer[tp].line)*(this->Cols) + (this->Buffer[tp].col + 1)] >= 100&&\
			this->Map[(this->Buffer[tp].line)*(this->Cols) + (this->Buffer[tp].col + 1)] <110)
		{
			this->Buffer[this->BufferLen].line = this->Buffer[tp].line;
			this->Buffer[this->BufferLen].col = this->Buffer[tp].col + 1;
			this->BufferLen++;
		}
		if (this->Map[(this->Buffer[tp].line)*(this->Cols) + (this->Buffer[tp].col)] >= 100)
			this->Map[(this->Buffer[tp].line)*(this->Cols) + (this->Buffer[tp].col)] -= 100;
		tp = (tp + 1) % 1024;
		if (tp == BufferLen)
			break;
	}
}
bool Sweep::Click(int rindex, int cindex, bool flag)
{
	if (rindex < 0 || cindex < 0 || rindex >= this->Lines || cindex >= this->Cols)
		return true;
	if (flag == false)
	{
		if (this->Map[rindex*this->Cols + cindex] == 99)
		{
			DisplayAllBoom();
			return false;
		}

		if (this->Map[rindex*this->Cols + cindex]>100 && this->Map[rindex*this->Cols + cindex] < 109)
		{
			this->Map[rindex*this->Cols + cindex] -= 100;
			return true;
		}
			
		if (this->Map[rindex*this->Cols + cindex] == 100)
		{
			DisplayNerVecant(rindex, cindex);
			return true;
		}
	}
	else
	{
		if (this->FlagCount>0 && this->Map[rindex*this->Cols + cindex] > 90 && this->Map[rindex*this->Cols + cindex] < 110)
		{
			this->Map[rindex*this->Cols + cindex] += 100;
			this->FlagCount--;
		}
		else if (this->FlagCount<this->BoomCount && this->Map[rindex*this->Cols + cindex] > 190 && this->Map[rindex*this->Cols + cindex] < 210)
		{
			this->Map[rindex*this->Cols + cindex] -= 100;
			this->FlagCount++;
		}
		if (this->FlagCount == 0)
		{
			if (AllKilled())
				return false;
		}
		
		return true;
	}

}
bool Sweep::AllKilled()
{
	int beflag = 0;
	for (int i = 0; i < this->Lines; i++)
	{
		for (int j = 0; j < this->Cols; j++)
		{
			if (this->Map[i*this->Cols + j] == 199)
				beflag++;
		}
	}
	if (beflag == this->BoomCount)
	{
		for (int i = 0; i < this->Lines; i++)
		{
			for (int j = 0; j < this->Cols; j++)
			{
				if (this->Map[i*this->Cols + j] == 199)
					this->Map[i*this->Cols + j] += 100;
			}
		}
		return true;
	}
	return false;
}
void Sweep::BuildBoomNumber()
{
	for (int i = 0; i < this->Lines; i++)
	{
		for (int j = 0; j < this->Cols; j++)
		{
			if (this->Map[i*this->Cols + j] == 0)
			{
				int num = 0;
				for (int m = i-1; m < i + 2; m++)
				{
					for (int n = j-1; n < j + 2; n++)
					{
						if (m >= 0 && n >= 0 && m < this->Lines&&n < this->Cols)
						{
							if (this->Map[m*this->Cols + n] == -1)
								num++;
						}
						
					}
				}
				this->Map[i*this->Cols + j] = num;
			}
		}
	}
}
ELEM_TYPE Sweep::GetElemType(int elem)
{
	if (elem == 299)
		return ELEM_FLAG_BOOM;
	if (elem > 90&&elem<110)
		return ELEM_MASK;
	if (elem == 0)
		return ELEM_NULL;
	if (elem == -1)
		return ELEM_BOOM;
	if (elem > 0 && elem < 9)
		return ELEM_NUMBER;
	if (elem>190 && elem < 210)
		return ELEM_FLAG_MASK;

}
void Sweep::BuildMask()
{
	for (int i = 0; i < this->Lines; i++)
	{
		for (int j = 0; j < this->Cols; j++)
		{
			this->Map[i*this->Cols + j] += 100;
		}
	}
}
void Sweep::CleanMap()
{
	for (int i = 0; i < this->Lines; i++)
	{
		for (int j = 0; j < this->Cols; j++)
		{
			this->Map[i*this->Cols + j] = 0;
		}
	}
}
void Sweep::CreateBoom()
{
	for (int i = 0; i < this->BoomCount; i++)
	{
		int bx = 0, by = 0;
		bx = rand() % this->Lines;
		by = rand() % this->Cols;
		while (this->Map[bx*this->Cols + by] != 0)
		{
			bx = rand() % this->Lines;
			by = rand() % this->Cols;
		}
		this->Map[bx*this->Cols + by] = -1;
	}
}
int & Sweep::MapAt(int rindex, int cindex)
{
	if (rindex < 0 || cindex < 0 || rindex >= this->Lines || cindex >= this->Cols)
	{
		int a = -1;
		return a;
	}
	return this->Map[rindex*this->Cols+cindex];
}
int Sweep::GetLines()
{
	return this->Lines;
}
int Sweep::GetCols()
{
	return this->Cols;
}