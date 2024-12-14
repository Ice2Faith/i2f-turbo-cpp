#include"stdafx.h"
#include"D3Graph.h"
Point3D::Point3D() :mx(0), my(0), mz(0)
{
}
Point3D::Point3D(double x, double y, double z) : mx(x), my(y), mz(z)
{
}
Point3D::Point3D(const Point3D & cp3)
{
	mx = cp3.mx;
	my = cp3.my;
	mz = cp3.mz;
}
Point3D & Point3D::operator=(const Point3D & cp3)
{
	mx = cp3.mx;
	my = cp3.my;
	mz = cp3.mz;
	return *this;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Graph3D::MulVaryMatrix(Point3D& pd, double matrix[][4])
{
	::GraphMulVaryMatrix(&pd.mx, &pd.my, &pd.mz, matrix);
}
void Graph3D::Move(Point3D & pd, double mx, double my, double mz)
{
	::GraphMove(&pd.mx, &pd.my, &pd.mz, mx, my, mz);
}
void Graph3D::Scale(Point3D & pd, double sx, double sy, double sz)
{
	::GraphScale(&pd.mx, &pd.my, &pd.mz, sx, sy, sz);
}
void Graph3D::Spin(Point3D & pd, double sx, double sy, double sz)
{
	::GraphSpin(&pd.mx, &pd.my, &pd.mz, sx, sy, sz);
}
void Graph3D::Reflact(Point3D & pd, bool bx, bool by, bool bz)
{
	::GraphReflact(&pd.mx, &pd.my, &pd.mz, bx, by, bz);
}
void Graph3D::FlatReflact(Point3D & pd, bool bxoy, bool byoz, bool bxoz)
{
	::GraphFlatReflact(&pd.mx, &pd.my, &pd.mz, bxoy, byoz, bxoz);
}
void Graph3D::Miscut(Point3D & pd, double xgz, double xdy, double yhz, double ybx, double zfy, double zcx)
{
	::GraphMiscut(&pd.mx, &pd.my, &pd.mz, xgz, xdy, yhz, ybx, zfy, zcx);
}
/////////////////////////////////////////////////////////////////////////////////////////////
void Org3D::Move(Point3D & pd, double mx, double my, double mz)
{
	::OrgMove(&pd.mx, &pd.my, &pd.mz, mx, my, mz);
}
void Org3D::Spin(Point3D & pd, double sx, double sy, double sz)
{
	::OrgSpin(&pd.mx, &pd.my, &pd.mz, sx, sy, sz);
}
void Org3D::Reflact(Point3D & pd, bool bx, bool by, bool bz)
{
	::OrgReflact(&pd.mx, &pd.my, &pd.mz, bx, by, bz);
}
void Org3D::FlatReflact(Point3D & pd, bool bxoy, bool byoz, bool bxoz)
{
	::OrgFlatReflact(&pd.mx, &pd.my, &pd.mz, bxoy, byoz, bxoz);
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void Orthogonal(Point3D & pd)
{
	::ProjOrthogonal(&pd.mx, &pd.my, &pd.mz);
}
void MainView(Point3D & pd)
{
	::ProjMainView(&pd.mx, &pd.my, &pd.mz);
}
void SideView(Point3D & pd)
{
	::ProjSideView(&pd.mx, &pd.my, &pd.mz);
}
void TopView(Point3D & pd)
{
	::ProjTopView(&pd.mx, &pd.my, &pd.mz);
}
void Oblique(Point3D & pd, double a, double b)
{
	::ProjOblique(&pd.mx, &pd.my, &pd.mz, a, b);
}
void WorldOrgToViewOrg(Point3D & pd, double R, double a, double b)
{
	::ProjWorldOrgToViewOrg(&pd.mx, &pd.my, &pd.mz, R, a, b);
}
void ViewOrgToScreenOrg(Point3D & pd, double d)
{
	::ProjViewOrgToScreenOrg(&pd.mx, &pd.my, &pd.mz, d);
}
void WorldOrgToScreenOrg(Point3D & pd, double R, double d, double a, double b)
{
	::ProjWorldOrgToScreenOrg(&pd.mx, &pd.my, &pd.mz, R, d, a, b);
}
void OnePoint(Point3D & pd, double R, double d)
{
	::ProjOnePoint(&pd.mx, &pd.my, &pd.mz, R, d);
}
void TwoPoint(Point3D & pd, double R, double d)
{
	::ProjTwoPoint(&pd.mx, &pd.my, &pd.mz, R, d);
}
void ThreePoint(Point3D & pd, double R, double d)
{
	::ProjThreePoint(&pd.mx, &pd.my, &pd.mz, R, d);
}
void ViewOrgToDeepScreenD3Org(Point3D & pd, double d, double Near, double Far)
{
	::ProjViewOrgToDeepScreenD3Org(&pd.mx, &pd.my, &pd.mz, d, Near, Far);
}