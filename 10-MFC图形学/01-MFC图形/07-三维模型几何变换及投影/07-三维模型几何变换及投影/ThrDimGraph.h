#ifndef _THRDIMGRAPH_H_
#define _THRDIMGRAPH_H_
#include<math.h>
//x,y,zΪ��ά����㣬�����ַ�������޸�ֵ
//��4*4��ά�任����
void GraphMulVaryMatrix(double * x,double * y,double * z,double matrix[][4]);
//ƽ�Ʊ任��x,y,z�ֱ�ƽ��mx,my,mz����
void GraphMove(double * x,double * y,double * z,double mx,double my,double mz);
//�����任��x,y,z�ֱ����sx,sy,sz����
void GraphScale(double * x,double * y,double * z,double sx,double sy,double sz);
//��ת�任������������x,y,z����תsx,sy,sz�Ƕȣ������ƣ�
void GraphSpin(double * x,double * y,double * z,double sx,double sy,double sz);
//����任���������ζ�x,y,z�ᷴ�䣬�����Ӧ��bx,by,bzֵΪ�棬��������
void GraphReflact(double * x,double * y,double * z,bool bx,bool by,bool bz);
//����任���������ζ�xoy,yoz,xozƽ�淴�䣬�����Ӧ��xoy,yoz,xozֵΪ�棬��������
void GraphFlatReflact(double * x,double * y,double * z,bool bxoy,bool byoz,bool bxoz);
//���б任������������x,y,z����У��ֱ��뿪z,y����x���ƶ�gz,dy���룬��������
void GraphMiscut(double * x,double * y,double * z,double xgz,double xdy,double yhz,double ybx,double zfy,double zcx);

//����ϵ�ƶ��任��x,y,z�ֱ�Ϊ����ϵƽ��mx,my,mz���λ��
void OrgMove(double * x,double * y,double * z,double mx,double my,double mz);
//����ϵ��ת�任������ϵ������x,y,z����תsx,sy,sz�Ƕȣ������ƣ����λ��
void OrgSpin(double * x,double * y,double * z,double sx,double sy,double sz);
//����ϵ����任��ֱ�Ӳ��õ�任��ʽ
void OrgReflact(double * x,double * y,double * z,bool bx,bool by,bool bz);
void OrgFlatReflact(double * x,double * y,double * z,bool bxoy,bool byoz,bool bxoz);

//����ͶӰ��ֱ��ȥ��z�ᣬxoy
void ProjOrthogonal(double * x,double * y,double * z);
//����ͼ,yoz
void ProjMainView(double * x,double * y,double * z);
//����ͼ,yoz
void ProjSideView(double * x,double * y,double * z);
//����ͼ,yoz
void ProjTopView(double * x,double * y,double * z);
//бͶӰ,ͶӰб��a,ͶӰ��x��н�b,xoy
void ProjOblique(double * x,double * y,double * z,double a,double b);

//͸��ͶӰ,��������ϵת�۲�����ϵ,�Ӿ�R,z��Ƕ�a,y��Ƕ�b
void ProjWorldOrgToViewOrg(double * x,double * y,double * z,double R,double a,double b);
//�۲�����ϵת��Ļ����ϵ���Ӿ�d,xoy
void ProjViewOrgToScreenOrg(double * x,double * y,double * z,double d);
//��������ϵת��Ļ����ϵ���Ӿ�R,�Ӿ�d��z��Ƕ�a,y��Ƕ�b,xoy
void ProjWorldOrgToScreenOrg(double * x,double * y,double * z,double R,double d,double a,double b);

//һ��͸��,xoy
void ProjOnePoint(double * x,double * y,double * z,double R,double d);
//����͸��,xoy
void ProjTwoPoint(double * x,double * y,double * z,double R,double d);
//����͸��,xoy
void ProjThreePoint(double * x,double * y,double * z,double R,double d);

//�۲�����ϵת������ȵĹ۲�����ϵ��������Near��Զ����Far,�޸ĺ�Ϊ��ά��Ļ����
void ProjViewOrgToDeepScreenD3Org(double * x,double * y,double * z,double d,double Near,double Far);

#endif // _THRDIMGRAPH_H_
