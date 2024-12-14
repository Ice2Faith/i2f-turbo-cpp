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
	data�����򱣴�һ����ά���飨���󣩣�
	����������row,col��������С,��Ҫ�ֶ��޸ģ�
	��ʹ��MakeMatrixSpace���·����С
*/
//����һ��row��col�еľ��󣬷���ָ�룬��ʹ��ʱ�ǵ�delete
LPMatrix CreateMatrix(int row, int col);
//ɾ��һ������ָ��ָ��Ľṹ�����ҽ�mtָ���
void DeleteMatrix(LPMatrix* mt);
//�����еľ���ṹ���·������ݿռ��С���������þ����С
void MakeMatrixSpace(LPMatrix mt, int row, int col);
//����˷����������ָ�룬����ܹ����г˷����㣬���ؽṹָ�룬���򷵻ؿ�ָ��
LPMatrix MatrixMul(LPMatrix mt1, LPMatrix mt2);
//����������
LPMatrix MatrixMul(DataType number, LPMatrix mt);
//����ӷ���������ͬ�;��󣬷��򷵻ؿ�ָ��
LPMatrix MatrixAdd(LPMatrix mt1, LPMatrix mt2);
//���������������ͬ�;��󣬷��򷵻ؿ�ָ��
LPMatrix MatrixSub(LPMatrix mt1, LPMatrix mt2);
//����ת��
LPMatrix MatrixTransposed(LPMatrix mt);
//���ƾ���
LPMatrix CopyMatrix(LPMatrix mt);
//������������޸�������ÿ������Ԫ�ص���procElemntFuncָ��ĺ���������Ϊ�գ�
void MatrixForEach(LPMatrix mt, void(*procElemntFunc)(DataType * date));
//������������޸�����ǿ����ÿ������Ԫ�ص���procElemntFuncָ��ĺ���������Ϊ�գ���ÿ�����ס���β����procRowEndFunc��procRowBegin���������ָ��Ϊ�գ�
void MatrixForEachEx(LPMatrix mt, void(*procElemntFunc)(DataType * date), void(*procRowEndFunc)(),void(*procRowBegin)());
//�ͷŽṹ�е����ݿռ䣬����ָ���ÿգ�����Ǳ�Ҫ�����������е���
void FreeMatrixSpace(LPMatrix mt);
#endif //_MATRIX_H_