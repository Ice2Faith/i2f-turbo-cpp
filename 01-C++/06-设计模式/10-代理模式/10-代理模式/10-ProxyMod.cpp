/** Name: ProxyMod*/
#include<iostream>

using namespace std;
/*
代理模式：
使用一个代理类，来接管任务，比如工厂直销（直接调用）和市场营销（代理调用）
需要有共同的接口实现，通过代理实现一些对象的权限控制和其他功能的限制等
对于用户来说，使用上不会感觉到什么不一样，毕竟接口是一样的
*/
class AbstractInterface //通用接口
{
public:
	virtual void Run() = 0;
};
class Goods : public AbstractInterface //真正的对象
{
public:
	virtual void Run()
	{
		cout << "goods run" << endl;
	}
};
class Proxyer :public AbstractInterface //代理人
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
		if (isAuthUser()) //通过代理人去验证是否拥有权限
			goods->Run(); //有权限才进行直接运行真正的对象
		else
			cout << "Not Auth Access!!" << endl; //没有权限就在代理上拒绝
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