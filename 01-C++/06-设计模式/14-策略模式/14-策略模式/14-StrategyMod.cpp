/** Name: StrategyMod*/
#include<iostream>

using namespace std;
/*
����ģʽ��
ͨ��һЩ�����������滻�ķ���ʵ�֣�ʵ��ͳһ�ĵ��ã��㷨������
��ʵ�ʵ������Ǹ���ʵ���������У��е����ƿ���ԭ��
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