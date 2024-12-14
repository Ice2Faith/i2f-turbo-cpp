#include"Matrix.h"
void FreeMatrixSpace(LPMatrix mt)
{
	if (mt->data != NULL)
	{
		for (int i = 0; i<mt->row; i++)
		{
			if (mt->data[i] != NULL)
				free(mt->data[i]);
		}
		free(mt->data);
		mt->data = NULL;
	}
	mt->row = 0;
	mt->col = 0;
}
void DeleteMatrix(LPMatrix* mt)
{
	FreeMatrixSpace(*mt);
	*mt = NULL;
}
void MakeMatrixSpace(LPMatrix mt, int row, int col)
{
	FreeMatrixSpace(mt);
	mt->row = row;
	mt->col = col;
	mt->data = (DataType **)malloc(sizeof(DataType*)*(mt->row));
	for (int i = 0; i<mt->row; i++)
	{
		mt->data[i] = (DataType*)malloc(sizeof(DataType)*(mt->col));
	}
}
LPMatrix CreateMatrix(int row, int col)
{
	LPMatrix mt = (LPMatrix)malloc(sizeof(Matrix));
	mt->data = NULL;
	MakeMatrixSpace(mt, row, col);
	return mt;
}
LPMatrix MatrixMul(LPMatrix mt1, LPMatrix mt2)
{
	if (mt1->col != mt2->row)
	{
		return NULL;
	}
	LPMatrix result = CreateMatrix(mt1->row, mt2->col);
	for (int i = 0; i < mt1->row; i++)
	{
		for (int j = 0; j < mt2->col; j++)
		{
			result->data[i][j] = 0;
			for (int k = 0; k < mt1->col; k++)
			{
				result->data[i][j] += mt1->data[i][k] * mt2->data[k][j];
			}
		}
	}
	return result;
}
LPMatrix MatrixMul(double number, LPMatrix mt)
{
	LPMatrix ret = CreateMatrix(mt->row, mt->col);
	for (int i = 0; i < mt->row; i++)
	{
		for (int j = 0; j < mt->col; j++)
		{
			ret->data[i][j] = number*mt->data[i][j];
		}
	}
	return ret;
}
LPMatrix MatrixAdd(LPMatrix mt1, LPMatrix mt2)
{
	if (mt1->row != mt2->row || mt1->col != mt2->col)
		return NULL;
	LPMatrix ret = CreateMatrix(mt1->row, mt1->col);
	for (int i = 0; i < mt1->row; i++)
	{
		for (int j = 0; j < mt1->col; j++)
		{
			ret->data[i][j] = mt1->data[i][j] + mt2->data[i][j];
		}
	}
	return ret;
}
LPMatrix MatrixSub(LPMatrix mt1, LPMatrix mt2)
{
	if (mt1->row != mt2->row || mt1->col != mt2->col)
		return NULL;
	LPMatrix ret = CreateMatrix(mt1->row, mt1->col);
	for (int i = 0; i < mt1->row; i++)
	{
		for (int j = 0; j < mt1->col; j++)
		{
			ret->data[i][j] = mt1->data[i][j] - mt2->data[i][j];
		}
	}
	return ret;
}
LPMatrix MatrixTransposed(LPMatrix mt)
{
	Matrix * ret = CreateMatrix(mt->col,mt->row);
	for (int i = 0; i < mt->row; i++)
	{
		for (int j = 0; j < mt->col; j++)
		{
			ret->data[j][i] = mt->data[i][j];
		}
	}
	return ret;
}
LPMatrix CopyMatrix(LPMatrix mt)
{
	LPMatrix ret = CreateMatrix(mt->row, mt->col);
	for (int i = 0; i < mt->row; i++)
	{
		for (int j = 0; j < mt->col; j++)
		{
			ret->data[i][j] = mt->data[i][j];
		}
	}
	return ret;
}
void MatrixForEach(LPMatrix mt, void(*procElemntFunc)(DataType * data))
{
	for (int i = 0; i < mt->row; i++)
	{
		for (int j = 0; j < mt->col; j++)
		{
			procElemntFunc(&(mt->data[i][j]));
		}
	}
}
void MatrixForEachEx(LPMatrix mt, void(*procElemntFunc)(DataType * date), void(*procRowEndFunc)(), void(*procRowBegin)())
{
	for (int i = 0; i < mt->row; i++)
	{
		if (procRowBegin)
			procRowBegin();
		for (int j = 0; j < mt->col; j++)
		{
			procElemntFunc(&(mt->data[i][j]));
		}
		if (procRowEndFunc)
			procRowEndFunc();
	}
}