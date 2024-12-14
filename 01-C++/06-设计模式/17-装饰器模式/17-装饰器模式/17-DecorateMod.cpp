/** Name: DecorateMod*/
#include<iostream>

using namespace std;
/*
装饰器模式：
通过继承的方式，实现对现有功能的拓展
*/
//抽象英雄
class AbstractHero
{
public:
	virtual void ShowStatus() = 0;
public:
	int mHp;
	int mMp;
};
class HeroA :public AbstractHero
{
public:
	HeroA()
	{
		mHp = 0;
		mMp = 0;
	}
	virtual void ShowStatus()
	{
		cout << "血量：" << mHp << endl;
		cout << "蓝量：" << mMp << endl;
	}
};
//装饰抽象，装饰完还是一个英雄，所以要继承
class AbstractEquipment:public AbstractHero
{
public:
	AbstractEquipment(AbstractHero * hero)
	{
		this->phero = hero;
	}
	virtual void ShowStatus(){}
public:
	AbstractHero * phero;//原来的英雄
};
//实现类，实现穿上衣服的英雄
class ClothEquip :public AbstractEquipment
{
public:
	ClothEquip(AbstractHero * hero) :AbstractEquipment(hero)
	{

	}
	void AddCloth()//添加私有方法，穿上装备
	{
		this->mHp = this->phero->mHp;
		this->mMp = this->phero->mMp+5;
		cout << "英雄穿上新衣服" << endl;
	}
	virtual void ShowStatus()//重写父类抽象方法
	{
		cout << "血量：" << mHp << endl;
		cout << "蓝量：" << mMp << endl;
	}
};
void test()
{
	AbstractHero * he = new HeroA();
	he->ShowStatus();
	ClothEquip * ce = new ClothEquip(he);
	ce->AddCloth();
	AbstractEquipment * ae = ce;
	ae->ShowStatus();

}
int main(int argc, char * argv[])
{
	test();
	system("pause");
	return 0;
}