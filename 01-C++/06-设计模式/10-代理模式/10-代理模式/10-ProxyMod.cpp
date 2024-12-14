/** Name: ProxyMod*/
#include<iostream>

using namespace std;
/*
����ģʽ��
ʹ��һ�������࣬���ӹ����񣬱��繤��ֱ����ֱ�ӵ��ã����г�Ӫ����������ã�
��Ҫ�й�ͬ�Ľӿ�ʵ�֣�ͨ������ʵ��һЩ�����Ȩ�޿��ƺ��������ܵ����Ƶ�
�����û���˵��ʹ���ϲ���о���ʲô��һ�����Ͼ��ӿ���һ����
*/
class AbstractInterface //ͨ�ýӿ�
{
public:
	virtual void Run() = 0;
};
class Goods : public AbstractInterface //�����Ķ���
{
public:
	virtual void Run()
	{
		cout << "goods run" << endl;
	}
};
class Proxyer :public AbstractInterface //������
{
public:
	Proxyer(string name, string pwd)
	{
		uname = name;
		upwd = pwd;
		goods = new Goods();
	}
	virtual void Run()
	{
		if (isAuthUser()) //ͨ��������ȥ��֤�Ƿ�ӵ��Ȩ��
			goods->Run(); //��Ȩ�޲Ž���ֱ�����������Ķ���
		else
			cout << "Not Auth Access!!" << endl; //û��Ȩ�޾��ڴ����Ͼܾ�
	}
private:
	bool isAuthUser()
	{
		if (uname == "user" && upwd == "admin")
			return true;
		return false;
	}
	string uname;
	string upwd;
	Goods * goods;
};

int main(int argc, char * argv[])
{
	Proxyer * p = new Proxyer("user","123");
	p->Run();
	system("pause");
	return 0;
}