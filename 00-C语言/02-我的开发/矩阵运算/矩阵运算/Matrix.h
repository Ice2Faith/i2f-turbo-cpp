#ifndef _MATRIX_H_
#define _MATRIX_H_
#include<stdio.h>
#include<stdlib.h>
typedef double DataType;
typedef struct
{
	DataType ** data;
	int row;
	int col;
}Matrix;
typedef Matrix* LPMatrix;
/*
	data数据域保存一个二维数组（矩阵），
	其他两个域row,col保存矩阵大小,不要手动修改，
	请使用MakeMatrixSpace重新分配大小
*/
//创建一个row行col列的矩阵，返回指针，不使用时记得delete
LPMatrix CreateMatrix(int row, int col);
//删除一个矩阵指针指向的结构，并且将mt指向空
void DeleteMatrix(LPMatrix* mt);
//给已有的矩阵结构重新分配数据空间大小，重新设置矩阵大小
void MakeMatrixSpace(LPMatrix mt, int row, int col);
//矩阵乘法，传入矩阵指针，如果能够进行乘法运算，返回结构指针，否则返回空指针
LPMatrix MatrixMul(LPMatrix mt1, LPMatrix mt2);
//数与矩阵相乘
LPMatrix MatrixMul(DataType number, LPMatrix mt);
//矩阵加法，必须是同型矩阵，否则返回空指针
LPMatrix MatrixAdd(LPMatrix mt1, LPMatrix mt2);
//矩阵减法，必须是同型矩阵，否则返回空指针
LPMatrix MatrixSub(LPMatrix mt1, LPMatrix mt2);
//矩阵转置
LPMatrix MatrixTransposed(LPMatrix mt);
//复制矩阵
LPMatrix CopyMatrix(LPMatrix mt);
//矩阵遍历访问修改器，对每个矩阵元素调用procElemntFunc指向的函数（不能为空）
void MatrixForEach(LPMatrix mt, void(*procElemntFunc)(DataType * date));
//矩阵遍历访问修改器增强，对每个矩阵元素调用procElemntFunc指向的函数（不能为空），每行行首、行尾调用procRowEndFunc、procRowBegin（如果他们指向不为空）
void MatrixForEachEx(LPMatrix mt, void(*procElemntFunc)(DataType * date), void(*procRowEndFunc)(),void(*procRowBegin)());
//释放结构中的数据空间，数据指针置空，如果非必要，不建议自行调用
void FreeMatrixSpace(LPMatrix mt);
#endif //_MATRIX_H_