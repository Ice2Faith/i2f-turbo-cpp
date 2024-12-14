#ifndef _GOBANG_H_
#define _GOBANG_H_
#include"Gobang.h"
#include<cstdlib>
#include<windows.h>
#include<stack>
#include<iterator>
#include<iostream>
using namespace std;
class KeyDown
{
public:
	int color;
	int row;
	int col;
	KeyDown(int color=0,int row=-1,int col=-1):color(color),row(row),col(col){}
	KeyDown(const KeyDown& kd)
	{
		this->color = kd.color;
		this->row = kd.row;
		this->col = kd.col;
	}
	KeyDown& operator=(const KeyDown& kd)
	{
		this->color = kd.color;
		this->row = kd.row;
		this->col = kd.col;
		return *this;
	}
};
class Gobang
{
private:
	const int mRow;
	const int mCol;
	int * map;	//1 white,-1 black color also
	int sortlen;
	KeyDown pkd;
	stack<KeyDown> DownStack;
public:
	int winsort[5][2];
	Gobang(int row = 20, int col = 20);
	~Gobang();
	int GetSizeRow();
	int GetSizeCol();
	int& AtIndex(int rindex, int cindex);
	bool BlockDown(int color, int rindex, int cindex);
	bool IsWin();
	void Undo();
};

#endif //_GOBANG_H_