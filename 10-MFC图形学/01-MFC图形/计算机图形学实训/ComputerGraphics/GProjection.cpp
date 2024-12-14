#include"StdAfx.h"
#include"GProjection.h"
void GProj::Orthogonal(GD3Point * p)
{
#if defined NOT_USE_MATRIX_VARY
	p->z = 0;
#else
	double matrixX[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 1 } };
	GTools::GraphMulVaryMatrix(p, matrixX);
#endif
}
void GProj::MainView(GD3Point * p)
{
#if defined NOT_USE_MATRIX_VARY
	p->x = 0;
#else
	double matrixX[4][4] = { { 0, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
	GTools::GraphMulVaryMatrix(p, matrixX);
#endif
}
void GProj::SideView(GD3Point * p)
{
#if defined NOT_USE_MATRIX_VARY
	p->y = -p->x;
	p->x = 0;
#else
	double matrixX[4][4] = { { 0, 0, -1, 0 }, { 0, 1, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 1 } };
	GTools::GraphMulVaryMatrix(p, matrixX);
#endif
}
void GProj::TopView(GD3Point * p)
{
#if defined NOT_USE_MATRIX_VARY
	p->z = -p->x;
	p->x = 0;
#else
	double matrixX[4][4] = { { 0, -1, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
	GTools::GraphMulVaryMatrix(p, matrixX);
#endif
}
void GProj::SwapXandZ(GD3Point * p)
{
	double tp = p->z;
	p->z = p->x;
	p->x = tp;
}
void GProj::Oblique(GD3Point * p, double aAngle, double bAngle)
{
#if defined NOT_USE_MATRIX_VARY
	p->x = p->x - p->z*(1.0 / (tan(aAngle))*cos(bAngle));
	p->y = p->y - p->z*(1.0 / (tan(aAngle))*sin(bAngle));
	p->z = 0;
#else
	double matrixX[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 1.0 / (-tan(aAngle))*cos(bAngle), 1.0 / (-tan(aAngle))*sin(bAngle), 0, 0 }, { 0, 0, 0, 1 } };
	GTools::GraphMulVaryMatrix(p, matrixX);
#endif

}
void GProj::WorldOrgToViewOrg(GD3Point * p, double R, double aAngle, double bAngle)
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
	GTools::GraphMulVaryMatrix(p, matrixX);
#endif

}
void WorldOrgToViewOrg(GD3Point * p, GD3SphericalPoint & viewPoint)
{
	//WorldOrgToViewOrg(p,viewPoint.R,viewPoint.aAngle,viewPoint.bAngle);
}
void GProj::ViewOrgToScreenOrg(GD3Point * p, double d)
{
#if defined NOT_USE_MATRIX_VARY
	p->x = d*p->x / p->z;
	p->y = d*p->y / p->z;
	p->z = 0;
#else
	double matrixX[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 0, 1.0 / d }, { 0, 0, 0, 0 } };
	GTools::GraphMulVaryMatrix(p, matrixX);
#endif

}
void GProj::WorldOrgToScreenOrg(GD3Point * p, double R, double d, double aAngle, double bAngle)
{
#if defined NOT_USE_MATRIX_VARY
	ProjWorldOrgToViewOrg(p, R, aAngle, bAngle);
	ProjViewOrgToScreenOrg(p, d);
#else
	double matrixX[4][4] = { { cos(aAngle), -cos(bAngle)*sin(aAngle), 0, -sin(bAngle)*sin(aAngle) / d }, { 0, sin(bAngle), 0, -cos(bAngle) / d }, { -sin(aAngle), -cos(bAngle)*cos(aAngle), 0, -sin(bAngle)*cos(aAngle) / d }, { 0, 0, 0, R / d } };
	GTools::GraphMulVaryMatrix(p, matrixX);
#endif

}
void GProj::OnePoint(GD3Point * p, double R, double d)
{
#if defined NOT_USE_MATRIX_VARY
	ProjWorldOrgToViewOrg(p, R, AngleToRadian(0), AngleToRadian(90));
	ProjViewOrgToScreenOrg(p, d);
#else
	double matrixX[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 0, -1.0 / d }, { 0, 0, 0, R / d } };
	GTools::GraphMulVaryMatrix(p, matrixX);
#endif

}
void GProj::TwoPoint(GD3Point * p, double R, double d)
{
#if defined NOT_USE_MATRIX_VARY
	ProjWorldOrgToViewOrg(p, R, AngleToRadian(45), AngleToRadian(90));
	ProjViewOrgToScreenOrg(p, d);
#else
	double sq2 = sqrt(2.0);
	double matrixX[4][4] = { { sq2 / 2, 0, 0, -sq2 / (2 * d) }, { 0, 1, 0, 0 }, { -sq2 / 2, 0, 0, -sq2 / (2 * d) }, { 0, 0, 0, R / d } };
	GTools::GraphMulVaryMatrix(p, matrixX);
#endif

}
void GProj::ThreePoint(GD3Point * p, double R, double d)
{
#if defined NOT_USE_MATRIX_VARY
	ProjWorldOrgToViewOrg(p, R, AngleToRadian(45), AngleToRadian(45));
	ProjViewOrgToScreenOrg(p, d);
#else
	double sq2 = sqrt(2.0);
	double matrixX[4][4] = { { sq2 / 2, -1.0 / 2, 0, -1.0 / (2 * d) }, { 0, sq2 / 2, 0, -sq2 / (2 * d) }, { -sq2 / 2, -1.0 / 2, 0, -1.0 / (2 * d) }, { 0, 0, 0, R / d } };
	GTools::GraphMulVaryMatrix(p, matrixX);
#endif

}
void GProj::ViewOrgToDeepScreenD3Org(GD3Point * p, double d, double Near, double Far)
{
	double rx = d*(p->x) / (p->z);
	double ry = d*(p->y) / (p->z);
	double rz = Far*(1.0 - Near / (p->z)) / (Far - Near);
	p->x = rx;
	p->y = ry;
	p->z = rz;
}
