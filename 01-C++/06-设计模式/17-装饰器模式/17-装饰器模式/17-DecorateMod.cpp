/** Name: DecorateMod*/
#include<iostream>

using namespace std;
/*
װ����ģʽ��
ͨ���̳еķ�ʽ��ʵ�ֶ����й��ܵ���չ
*/
//����Ӣ��
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
		cout << "Ѫ����" << mHp << endl;
		cout << "������" << mMp << endl;
	}
};
//װ�γ���װ���껹��һ��Ӣ�ۣ�����Ҫ�̳�
class AbstractEquipment:public AbstractHero
{
public:
	AbstractEquipment(AbstractHero * hero)
	{
		this->phero = hero;
	}
	virtual void ShowStatus(){}
public:
	AbstractHero * phero;//ԭ����Ӣ��
};
//ʵ���࣬ʵ�ִ����·���Ӣ��
class ClothEquip :public AbstractEquipment
{
public:
	ClothEquip(AbstractHero * hero) :AbstractEquipment(hero)
	{

	}
	void AddCloth()//���˽�з���������װ��
	{
		this->mHp = this->phero->mHp;
		this->mMp = this->phero->mMp+5;
		cout << "Ӣ�۴������·�" << endl;
	}
	virtual void ShowStatus()//��д������󷽷�
	{
		cout << "Ѫ����" << mHp << endl;
		cout << "������" << mMp << endl;
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