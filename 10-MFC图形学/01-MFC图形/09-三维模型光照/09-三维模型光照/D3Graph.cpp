#include"stdafx.h"
#include"D3Graph.h"
#include<math.h>
#include<Windows.h>
double AngleToRadian(double a)
{
	return ((int)a % 360) + (a - (int)a) / 180 * MATH_PI;
}
double RadianToAngle(double a)
{
	double ret = a / MATH_PI * 180;
	return (int)ret%360+(ret-(int)ret);
}
D3Point MakeD3Point(double x, double y, double z)
{
	D3Point p;
	p.x = x;
	p.y = y;
	p.z = z;
	return p;
}
D2Point MakeD2Point(double x, double y)
{
	D2Point p;
	p.x = x;
	p.y = y;
	return p;
}
D2Line MakeD2Line(D2Point p1, D2Point p2)
{
	D2Line l;
	l.p1 = p1;
	l.p2 = p2;
	return l;
}
D3Line MakeD3Line(D3Point p1, D3Point p2)
{
	D3Line l;
	l.p1 = p1;
	l.p2 = p2;
	return l;
}
D3Flat MakeD3Flat(D3Point p1, D3Point p2, D3Point p3)
{
	D3Flat f;
	f.p1 = p1;
	f.p2 = p2;
	f.p3 = p3;
	return f;
}
D2Flat MakeD2Flat(D2Point p1, D2Point p2, D2Point p3)
{
	D2Flat f;
	f.p1 = p1;
	f.p2 = p2;
	f.p3 = p3;
	return f;
}
void D3PointToArray(D3Point p, double arr[])
{
	arr[0] = p.x;
	arr[1] = p.y;
	arr[2] = p.z;
}
void D3FlatToArray(D3Flat f, D3Point arr[])
{
	arr[0] = f.p1;
	arr[1] = f.p2;
	arr[2] = f.p3;
}
D3Point ArrayToD3Point(double arr[])
{
	D3Point p;
	p.x = arr[0];
	p.y = arr[1];
	p.z = arr[2];
	return p;
}
D3Flat ArrayToD3Flat(D3Point arr[])
{
	D3Flat f;
	f.p1 = arr[0];
	f.p2 = arr[1];
	f.p3 = arr[2];
	return f;
}
void GetD3Vector(D3Point p1, D3Point p2, D3Vector * vec)
{
	vec->x = p2.x - p1.x;
	vec->y = p2.y - p1.y;
	vec->z = p2.z - p1.z;
}
double GetD3VectorRadian(D3Vector v1, D3Vector v2)
{
	return  GetD3VectorPointMul(v1, v2) / (GetD3VectorModulus(v1)*GetD3VectorModulus(v2));
}
double GetD3VectorPointMul(D3Vector v1, D3Vector v2)
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}
double GetD3VectorModulus(D3Vector v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}
void D3SphericalToCartesianCoordinates(double R, double aAngle, double bAngle, D3Point * point)
{
	point->x = R*sin(aAngle)*sin(bAngle);
	point->y = R*cos(aAngle);
	point->z = R*sin(aAngle)*cos(bAngle);
}
void GetViewVector(D3Point p, double R, double aAngle, double bAngle, D3Vector * v)
{
	D3Point vp = { 0 };
	D3SphericalToCartesianCoordinates(R, aAngle, bAngle, &vp);
	GetD3Vector(p, vp, v);
}
void GetD3NormalLine(D3Vector v1, D3Vector v2, D3NormalLine * nl)
{
	nl->x = v2.z*v1.y - v2.y*v1.z;
	nl->y = v2.x*v1.z - v2.z*v1.x;
	nl->z = v2.y*v1.x - v2.x*v1.y;
}
//三角形填充算法
void FillScanLine(D2Flat flat, COLORREF fillcolor, HDC hdc)
{
	D2Point arr[3] = { flat.p1, flat.p2, flat.p3 };
	for (int i = 0; i<3; i++)//按Y值从大到小排列
	{
		int swap = 0;
		for (int j = 0; j<2; j++)
		{
			if (arr[j].y<arr[j + 1].y)
			{
				D2Point tp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tp;
				swap = 1;
			}
		}
		if (swap == 0)
			break;
	}
	//防止计算斜率K为无穷大无法计算
	const double limit = 1e-3;
	if (abs(arr[2].x - arr[1].x)< limit)
	{
		arr[1].x += 0.3;
	}
	if (abs(arr[2].x - arr[0].x)< limit)
	{
		arr[0].x += 0.3;
	}
	if (abs(arr[1].x - arr[0].x)< limit)
	{
		arr[0].x += 0.3;
	}
	//得到三条线的点斜式方程参数K，B
	//最长边，Y最小和Y最大构成
	double k1 = (arr[2].y - arr[0].y) / (arr[2].x - arr[0].x);
	double b1 = arr[2].y - k1*arr[2].x;
	//下短边，Y最小和次小构成
	double k2 = (arr[2].y - arr[1].y) / (arr[2].x - arr[1].x);
	double b2 = arr[2].y - k2*arr[2].x;
	//上短边，Y最大和Y次大构成
	double k3 = (arr[1].y - arr[0].y) / (arr[1].x - arr[0].x);
	double b3 = arr[0].y - k3*arr[0].x;
	//从次大的分割线开始同时对上半部分和下半部分填充
	for (double ly = arr[1].y, hy = arr[1].y; ly >= arr[2].y || hy < arr[0].y; ly -= 1, hy += 1)
	{
		//根据对应Y的值计算交点，算出起点和重点X坐标
		double lxs = (ly - b1) / k1;
		double lxe = (ly - b2) / k2;
		double hxs = (hy - b1) / k1;
		double hxe = (hy - b3) / k3;
		//保证XS起点坐标小于终点XE
		if (lxs>lxe)
		{
			double tp = lxs;
			lxs = lxe;
			lxe = tp;
		}
		if (hxs>hxe)
		{
			double tp = hxs;
			hxs = hxe;
			hxe = tp;
		}
		while (1)
		{
			bool change = 0;
			if (lxs <= lxe)
			{
				SetPixelV(hdc, (int)lxs, (int)ly, fillcolor);
				lxs += 1;
				change = 1;
			}
			if (hxs <= hxe)
			{
				SetPixelV(hdc, (int)hxs, (int)hy, fillcolor);
				hxs += 1;
				change = 1;
			}
			if (change == 0)
				break;

		}

	}

}
/*
隐面算法：
对每个面上的所有像素点进行投影到屏幕
选取离视点最近的点作为显示点即可
*/
double D3FlatBlankingAlgorithm(double R, double aAngle, double bAngle, D3Flat flat)
{
	D3Vector v1 = { 0 }, v2 = { 0 };
	GetD3Vector(flat.p1, flat.p2, &v1);
	GetD3Vector(flat.p2, flat.p3, &v2);
	D3NormalLine nl = { 0 };
	GetD3NormalLine(v1, v2, &nl);
	D3Vector sv = { 0 };
	GetViewVector(flat.p1, R, aAngle, bAngle, &sv);
	return GetD3VectorRadian(nl, sv);
}
void GraphMulVaryMatrix(D3Point * p, double matrix[][4])
{
	double PointVector[4] = { p->x, p->y, p->z, 1.0 };
	double ResultVector[4] = {0};
	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ResultVector[j] += PointVector[i] * matrix[i][j];
		}
		
	}
	for (int i = 0; i < 4; i++)//点向量变换前后，都要把向量的第四维度置为1
	{
		ResultVector[i] /= ResultVector[3];
	}
	p->x = ResultVector[0];
	p->y = ResultVector[1];
	p->z = ResultVector[2];
}
void GraphMove(D3Point * p, double mx, double my, double mz)
{
#if defined NOT_USE_MATRIX_VARY
	p->x += mx;
	p->y += my;
	p->z += mz;
#else
	double matrix[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { mx, my, mz, 1 } };
	GraphMulVaryMatrix(p, matrix);
#endif
}
void GraphScale(D3Point * p, double sx, double sy, double sz)
{
#if defined NOT_USE_MATRIX_VARY
	p->x *= sx;
	p->y *= sy;
	p->z *= sz;
#else
	double matrix[4][4] = { { sx, 0, 0, 0 }, { 0, sy, 0, 0 }, { 0, 0, sz, 0 }, { 0, 0, 0, 1 } };
	GraphMulVaryMatrix(p, matrix);
#endif 
}
void GraphSpin(D3Point * p, double sx, double sy, double sz)
{
#if defined NOT_USE_MATRIX_VARY
	p->y = p->y*cos(sx) - p->z*sin(sx);
	p->z = p->y*sin(sx) + p->z*cos(sx);

	p->x = p->z*sin(sy) + p->x*cos(sy);
	p->z = p->z*cos(sy) - p->x*sin(sy);

	p->x = p->x*cos(sz) - p->y*sin(sz);
	p->y = p->x*sin(sz) + p->y*cos(sz);
#else
	double matrixX[4][4] = { { 1, 0, 0, 0 }, { 0, cos(sx), sin(sx), 0 }, { 0, -sin(sx), cos(sx), 0 }, { 0, 0, 0, 1 } };
	GraphMulVaryMatrix(p, matrixX);
	double matrixY[4][4] = { { cos(sy), 0, -sin(sy), 0 }, { 0, 1, 0, 0 }, { sin(sy), 0, cos(sy), 0 }, { 0, 0, 0, 1 } };
	GraphMulVaryMatrix(p, matrixY);
	double matrixZ[4][4] = { { cos(sz), sin(sz), 0, 0 }, { -sin(sz), cos(sz), 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
	GraphMulVaryMatrix(p, matrixZ);
#endif

}
void GraphReflact(D3Point * p, bool bx, bool by, bool bz)
{
#if defined NOT_USE_MATRIX_VARY
	if (bx)
	{
		p->y = -p->y;
		p->z = -p->z;
	}
	if (by)
	{
		p->x = -p->x;
		p->z = -p->z;
	}
	if (bz)
	{
		p->x = -p->x;
		p->y = -p->y;
	}
#else
	if (bx)
	{
		double matrixX[4][4] = { { 1, 0, 0, 0 }, { 0, -1, 0, 0 }, { 0, 0, -1, 0 }, { 0, 0, 0, 1 } };
		GraphMulVaryMatrix(p, matrixX);
	}
	if (by)
	{
		double matrixY[4][4] = { { -1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, -1, 0 }, { 0, 0, 0, 1 } };
		GraphMulVaryMatrix(p, matrixY);
	}
	if (bz)
	{
		double matrixZ[4][4] = { { -1, 0, 0, 0 }, { 0, -1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
		GraphMulVaryMatrix(p, matrixZ);
	}
#endif
}
void GraphFlatReflact(D3Point * p, bool bxoy, bool byoz, bool bxoz)
{
#if defined NOT_USE_MATRIX_VARY
	if (bxoy)
	{
		p->z = -p->z;
	}
	if (byoz)
	{
		p->x = -p->x;
	}
	if (bxoz)
	{
		p->y = -p->y;
	}
#else
	if (bxoy)
	{
		double matrixX[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, -1, 0 }, { 0, 0, 0, 1 } };
		GraphMulVaryMatrix(p, matrixX);
	}
	if (byoz)
	{
		double matrixY[4][4] = { { -1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
		GraphMulVaryMatrix(p, matrixY);
	}
	if (bxoz)
	{
		double matrixZ[4][4] = { { 1, 0, 0, 0 }, { 0, -1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
		GraphMulVaryMatrix(p, matrixZ);
	}
#endif

}
void GraphMiscut(D3Point * p, double xgz, double xdy, double yhz, double ybx, double zfy, double zcx)
{
#if defined NOT_USE_MATRIX_VARY
	p->x = p->x + xdy*p->y + xgz*p->z;
	p->y = ybx*p->x + p->y + p->z*yhz;
	p->z = zcx*p->x + zfy*p->y + p->z;
#else
	double matrixX[4][4] = { { 1, 0, 0, 0 }, { xdy, 1, 0, 0 }, { xgz, 0, 1, 0 }, { 0, 0, 0, 1 } };
	GraphMulVaryMatrix(p, matrixX);
	double matrixY[4][4] = { { 1, ybx, 0, 0 }, { 0, 1, 0, 0 }, { 0, yhz, 1, 0 }, { 0, 0, 0, 1 } };
	GraphMulVaryMatrix(p, matrixY);
	double matrixZ[4][4] = { { 1, 0, zcx, 0 }, { 0, 1, zfy, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
	GraphMulVaryMatrix(p, matrixZ);
#endif

}
void OrgMove(D3Point * p, double mx, double my, double mz)
{
#if defined NOT_USE_MATRIX_VARY
	p->x -= mx;
	p->y -= my;
	p->z -= mz;
#else
	double matrix[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { -mx, -my, -mz, 1 } };
	GraphMulVaryMatrix(p, matrix);
#endif

}
void OrgSpin(D3Point * p, double sx, double sy, double sz)
{
#if defined NOT_USE_MATRIX_VARY
	p->y = p->y*cos(sx) + p->z*sin(sx);
	p->z = p->z*cos(sx) - p->y*sin(sx);

	p->x = p->x*cos(sy) - p->z*sin(sy);
	p->z = p->z*cos(sy) + p->x*sin(sy);

	p->x = p->x*cos(sz) + p->y*sin(sz);
	p->y = p->y*cos(sz) - p->x*sin(sz);
#else
	double matrixX[4][4] = { { 1, 0, 0, 0 }, { 0, cos(sx), -sin(sx), 0 }, { 0, sin(sx), cos(sx), 0 }, { 0, 0, 0, 1 } };
	GraphMulVaryMatrix(p, matrixX);
	double matrixY[4][4] = { { cos(sy), 0, sin(sy), 0 }, { 0, 1, 0, 0 }, { -sin(sy), 0, cos(sy), 0 }, { 0, 0, 0, 1 } };
	GraphMulVaryMatrix(p, matrixY);
	double matrixZ[4][4] = { { cos(sz), -sin(sz), 0, 0 }, { sin(sz), cos(sz), 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
	GraphMulVaryMatrix(p, matrixZ);
#endif

}
void OrgReflact(D3Point * p, bool bx, bool by, bool bz)
{
	GraphReflact(p, bx, by, bz);
}
void OrgFlatReflact(D3Point * p, bool bxoy, bool byoz, bool bxoz)
{
	GraphFlatReflact(p, bxoy, byoz, bxoz);
}
void ProjOrthogonal(D3Point * p)
{
#if defined NOT_USE_MATRIX_VARY
	p->z = 0;
#else
	double matrixX[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 1 } };
	GraphMulVaryMatrix(p, matrixX);
#endif
}
void ProjMainView(D3Point * p)
{
#if defined NOT_USE_MATRIX_VARY
	p->x = 0;
#else
	double matrixX[4][4] = { { 0, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
	GraphMulVaryMatrix(p, matrixX);
#endif

}
void ProjSideView(D3Point * p)
{
#if defined NOT_USE_MATRIX_VARY
	p->y = -p->x;
	p->x = 0;
#else
	double matrixX[4][4] = { { 0, 0, -1, 0 }, { 0, 1, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 1 } };
	GraphMulVaryMatrix(p, matrixX);
#endif

}
void ProjTopView(D3Point * p)
{
#if defined NOT_USE_MATRIX_VARY
	p->z = -p->x;
	p->x = 0;
#else
	double matrixX[4][4] = { { 0, -1, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
	GraphMulVaryMatrix(p, matrixX);
#endif

}
void ProjOblique(D3Point * p, double aAngle, double bAngle)
{
#if defined NOT_USE_MATRIX_VARY
	p->x = p->x - p->z*(1.0 / (tan(aAngle))*cos(bAngle));
	p->y = p->y - p->z*(1.0 / (tan(aAngle))*sin(bAngle));
	p->z = 0;
#else
	double matrixX[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 1.0 / (-tan(aAngle))*cos(bAngle), 1.0 / (-tan(aAngle))*sin(bAngle), 0, 0 }, { 0, 0, 0, 1 } };
	GraphMulVaryMatrix(p, matrixX);
#endif

}
void ProjWorldOrgToViewOrg(D3Point * p, double R, double aAngle, double bAngle)
{
#if defined NOT_USE_MATRIX_VARY
	double k1 = sin(aAngle);
	double k2 = sin(bAngle);
	double k3 = cos(aAngle);
	double k4 = cos(bAngle);
	double k5 = k2*k3, k6 = k2*k1, k7 = k4*k3, k8 = k4*k1;
	D3Point word = *p;
	p->x = word.x*k3 - k1*word.z;
	p->y = k2*word.y - k8*word.x - k7*word.z;
	p->z = R - k6*word.x - k4*word.y - k5*word.z;
#else
	double matrixX[4][4] = { { cos(aAngle), -cos(bAngle)*sin(aAngle), -sin(bAngle)*sin(aAngle), 0 }, { 0, sin(bAngle), -cos(bAngle), 0 }, { -sin(aAngle), -cos(bAngle)*cos(aAngle), -sin(bAngle)*cos(aAngle), 0 }, { 0, 0, R, 1 } };
	GraphMulVaryMatrix(p, matrixX);
#endif

}
void ProjViewOrgToScreenOrg(D3Point * p, double d)
{
#if defined NOT_USE_MATRIX_VARY
	p->x = d*p->x / p->z;
	p->y = d*p->y / p->z;
	p->z = 0;
#else
	double matrixX[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 0, 1.0 / d }, { 0, 0, 0, 0 } };
	GraphMulVaryMatrix(p, matrixX);
#endif

}
void ProjWorldOrgToScreenOrg(D3Point * p, double R, double d, double aAngle, double bAngle)
{
#if defined NOT_USE_MATRIX_VARY
	ProjWorldOrgToViewOrg(p, R, aAngle, bAngle);
	ProjViewOrgToScreenOrg(p, d);
#else
	double matrixX[4][4] = { { cos(aAngle), -cos(bAngle)*sin(aAngle), 0, -sin(bAngle)*sin(aAngle) / d }, { 0, sin(bAngle), 0, -cos(bAngle) / d }, { -sin(aAngle), -cos(bAngle)*cos(aAngle), 0, -sin(bAngle)*cos(aAngle) / d }, { 0, 0, 0, R / d } };
	GraphMulVaryMatrix(p, matrixX);
#endif

}
void ProjOnePoint(D3Point * p, double R, double d)
{
#if defined NOT_USE_MATRIX_VARY
	ProjWorldOrgToViewOrg(p, R, AngleToRadian(0), AngleToRadian(90));
	ProjViewOrgToScreenOrg(p, d);
#else
	double matrixX[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 0, -1.0 / d }, { 0, 0, 0, R / d } };
	GraphMulVaryMatrix(p, matrixX);
#endif

}
void ProjTwoPoint(D3Point * p, double R, double d)
{
#if defined NOT_USE_MATRIX_VARY
	ProjWorldOrgToViewOrg(p, R, AngleToRadian(45), AngleToRadian(90));
	ProjViewOrgToScreenOrg(p, d);
#else
	double sq2 = sqrt(2.0);
	double matrixX[4][4] = { { sq2 / 2, 0, 0, -sq2 / (2 * d) }, { 0, 1, 0, 0 }, { -sq2 / 2, 0, 0, -sq2 / (2 * d) }, { 0, 0, 0, R / d } };
	GraphMulVaryMatrix(p, matrixX);
#endif

}
void ProjThreePoint(D3Point * p, double R, double d)
{
#if defined NOT_USE_MATRIX_VARY
	ProjWorldOrgToViewOrg(p, R, AngleToRadian(45), AngleToRadian(45));
	ProjViewOrgToScreenOrg(p, d);
#else
	double sq2 = sqrt(2.0);
	double matrixX[4][4] = { { sq2 / 2, -1.0 / 2, 0, -1.0 / (2 * d) }, { 0, sq2 / 2, 0, -sq2 / (2 * d) }, { -sq2 / 2, -1.0 / 2, 0, -1.0 / (2 * d) }, { 0, 0, 0, R / d } };
	GraphMulVaryMatrix(p, matrixX);
#endif

}
void ProjViewOrgToDeepScreenD3Org(D3Point * p, double d, double Near, double Far)
{
	double rx = d*(p->x) / (p->z);
	double ry = d*(p->y) / (p->z);
	double rz = Far*(1.0 - Near / (p->z)) / (Far - Near);
	p->x = rx;
	p->y = ry;
	p->z = rz;
}



