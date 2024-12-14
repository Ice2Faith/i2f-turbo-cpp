/** Name: ModelMethodMod*/
#include<iostream>

using namespace std;
/*
模板方法模式：
对于算法实现部分，如果算法实现大体相同，则算法实现在父类进行实现
算法的细节，由子类继承之后进行具体实现，这样就实现算法的通用性个偏特化分离
比如做饭为例：
*/
class AbstractCook
{
public:
	virtual void ReadyFood() = 0;
	virtual void CleanFood() = 0;
	virtual void CookFood() = 0;
	virtual void MoveToDesk() = 0;
	void Cook() 
	{
		ReadyFood();
		CleanFood();
		CookFood();
		MoveToDesk();
	}

};
class CookRice :public AbstractCook
{
public:
	virtual void ReadyFood()
	{
		cout << "准备大米" << endl;
	}
	virtual void CleanFood()
	{
		cout << "清洗大米" << endl;
	}
	virtual void CookFood()
	{
		cout << "烹饪大米" << endl;
	}
	virtual void MoveToDesk()
	{
		cout << "出锅上饭" << endl;
	}
};
class CookFish :public AbstractCook
{
public:
	virtual void ReadyFood()
	{
		cout << "准备鱼儿" << endl;
	}
	virtual void CleanFood()
	{
		cout << "刮去鱼鳞" << endl;
	}
	virtual void CookFood()
	{
		cout << "清煮收汁" << endl;
	}
	virtual void MoveToDesk()
	{
		cout << "出锅上菜" << endl;
	}
};
int main(int argc, char * argv[])
{
	CookRice * cr = new CookRice();
	cr->Cook();
	delete cr;
	CookFish * cf = new CookFish();
	cf->Cook();
	delete cf;
	system("pause");
	return 0;
}