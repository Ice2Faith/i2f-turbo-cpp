#pragma once
#include"ThrDimGraph.h"

class Point3D
{
public:
	Point3D();
	Point3D(double x, double y, double z);
	Point3D(const Point3D & cp3);
	Point3D & operator=(const Point3D & cp3);
public:
	double mx;
	double my;
	double mz;
};

class Graph3D
{
public:
	static void MulVaryMatrix(Point3D& pd, double matrix[][4]);
	static void Move(Point3D & pd, double mx = 0, double my = 0, double mz = 0);
	static void Scale(Point3D & pd, double sx = 1, double sy = 1, double sz = 1);
	static void Spin(Point3D & pd, double sx = 0, double sy = 0, double sz = 0);
	static void Reflact(Point3D & pd, bool bx = false, bool by = false, bool bz = false);
	static void FlatReflact(Point3D & pd, bool bxoy = false, bool byoz = false, bool bxoz = false);
	static void Miscut(Point3D & pd, double xgz = 0, double xdy = 0, double yhz = 0, double ybx = 0, double zfy = 0, double zcx = 0);
};
class Org3D
{
public:
	static void Move(Point3D & pd, double mx = 0, double my = 0, double mz = 0);
	static void Spin(Point3D & pd, double sx = 0, double sy = 0, double sz = 0);
	static void Reflact(Point3D & pd, bool bx = false, bool by = false, bool bz = false);
	static void FlatReflact(Point3D & pd, bool bxoy = false, bool byoz = false, bool bxoz = false);
};


class Proj3D
{
public:
	static void Orthogonal(Point3D & pd);
	static void MainView(Point3D & pd);
	static void SideView(Point3D & pd);
	static void TopView(Point3D & pd);
	static void Oblique(Point3D & pd, double a=0, double b=0);
	static void WorldOrgToViewOrg(Point3D & pd, double R = 800, double a = 0, double b = 0);
	static void ViewOrgToScreenOrg(Point3D & pd, double d = 80);
	static void WorldOrgToScreenOrg(Point3D & pd, double R = 800, double d = 80, double a = 0, double b = 0);
	static void OnePoint(Point3D & pd, double R = 800, double d = 80);
	static void TwoPoint(Point3D & pd, double R = 800, double d = 80);
	static void ThreePoint(Point3D & pd, double R = 800, double d = 80);
	static void ViewOrgToDeepScreenD3Org(Point3D & pd, double d = 80, double Near = 20, double Far = 1200);
};

