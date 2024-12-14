#ifndef _D3LIGHT_H_
#define _D3LIGHT_H_
#include"D3Graph.h"
#include<iostream>
using namespace std;
typedef struct
{
	double red;
	double green;
	double blue;
}D3Color;
typedef struct
{
	//�������
	double diff_red;
	double diff_green;
	double diff_blue;
	//���淴���
	double spec_red;
	double spec_green;
	double spec_blue;
	//������
	double ambi_red;
	double ambi_green;
	double ambi_blue;
	//�߹�ָ��
	double heig_n;
}D3Material;
typedef struct
{
	double ambi_red;
	double ambi_green;
	double ambi_blue;
}Ambient;
typedef struct
{
	double diff_red;
	double diff_green;
	double diff_blue;

	double spec_red;
	double spec_green;
	double spec_blue;

	//˥������
	double c0;
	double c1;
	double c2;

	D3Point point;
}D3Light;
void D3NormalLineStandard(D3Vector* vec);
D3Color GraphLight(D3Light light, D3Point point, D3Point viewPoint, D3NormalLine normal, D3Material mate, Ambient amb);
#endif // _D3LIGHT_H_