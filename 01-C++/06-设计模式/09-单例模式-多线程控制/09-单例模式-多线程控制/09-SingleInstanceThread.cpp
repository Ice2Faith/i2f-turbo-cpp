#include<iostream>
using namespace std;
/*
����ģʽ�Ͷ��̣߳�
����ʽ�������߳����̲߳���ȫ�ģ��п��ܴ������ʵ��
����ʽ�������߳����̰߳�ȫ�ģ�ֻ����һ��ʵ��
*/
class Adder
{
private:
	Adder(){
		cout << "Adder" << endl;
	}//���캯��˽�л�
public:
	static Adder * GetInstance()//�ṩ���ʷ�ʽ
	{
		if (adder == NULL)//���߳�ʱ���ܻᵼ���ж�ͬһʱ�䶼Ϊ��
			adder = new Adder();//����ģʽ��ֻ����Ҫʱ����
		return adder;
	}

private:
	static Adder * adder;
};
Adder * Adder::adder = NULL;



int main()
{
	Adder * lay = Adder::GetInstance();
	system("pause");
	return 0;
}