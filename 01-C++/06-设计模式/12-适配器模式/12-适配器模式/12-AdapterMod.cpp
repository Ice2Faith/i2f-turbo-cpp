/** Name: `AdapterMode*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
/*
适配器模式：
通过适配器，适配接口参数数量
*/
//目标接口，需要传递两个参数
class TargetPrint
{
public:
	void operator()(int v1, int v2)
	{
		cout << v1 << ":" << v2 << endl;
	}
};
//构造接口转换接口
class TargetInterface
{
public:
	virtual void operator()(int v) = 0;
};
class Adapter :public TargetInterface
{
public:
	Adapter(int val2)
	{
		this->val2 = val2;
	}
	virtual void operator()(int v)//完成目标接口的转换
	{
		tar(v,val2);//适配成为目标接口
	}
private:
	TargetPrint tar;
	int val2;
};
Adapter MyPrint(int v)//使用绑定函数进行绑定
{
	return Adapter(v);
}
int main(int argc, char * argv[])
{
	vector<int> vec;
	for (int i = 0; i < 10;i++)
		vec.push_back(i);
	for_each(vec.begin(), vec.end(), MyPrint(10));//进行了接口转换，单参数到双参数
	system("pause");
	return 0;
}