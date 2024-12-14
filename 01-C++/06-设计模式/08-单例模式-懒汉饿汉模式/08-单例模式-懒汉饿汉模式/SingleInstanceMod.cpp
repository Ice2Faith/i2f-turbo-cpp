#include<iostream>
using namespace std;
/*
单例模式：
保证整个系统中只会有一个对象被创建，无法创建其他对象
有懒汉和饿汉两种实现方式
具体为：
构造函数私有化，让外部无法进行创建对象，
提供静态方法获得实例的接口
自己类型的私有属性进行静态初始化
对象的我释放方式：
一般来说，采用单例模式之后，不考虑释放的问题，因为程序运行结束之后会自动释放
也可以强行设置释放，通过内部类析构调用析构的方式实现的方式实现
*/
class LazyMan
{
private:
	LazyMan(){ 
		cout << "Lazy Man" << endl;
	}//构造函数私有化
public:
	static LazyMan * GetInstance()//提供访问方式
	{
		if (layman == NULL)
			layman = new LazyMan();//懒汉模式，只在需要时创建
		return layman;
	}
	
private:
	static LazyMan * layman;
	class GarbegeCollecton//程序结束时创建的对象会自动调用析构函数
	{
	public:
		~GarbegeCollecton()
		{
			if (layman != NULL)
				delete layman;
		}
	};
	static GarbegeCollecton  gc;//程序结束时，自动调用其析构，实现直接释放，显然多此一举
};
LazyMan * LazyMan::layman=NULL;

class HungryMan
{
private:
	HungryMan(){
		cout << "Hungry man" << endl;
	};
public:
	static HungryMan * GetInstance()//饿汉模式，类加载时就创建了示例
	{
		return hunman;
	}
private:
	static HungryMan * hunman;
};
HungryMan * HungryMan::hunman = new HungryMan();

int main()
{
	LazyMan * lay = LazyMan::GetInstance();
	system("pause");
	return 0;
}