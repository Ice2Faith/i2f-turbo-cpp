#include<iostream>
using namespace std;
/*
单例模式和多线程：
懒汉式碰到多线程是线程不安全的，有可能创建多个实例
饿汉式碰到多线程是线程安全的，只会有一个实例
*/
class Adder
{
private:
	Adder(){
		cout << "Adder" << endl;
	}//构造函数私有化
public:
	static Adder * GetInstance()//提供访问方式
	{
		if (adder == NULL)//多线程时可能会导致判定同一时间都为真
			adder = new Adder();//懒汉模式，只在需要时创建
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