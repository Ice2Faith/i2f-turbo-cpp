#ifndef _GTRANGLELIZED_H_
#define _GTRANGLELIZED_H_
#include"GData.h"
#include<vector>
#include<iterator>
using namespace std;
typedef struct
{
	long index;
	double distance;
}DTSortStruct;
class GTeanglelized
{
public:
	static GD3DataGroup * PointsTranglelized(GD3DataGroup * dg);
private:
	static void SortDistanceUpper(vector<DTSortStruct> & sdv);
	static void SortPointYdesc(GD3DataGroup * dg);
};
#endif // _GTRANGLELIZED_H_
