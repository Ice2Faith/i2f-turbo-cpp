#ifndef _GDATA_H_
#define _GDATA_H_
#include<math.h>
#include<Windows.h>
#include<vector>
#include<iterator>
//如果定义了此宏，则进行变换投影时不使用变换矩阵乘法进行运算，进行直接运算，拥有更好的性能
#if defined NOT_USE_MATRIX_VARY
#error "Error!!! NOT_USE_MATRIX_VARY has be defined before here!"
#endif // defined NOT_USE_MATRIX_VARY
//#define NOT_USE_MATRIX_VARY

//向前申明
class GD3Point;
//工具类
class GTools
{
public:
	static const double MATH_PI;
	/*弧度角度互转*/
	static double AngleToRadian(double a);
	static double RadianToAngle(double a);
	//乘4*4三维变换矩阵
	static void GraphMulVaryMatrix(GD3Point * p, double matrix[][4]);
};
//三维球坐标类
class GD3SphericalPoint
{
public:
	//视径R, z轴角度aAngle，水平夹角：0 - 2 * PI, y轴角度bAngle，垂直夹角：0 - PI
	double R;
	double aAngle;
	double bAngle;
	GD3SphericalPoint();
	GD3SphericalPoint(double R,double aAngle,double bAngle);
	GD3SphericalPoint(GD3SphericalPoint & sp);
	GD3SphericalPoint& operator=(const GD3SphericalPoint & p);
};
//三维点类
class GD3Point
{
public:
    double x;
    double y;
    double z;
	GD3Point();
    GD3Point(double x,double y,double z);
    GD3Point(const GD3Point & p);
	GD3Point(GD3SphericalPoint & sp);
    GD3Point& operator=(const GD3Point & p);
    bool operator==(const GD3Point & p);
	void ParseSpherical(double R,double aAngle,double bAngle);
	GD3Point(double * arr);
	void toArrayDouble(double arr[]);
};
//三维向量类
class GD3Vector : public GD3Point
{
public:
	GD3Vector();
    GD3Vector(double x,double y,double z);
    GD3Vector(GD3Vector & v);
    GD3Vector(GD3Point & p);
	GD3Vector(GD3Point & ps,GD3Point & pe);
    GD3Vector& operator=(const GD3Vector & v);
    bool operator==(const GD3Vector & v);
    double GetModuleLength();//获取向量模长
    void Untization();//单位化
    GD3Vector operator+(const GD3Vector & v);//向量加法
    double operator*(const GD3Vector & v);//向量点乘
    GD3Vector CrossMultiply(GD3Vector & v);//向量叉乘
	double CosRadian(GD3Vector & v);//向量夹角
	GD3Vector(double * arr);
};
//三维法向量类
class GD3NormalLine :public GD3Vector
{
public:
	GD3NormalLine();
	GD3NormalLine(double x,double y,double z);
	GD3NormalLine(GD3Vector & v);
	GD3NormalLine(GD3NormalLine & n);
	GD3NormalLine(GD3Vector & v1, GD3Vector & v2);
	GD3NormalLine& operator=(const GD3NormalLine & n);
	GD3NormalLine(double * arr);
};
//三维平面类
class GD3Flat
{
public:
	GD3Point p1;
	GD3Point p2;
	GD3Point p3;
	GD3Flat();
	GD3Flat(GD3Point & p1, GD3Point & p2, GD3Point & p3 );
	GD3NormalLine GetNormalLine();
	GD3NormalLine GetUntizationNormalLine();
	GD3Flat(GD3Point * arr);
	void toArrayPoint(GD3Point arr[]);
};
//二维点类
class GD2Point
{
public:
	double x;
	double y;
	GD2Point();
	GD2Point(double x, double y);
	GD2Point(const GD2Point & p);
	GD2Point& operator=(const GD2Point & p);
};
//二维向量类
class GD2Vector : public GD2Point
{
public:
	GD2Vector();
	GD2Vector(double x, double y);
	GD2Vector(GD2Vector & v);
	GD2Vector(GD2Point & p);
	GD2Vector(GD2Point & ps, GD2Point & pe);
	GD2Vector& operator=(const GD2Vector & v);
	bool operator==(const GD2Vector & v);
	double GetModuleLength();//获取向量模长
	void Untization();//单位化
	GD2Vector operator+(const GD2Vector & v);//向量加法
	double operator*(const GD2Vector & v);//向量点乘
	double CosRadian(GD2Vector & v);//向量夹角
};
//二维直线类
class GD2Line
{
public:
	GD2Point p1;
	GD2Point p2;
	GD2Line();
	GD2Line(GD2Line & l);
	GD2Line(GD2Point & p1, GD2Point & p2);
	double GetDistance();
	GD2Line(GD2Point * arr);
	void toArrayPoint(GD2Point arr[]);
};
//二维平面类
class GD2Flat
{
public:
	GD2Point p1;
	GD2Point p2;
	GD2Point p3;
	GD2Flat();
	GD2Flat(GD2Point & p1, GD2Point & p2, GD2Point & p3);
	GD2Flat(GD2Flat & f);
	GD2Flat(GD2Point * arr);
	void toArrayPoint(GD2Point arr[]);
};
//三角片面顶点类
class GD3Trangle
{
public:
	long p1;
	long p2;
	long p3;
	GD3Trangle();
	GD3Trangle(long p1,long p2,long p3);
	GD3Trangle(const GD3Trangle & t);
	GD3Trangle& operator=(const GD3Trangle & t);
};
//三维数据存储类
class GD3DataGroup
{
public:
    GD3DataGroup();
    GD3DataGroup(GD3DataGroup & dg);
    GD3DataGroup& operator=(const GD3DataGroup & dg);
    ~GD3DataGroup();
    void allocMemory(long pointCount,long trangleCount);
	long getPointCount();
	long getTrangleCount();
	GD3Point & pointAt(long index);
	GD3Trangle & trangleAt(long index);
private:
    void freeMemory();
    long pointCount;
	long trangleCount;
	GD3Point * points;
	GD3Trangle * trangles;
};
#endif // _GDATA_H_
