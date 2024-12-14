#pragma once
#include<math.h>
namespace PhysicalReflect
{
	/**
	* 内部点类，注意不要和安卓的绘图包中的点混用
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
	* 角度转弧度
	* @param angle 角度
	* @return 弧度
	*/

	double AngleToRadian(double angle);
		/**
		* 弧度转角度
		* @param radian 弧度
		* @return 角度
		*/
	double RadianToAlgle(double radian);
	/**
	* 根据直线的两点计算直线的弧度
	* @param x1 起始点x
	* @param y1 起始点y
	* @param x2 结束点x
	* @param y2 结束点y
	* @return 该直线的弧度
	*/
	double getRadianFromLine(double x1, double y1, double x2, double y2);
	/**
	* 获取传入角度的规范化角度【0-360】
	* @param angle 待规范的角度
	* @return 已经规范的角度
	*/
	double getRegularAngle(double angle);
	/**
	* 获取传入弧度的规范化弧度【0-2*PI】
	* @param radian 待规范的弧度
	* @return 已经规范的弧度
	*/
	double getRegularRadian(double radian);
	/**
	* 计算反射角（弧度计算）
	* @param inRadian 入射弧度
	* @param flatRadian 反射平面弧度
	* @return 反射弧度
	*/
	double getReflectRadian(double inRadian, double flatRadian);
	/**
	* 根据线段的开始坐标方向和长度，计算结束坐标
	* @param startx 开始x
	* @param starty 开始y
	* @param length 线段长度
	* @param radian 线段弧度
	* @return 结束坐标
	*/
	Point getEndPoint(double startx, double starty, double length, double radian);
	/**
	* 根据线段的结束坐标方向和长度，计算开始坐标
	* @param endx 结束x
	* @param endy 结束y
	* @param length 线段长度
	* @param radian 线段弧度
	* @return 开始点坐标
	*/
	Point getStartPoint(double endx, double endy, double length, double radian);
}



