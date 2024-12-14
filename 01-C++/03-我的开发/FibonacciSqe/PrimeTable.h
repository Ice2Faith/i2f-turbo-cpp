#ifndef _PRIMETABLE_H_
#define _PRIMETABLE_H_
#include<deque>
#include<iterator>
using namespace std;
class PrimeTable
{
public:
	PrimeTable(int Length = 100);
	PrimeTable(int start,int end);
	PrimeTable(PrimeTable & table);
	PrimeTable& operator=(PrimeTable & table);
	bool IsPrimeNumber(int num);
	int operator[](int index);
	int Size();
	int Back();
	int Front();
	void Pop_front();
	void Pop_back();
	bool Empty();
	void Clear();
	void ReSize(int size);
	void ReStart(int start);
	bool In(int num);
	int ValueAtIndex(int index);
	int IndexAtValue(int num);
private:
	deque<int> m_table;
};

#endif // !_PRIMETABLE_H_
