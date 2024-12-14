#ifndef _GVARY_H_
#define _GVARY_H_
#include"GData.h"

class GD3Vary
{
public:
	//x,y,z为三维坐标点，传入地址，进行修改值
	//平移变换，x,y,z分别平移mx,my,mz距离
	static void Move(GD3Point * p, double mx, double my, double mz);
	//比例变换，x,y,z分别乘以sx,sy,sz比例
	static void Scale(GD3Point * p, double sx, double sy, double sz);
	//旋转变换，坐标依次绕x,y,z轴旋转sx,sy,sz角度（弧度制）,相对于轴右手向旋转
	static void Spin(GD3Point * p, double sx, double sy, double sz);
	//反射变换，坐标依次对x,y,z轴反射，如果对应的bx,by,bz值为真，否则跳过
	static void Reflact(GD3Point * p, bool bx, bool by, bool bz);
	//反射变换，坐标依次对xoy,yoz,xoz平面反射，如果对应的xoy,yoz,xoz值为真，否则跳过
	static void FlatReflact(GD3Point * p, bool bxoy, bool byoz, bool bxoz);
	//错切变换，坐标依次沿x,y,z轴错切，分别离开z,y轴向x轴移动gz,dy距离，依次类推
	static void Miscut(GD3Point * p, double xgz, double xdy, double yhz, double ybx, double zfy, double zcx);

	//坐标系移动变换，x,y,z分别为坐标系平移mx,my,mz后的位置
	static void OrgMove(GD3Point * p, double mx, double my, double mz);
	//坐标系旋转变换，坐标系依次绕x,y,z轴旋转sx,sy,sz角度（弧度制）后的位置
	static void OrgSpin(GD3Point * p, double sx, double sy, double sz);
	//坐标系反射变换，直接采用点变换方式
	static void OrgReflact(GD3Point * p, bool bx, bool by, bool bz);
	static void OrgFlatReflact(GD3Point * p, bool bxoy, bool byoz, bool bxoz);
};

#endif // _GVARY_H_