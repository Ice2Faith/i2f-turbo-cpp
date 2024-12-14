/** Name: StrategyMod*/
#include<iostream>

using namespace std;
/*
策略模式：
通过一些方法，进行替换的方法实现，实现统一的调用（算法）方法
而实际的运行是根据实际设置运行，有点类似开闭原则
*/
class WeaponStrategy
{
public:
	virtual void UseWeapon() = 0;
};
class Knife : public WeaponStrategy
{
public:
	virtual void UseWeapon()
	{
		cout << "Use Knife" << endl;
	}
};
class Gang : public WeaponStrategy
{
public:
	virtual void UseWeapon()
	{
		cout << "Use Gang" << endl;
	}
};
class People
{
public:
	void setWeapon(WeaponStrategy * weapon)
	{
		this->weapon = weapon;
	}
	void Fitting()
	{
		weapon->UseWeapon();
	}
private:
	WeaponStrategy * weapon;
};
void test()
{
	People * p = new People();
	Knife * kf = new Knife();
	p->setWeapon(kf);
	p->Fitting();
	delete kf;
	Gang * ga = new Gang();
	p->setWeapon(ga);
	p->Fitting();
	delete ga;
	delete p;
}
int main(int argc, char * argv[])
{
	test();
	system("pause");
	return 0;
}