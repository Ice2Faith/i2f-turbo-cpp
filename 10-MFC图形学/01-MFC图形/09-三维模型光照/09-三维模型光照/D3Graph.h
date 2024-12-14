#ifndef _D3GRAPH_H_
#define _D3GRAPH_H_
//如果定义了此宏，则进行变换时不使用变换矩阵乘法进行运算，进行直接运算，拥有更好的性能
#if defined NOT_USE_MATRIX_VARY
#error "Error!!!Please Check Define NOT_USE_MATRIX_VARY"
#endif
//#define NOT_USE_MATRIX_VARY
/*
计算机图形学3D绘图，C语言接口函数，接口中角度表示全部使用弧度制
*/
const double MATH_PI = 3.1415926535;
typedef struct
{
	double x;
	double y;
	double z;
}D3Point;
typedef D3Point D3Vector;
typedef D3Vector D3NormalLine;
typedef struct
{
	D3Point p1;
	D3Point p2;
}D3Line;
typedef struct
{
	D3Point p1;
	D3Point p2;
	D3Point p3;
}D3Flat;
typedef struct
{
	double x;
	double y;
}D2Point;
typedef D2Point D2Vector;
typedef struct
{
	D2Point p1;
	D2Point p2;
}D2Line;
typedef struct
{
	D2Point p1;
	D2Point p2;
	D2Point p3;
}D2Flat;
/*弧度角度互转*/
double AngleToRadian(double a);
double RadianToAngle(double a);
//基本数据转换
D3Point MakeD3Point(double x, double y, double z);
D2Point MakeD2Point(double x, double y);
D2Line MakeD2Line(D2Point p1, D2Point p2);
D3Line MakeD3Line(D3Point p1, D3Point p2);
D3Flat MakeD3Flat(D3Point p1, D3Point p2, D3Point p3);
D2Flat MakeD2Flat(D2Point p1, D2Point p2, D2Point p3);
void D3PointToArray(D3Point p, double arr[]);
void D3FlatToArray(D3Flat f, D3Point arr[]);
D3Point ArrayToD3Point(double arr[]);
D3Flat ArrayToD3Flat(D3Point arr[]);
/*获取三维向量*/
void GetD3Vector(D3Point p1, D3Point p2, D3Vector * vec);
/*获取三维向量夹角弧度*/
double GetD3VectorRadian(D3Vector v1, D3Vector v2);
/*获得三维向量点乘*/
double GetD3VectorPointMul(D3Vector v1, D3Vector v2);
/*获取三维向量模长*/
double GetD3VectorModulus(D3Vector v);
/*三维球坐标转指教坐标 aAngle:0->MATH_PI bAngle:0->2*MATH_PI*/
void D3SphericalToCartesianCoordinates(double R, double aAngle, double bAngle, D3Point * point);
/*获取三维视向量*/
void GetViewVector(D3Point p, double R, double aAngle, double bAngle, D3Vector * v);
/*获取三维面法向量*/
void GetD3NormalLine(D3Vector v1, D3Vector v2, D3NormalLine * nl);

/*
隐线算法：如果视向量和面法向量的夹角余弦大于0，则可见，否则不可见
算法实现：
任取平面上三点，构造两个向量
利用两个向量点乘获得平面法向量
取平面内任意一点和视点构造视向量
计算视向量和法向量夹角的余弦判定符号即可
*/
double D3FlatBlankingAlgorithm(double R, double aAngle, double bAngle, D3Flat flat);

/*平面三角填充算法*/
void FillScanLine(D2Flat flat, COLORREF fillcolor, HDC hdc);


//x,y,z为三维坐标点，传入地址，进行修改值
//乘4*4三维变换矩阵
void GraphMulVaryMatrix(D3Point * p, double matrix[][4]);
//平移变换，x,y,z分别平移mx,my,mz距离
void GraphMove(D3Point * p, double mx, double my, double mz);
//比例变换，x,y,z分别乘以sx,sy,sz比例
void GraphScale(D3Point * p, double sx, double sy, double sz);
//旋转变换，坐标依次绕x,y,z轴旋转sx,sy,sz角度（弧度制）,相对于轴右手向旋转
void GraphSpin(D3Point * p, double sx, double sy, double sz);
//反射变换，坐标依次对x,y,z轴反射，如果对应的bx,by,bz值为真，否则跳过
void GraphReflact(D3Point * p, bool bx, bool by, bool bz);
//反射变换，坐标依次对xoy,yoz,xoz平面反射，如果对应的xoy,yoz,xoz值为真，否则跳过
void GraphFlatReflact(D3Point * p, bool bxoy, bool byoz, bool bxoz);
//错切变换，坐标依次沿x,y,z轴错切，分别离开z,y轴向x轴移动gz,dy距离，依次类推
void GraphMiscut(D3Point * p, double xgz, double xdy, double yhz, double ybx, double zfy, double zcx);

//坐标系移动变换，x,y,z分别为坐标系平移mx,my,mz后的位置
void OrgMove(D3Point * p, double mx, double my, double mz);
//坐标系旋转变换，坐标系依次绕x,y,z轴旋转sx,sy,sz角度（弧度制）后的位置
void OrgSpin(D3Point * p, double sx, double sy, double sz);
//坐标系反射变换，直接采用点变换方式
void OrgReflact(D3Point * p, bool bx, bool by, bool bz);
void OrgFlatReflact(D3Point * p, bool bxoy, bool byoz, bool bxoz);

//正交投影，直接去掉z轴，xoy
void ProjOrthogonal(D3Point * p);
//主视图,yoz
void ProjMainView(D3Point * p);
//侧视图,yoz
void ProjSideView(D3Point * p);
//俯视图,yoz
void ProjTopView(D3Point * p);
//斜投影,投影斜度aAngle,越大越接近正交投影：0-PI/2,投影和x轴夹角bAngle,也是光照方向：0-2*PI,xoy
void ProjOblique(D3Point * p, double aAngle, double bAngle);

//透视投影,世界坐标系转观察坐标系,视径R,z轴角度aAngle，水平夹角：0-2*PI,y轴角度bAngle，垂直夹角：0-PI
void ProjWorldOrgToViewOrg(D3Point * p, double R, double aAngle, double bAngle);
//观察坐标系转屏幕坐标系，视距d:视点到视心的距离,xoy
void ProjViewOrgToScreenOrg(D3Point * p, double d);
//世界坐标系转屏幕坐标系，视径R,视距d，z轴角度a,y轴角度b,xoy
void ProjWorldOrgToScreenOrg(D3Point * p, double R, double d, double aAngle, double bAngle);

//一点透视,xoy
void ProjOnePoint(D3Point * p, double R, double d);
//两点透视,xoy
void ProjTwoPoint(D3Point * p, double R, double d);
//三点透视,xoy
void ProjThreePoint(D3Point * p, double R, double d);

/*观察坐标系转具有深度的屏幕坐标系，
相机镜头的近焦和远焦
近切面Near：物体离相机的距离，越小越模糊，
远切面Far：一段指定长度直线的图像在此处变为灭点,大于此值时将会变得模糊,
修改后为三维屏幕坐标,z标识伪深度
*/
void ProjViewOrgToDeepScreenD3Org(D3Point * p, double d, double Near, double Far);

#endif //_D3GRAPH_H_