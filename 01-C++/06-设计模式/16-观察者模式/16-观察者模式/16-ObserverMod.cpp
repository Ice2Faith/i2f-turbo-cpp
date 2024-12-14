/** Name: Observer*/
#include<iostream>
#include<list>
using namespace std;
/*
�۲���ģʽ:
����֮���ܹ�ͨ�����ӵķ�ʽ��ʵ�ָ���һ�������һ��״̬Ӱ����һ��״̬
��ˣ���Ҫ���۲���󷢳���Ϣ���Ӷ�ʹ�۲����ܹ����յ��źŽ�����Ӧ
*/
//�۲���
class AbstractPlayer
{
public:
	virtual void Updata() = 0;
};
class PlayerA :public AbstractPlayer
{
public:
	PlayerA()
	{
		cout << "���A����ս��" << endl;
	}
	virtual void Updata()
	{
		cout << "���Aֹͣս��" << endl;
	}
};
class PlayerB :public AbstractPlayer
{
public:
	PlayerB()
	{
		cout << "���B����ս��" << endl;
	}
	virtual void Updata()
	{
		cout << "���Bֹͣս��" << endl;
	}
};
//�۲�Ŀ��
class AbstractMonster
{
public:
	virtual void AddPlayer(AbstractPlayer * player) = 0;
	virtual void DeletePlayer(AbstractPlayer * player) = 0;
	virtual void Notify() = 0;
};
class MonsterA :public AbstractMonster
{
public:
	virtual void AddPlayer(AbstractPlayer * player)
	{
		players.push_back(player);
	}
	virtual void DeletePlayer(AbstractPlayer * player)
	{
		players.remove(player);
	}
	virtual void Notify()
	{
		for (auto it = players.begin(); it != players.end(); it++)
		{
			(*it)->Updata();
		}
	}
public:
	list<AbstractPlayer*> players;
};
void test()
{
	AbstractPlayer * pa = new PlayerA();
	AbstractPlayer * pb = new PlayerB();
	AbstractMonster * am = new MonsterA();
	am->AddPlayer(pa);
	am->AddPlayer(pb);
	cout << "Player B ����" << endl;
	//�������
	am->DeletePlayer(pb);
	//֪ͨ��Ҹ���״̬
	am->Notify();
}
int main(int argc, char * argv[])
{
	test();
	system("pause");
	return 0;
}