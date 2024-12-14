#ifndef _D3GRAPH_H_
#define _D3GRAPH_H_
//��������˴˺꣬����б任ʱ��ʹ�ñ任����˷��������㣬����ֱ�����㣬ӵ�и��õ�����
#if defined NOT_USE_MATRIX_VARY
#error "Error!!!Please Check Define NOT_USE_MATRIX_VARY"
#endif
//#define NOT_USE_MATRIX_VARY
/*
�����ͼ��ѧ3D��ͼ��C���Խӿں������ӿ��нǶȱ�ʾȫ��ʹ�û�����
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
/*���ȽǶȻ�ת*/
double AngleToRadian(double a);
double RadianToAngle(double a);
//��������ת��
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
/*��ȡ��ά����*/
void GetD3Vector(D3Point p1, D3Point p2, D3Vector * vec);
/*��ȡ��ά�����нǻ���*/
double GetD3VectorRadian(D3Vector v1, D3Vector v2);
/*�����ά�������*/
double GetD3VectorPointMul(D3Vector v1, D3Vector v2);
/*��ȡ��ά����ģ��*/
double GetD3VectorModulus(D3Vector v);
/*��ά������תָ������ aAngle:0->MATH_PI bAngle:0->2*MATH_PI*/
void D3SphericalToCartesianCoordinates(double R, double aAngle, double bAngle, D3Point * point);
/*��ȡ��ά������*/
void GetViewVector(D3Point p, double R, double aAngle, double bAngle, D3Vector * v);
/*��ȡ��ά�淨����*/
void GetD3NormalLine(D3Vector v1, D3Vector v2, D3NormalLine * nl);

/*
�����㷨��������������淨�����ļн����Ҵ���0����ɼ������򲻿ɼ�
�㷨ʵ�֣�
��ȡƽ�������㣬������������
��������������˻��ƽ�淨����
ȡƽ��������һ����ӵ㹹��������
�����������ͷ������нǵ������ж����ż���
*/
double D3FlatBlankingAlgorithm(double R, double aAngle, double bAngle, D3Flat flat);

/*ƽ����������㷨*/
void FillScanLine(D2Flat flat, COLORREF fillcolor, HDC hdc);


//x,y,zΪ��ά����㣬�����ַ�������޸�ֵ
//��4*4��ά�任����
void GraphMulVaryMatrix(D3Point * p, double matrix[][4]);
//ƽ�Ʊ任��x,y,z�ֱ�ƽ��mx,my,mz����
void GraphMove(D3Point * p, double mx, double my, double mz);
//�����任��x,y,z�ֱ����sx,sy,sz����
void GraphScale(D3Point * p, double sx, double sy, double sz);
//��ת�任������������x,y,z����תsx,sy,sz�Ƕȣ������ƣ�,���������������ת
void GraphSpin(D3Point * p, double sx, double sy, double sz);
//����任���������ζ�x,y,z�ᷴ�䣬�����Ӧ��bx,by,bzֵΪ�棬��������
void GraphReflact(D3Point * p, bool bx, bool by, bool bz);
//����任���������ζ�xoy,yoz,xozƽ�淴�䣬�����Ӧ��xoy,yoz,xozֵΪ�棬��������
void GraphFlatReflact(D3Point * p, bool bxoy, bool byoz, bool bxoz);
//���б任������������x,y,z����У��ֱ��뿪z,y����x���ƶ�gz,dy���룬��������
void GraphMiscut(D3Point * p, double xgz, double xdy, double yhz, double ybx, double zfy, double zcx);

//����ϵ�ƶ��任��x,y,z�ֱ�Ϊ����ϵƽ��mx,my,mz���λ��
void OrgMove(D3Point * p, double mx, double my, double mz);
//����ϵ��ת�任������ϵ������x,y,z����תsx,sy,sz�Ƕȣ������ƣ����λ��
void OrgSpin(D3Point * p, double sx, double sy, double sz);
//����ϵ����任��ֱ�Ӳ��õ�任��ʽ
void OrgReflact(D3Point * p, bool bx, bool by, bool bz);
void OrgFlatReflact(D3Point * p, bool bxoy, bool byoz, bool bxoz);

//����ͶӰ��ֱ��ȥ��z�ᣬxoy
void ProjOrthogonal(D3Point * p);
//����ͼ,yoz
void ProjMainView(D3Point * p);
//����ͼ,yoz
void ProjSideView(D3Point * p);
//����ͼ,yoz
void ProjTopView(D3Point * p);
//бͶӰ,ͶӰб��aAngle,Խ��Խ�ӽ�����ͶӰ��0-PI/2,ͶӰ��x��н�bAngle,Ҳ�ǹ��շ���0-2*PI,xoy
void ProjOblique(D3Point * p, double aAngle, double bAngle);

//͸��ͶӰ,��������ϵת�۲�����ϵ,�Ӿ�R,z��Ƕ�aAngle��ˮƽ�нǣ�0-2*PI,y��Ƕ�bAngle����ֱ�нǣ�0-PI
void ProjWorldOrgToViewOrg(D3Point * p, double R, double aAngle, double bAngle);
//�۲�����ϵת��Ļ����ϵ���Ӿ�d:�ӵ㵽���ĵľ���,xoy
void ProjViewOrgToScreenOrg(D3Point * p, double d);
//��������ϵת��Ļ����ϵ���Ӿ�R,�Ӿ�d��z��Ƕ�a,y��Ƕ�b,xoy
void ProjWorldOrgToScreenOrg(D3Point * p, double R, double d, double aAngle, double bAngle);

//һ��͸��,xoy
void ProjOnePoint(D3Point * p, double R, double d);
//����͸��,xoy
void ProjTwoPoint(D3Point * p, double R, double d);
//����͸��,xoy
void ProjThreePoint(D3Point * p, double R, double d);

/*�۲�����ϵת������ȵ���Ļ����ϵ��
�����ͷ�Ľ�����Զ��
������Near������������ľ��룬ԽСԽģ����
Զ����Far��һ��ָ������ֱ�ߵ�ͼ���ڴ˴���Ϊ���,���ڴ�ֵʱ������ģ��,
�޸ĺ�Ϊ��ά��Ļ����,z��ʶα���
*/
void ProjViewOrgToDeepScreenD3Org(D3Point * p, double d, double Near, double Far);

#endif //_D3GRAPH_H_