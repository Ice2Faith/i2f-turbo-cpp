#include"stdafx.h"
#include"D3Light.h"
void D3NormalLineStandard(D3Vector* vec)
{
	double mod = GetD3VectorModulus(*vec);
	vec->x = vec->x / mod;
	vec->y = vec->y / mod;
	vec->z = vec->z / mod;
}
D3Color GraphLight(D3Light light, D3Point point, D3Point viewPoint, D3NormalLine normal, D3Material mate, Ambient amb)
{
	D3Color retC = { 0 };
	D3Vector lightVec;
	GetD3Vector(point, light.point, &lightVec);
	double distance = GetD3VectorModulus(lightVec);
	D3NormalLineStandard(&lightVec);
	D3Vector normalVec = normal;
	D3NormalLineStandard(&normalVec);
	double cosLightNormal = GetD3VectorRadian(lightVec, normalVec);
	if (cosLightNormal<0)
		cosLightNormal = 0;
	//加入漫反射光
	retC.red += light.diff_red*mate.diff_red*cosLightNormal;
	retC.green += light.diff_green*mate.diff_green*cosLightNormal;
	retC.blue += light.diff_blue*mate.diff_blue*cosLightNormal;
	//加入镜面反射光
	D3Vector viewVec;
	GetD3Vector(point, viewPoint, &viewVec);
	D3NormalLineStandard(&viewVec);
	D3Vector halfVec, tempVec;
	tempVec = lightVec;
	tempVec.x += viewVec.x;
	tempVec.y += viewVec.y;
	tempVec.z += viewVec.z;
	D3NormalLineStandard(&tempVec);
	halfVec = tempVec;

	double cosHalfNormal = GetD3VectorRadian(halfVec, normalVec);
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
	D3NormalLineStandard((D3Vector*)&retC);
	//颜色映射
	retC.red *= 256;
	retC.green *= 256;
	retC.blue *= 256;
	return retC;
}