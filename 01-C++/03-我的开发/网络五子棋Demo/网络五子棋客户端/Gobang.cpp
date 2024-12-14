#include"stdafx.h"
#include"Gobang.h"
Gobang::Gobang(int row, int col) :mRow(row), mCol(col), sortlen(0)
{
	map = (int*)malloc(sizeof(int)*mRow*mCol);
	memset(map, 0, sizeof(int)*mRow*mCol);
}
Gobang::~Gobang()
{
	free(map);
}
int Gobang::GetSizeRow()
{
	return mRow;
}
int Gobang::GetSizeCol()
{
	return mCol;
}
int& Gobang::AtIndex(int rindex, int cindex)
{
	return map[rindex*mRow + cindex];
}
bool Gobang::BlockDown(int color, int rindex, int cindex)
{
	if (color != -1 && color != 1)
		return false;
	if (pkd.color + color == 0 || pkd.row + pkd.col == -2)
	{
		if (rindex < mRow &&rindex >= 0 && cindex < mCol &&cindex >= 0 && AtIndex(rindex, cindex) == 0)
		{
			AtIndex(rindex, cindex) = color;
			pkd.color = color;
			pkd.row = rindex;
			pkd.col = cindex;
			cout << "Space:" << pkd.color << " " << pkd.row << " " << pkd.col << endl;
			DownStack.push(pkd);
			return true;
		}
	}
	else return false;
}
void Gobang::Undo()
{
	if (DownStack.empty())
		return;
	pkd=DownStack.top();
	DownStack.pop();
	AtIndex(pkd.row,pkd.col)=0;
	if (!DownStack.empty())
	pkd = DownStack.top();
}
bool Gobang::IsWin()
{
	if (pkd.color == 0)
		return false;
	winsort[0][0] = pkd.row;
	winsort[0][1] = pkd.col;
	//横向
	sortlen = 1;
	for (int i = 1; i < 5; i++)
	{
		if (pkd.col - i < 0 || AtIndex(pkd.row, pkd.col - i) != pkd.color)
		{
			break;
		}
		if (sortlen < 5)
		{
			winsort[sortlen][0] = pkd.row;
			winsort[sortlen][1] = pkd.col - i;
		}
		sortlen++;
	}
	for (int i = 1; i < 5; i++)
	{
		if (pkd.col + i>mCol - 1 || AtIndex(pkd.row, pkd.col + i) != pkd.color)
		{
			break;
		}
		if (sortlen < 5)
		{
			winsort[sortlen][0] = pkd.row;
			winsort[sortlen][1] = pkd.col + i;
		}
		sortlen++;
	}
	if (sortlen >= 5)
	{
		return true;
	}
	//纵向
	sortlen = 1;
	for (int i = 1; i < 5; i++)
	{
		if (pkd.row - i < 0 || AtIndex(pkd.row - i, pkd.col) != pkd.color)
		{
			break;
		}
		if (sortlen < 5)
		{
			winsort[sortlen][0] = pkd.row - i;
			winsort[sortlen][1] = pkd.col;
		}
		sortlen++;
	}
	for (int i = 1; i < 5; i++)
	{
		if (pkd.row + i>mRow - 1 || AtIndex(pkd.row + i, pkd.col) != pkd.color)
		{
			break;
		}
		if (sortlen < 5)
		{
			winsort[sortlen][0] = pkd.row + i;
			winsort[sortlen][1] = pkd.col;
		}
		sortlen++;
	}
	if (sortlen >= 5)
	{
		return true;
	}
	//右上
	sortlen = 1;
	for (int i = 1; i < 5; i++)
	{
		if (pkd.col + i>mCol - 1 || pkd.row - i < 0 || AtIndex(pkd.row - i, pkd.col + i) != pkd.color)
		{
			break;
		}
		if (sortlen < 5)
		{
			winsort[sortlen][0] = pkd.row - i;
			winsort[sortlen][1] = pkd.col + i;
		}
		sortlen++;
	}
	for (int i = 1; i < 5; i++)
	{
		if (pkd.row + i>mRow - 1 || pkd.col - i < 0 || AtIndex(pkd.row + i, pkd.col - i) != pkd.color)
		{
			break;
		}
		if (sortlen < 5)
		{
			winsort[sortlen][0] = pkd.row + i;
			winsort[sortlen][1] = pkd.col - i;
		}
		sortlen++;
	}
	if (sortlen >= 5)
	{
		return true;
	}
	//左上
	sortlen = 1;
	for (int i = 1; i < 5; i++)
	{
		if (pkd.col - i < 0 || pkd.row - i < 0 || AtIndex(pkd.row - i, pkd.col - i) != pkd.color)
		{
			break;
		}
		if (sortlen < 5)
		{
			winsort[sortlen][0] = pkd.row - i;
			winsort[sortlen][1] = pkd.col - i;
		}
		sortlen++;
	}
	for (int i = 1; i < 5; i++)
	{
		if (pkd.row + i>mRow - 1 || pkd.col + i>mCol - 1 || AtIndex(pkd.row + i, pkd.col + i) != pkd.color)
		{
			break;
		}
		if (sortlen < 5)
		{
			winsort[sortlen][0] = pkd.row + i;
			winsort[sortlen][1] = pkd.col + i;
		}
		sortlen++;
	}
	if (sortlen >= 5)
	{
		return true;
	}

	return false;
}
