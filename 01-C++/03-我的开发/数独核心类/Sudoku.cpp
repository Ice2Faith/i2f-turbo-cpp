#include"Sudoku.h"
Sudoku::Sudoku()
{
	srand((unsigned int)time(NULL));
	this->Lines = 9;
	this->Cols = 9;
	this->BlockLines = 3;
	this->BlockCols = 3;
	this->Map = (int*)malloc(sizeof(int)*this->Lines*this->Cols);
	this->Mask = (bool*)malloc(sizeof(bool)*this->Lines*this->Cols);
	this->TipsCount = 17 + rand() % 10;
	CleanMap();
	CreateTipsNum();
	CreateMask();
}

Sudoku::~Sudoku()
{
	free(this->Map);
	free(this->Mask);
}
void Sudoku::clear()
{
	CleanMap();
	this->TipsCount = 17 + rand() % 10;
	CreateTipsNum();
	CreateMask();
}
void Sudoku::CreateMask()
{
	for (int i = 0; i < this->Lines; i++)
	{
		for (int j = 0; j < this->Cols; j++)
		{
			if (this->Map[(i)*(this->Cols) + (j)] != 0)
				this->Mask[(i)*(this->Cols) + (j)] = true;
			else
				this->Mask[(i)*(this->Cols) + (j)] = false;
		}
	}
}
void Sudoku::CleanMap()
{
	for (int i = 0; i < this->Lines; i++)
	{
		for (int j = 0; j < this->Cols; j++)
		{
			this->Map[(i)*(this->Cols)+(j)]=0;
		}
	}
}
int Sudoku::GetSumCount()
{
	return this->Lines*this->Cols;
}
int Sudoku::GetEmptyCount()
{
	int tcount = 0;
	for (int i = 0; i < this->Lines; i++)
	{
		for (int j = 0; j < this->Cols; j++)
		{
			if (this->Map[(i)*(this->Cols) + (j)] == 0)
				tcount++;
		}
	}
	return tcount;
}
int Sudoku::GetTipsCount()
{
	return this->TipsCount;
}
bool Sudoku::SetMapAtValue(int rindex, int cindex, int number)
{
	if (rindex<0 || cindex<0 || rindex>this->Lines - 1 || cindex>this->Cols - 1)
		return false;
	if (number<1 || number>9)
		return false;
	if (this->Mask[rindex*(this->Cols) + cindex] == true)
		return false;
	this->Map[rindex*(this->Cols) + cindex] = number;
	if (!LineColsOnly(rindex, cindex))
	{
		this->Map[rindex*(this->Cols) + cindex] = 0;
		return false;
	}
	return true;
}
bool Sudoku::MaskAt(int rindex, int cindex)
{
	if (rindex<0 || cindex<0 || rindex>this->Lines - 1 || cindex>this->Cols - 1)
		return true;
	return this->Mask[rindex*(this->Cols) + cindex];
}
int Sudoku::GetSuccessCount()
{
	int tcount = 0;
	for (int i = 0; i < this->Lines; i++)
	{
		for (int j = 0; j < this->Cols; j++)
		{
			if (this->Map[(i)*(this->Cols) + (j)] != 0)
				tcount++;
		}
	}
	return tcount;
}
void Sudoku::CreateTipsNum()
{
	for (int i = 0; i < this->TipsCount; i++)
	{
		int rindex = rand() % this->Lines;
		int cindex = rand() % this->Cols;
		if (this->Map[(rindex)*(this->Cols) + (cindex)]==0)
		{
			this->Map[(rindex)*(this->Cols) + (cindex)] = rand() % 9 + 1;
			if (!LineColsOnly(rindex, cindex))
			{
				this->Map[(rindex)*(this->Cols) + (cindex)] = 0;
				i--;
			}
		}
		else
		{
			i--;
		}
	}
}
bool Sudoku::LineColsOnly(int rindex, int cindex)
{
	bool lineonly = true;
	bool colonly = true;
	bool blockonly = true;
	int existValue[10] = { 0 };
	///////////////////////////Line
	for (int i = 0; i < 10; i++)
	{
		existValue[i] = 0;
	}
	for (int i = 0; i < this->Lines; i++)
	{
		if (this->Map[(i)*(this->Cols) + (cindex)]>0)
		{
			existValue[this->Map[(i)*(this->Cols) + (cindex)]] += 1;
		}
	}
	for (int i = 1; i < 10; i++)
	{
		if (existValue[i]>1)
			colonly = false;
	}
	//////////////////////////Cols
	for (int i = 0; i < 10; i++)
	{
		existValue[i] = 0;
	}
	for (int j = 0; j < this->Cols; j++)
	{
		if (this->Map[(rindex)*(this->Cols) + (j)]>0)
		{
			existValue[this->Map[(rindex)*(this->Cols) + (j)]] += 1;
		}
	}
	for (int i = 1; i < 10; i++)
	{
		if (existValue[i]>1)
			lineonly = false;
	}

	//////////////////////////////Block
	int bline = rindex / 3;
	int bcol = cindex / 3;
	for (int i = 0; i < 10; i++)
	{
		existValue[i] = 0;
	}

	for (int i = bline*3; i < bline*3 + 3; i++)
	{
		for (int j = bcol*3; j < bcol*3 + 3; j++)
		{
			if (this->Map[(i)*(this->Cols) + (j)]>0)
			{
				existValue[this->Map[(i)*(this->Cols) + (j)]] += 1;
			}
		}
	}

	for (int i = 1; i < 10; i++)
	{
		if (existValue[i]>1)
			blockonly = false;
	}
	return lineonly&&colonly&&blockonly;
}
int Sudoku::MapAt(int rindex, int cindex)
{
	if (rindex<0 || cindex<0 || rindex>this->Lines - 1 || cindex>this->Cols - 1)
	{
		int a = -1;
		return a;
	}
	return this->Map[rindex*(this->Cols) + cindex];;
}
int Sudoku::GetLine()
{
	return this->Lines;
}
int Sudoku::GetCol()
{
	return this->Cols;
}
int Sudoku::GetBlockLine()
{
	return this->BlockLines;
}
int Sudoku::GetBlockCol()
{
	return this->BlockCols;
}