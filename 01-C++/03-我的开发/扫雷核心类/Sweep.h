#ifndef _SWEEP_H_
#define _SWEEP_H_
/** _SWEEP_H_ :
*/
typedef int ELEM_TYPE;
#define ELEM_NULL 0		//空地形
#define ELEM_BOOM -1	//炸弹
#define ELEM_MASK 1		//未知地形
#define ELEM_NUMBER 2	//炸弹提示数字
#define ELEM_FLAG_BOOM 3	//被标记的炸弹
#define ELEM_FLAG_MASK 4	//被标记的未知地形
#include<stdlib.h>
#include<time.h>
typedef struct
{
	int line;
	int col;
}Point;
class Sweep
{
public:
	Sweep(int line=20,int col=20);
	~Sweep();
	int & MapAt(int rindex,int cindex);
	int GetLines();
	int GetCols();
	//获取元素类型
	ELEM_TYPE GetElemType(int elem);
	//false 打开地形，true 标记地形，返回false游戏结束
	bool Click(int rindex, int cindex,bool flag=false);
	void clear();
	//获取当前剩余标记数量
	int GetFlagCount();
	//获取最终得分，仅在游戏结束时有效
	int GetScore();
	//获取总共炸弹总数
	int GetBoomCount();
private:
	void CleanMap();
	void CreateBoom();
	void BuildMask();
	void BuildBoomNumber();
	void DisplayAllBoom();
	void DisplayNerVecant(int rindex, int cindex);
	bool AllKilled();
	int * Map;
	int Lines;
	int Cols;
	int BoomCount;
	int FlagCount;
	Point Buffer[1024];
	int BufferLen;
};

#endif // _SWEEP_H_