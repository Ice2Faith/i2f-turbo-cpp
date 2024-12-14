#pragma once
#include<math.h>
namespace PhysicalReflect
{
	/**
	* �ڲ����࣬ע�ⲻҪ�Ͱ�׿�Ļ�ͼ���еĵ����
	*/
	class Point{
	public:
		double x;
		double y;
		Point(double x, double y){
			this->x = x;
			this->y = y;
		}
	};

	double const PI = 3.141592653549;
	/**
	* �Ƕ�ת����
	* @param angle �Ƕ�
	* @return ����
	*/

	double AngleToRadian(double angle);
		/**
		* ����ת�Ƕ�
		* @param radian ����
		* @return �Ƕ�
		*/
	double RadianToAlgle(double radian);
	/**
	* ����ֱ�ߵ��������ֱ�ߵĻ���
	* @param x1 ��ʼ��x
	* @param y1 ��ʼ��y
	* @param x2 ������x
	* @param y2 ������y
	* @return ��ֱ�ߵĻ���
	*/
	double getRadianFromLine(double x1, double y1, double x2, double y2);
	/**
	* ��ȡ����ǶȵĹ淶���Ƕȡ�0-360��
	* @param angle ���淶�ĽǶ�
	* @return �Ѿ��淶�ĽǶ�
	*/
	double getRegularAngle(double angle);
	/**
	* ��ȡ���뻡�ȵĹ淶�����ȡ�0-2*PI��
	* @param radian ���淶�Ļ���
	* @return �Ѿ��淶�Ļ���
	*/
	double getRegularRadian(double radian);
	/**
	* ���㷴��ǣ����ȼ��㣩
	* @param inRadian ���仡��
	* @param flatRadian ����ƽ�满��
	* @return ���仡��
	*/
	double getReflectRadian(double inRadian, double flatRadian);
	/**
	* �����߶εĿ�ʼ���귽��ͳ��ȣ������������
	* @param startx ��ʼx
	* @param starty ��ʼy
	* @param length �߶γ���
	* @param radian �߶λ���
	* @return ��������
	*/
	Point getEndPoint(double startx, double starty, double length, double radian);
	/**
	* �����߶εĽ������귽��ͳ��ȣ����㿪ʼ����
	* @param endx ����x
	* @param endy ����y
	* @param length �߶γ���
	* @param radian �߶λ���
	* @return ��ʼ������
	*/
	Point getStartPoint(double endx, double endy, double length, double radian);
}



