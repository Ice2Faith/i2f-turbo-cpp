#ifndef _ALGO_GRAPHICS_HPP_
#define _ALGO_GRAPHICS_HPP_

#include<math.h>
#include<stdlib.h>
#define ALGO_MATH_PI 3.141592653549
/*
微分插值模板函数：
参数：
开始插值	start
结束插值	end
微分率		rate
返回值：
插值的值
描述：
微分差值，是指微分率在[0-1]区间变化，给定插值区间和微分率之后，
给出当前微分率对应的插值
微分率越低越接近开始插值，越大越接近结束插值
常常用于给定两点确定直线的某一个微分点
*/
template<typename T, typename E>
T AlgoSmooth(T start, T end, E rate)
{
	return start + rate*(end - start);
}

/*
透明计算模板函数：
参数：
前端颜色	front
后端颜色	behind
透明率		rate
返回值：
混合之后的颜色
描述：
透明计算，原本用于计算机图形学中，计算一个透明材质透明之后，显示
材质本身颜色与后端隐藏物颜色的混合颜色
常常用于参数的混合
*/
template<typename T, typename E>
T AlgoTransparent(T front, T behind, E rate)
{
	return front*rate + behind*(1.0 - rate);
}
/*
获取两点构成直线的弧度
*/
template<typename T>
double AlgoGetLineDirection(T x1, T y1, T x2, T y2)
{
	return atan2(y2 - y1*1.0, x2 - x1*1.0);
}
/*
获取两点之间的距离
*/
template<typename T>
double AlgoGetDistance(T x1, T y1, T x2, T y2)
{
	return sqrt(pow(x2 - x1*1.0, 2.0) + pow(y2 - y1*1.0, 2.0));
}
/*
角度制转弧度制
*/
template<typename T>
double AlgoAngleToRadian(T angle)
{
	return angle / 180.0*ALGO_MATH_PI;
}
/*
弧度制转角度制
*/
template<typename T>
double AlgoRadianToAngle(T radian)
{
	return radian / ALGO_MATH_PI*180.0;
}
/*
计算相对于起点的距离一定长度在某个方向上的终点坐标
*/
template<typename T, typename E>
void AlgoGetEndPoint(T ix, T iy, E length, double direct, T * ox, T * oy)
{
	*ox = ix + length*cos(direct);
	*oy = iy + length*sin(direct);
}
/*
将点移动到距离一定长度的某个方向上的坐标去
*/
template<typename T, typename E>
void AlgoMovePoint(T * iox, T * ioy, E length, double direct)
{
	*iox = (*iox) + length*cos(direct);
	*ioy = (*ioy) + length*sin(direct);
}
/*
移动点到x,y分量偏移的坐标去
*/
template<typename T, typename E>
void AlgoMovePoint(T * iox, T * ioy, E dx, E dy)
{
	*iox = (*iox) + dx;
	*ioy = (*ioy) + dy;
}
/*
标准化起始坐标，无论是右上到左下还是左下到右上还是其他方向，
统一归一化到左上到右下
*/
template<typename T>
void AlgoStdSEPoints(T * sx, T * sy, T * ex, T * ey)
{
	T minX = (*sx) < (*ex) ? (*sx) : (*ex);
	T minY = (*sy) < (*ey) ? (*sy) : (*ey);
	T maxX = (*sx) > (*ex) ? (*sx) : (*ex);
	T maxY = (*sy) > (*ey) ? (*sy) : (*ey);
	*sx = minX;
	*sy = minY;
	*ex = maxX;
	*ey = maxY;
}

/**
* 获取传入角度的规范化角度【0-360】
* @param angle 待规范的角度
* @return 已经规范的角度
*/
double AlgoGetRegularAngle(double angle)
{
	int limitControl = 100;
	return ((int)angle*limitControl) % (360 * limitControl)*1.0 / limitControl;
}

/**
* 获取传入弧度的规范化弧度【0-2*PI】
* @param radian 待规范的弧度
* @return 已经规范的弧度
*/
double AlgoGetRegularRadian(double radian)
{
	double angle = AlgoRadianToAngle(radian);
	return AlgoAngleToRadian(AlgoGetRegularAngle(angle));
}

/**
* 计算反射角（弧度计算）
* @param inRadian 入射弧度
* @param flatRadian 反射平面弧度
* @return 反射弧度
*/
double AlgoGetReflectRadian(double inRadian, double flatRadian)
{
	double i = AlgoGetRegularRadian(inRadian);
	double mi = AlgoGetRegularRadian(flatRadian);
	//double a=i-mi+2*PI;
	//return AlgoGetRegularRadian((i+PI)+2*(PI/2-a));
	return AlgoGetRegularRadian(-i + 2 * mi);
}

template<typename T>
class AlgoPoint2
{
public:
	T x;
	T y;
	AlgoPoint2()
	{
		this->x = 0;
		this->y = 0;
	}
	AlgoPoint2(T x, T y)
	{
		this->x = x;
		this->y = y;
	}
	AlgoPoint2(const AlgoPoint2 & p)
	{
		this->x = p.x;
		this->y = p.y;
	}
	AlgoPoint2 & operator=(const AlgoPoint2 & p)
	{
		this->x = p.x;
		this->y = p.y;

		return *this;
	}
	AlgoPoint2 & move(T dx, T dy)
	{
		this->x += dx;
		this->y += dy;
		return *this;
	}
	AlgoPoint2 & move(T len, double direct)
	{
		this->x += len*cos(direct);
		this->y += len*sin(direct);
		return *this;
	}
	AlgoPoint2 & move(const AlgoPoint2 & p)
	{
		this->x += p.x;
		this->y += p.y;
		return *this;
	}
	AlgoPoint2 & operator+(const AlgoPoint2 & p)
	{
		this->x += p.x;
		this->y += p.y;
		return *this;
	}
	AlgoPoint2 & operator-(const AlgoPoint2 & p)
	{
		this->x -= p.x;
		this->y -= p.y;
		return *this;
	}
	AlgoPoint2 & operator*(const AlgoPoint2 & p)
	{
		this->x *= p.x;
		this->y *= p.y;
		return *this;
	}
	AlgoPoint2 & operator/(const AlgoPoint2 & p)
	{
		this->x /= p.x*1.0;
		this->y /= p.y*1.0;
		return *this;
	}
	AlgoPoint2 & operator+=(const AlgoPoint2 & p)
	{
		this->x += p.x;
		this->y += p.y;
		return *this;
	}
	AlgoPoint2 & operator-=(const AlgoPoint2 & p)
	{
		this->x -= p.x;
		this->y -= p.y;
		return *this;
	}
	AlgoPoint2 & operator*=(const AlgoPoint2 & p)
	{
		this->x *= p.x;
		this->y *= p.y;
		return *this;
	}
	AlgoPoint2 & operator/=(const AlgoPoint2 & p)
	{
		this->x /= p.x*1.0;
		this->y /= p.y*1.0;
		return *this;
	}
};

template<typename T>
class AlgoSize2
{
public:
	T width;
	T height;
	AlgoSize2()
	{
		this->width = 0;
		this->height = 0;
	}
	AlgoSize2(T wid, T hei)
	{
		this->width = wid;
		this->height = hei;
	}
	AlgoSize2& operator=(const AlgoSize2 & s)
	{
		this->width = s.width;
		this->height = s.height;
		return *this;
	}
	AlgoSize2& operator+(const AlgoSize2 &s)
	{
		this->width += s.width;
		this->height += s.height;
		return *this;
	}
	AlgoSize2& operator+=(const AlgoSize2 &s)
	{
		this->width += s.width;
		this->height += s.height;
		return *this;
	}
	AlgoSize2& operator-(const AlgoSize2 &s)
	{
		this->width -= s.width;
		this->height -= s.height;
		return *this;
	}
	AlgoSize2& operator-=(const AlgoSize2 &s)
	{
		this->width -= s.width;
		this->height -= s.height;
		return *this;
	}
};

template<typename T,typename E>
class AlgoRect2
{
public:
	AlgoPoint2<T> point;
	AlgoSize2<E> size;
	AlgoRect2()
	{

	}
	AlgoRect2(const AlgoPoint2<T> & point)
	{
		this->point = point;
	}
	AlgoRect2(T x, T y, E wid, E hei)
	{
		point.x = x;
		point.y = y;
		size.width = wid;
		size.height = hei;
	}
	AlgoRect2(T x1, T y1, T x2, T y2)
	{
		point.x = x1;
		point.y = y1;
		size.width = x2-x1;
		size.height = y2-y1;
	}
	AlgoRect2(const AlgoSize2<E> & size)
	{
		this->size = size;
	}
	AlgoRect2(const AlgoPoint2<T> & point, const AlgoSize2<E> & size)
	{
		this->point = point;
		this->size = size;
	}
	T top()
	{
		return y;
	}
	T left()
	{
		return x;
	}
	T bottom()
	{
		return y + size.height;
	}
	T right()
	{
		return x + size.width;
	}
	E getArea()
	{
		return size.width*size.height;
	}
};

template<typename T>
class AlgoLine2
{
public:
	AlgoPoint2<T> p1;
	AlgoPoint2<T> p2;
	AlgoLine2()
	{

	}
	AlgoLine2(const AlgoPoint2<T> & p1, const AlgoPoint2<T> & p2)
	{
		this->p1 = p1;
		this->p2 = p2;
	}
	AlgoLine2(T x1, T y1, T x2, T y2)
	{
		p1.x = x1;
		p1.y = y1;
		p2.x = x2;
		p2.y = y2;
	}
	AlgoLine2(const AlgoLine2<T> & line)
	{
		this->p1 = line.p1;
		this->p2 = line.p2;
	}
	AlgoLine2& operator=(const AlgoLine2 & line)
	{
		this->p1 = line.p1;
		this->p2 = line.p2;
		return *this;
	}
	double getLength()
	{
		return (double)(sqrt(pow(x2-x1*1.0,2.0)+pow(y2-y1*1.0,2.0)));
	}
	double getDirection()
	{
		return (double)(atan2(y2-y1*1.0,x2-x1*1.0));
	}
};

template<typename T>
class AlgoVector2
{
public:
	T dx;
	T dy;
	AlgoVector2()
	{
		dx = 0;
		dy = 0;
	}
	AlgoVector2(const AlgoVector2 & vec)
	{
		this->dx = vec.dx;
		this->dy = vec.dy;
	}
	AlgoVector2(const AlgoLine<T> & line)
	{
		this->dx = line.p2.x - line.p1.x;
		this->dy = line.p2.y - line.p1.y;
	}
	AlgoVector2(const AlgoPoint2<T> & p1, const AlgoPoint2<T> & p2)
	{
		this->dx = p2.x - p1.x;
		this->dy = p2.y - p1.y;
	}
	AlgoVector2(T x1, T y1, T x2, T y2)
	{
		this->dx = x2 - x1;
		this->dy = y2 - y1;
	}
	double getModuleLength()
	{
		return (double)(sqrt(dx*dx+dy*dy*1.0);
	}
	AlgoVector2& untization()
	{
		double mod = getModuleLength();
		this->dx /= mod;
		this->dy /= mod;
		return *this;
	}
	AlgoVector2& operator+(const AlgoVector2 & vec)
	{
		this->dx += vec.dx;
		this->dy += vec.dy;
		return *this;
	}
	double operator*(const AlgoVector2 & vec)
	{
		return (double)(this->dx*vec.dx+this->dy*vec.dy);
	}
	double cosRadian(const AlgoVector2 & vec)
	{
		return (double)((*this)*vec / (this->getModuleLength()*vec.getModuleLength()));
	}
	AlgoVector2 getNormalVector()
	{
		AlgoVector2 ret;
		ret.dx = 1;
		ret.dy = ((0.0-(this->dx*ret.dx)) / (this->dy*1.0));
		return ret;
	}
};

template<typename T>
class AlgoPoint3
{
public:
	T x;
	T y;
	T z;
	AlgoPoint3()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	AlgoPoint3(T x, T y,T z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	AlgoPoint3(const AlgoPoint3 & p)
	{
		this->x = p.x;
		this->y = p.y;
		this->z = p.z;
	}
	AlgoPoint3 & operator=(const AlgoPoint3 & p)
	{
		this->x = p.x;
		this->y = p.y;
		this->z = p.z;
		return *this;
	}
	AlgoPoint3 & move(T dx, T dy,T dz)
	{
		this->x += dx;
		this->y += dy;
		this->z += dz;
		return *this;
	}
	AlgoPoint3 & move(const AlgoPoint3 & p)
	{
		this->x += p.x;
		this->y += p.y;
		this->z += p.z;
		return *this;
	}
	AlgoPoint3 & operator+(const AlgoPoint3 & p)
	{
		this->x += p.x;
		this->y += p.y;
		this->z += p.z;
		return *this;
	}
	AlgoPoint3 & operator-(const AlgoPoint3 & p)
	{
		this->x -= p.x;
		this->y -= p.y;
		this->z -= p.z;
		return *this;
	}
	AlgoPoint3 & operator*(const AlgoPoint3 & p)
	{
		this->x *= p.x;
		this->y *= p.y;
		this->z *= p.z;
		return *this;
	}
	AlgoPoint3 & operator/(const AlgoPoint3 & p)
	{
		this->x /= p.x*1.0;
		this->y /= p.y*1.0;
		this->z /= p.z*1.0;
		return *this;
	}
	AlgoPoint3 & operator+=(const AlgoPoint3 & p)
	{
		this->x += p.x;
		this->y += p.y;
		this->z += p.z;
		return *this;
	}
	AlgoPoint3 & operator-=(const AlgoPoint3 & p)
	{
		this->x -= p.x;
		this->y -= p.y;
		this->z -= p.z;
		return *this;
	}
	AlgoPoint3 & operator*=(const AlgoPoint3 & p)
	{
		this->x *= p.x;
		this->y *= p.y;
		this->z *= p.z;
		return *this;
	}
	AlgoPoint3 & operator/=(const AlgoPoint3 & p)
	{
		this->x /= p.x*1.0;
		this->y /= p.y*1.0;
		this->z /= p.z*1.0;
		return *this;
	}
	AlgoPoint3 & parseSpherical(double r, double aAngle, double bAngle)
	{
		this->x = r*sin(aAngle)*sin(bAngle);
		this->y = r*cos(aAngle);
		this->z = r*sin(aAngle)*cos(bAngle);
		return *this;
	}

};

template<typename T>
class AlgoVector3
{
public:
	T dx;
	T dy;
	T dz;
	AlgoVector3()
	{
		dx = 0;
		dy = 0;
		dz = 0;
	}
	AlgoVector3(const AlgoVector3 & vec)
	{
		this->dx = vec.dx;
		this->dy = vec.dy;
		this->dz = vec.dz;
	}
	AlgoVector3(const AlgoPoint3<T> & p1, const AlgoPoint3<T> & p2)
	{
		this->dx = p2.x - p1.x;
		this->dy = p2.y - p1.y;
		this->dz = p2.z - p1.z;
	}
	AlgoVector3(T x1, T y1,T z1, T x2, T y2,T z2)
	{
		this->dx = x2 - x1;
		this->dy = y2 - y1;
		this->dz = z2 - z1;
	}
	double getModuleLength()
	{
		return (double)(sqrt(dx*dx + dy*dy+dz*dz*1.0);
	}
	AlgoVector3& untization()
	{
		double mod = getModuleLength();
		this->dx /= mod;
		this->dy /= mod;
		this->dz /= mod;
		return *this;
	}
	AlgoVector3& operator+(const AlgoVector3 & vec)
	{
		this->dx += vec.dx;
		this->dy += vec.dy;
		this->dz += vec.dz;
		return *this;
	}
	double operator*(const AlgoVector3 & vec)
	{
		return (double)(this->dx*vec.dx + this->dy*vec.dy+this->dz*vec.dz);
	}

	double cosRadian(const AlgoVector3 & vec)
	{
		return (double)((*this)*vec / (this->getModuleLength()*vec.getModuleLength()));
	}
	AlgoVector3 xMul(const AlgoVector3 & vec)
	{
		AlgoVector3 ret;
		ret.dx = vec.dz*this->dy - vec.dy*this->dz;
		ret.dy = vec.dx*this->dz - vec.dz*this->dx;
		ret.dz = vec.dy*this->dx - vec.dx*this->dy;
		return ret;			 
	}
	AlgoVector3 getNormalLine(const AlgoVector3 & vec)
	{
		return xMul(vec);
	}
};
#endif // _ALGO_GRAPHICS_HPP_