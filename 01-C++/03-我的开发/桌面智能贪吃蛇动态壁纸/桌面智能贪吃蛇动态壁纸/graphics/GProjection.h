#ifndef _GPROJECTION_H_
#define _GPROJECTION_H_
#include"GData.h"

class GProj
{
public:
	//����ͶӰ��ֱ��ȥ��z�ᣬxoy(ͶӰ��xoyƽ��)
	static void Orthogonal(GD3Point * p);
	//����ͼ,yoz
	static void MainView(GD3Point * p);
	//����ͼ,yoz
	static void SideView(GD3Point * p);
	//����ͼ,yoz
	static void TopView(GD3Point * p);
	//����ͼ�Ľ����yozƽ���ڣ�������Ҫת����xoyƽ����ʾ����˽���X,Z��
	static void SwapXandZ(GD3Point * p);
	//бͶӰ,ͶӰб��aAngle,Խ��Խ�ӽ�����ͶӰ��0-PI/2,ͶӰ��x��н�bAngle,Ҳ�ǹ��շ���0-2*PI,xoy
	static void Oblique(GD3Point * p, double aAngle, double bAngle);

	//͸��ͶӰ,��������ϵת�۲�����ϵ,�Ӿ�R,z��Ƕ�aAngle��ˮƽ�нǣ�0-2*PI,y��Ƕ�bAngle����ֱ�нǣ�0-PI
	static void WorldOrgToViewOrg(GD3Point * p, double R, double aAngle, double bAngle);
	//�۲�����ϵת��Ļ����ϵ���Ӿ�d:�ӵ㵽���ĵľ���,xoy
	static void ViewOrgToScreenOrg(GD3Point * p, double d);
	//��������ϵת��Ļ����ϵ���Ӿ�R,�Ӿ�d��z��Ƕ�a,y��Ƕ�b,xoy
	static void WorldOrgToScreenOrg(GD3Point * p, double R, double d, double aAngle, double bAngle);

	//һ��͸��,xoy
	static void OnePoint(GD3Point * p, double R, double d);
	//����͸��,xoy
	static void TwoPoint(GD3Point * p, double R, double d);
	//����͸��,xoy
	static void ThreePoint(GD3Point * p, double R, double d);

	/*�۲�����ϵת������ȵ���Ļ����ϵ��
	�����ͷ�Ľ�����Զ��
	������Near������������ľ��룬ԽСԽģ����
	Զ����Far��һ��ָ������ֱ�ߵ�ͼ���ڴ˴���Ϊ���,���ڴ�ֵʱ������ģ��,
	�޸ĺ�Ϊ��ά��Ļ����,z��ʶα���
	*/
	static void ViewOrgToDeepScreenD3Org(GD3Point * p, double d, double Near, double Far);
};

#endif // _GPROJECTION_H_