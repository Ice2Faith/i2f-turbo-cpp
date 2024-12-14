/** Name: FacadeMod*/
#include<iostream>

using namespace std;
/*
外观模式：
将多个子系统集成到统一的一个交互界面中进行管理，减少外部了解的类的数量
通过外观者进行统一的管理
*/
class TV
{
public:
	void on()
	{
		cout << "TV ON" << endl;
	}
	void off()
	{
		cout << "TV OFF" << endl;
	}
};
class DVD
{
public:
	void on()
	{
		cout << "DVD ON" << endl;
	}
	void off()
	{
		cout << "DVD OFF" << endl;
	}
};
class CD
{
public:
	void on()
	{
		cout << "CD ON" << endl;
	}
	void off()
	{
		cout << "CD OFF" << endl;
	}
};
class Game
{
public:
	void on()
	{
		cout << "Game ON" << endl;
	}
	void off()
	{
		cout << "Game OFF" << endl;
	}
};
class KTV//使用统一的外观者进行统一的管理，而不再是单一管理
{
public:
	KTV()
	{
		tv = new TV();
		dvd = new DVD();
		cd = new CD();
		game = new Game();
	}
	~KTV()
	{
		delete tv;
		delete dvd;
		delete cd;
		delete game;
	}
	void run()
	{
		tv->on();
		dvd->on();
		cd->on();
		game->on();
	}
	void stop()
	{
		tv->off();
		dvd->off();
		cd->off();
		game->off();
	}
private:
	TV * tv;
	DVD * dvd;
	CD * cd;
	Game * game;
};

int main(int argc, char * argv[])
{
	KTV * ktv = new KTV();
	ktv->run();
	ktv->stop();
	delete ktv;
	system("pause");
	return 0;
}