#include"StdAfx.h"
#include"GVary.h"
void GD3Vary::Move(GD3Point * p, double mx, double my, double mz)
{
#if defined NOT_USE_MATRIX_VARY
	p->x += mx;
	p->y += my;
	p->z += mz;
#else
	double matrix[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { mx, my, mz, 1 } };
	GTools::GraphMulVaryMatrix(p, matrix);
#endif
}
void GD3Vary::Scale(GD3Point * p, double sx, double sy, double sz)
{
#if defined NOT_USE_MATRIX_VARY
	p->x *= sx;
	p->y *= sy;
	p->z *= sz;
#else
	double matrix[4][4] = { { sx, 0, 0, 0 }, { 0, sy, 0, 0 }, { 0, 0, sz, 0 }, { 0, 0, 0, 1 } };
	GTools::GraphMulVaryMatrix(p, matrix);
#endif 
}
void GD3Vary::Spin(GD3Point * p, double sx, double sy, double sz)
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
	GTools::GraphMulVaryMatrix(p, matrixX);
	double matrixY[4][4] = { { cos(sy), 0, -sin(sy), 0 }, { 0, 1, 0, 0 }, { sin(sy), 0, cos(sy), 0 }, { 0, 0, 0, 1 } };
	GTools::GraphMulVaryMatrix(p, matrixY);
	double matrixZ[4][4] = { { cos(sz), sin(sz), 0, 0 }, { -sin(sz), cos(sz), 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
	GTools::GraphMulVaryMatrix(p, matrixZ);
#endif

}
void GD3Vary::Reflact(GD3Point * p, bool bx, bool by, bool bz)
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
		GTools::GraphMulVaryMatrix(p, matrixX);
	}
	if (by)
	{
		double matrixY[4][4] = { { -1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, -1, 0 }, { 0, 0, 0, 1 } };
		GTools::GraphMulVaryMatrix(p, matrixY);
	}
	if (bz)
	{
		double matrixZ[4][4] = { { -1, 0, 0, 0 }, { 0, -1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
		GTools::GraphMulVaryMatrix(p, matrixZ);
	}
#endif
}
void GD3Vary::FlatReflact(GD3Point * p, bool bxoy, bool byoz, bool bxoz)
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
		GTools::GraphMulVaryMatrix(p, matrixX);
	}
	if (byoz)
	{
		double matrixY[4][4] = { { -1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
		GTools::GraphMulVaryMatrix(p, matrixY);
	}
	if (bxoz)
	{
		double matrixZ[4][4] = { { 1, 0, 0, 0 }, { 0, -1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
		GTools::GraphMulVaryMatrix(p, matrixZ);
	}
#endif

}
void GD3Vary::Miscut(GD3Point * p, double xgz, double xdy, double yhz, double ybx, double zfy, double zcx)
{
#if defined NOT_USE_MATRIX_VARY
	p->x = p->x + xdy*p->y + xgz*p->z;
	p->y = ybx*p->x + p->y + p->z*yhz;
	p->z = zcx*p->x + zfy*p->y + p->z;
#else
	double matrixX[4][4] = { { 1, 0, 0, 0 }, { xdy, 1, 0, 0 }, { xgz, 0, 1, 0 }, { 0, 0, 0, 1 } };
	GTools::GraphMulVaryMatrix(p, matrixX);
	double matrixY[4][4] = { { 1, ybx, 0, 0 }, { 0, 1, 0, 0 }, { 0, yhz, 1, 0 }, { 0, 0, 0, 1 } };
	GTools::GraphMulVaryMatrix(p, matrixY);
	double matrixZ[4][4] = { { 1, 0, zcx, 0 }, { 0, 1, zfy, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
	GTools::GraphMulVaryMatrix(p, matrixZ);
#endif

}
void GD3Vary::OrgMove(GD3Point * p, double mx, double my, double mz)
{
#if defined NOT_USE_MATRIX_VARY
	p->x -= mx;
	p->y -= my;
	p->z -= mz;
#else
	double matrix[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { -mx, -my, -mz, 1 } };
	GTools::GraphMulVaryMatrix(p, matrix);
#endif

}
void GD3Vary::OrgSpin(GD3Point * p, double sx, double sy, double sz)
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
	GTools::GraphMulVaryMatrix(p, matrixX);
	double matrixY[4][4] = { { cos(sy), 0, sin(sy), 0 }, { 0, 1, 0, 0 }, { -sin(sy), 0, cos(sy), 0 }, { 0, 0, 0, 1 } };
	GTools::GraphMulVaryMatrix(p, matrixY);
	double matrixZ[4][4] = { { cos(sz), -sin(sz), 0, 0 }, { sin(sz), cos(sz), 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };
	GTools::GraphMulVaryMatrix(p, matrixZ);
#endif

}
void GD3Vary::OrgReflact(GD3Point * p, bool bx, bool by, bool bz)
{
	Reflact(p, bx, by, bz);
}
void GD3Vary::OrgFlatReflact(GD3Point * p, bool bxoy, bool byoz, bool bxoz)
{
	FlatReflact(p, bxoy, byoz, bxoz);
}