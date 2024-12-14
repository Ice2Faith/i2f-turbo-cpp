#include"stdafx.h"
#include"Game2048.h"
Game2048::Game2048(int line,int col)
{
	this->lines = line;
	this->cols = col;
    this->step=0;
    this->core=0;
    this->runtime=0;
    this->usetime=0;
    this->maxnum=2;
    this->Map=(int *)malloc(sizeof(int)*(this->lines)*(this->cols));
	runtime = time(NULL);     //��¼��ʼʱ�䣬��������ʱ��
	srand((unsigned)time(NULL));
	for (int i = 0; i<this->lines; i++)
	{
		for (int j = 0; j<this->cols; j++)
		{
			Map[i*this->cols+j] = 0;
		}
	}
	CreateNew();
}
Game2048::~Game2048()
{
	free(this->Map);
}
void Game2048::clear()
{
	this->step = 0;
	this->core = 0;
	this->runtime = 0;
	this->usetime = 0;
	this->maxnum = 2;
	runtime = time(NULL);     //��¼��ʼʱ�䣬��������ʱ��
	srand((unsigned)time(NULL));
	for (int i = 0; i<this->lines; i++)
	{
		for (int j = 0; j<this->cols; j++)
		{
			Map[i*this->cols + j] = 0;
		}
	}
	CreateNew();
}
bool Game2048::Run(MoveDirect mov)
{
	CreateNew();
	MoveAndResult(mov);
	if (step > (lines*cols * 2))
	if (IsDead() == 1)
		return false;
	usetime = time(NULL) - runtime;
	return true;
}
int Game2048::GetCols()
{
	return this->cols;
}
int Game2048::GetLines()
{
	return this->lines;
}
int Game2048::MapAt(int rindex, int cindex)
{
	if (rindex<0||cindex<0||rindex >= this->lines || cindex >= this->cols)
		return -1;
	return Map[rindex*this->cols+cindex];
}
int Game2048::GetStep()
{
	return this->step;
}
int Game2048::GetScore()
{
	return this->core;
}
int Game2048::GetUsedTime()
{
	return this->usetime;
}
int Game2048::GetMaxNum()
{
	return this->maxnum;
}
void Game2048::CreateNew()
{
	int hasfull = 1;
	for (int i = 0; i<lines; i++)
	{
		for (int j = 0; j<cols; j++)
		{
			if (Map[i*this->cols+j] == 0)
				hasfull = 0;      //�ж��Ƿ����ˣ������Ŵ���
		}
	}
	if (hasfull == 1)
		return;
	int si, sj;
	si = rand() % lines;
	sj = rand() % cols;
	while (Map[si*this->cols+sj] != 0)
	{
		si = rand() % lines;
		sj = rand() % cols;
	}
	Map[si*this->cols+sj] = 2;
}
bool Game2048::IsDead()
{
	for (int i = 0; i<lines; i++)
	{
		for (int j = 0; j<cols; j++)
		{
			if (Map[i*this->lines + j] == 0)
				return false;       //������ڿյĸ���϶�������
			int up, down, right, left;
			up = i - 1;
			down = i + 1;
			right = j + 1;
			left = j - 1;       //�ĸ���������ж�
			while (up >= 0 && Map[up*this->lines + j] == 0)
				up--;
			if (Map[up*this->lines + j] == Map[i*this->lines + j] && up != -1)       //ֻҪһ��������Ժϲ��򲻽���
				return false;
			while (down<lines&&Map[down*this->lines + j] == 0)
				down--;
			if (Map[down*this->lines + j] == Map[i*this->lines + j] && down != lines)
				return false;
			while (right<cols&&Map[i*this->lines + right] == 0)
				right++;
			if (Map[i*this->lines + right] == Map[i*this->lines + j] && right != cols)
				return false;
			while (left >= 0 && Map[i*this->lines + left] == 0)
				left--;
			if (Map[i*this->lines + left] == Map[i*this->lines + j] && left != -1)
				return false;
		}
	}
	return true;       //�ų�����������������϶�������
}
void Game2048::MoveAndResult(MoveDirect mov)
{
	if (mov == MOV_NULL)
		return;
	step++;     //��������
	int ffind, nfind;
	if (mov == MOV_UP)
	{
		for (int i = 0; i<cols; i++)
		{
			ffind = -1;
			nfind = -1;
			for (int j = 0; j < this->lines; j++)
			{
				int k = j;
				while (k <this->lines && Map[k*this->cols + i] == 0)
					k++;
				if (k != this->lines)
					ffind = k;
				k++;
				while (k <this->lines && Map[k*this->cols + i] == 0)
					k++;
				if (k != this->lines)
					nfind = k;
				if (ffind != this->lines && nfind != this->lines)
				{
					if (ffind != nfind)
					{
						if (Map[ffind*this->cols + i] == Map[nfind*this->cols + i])
						{
							Map[ffind*this->cols + i] *= 2;
							if (Map[ffind*this->cols + i]>maxnum)
								maxnum = Map[ffind*this->cols + i];
							Map[nfind*this->cols + i] = 0;
							core++;
						}
					}
				}

			}
			int count = 0;
			for (int j = 0; j < this->lines; j++)
			{
				if (Map[j*this->cols + i] != 0)
				{
					int temp = Map[j*this->cols + i];
					Map[j*this->cols + i] = 0;
					Map[count*this->cols + i] = temp;
					count++;
				}

			}
		}

		//for (int i = 0; i<cols; i++)
		//{
		//	ffind = -1;
		//	nfind = -1;
		//	for (int j = 0; j<lines; j++)
		//	{
		//		int k = j;
		//		while (k<lines&&Map[k*this->cols+i] == 0)
		//			k++;
		//		if (k != lines)
		//			ffind = k;
		//		k++;
		//		while (k<lines&&Map[k*this->lines + i] == 0)
		//			k++;
		//		if (k != lines)
		//			nfind = k;     //��ȡ��һ����Ϊ�����һ����Ϊ��
		//		if (ffind != -1 && nfind != -1)
		//		{
		//			if (ffind != nfind)
		//			{
		//				if (Map[ffind*this->lines + i] == Map[nfind*this->lines + i])        //������ȡ��������
		//				{
		//					Map[ffind*this->lines + i] *= 2;
		//					if (Map[ffind*this->lines + i]>maxnum)
		//						maxnum = Map[ffind*this->lines + i];
		//					Map[nfind*this->lines + i] = 0;
		//					core++;         //��������
		//				}
		//			}
		//		}

		//	}
		//	int count = 0;
		//	for (int j = 0; j<lines; j++)      //���߶���
		//	{
		//		if (Map[j*this->lines + i] != 0)
		//		{
		//			int temp = Map[j*this->lines + i];
		//			Map[j*this->lines + i] = 0;
		//			Map[count*this->lines + i] = temp;
		//			count++;
		//		}

		//	}

		//}
	}
	else if (mov == MOV_DOWN)
	{
		for (int i = 0; i<cols; i++)
		{
			ffind = -1;
			nfind = -1;
			for (int j = lines; j >= 0; j--)
			{
				int k = j;
				while (k >= 0 && Map[k*this->cols+i] == 0)
					k--;
				if (k != -1)
					ffind = k;
				k--;
				while (k >= 0 && Map[k*this->cols+i] == 0)
					k--;
				if (k != -1)
					nfind = k;
				if (ffind != -1 && nfind != -1)
				{
					if (ffind != nfind)
					{
						if (Map[ffind*this->cols+i] == Map[nfind*this->cols+i])
						{
							Map[ffind*this->cols+i] *= 2;
							if (Map[ffind*this->cols+i]>maxnum)
								maxnum = Map[ffind*this->cols+i];
							Map[nfind*this->cols+i] = 0;
							core++;
						}
					}
				}

			}
			int count = lines - 1;
			for (int j = lines - 1; j >= 0; j--)
			{
				if (Map[j*this->cols+i] != 0)
				{
					int temp = Map[j*this->cols+i];
					Map[j*this->cols+i] = 0;
					Map[count*this->cols+i] = temp;
					count--;
				}

			}
		}
	}
	else if (mov == MOV_LEFT)
	{
		for (int i = 0; i<lines; i++)
		{
			ffind = -1;
			nfind = -1;
			for (int j = 0; j<cols; j++)
			{
				int k = j;
				while (k<cols&&Map[i*this->cols+k] == 0)
					k++;
				if (k != cols)
					ffind = k;
				k++;
				while (k<cols&&Map[i*this->cols+k] == 0)
					k++;
				if (k != cols)
					nfind = k;
				if (ffind != -1 && nfind != -1)
				{
					if (ffind != nfind)
					{
						if (Map[i*this->cols+ffind] == Map[i*this->cols+nfind])
						{
							Map[i*this->cols+ffind] *= 2;
							if (Map[i*this->cols+ffind]>maxnum)
								maxnum = Map[i*this->cols+ffind];
							Map[i*this->cols+nfind] = 0;
							core++;
						}
					}
				}

			}
			int count = 0;
			for (int j = 0; j<cols; j++)
			{
				if (Map[i*this->cols+j] != 0)
				{
					int temp = Map[i*this->cols+j];
					Map[i*this->cols+j] = 0;
					Map[i*this->cols+count] = temp;
					count++;
				}

			}
		}
	}
	else if (mov == MOV_RIGHT)
	{
		for (int i = 0; i<lines; i++)
		{
			ffind = -1;
			nfind = -1;
			for (int j = cols; j >= 0; j--)
			{
				int k = j;
				while (k >= 0 && Map[i*this->cols+k] == 0)
					k--;
				if (k != -1)
					ffind = k;
				k--;
				while (k >= 0 && Map[i*this->cols+k] == 0)
					k--;
				if (k != -1)
					nfind = k;
				if (ffind != -1 && nfind != -1)
				{
					if (ffind != nfind)
					{
						if (Map[i*this->cols+ffind] == Map[i*this->cols+nfind])
						{
							Map[i*this->cols+ffind] *= 2;
							if (Map[i*this->cols+ffind]>maxnum)
								maxnum = Map[i*this->cols+ffind];
							Map[i*this->cols+nfind] = 0;
							core++;
						}
					}
				}

			}
			int count = cols - 1;
			for (int j = cols - 1; j >= 0; j--)
			{
				if (Map[i*this->cols+j] != 0)
				{
					int temp = Map[i*this->cols+j];
					Map[i*this->cols+j] = 0;
					Map[i*this->cols+count] = temp;
					count--;
				}

			}
		}
	}
}