/** Name: CommandMod*/
#include<iostream>
#include<Windows.h>
#include<queue>
using namespace std;
/*
����ģʽ��
ͨ��˫������֮ǰԼ���Ĺ��������Ӧ�Ĳ���
һ�����������һ���������������������Ӧ�Ĳ���
*/
//Э�鴦��
class ProtocalCommand
{
public:
	void AddMoney()
	{
		cout << "���+1" << endl;
	}
	void AddIcon()
	{
		cout << "Ӳ��+1" << endl;
	}
	void AddCrestal()
	{
		cout << "ˮ��+1" << endl;
	}
	void AddLevel()
	{
		cout << "�ȼ�+1" << endl;
	}
};
//ͳһ�ӿ�
class AbstractCommand
{
public:
	virtual void Process() = 0;
};
//��������з�װ�����ã������������
class AddMoneyCommand : public AbstractCommand
{
public:
	AddMoneyCommand(ProtocalCommand * pc)
	{
		this->pc = pc;
	}
	virtual void Process()
	{
		pc->AddMoney();
		delete pc;
	}
private:
	ProtocalCommand * pc;
};
class AddIconCommand : public AbstractCommand
{
public:
	AddIconCommand(ProtocalCommand * pc)
	{
		this->pc = pc;
	}
	virtual void Process()
	{
		pc->AddIcon();
		delete pc;
	}
private:
	ProtocalCommand * pc;
};
//�������������
class ServiceControl
{
public:
	void AddRequest(AbstractCommand * ac)
	{
		que.push(ac);
	}
	void StartProcess()
	{
		while (!que.empty())
		{
			AbstractCommand * ac = que.front();
			ac->Process();
			que.pop();
			Sleep(1000);
		}
	}
private:
	queue<AbstractCommand*> que;
};
void test()
{
	AbstractCommand * am = new AddMoneyCommand(new ProtocalCommand());
	AbstractCommand * ai = new AddIconCommand(new ProtocalCommand());
	ServiceControl * sc = new ServiceControl();
	sc->AddRequest(am);
	sc->AddRequest(ai);
	sc->StartProcess();
}
int main(int argc, char * argv[])
{
	test();
	system("pause");
	return 0;
}