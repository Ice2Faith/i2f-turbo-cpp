#ifndef _GLIGHTING_H_
#define _GLIGHTING_H_
#include"GData.h"
typedef struct
{
	double red;
	double green;
	double blue;
}D3Color;
typedef struct
{
	//漫反射光
	double diff_red;
	double diff_green;
	double diff_blue;
	//镜面反射光
	double spec_red;
	double spec_green;
	double spec_blue;
	//环境光
	double ambi_red;
	double ambi_green;
	double ambi_blue;
	//高光指数
	double heig_n;
}D3Material;
typedef struct
{
	double ambi_red;
	double ambi_green;
	double ambi_blue;
}D3Ambient;
typedef struct
{
	double diff_red;
	double diff_green;
	double diff_blue;

	double spec_red;
	double spec_green;
	double spec_blue;

	//衰减因子
	double c0;
	double c1;
	double c2;

	GD3Point point;
}D3Light;
class GD3Light
{
public:
	static D3Color Light(D3Light light, GD3Point point, GD3Point viewPoint, GD3NormalLine normal, D3Material mate, D3Ambient amb);
	static D3Material GetGoldMaterial();
	static D3Material GetSilverMaterial();
	static D3Material GetRedGemstoneMaterial();
	static D3Material GetGreenGemstoneMaterial();
};

#endif // _GLIGHTING_H_