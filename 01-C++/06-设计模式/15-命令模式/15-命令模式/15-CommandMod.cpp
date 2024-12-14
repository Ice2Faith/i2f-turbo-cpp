/** Name: CommandMod*/
#include<iostream>
#include<Windows.h>
#include<queue>
using namespace std;
/*
命令模式：
通信双方根据之前约定的规则进行响应的操作
一方发送命令，另一方根据命令解析，进行响应的操作
*/
//协议处理
class ProtocalCommand
{
public:
	void AddMoney()
	{
		cout << "金币+1" << endl;
	}
	void AddIcon()
	{
		cout << "硬币+1" << endl;
	}
	void AddCrestal()
	{
		cout << "水晶+1" << endl;
	}
	void AddLevel()
	{
		cout << "等级+1" << endl;
	}
};
//统一接口
class AbstractCommand
{
public:
	virtual void Process() = 0;
};
//将命令进行封装，调用，放入就绪队列
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
//服务器处理程序
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