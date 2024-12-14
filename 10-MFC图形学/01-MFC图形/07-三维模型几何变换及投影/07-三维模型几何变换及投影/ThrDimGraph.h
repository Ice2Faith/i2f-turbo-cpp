#ifndef _THRDIMGRAPH_H_
#define _THRDIMGRAPH_H_
#include<math.h>
//x,y,z为三维坐标点，传入地址，进行修改值
//乘4*4三维变换矩阵
void GraphMulVaryMatrix(double * x,double * y,double * z,double matrix[][4]);
//平移变换，x,y,z分别平移mx,my,mz距离
void GraphMove(double * x,double * y,double * z,double mx,double my,double mz);
//比例变换，x,y,z分别乘以sx,sy,sz比例
void GraphScale(double * x,double * y,double * z,double sx,double sy,double sz);
//旋转变换，坐标依次绕x,y,z轴旋转sx,sy,sz角度（弧度制）
void GraphSpin(double * x,double * y,double * z,double sx,double sy,double sz);
//反射变换，坐标依次对x,y,z轴反射，如果对应的bx,by,bz值为真，否则跳过
void GraphReflact(double * x,double * y,double * z,bool bx,bool by,bool bz);
//反射变换，坐标依次对xoy,yoz,xoz平面反射，如果对应的xoy,yoz,xoz值为真，否则跳过
void GraphFlatReflact(double * x,double * y,double * z,bool bxoy,bool byoz,bool bxoz);
//错切变换，坐标依次沿x,y,z轴错切，分别离开z,y轴向x轴移动gz,dy距离，依次类推
void GraphMiscut(double * x,double * y,double * z,double xgz,double xdy,double yhz,double ybx,double zfy,double zcx);

//坐标系移动变换，x,y,z分别为坐标系平移mx,my,mz后的位置
void OrgMove(double * x,double * y,double * z,double mx,double my,double mz);
//坐标系旋转变换，坐标系依次绕x,y,z轴旋转sx,sy,sz角度（弧度制）后的位置
void OrgSpin(double * x,double * y,double * z,double sx,double sy,double sz);
//坐标系反射变换，直接采用点变换方式
void OrgReflact(double * x,double * y,double * z,bool bx,bool by,bool bz);
void OrgFlatReflact(double * x,double * y,double * z,bool bxoy,bool byoz,bool bxoz);

//正交投影，直接去掉z轴，xoy
void ProjOrthogonal(double * x,double * y,double * z);
//主视图,yoz
void ProjMainView(double * x,double * y,double * z);
//侧视图,yoz
void ProjSideView(double * x,double * y,double * z);
//俯视图,yoz
void ProjTopView(double * x,double * y,double * z);
//斜投影,投影斜度a,投影和x轴夹角b,xoy
void ProjOblique(double * x,double * y,double * z,double a,double b);

//透视投影,世界坐标系转观察坐标系,视径R,z轴角度a,y轴角度b
void ProjWorldOrgToViewOrg(double * x,double * y,double * z,double R,double a,double b);
//观察坐标系转屏幕坐标系，视距d,xoy
void ProjViewOrgToScreenOrg(double * x,double * y,double * z,double d);
//世界坐标系转屏幕坐标系，视径R,视距d，z轴角度a,y轴角度b,xoy
void ProjWorldOrgToScreenOrg(double * x,double * y,double * z,double R,double d,double a,double b);

//一点透视,xoy
void ProjOnePoint(double * x,double * y,double * z,double R,double d);
//两点透视,xoy
void ProjTwoPoint(double * x,double * y,double * z,double R,double d);
//三点透视,xoy
void ProjThreePoint(double * x,double * y,double * z,double R,double d);

//观察坐标系转具有深度的观察坐标系，近切面Near，远切面Far,修改后为三维屏幕坐标
void ProjViewOrgToDeepScreenD3Org(double * x,double * y,double * z,double d,double Near,double Far);

#endif // _THRDIMGRAPH_H_
