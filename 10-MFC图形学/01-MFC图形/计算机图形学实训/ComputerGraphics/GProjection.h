#ifndef _GPROJECTION_H_
#define _GPROJECTION_H_
#include"GData.h"

class GProj
{
public:
	//正交投影，直接去掉z轴，xoy(投影到xoy平面)
	static void Orthogonal(GD3Point * p);
	//主视图,yoz
	static void MainView(GD3Point * p);
	//侧视图,yoz
	static void SideView(GD3Point * p);
	//俯视图,yoz
	static void TopView(GD3Point * p);
	//三视图的结果在yoz平面内，可能需要转换到xoy平面显示，因此交换X,Z轴
	static void SwapXandZ(GD3Point * p);
	//斜投影,投影斜度aAngle,越大越接近正交投影：0-PI/2,投影和x轴夹角bAngle,也是光照方向：0-2*PI,xoy
	static void Oblique(GD3Point * p, double aAngle, double bAngle);

	//透视投影,世界坐标系转观察坐标系,视径R,z轴角度aAngle，水平夹角：0-2*PI,y轴角度bAngle，垂直夹角：0-PI
	static void WorldOrgToViewOrg(GD3Point * p, double R, double aAngle, double bAngle);
	//观察坐标系转屏幕坐标系，视距d:视点到视心的距离,xoy
	static void ViewOrgToScreenOrg(GD3Point * p, double d);
	//世界坐标系转屏幕坐标系，视径R,视距d，z轴角度a,y轴角度b,xoy
	static void WorldOrgToScreenOrg(GD3Point * p, double R, double d, double aAngle, double bAngle);

	//一点透视,xoy
	static void OnePoint(GD3Point * p, double R, double d);
	//两点透视,xoy
	static void TwoPoint(GD3Point * p, double R, double d);
	//三点透视,xoy
	static void ThreePoint(GD3Point * p, double R, double d);

	/*观察坐标系转具有深度的屏幕坐标系，
	相机镜头的近焦和远焦
	近切面Near：物体离相机的距离，越小越模糊，
	远切面Far：一段指定长度直线的图像在此处变为灭点,大于此值时将会变得模糊,
	修改后为三维屏幕坐标,z标识伪深度
	*/
	static void ViewOrgToDeepScreenD3Org(GD3Point * p, double d, double Near, double Far);
};

#endif // _GPROJECTION_H_