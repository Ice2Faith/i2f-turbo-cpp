#include "PhysicalReflect.h"
namespace PhysicalReflect
{
	/**
	* 计算反射角（弧度计算）
	* @param inRadian 入射弧度
	* @param flatRadian 反射平面弧度
	* @return 反射弧度
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
	* 角度转弧度
	* @param angle 角度
	* @return 弧度
	*/

	double AngleToRadian(double angle)
	{
		return angle / 180.0*PI;
	}

	/**
	* 弧度转角度
	* @param radian 弧度
	* @return 角度
	*/
	double RadianToAlgle(double radian)
	{
		return radian / PI*180.0;
	}

	/**
	* 根据直线的两点计算直线的弧度
	* @param x1 起始点x
	* @param y1 起始点y
	* @param x2 结束点x
	* @param y2 结束点y
	* @return 该直线的弧度
	*/
	double getRadianFromLine(double x1, double y1, double x2, double y2)
	{
		return atan2(y2 - y1, x2 - x1);
	}

	/**
	* 获取传入角度的规范化角度【0-360】
	* @param angle 待规范的角度
	* @return 已经规范的角度
	*/
	double getRegularAngle(double angle)
	{
		int limitControl = 100;
		return ((int)angle*limitControl) % (360 * limitControl)*1.0 / limitControl;
	}

	/**
	* 获取传入弧度的规范化弧度【0-2*PI】
	* @param radian 待规范的弧度
	* @return 已经规范的弧度
	*/
	double getRegularRadian(double radian)
	{
		double angle = RadianToAlgle(radian);
		return AngleToRadian(getRegularAngle(angle));
	}

	/**
	* 根据线段的开始坐标方向和长度，计算结束坐标
	* @param startx 开始x
	* @param starty 开始y
	* @param length 线段长度
	* @param radian 线段弧度
	* @return 结束坐标
	*/
	Point getEndPoint(double startx, double starty, double length, double radian)
	{
		return Point(startx + length * cos(radian), starty + length * sin(radian));
	}

	/**
	* 根据线段的结束坐标方向和长度，计算开始坐标
	* @param endx 结束x
	* @param endy 结束y
	* @param length 线段长度
	* @param radian 线段弧度
	* @return 开始点坐标
	*/
	Point getStartPoint(double endx, double endy, double length, double radian)
	{
		return Point(endx - length * cos(radian), endy - +length * sin(radian));
	}

}