/** Name: Test*/
#include<stdio.h>
#include"PhysicalReflect.h"
using namespace PhysicalReflect;
int main(int argc, char * argv[])
{
	Point sPoint(10, 40);
	double length = 15;
	double direct = AngleToRadian(60);
	Point ePoint = getEndPoint(sPoint.x, sPoint.y, length, direct);
	Point rPoint = getStartPoint(ePoint.x, ePoint.y, length, direct);
	printf("%.2lf %.2lf\n",ePoint.x , ePoint.y);
	printf("%.2lf %.2lf\n",rPoint.x , rPoint.y);

	double inAngle = 180 + 60;
	double flatAngle = 120;
	double nflatAngle = ((int)(flatAngle + 180)) % 360;
	double outAngle = RadianToAlgle(
		getReflectRadian(
			AngleToRadian(inAngle), 
			AngleToRadian(flatAngle)
			)
		);
	double noutAngle = RadianToAlgle(
		getReflectRadian(
			AngleToRadian(inAngle),
			AngleToRadian(nflatAngle)
			)
		);
	printf("%.2lf V %.2lf ==> %.2lf\n",inAngle, flatAngle ,outAngle);
	printf("%.2lf V %.2lf ==> %.2lf\n",inAngle, nflatAngle, noutAngle);

	printf("please input any key to exit.");
	getchar();
	return 0;
}