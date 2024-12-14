#include "PhysicalReflect.h"
namespace PhysicalReflect
{
	/**
	* ���㷴��ǣ����ȼ��㣩
	* @param inRadian ���仡��
	* @param flatRadian ����ƽ�满��
	* @return ���仡��
	*/
	double getReflectRadian(double inRadian, double flatRadian)
	{
		double i = getRegularRadian(inRadian);
		double mi = getRegularRadian(flatRadian);
		//double a=i-mi+2*PI;
		//return getRegularRadian((i+PI)+2*(PI/2-a));
		return getRegularRadian(-i + 2 * mi);
	}

	/**
	* �Ƕ�ת����
	* @param angle �Ƕ�
	* @return ����
	*/

	double AngleToRadian(double angle)
	{
		return angle / 180.0*PI;
	}

	/**
	* ����ת�Ƕ�
	* @param radian ����
	* @return �Ƕ�
	*/
	double RadianToAlgle(double radian)
	{
		return radian / PI*180.0;
	}

	/**
	* ����ֱ�ߵ��������ֱ�ߵĻ���
	* @param x1 ��ʼ��x
	* @param y1 ��ʼ��y
	* @param x2 ������x
	* @param y2 ������y
	* @return ��ֱ�ߵĻ���
	*/
	double getRadianFromLine(double x1, double y1, double x2, double y2)
	{
		return atan2(y2 - y1, x2 - x1);
	}

	/**
	* ��ȡ����ǶȵĹ淶���Ƕȡ�0-360��
	* @param angle ���淶�ĽǶ�
	* @return �Ѿ��淶�ĽǶ�
	*/
	double getRegularAngle(double angle)
	{
		int limitControl = 100;
		return ((int)angle*limitControl) % (360 * limitControl)*1.0 / limitControl;
	}

	/**
	* ��ȡ���뻡�ȵĹ淶�����ȡ�0-2*PI��
	* @param radian ���淶�Ļ���
	* @return �Ѿ��淶�Ļ���
	*/
	double getRegularRadian(double radian)
	{
		double angle = RadianToAlgle(radian);
		return AngleToRadian(getRegularAngle(angle));
	}

	/**
	* �����߶εĿ�ʼ���귽��ͳ��ȣ������������
	* @param startx ��ʼx
	* @param starty ��ʼy
	* @param length �߶γ���
	* @param radian �߶λ���
	* @return ��������
	*/
	Point getEndPoint(double startx, double starty, double length, double radian)
	{
		return Point(startx + length * cos(radian), starty + length * sin(radian));
	}

	/**
	* �����߶εĽ������귽��ͳ��ȣ����㿪ʼ����
	* @param endx ����x
	* @param endy ����y
	* @param length �߶γ���
	* @param radian �߶λ���
	* @return ��ʼ������
	*/
	Point getStartPoint(double endx, double endy, double length, double radian)
	{
		return Point(endx - length * cos(radian), endy - +length * sin(radian));
	}

}