#ifndef _SWEEP_H_
#define _SWEEP_H_
/** _SWEEP_H_ :
*/
typedef int ELEM_TYPE;
#define ELEM_NULL 0		//�յ���
#define ELEM_BOOM -1	//ը��
#define ELEM_MASK 1		//δ֪����
#define ELEM_NUMBER 2	//ը����ʾ����
#define ELEM_FLAG_BOOM 3	//����ǵ�ը��
#define ELEM_FLAG_MASK 4	//����ǵ�δ֪����
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
	//��ȡԪ������
	ELEM_TYPE GetElemType(int elem);
	//false �򿪵��Σ�true ��ǵ��Σ�����false��Ϸ����
	bool Click(int rindex, int cindex,bool flag=false);
	void clear();
	//��ȡ��ǰʣ��������
	int GetFlagCount();
	//��ȡ���յ÷֣�������Ϸ����ʱ��Ч
	int GetScore();
	//��ȡ�ܹ�ը������
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