/** Name: ModelMethodMod*/
#include<iostream>

using namespace std;
/*
ģ�巽��ģʽ��
�����㷨ʵ�ֲ��֣�����㷨ʵ�ִ�����ͬ�����㷨ʵ���ڸ������ʵ��
�㷨��ϸ�ڣ�������̳�֮����о���ʵ�֣�������ʵ���㷨��ͨ���Ը�ƫ�ػ�����
��������Ϊ����
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
		cout << "׼������" << endl;
	}
	virtual void CleanFood()
	{
		cout << "��ϴ����" << endl;
	}
	virtual void CookFood()
	{
		cout << "��⿴���" << endl;
	}
	virtual void MoveToDesk()
	{
		cout << "�����Ϸ�" << endl;
	}
};
class CookFish :public AbstractCook
{
public:
	virtual void ReadyFood()
	{
		cout << "׼�����" << endl;
	}
	virtual void CleanFood()
	{
		cout << "��ȥ����" << endl;
	}
	virtual void CookFood()
	{
		cout << "������֭" << endl;
	}
	virtual void MoveToDesk()
	{
		cout << "�����ϲ�" << endl;
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