#ifndef _GDATA_H_
#define _GDATA_H_
#include<math.h>
#include<Windows.h>
#include<vector>
#include<iterator>
//��������˴˺꣬����б任ͶӰʱ��ʹ�ñ任����˷��������㣬����ֱ�����㣬ӵ�и��õ�����
#if defined NOT_USE_MATRIX_VARY
#error "Error!!! NOT_USE_MATRIX_VARY has be defined before here!"
#endif // defined NOT_USE_MATRIX_VARY
//#define NOT_USE_MATRIX_VARY

//��ǰ����
class GD3Point;
//������
class GTools
{
public:
	static const double MATH_PI;
	/*���ȽǶȻ�ת*/
	static double AngleToRadian(double a);
	static double RadianToAngle(double a);
	//��4*4��ά�任����
	static void GraphMulVaryMatrix(GD3Point * p, double matrix[][4]);
};
//��ά��������
class GD3SphericalPoint
{
public:
	//�Ӿ�R, z��Ƕ�aAngle��ˮƽ�нǣ�0 - 2 * PI, y��Ƕ�bAngle����ֱ�нǣ�0 - PI
	double R;
	double aAngle;
	double bAngle;
	GD3SphericalPoint();
	GD3SphericalPoint(double R,double aAngle,double bAngle);
	GD3SphericalPoint(GD3SphericalPoint & sp);
	GD3SphericalPoint& operator=(const GD3SphericalPoint & p);
};
//��ά����
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
//��ά������
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
    double GetModuleLength();//��ȡ����ģ��
    void Untization();//��λ��
    GD3Vector operator+(const GD3Vector & v);//�����ӷ�
    double operator*(const GD3Vector & v);//�������
    GD3Vector CrossMultiply(GD3Vector & v);//�������
	double CosRadian(GD3Vector & v);//�����н�
	GD3Vector(double * arr);
};
//��ά��������
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
//��άƽ����
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
//��ά����
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
//��ά������
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
	double GetModuleLength();//��ȡ����ģ��
	void Untization();//��λ��
	GD2Vector operator+(const GD2Vector & v);//�����ӷ�
	double operator*(const GD2Vector & v);//�������
	double CosRadian(GD2Vector & v);//�����н�
};
//��άֱ����
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
//��άƽ����
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
//����Ƭ�涥����
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
//��ά���ݴ洢��
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
