#include"StdAfx.h"
#include"GLighting.h"
D3Color GD3Light::Light(D3Light light, GD3Point point, GD3Point viewPoint, GD3NormalLine normal, D3Material mate, D3Ambient amb)
{
	D3Color retC = { 0 };
	GD3Vector lightVec(point, light.point);
	double distance = lightVec.GetModuleLength();
	lightVec.Untization();
	GD3NormalLine normalVec = normal;
	normalVec.Untization();
	double cosLightNormal = lightVec.CosRadian(normal);
	if (cosLightNormal<0)
		cosLightNormal = 0;
	//加入漫反射光
	retC.red += light.diff_red*mate.diff_red*cosLightNormal;
	retC.green += light.diff_green*mate.diff_green*cosLightNormal;
	retC.blue += light.diff_blue*mate.diff_blue*cosLightNormal;
	//加入镜面反射光
	GD3Vector viewVec(point, viewPoint);
	viewVec.Untization();
	GD3Vector halfVec;
	halfVec = lightVec + viewVec;
	halfVec.Untization();

	double cosHalfNormal = halfVec.CosRadian(normalVec);
	if (cosHalfNormal<0)
		cosHalfNormal = 0;
	retC.red += light.spec_red*mate.spec_red*pow(cosHalfNormal, mate.heig_n);
	retC.green += light.spec_green*mate.spec_green*pow(cosHalfNormal, mate.heig_n);
	retC.blue += light.spec_blue*mate.spec_blue*pow(cosHalfNormal, mate.heig_n);

	//光强衰弱
	double func = (1.0 / (light.c0 + light.c1*distance + light.c2*distance*distance));
	if (func>1.0)
		func = 1.0;
	retC.red *= func;
	retC.green *= func;
	retC.blue *= func;
	//加入环境光
	retC.red += amb.ambi_red*mate.ambi_red;
	retC.green += amb.ambi_green*mate.ambi_green;
	retC.blue += amb.ambi_blue*mate.ambi_blue;
	//颜色归一
	GD3Vector tp(retC.red,retC.green,retC.blue);
	tp.Untization();
	//颜色映射
	retC.red = tp.x*256;
	retC.green = tp.y*256;
	retC.blue = tp.z*256;
	return retC;
}
D3Material GD3Light::GetGoldMaterial()
{
	D3Material mate = { 0 };
	mate.diff_red = 0.752;
	mate.diff_green = 0.606;
	mate.diff_blue = 0.226;
	mate.spec_red = 0.628;
	mate.spec_green = 0.556;
	mate.spec_blue = 0.366;
	mate.ambi_red = 0.247;
	mate.ambi_green = 0.200;
	mate.ambi_blue = 0.075;
	mate.heig_n = 50;
	return mate;
}
D3Material GD3Light::GetSilverMaterial()
{
	D3Material mate = { 0 };
	mate.diff_red = 0.508;
	mate.diff_green = 0.508;
	mate.diff_blue = 0.508;
	mate.spec_red = 0.508;
	mate.spec_green = 0.508;
	mate.spec_blue = 0.508;
	mate.ambi_red = 0.192;
	mate.ambi_green = 0.192;
	mate.ambi_blue = 0.192;
	mate.heig_n = 50;
	return mate;
}
D3Material GD3Light::GetRedGemstoneMaterial()
{
	D3Material mate = { 0 };
	mate.diff_red = 0.614;
	mate.diff_green = 0.041;
	mate.diff_blue = 0.041;
	mate.spec_red = 0.728;
	mate.spec_green = 0.527;
	mate.spec_blue = 0.527;
	mate.ambi_red = 0.175;
	mate.ambi_green = 0.012;
	mate.ambi_blue = 0.012;
	mate.heig_n = 30;
	return mate;
}
D3Material GD3Light::GetGreenGemstoneMaterial()
{
	D3Material mate = { 0 };
	mate.diff_red = 0.076;
	mate.diff_green = 0.614;
	mate.diff_blue = 0.075;
	mate.spec_red = 0.633;
	mate.spec_green = 0.728;
	mate.spec_blue = 0.633;
	mate.ambi_red = 0.022;
	mate.ambi_green = 0.175;
	mate.ambi_blue = 0.023;
	mate.heig_n = 30;
	return mate;
}