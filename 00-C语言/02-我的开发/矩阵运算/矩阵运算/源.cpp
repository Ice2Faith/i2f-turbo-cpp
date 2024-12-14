#include"Matrix.h"
void ProcMatrix(DataType * data)
{
	printf("%.2lf\t",*data);
}
void ProcStartLine()
{
	printf(" | ");
}
void ProcNextLine()
{
	printf(" |\n");
}
int main()
{
	LPMatrix mt1= CreateMatrix(3,2);
	LPMatrix mt2 = CreateMatrix(2,2);
	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<2; j++)
		{
			mt1->data[i][j] = 1;
		}
	}
	for (int i = 0; i<2; i++)
	{
		for (int j = 0; j<2; j++)
		{
			mt2->data[i][j] = 2;
		}
	}
	LPMatrix result = MatrixMul(mt1, mt2);

	MatrixForEachEx(result, &ProcMatrix, &ProcNextLine, &ProcStartLine);
	DeleteMatrix(&mt1);
	DeleteMatrix(&mt2);
	DeleteMatrix(&result);
	if (result == NULL)
		printf("is Deleted\n");
	system("pause");
	return 0;
}