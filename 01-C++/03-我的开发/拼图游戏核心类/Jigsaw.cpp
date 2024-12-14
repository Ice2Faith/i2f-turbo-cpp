#include"Jigsaw.h"
Jigsaw::Jigsaw(int line,int col)
{
	srand((unsigned)time(NULL));
	this->step = 0;
	this->Lines = line;
	this->Cols = col;
	this->Map = (int *)malloc(sizeof(int)*this->Lines*this->Cols);
	int k = 0;
	for (int i = 0; i<Lines; i++)
	{
		for (int j = 0; j<Cols; j++)
		{
			Map[i*this->Cols+j] = k++;
		}
	}
	maxblock = this->Lines*this->Cols - 1;
	maxx = this->Lines - 1;
	maxy = this->Cols - 1;
	int mdirec[4] = { 8, 4, 5, 6 };
	int mantidirec[4] = { 5, 6, 8, 4 };
	for (int i = 0; i<4; i++)
	{
		direc[i] = mdirec[i];
		antidirec[i] = mantidirec[i];
	}
	step = 0;
	SetState();

}
void Jigsaw::SetState()
{
	int times = (Lines*Cols)*((rand() % 150 + 50) / 100) + 1;

	queuelen = 0;
	queueinit = (int *)malloc(sizeof(int)*times);

	int randdirec = 0, tp = 0;
	for (int i = 0; i<times; i++)
	{
		tp = rand() % 4;
		while (direc[tp] + direc[randdirec] == 10)
			tp = rand() % 4;
		while (direc[tp] + direc[randdirec] == 13)
			tp = rand() % 4;
		randdirec = tp;
		if (MovePic(direc[randdirec]) == false)
			i--;
		else
		{
			queueinit[queuelen++] = randdirec;
		}
	}
	autoindex = queuelen - 1;
}
bool Jigsaw::AutoRun()
{
	bool ret = Run(antidirec[queueinit[autoindex]]);
	if (autoindex >= 0)
		autoindex--;
	return ret;
}
int Jigsaw::GetWalkLen()
{
	return this->queuelen;
}
int* Jigsaw::GetWalkRoute()
{
	return this->queueinit;
}
int Jigsaw::GetStep()
{
	return this->step;
}
Jigsaw::~Jigsaw()
{
	free(this->Map);
	free(this->queueinit);
}
int Jigsaw::GetMaxBlock()
{
	return this->maxblock;
}
void Jigsaw::clear()
{
	free(this->queueinit);
	this->step = 0;
	this->maxblock = this->Lines*this->Cols - 1;
	this->maxx = 4;
	this->maxy = 4;
	for (int i = 0; i <= this->maxblock; i++)
		this->Map[i] = i;
	int mdirec[4] = { 8, 4, 5, 6 };
	int mantidirec[4] = { 5, 6, 8, 4 };
	for (int i = 0; i<4; i++)
	{
		direc[i] = mdirec[i];
		antidirec[i] = mantidirec[i];
	}
	step = 0;
	SetState();
}
bool Jigsaw::Run(MoveDirect direc)
{
	bool tstep = MovePic(direc);
	if (tstep == true)
		step++;
	if (IsWin())
		return false;
	return true;
}

bool Jigsaw::MovePic(MoveDirect direc)
{
	int temp = 0;
	int mx=0, my=0;
	if (direc == MOV_NULL)
		return true;
	else if (direc == MOV_UP)
	{
		if (maxx - 1 == -1)
			return false;
		mx = maxx - 1;
		my = maxy;

	}
	else if (direc == MOV_DOWN)
	{
		if (maxx + 1 == Lines)
			return false;
		mx = maxx + 1;
		my = maxy;
	}
	else if (direc == MOV_RIGHT)
	{
		if (maxy + 1 == Cols)
			return false;
		mx = maxx;
		my = maxy + 1;
	}
	else if (direc == MOV_LEFT)
	{
		if (maxy - 1 == -1)
			return false;
		mx = maxx;
		my = maxy - 1;
	}
	temp = Map[maxx*this->Cols+maxy];
	Map[maxx*this->Cols+maxy] = Map[mx*this->Cols+my];
	Map[mx*this->Cols+my] = temp;
	maxx = mx;
	maxy = my;
	return true;
}
bool Jigsaw::IsWin()
{
	int k = 0;
	for (int i = 0; i<Lines; i++)
	{
		for (int j = 0; j<Cols; j++)
		{
			if (Map[i*this->Cols+j] != k++)
				return false;
		}
	}
	return true;
}
int Jigsaw::GetCols()
{
	return this->Cols;
}
int Jigsaw::GetLines()
{
	return this->Lines;
}
int Jigsaw::MapAt(int rindex, int cindex)
{
	if (rindex<0 || cindex<0 || rindex >= this->Lines || cindex >= this->Cols)
		return -1;
	return Map[rindex*this->Cols + cindex];
}