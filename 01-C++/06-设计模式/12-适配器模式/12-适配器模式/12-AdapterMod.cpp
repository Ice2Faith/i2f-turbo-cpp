/** Name: `AdapterMode*/
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
/*
������ģʽ��
ͨ��������������ӿڲ�������
*/
//Ŀ��ӿڣ���Ҫ������������
class TargetPrint
{
public:
	void operator()(int v1, int v2)
	{
		cout << v1 << ":" << v2 << endl;
	}
};
//����ӿ�ת���ӿ�
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
	virtual void operator()(int v)//���Ŀ��ӿڵ�ת��
	{
		tar(v,val2);//�����ΪĿ��ӿ�
	}
private:
	TargetPrint tar;
	int val2;
};
Adapter MyPrint(int v)//ʹ�ð󶨺������а�
{
	return Adapter(v);
}
int main(int argc, char * argv[])
{
	vector<int> vec;
	for (int i = 0; i < 10;i++)
		vec.push_back(i);
	for_each(vec.begin(), vec.end(), MyPrint(10));//�����˽ӿ�ת������������˫����
	system("pause");
	return 0;
}