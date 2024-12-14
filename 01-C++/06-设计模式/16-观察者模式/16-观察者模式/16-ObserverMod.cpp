/** Name: Observer*/
#include<iostream>
#include<list>
using namespace std;
/*
观察者模式:
对象之间能够通过监视的方式，实现根据一个对象的一个状态影响另一个状态
因此，需要被观察对象发出消息，从而使观察者能够接收到信号进行响应
*/
//观察者
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
		cout << "玩家A正在战斗" << endl;
	}
	virtual void Updata()
	{
		cout << "玩家A停止战斗" << endl;
	}
};
class PlayerB :public AbstractPlayer
{
public:
	PlayerB()
	{
		cout << "玩家B正在战斗" << endl;
	}
	virtual void Updata()
	{
		cout << "玩家B停止战斗" << endl;
	}
};
//观察目标
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
	cout << "Player B 死亡" << endl;
	//玩家死亡
	am->DeletePlayer(pb);
	//通知玩家更新状态
	am->Notify();
}
int main(int argc, char * argv[])
{
	test();
	system("pause");
	return 0;
}