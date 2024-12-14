#include "stdafx.h"
#include "RaiseChar.h"

RaiseChar::RaiseChar()
{
	SetDefaultArgument();
	SetWindowSize(720, 480);
	SetMaxCount(2000);
}

RaiseChar::RaiseChar(int width, int height, int count)
{
	SetDefaultArgument();
	SetWindowSize(width, height);
	SetMaxCount(count);
}

void RaiseChar::SetDefaultArgument()
{
	mMaxCount = 200;
	mCharNode = NULL;
	mWinWidth = 720;
	mWinHeight = 480;
}


RaiseChar::~RaiseChar()
{
	if (mCharNode != NULL)
	{
		free(mCharNode);
	}
}

void RaiseChar::SetMaxCount(int count)
{
	if (mCharNode != NULL)
	{
		free(mCharNode);
		mCharNode = NULL;
	}
	mMaxCount = count;
	mCharNode = (CharNode*)malloc(sizeof(CharNode)*mMaxCount);
}

void RaiseChar::SetWindowSize(int width, int height)
{
	mWinWidth = width;
	mWinHeight = height;
}


void RaiseChar::InitCharNode()
{
	for (int i = 0; i < mMaxCount; i++)
	{
		if (3 > rand() % 100)
			mCharNode[i].live = true;
		else
			mCharNode[i].live = false;
		ResetNodeArgs(i);
	}
}
void RaiseChar::ResetNodeArgs(int pos)
{
	int i = pos;
	mCharNode[i].x = rand() % mWinWidth;
	mCharNode[i].y = mWinHeight;
	mCharNode[i].speed = rand() % (mWinHeight * 1 / 100) + 1;
	if (mCharNode[i].speed == 1) mCharNode[i].speed = 2;
	mCharNode[i].r = rand() % 200 + 54;
	mCharNode[i].b = rand() % 200 + 54;
	mCharNode[i].g = rand() % 200 + 54;
	memset(mCharNode[i].ch, 0, sizeof(mCharNode[i].ch));
	if (rand() % 100 < 90)
	{
		if (sizeof(mCharNode[i].ch) == 8)
		{
			mCharNode[i].ch[0] = rand() % 0x100;
			if (mCharNode[i].ch[0] < 0 || mCharNode[i].ch[0] >= 128)
				mCharNode[i].ch[1] = rand() % 0x100;
		}
		else
		{
			mCharNode[i].ch[0] = rand() % 0x10000;
		}
	}
	else
	{
		static TCHAR CodingLangArray[][100] = { TEXT("#include<stdio.h>")
			, TEXT("stdlib.h")
			, TEXT("math.h")
			, TEXT("int main(void)")
			, TEXT("int main(int argc,char * argv[])")
			, TEXT("printf(\"hello world\");")
			, TEXT("scanf(\"%d\");")
			, TEXT("FILE * fp=NULL;")
			, TEXT("int * b=&a;")
			, TEXT("i++;")
			, TEXT("char * p=(char *)(void *)&a;")
			, TEXT("srand((unsigned int)time(NULL));")
			, TEXT("rand()%100<30;")
			, TEXT("system(\"pause\");")
			, TEXT("conio.h")
			, TEXT("time_t ptime;")
			, TEXT("struct tm * nowtime;")
			, TEXT("ptime = time(NULL);")
			, TEXT("nowtime = localtime(&ptime);")
			, TEXT("nowtime->tm_hour")
			, TEXT("char * p=(char *)malloc(sizeof(char)*100);")
			, TEXT("free(p);")
			, TEXT("enum{RED,GREEN=2,BLUE};")
			, TEXT("sprintf(temp,\"%0x02\\0\",(unsigned char)ch);")
			, TEXT("typedef struct {} Node;")
			, TEXT("using namespace std;")
			, TEXT("#include<iostream>")
			, TEXT("cout << \"hello world\" << endl; ")
			, TEXT("cin >> a >> b;")
			, TEXT("fstream")
			, TEXT("class Animal{};")
			, TEXT("public:")
			, TEXT("protect:")
			, TEXT("private:")
			, TEXT("virtual ~Animal();")
			, TEXT("class Dog : Animal {};")
			, TEXT("class RobotDog : public Robot,public Dog{};")
			, TEXT("class Cat:virtual public Animal{}")
			, TEXT("for(int i=0;i<10;i++){}")
			, TEXT("while(1){}")
			, TEXT("do{}while(true);")
			, TEXT("std::string")
			, TEXT("functional")
			, TEXT("std::vector<>")
			, TEXT("std::deque<>")
			, TEXT("std::queue<>")
			, TEXT("algorithm")
			, TEXT("std::iterater<>")
			, TEXT("std::stack<>")
			, TEXT("Animal ani=new Animal();")
			, TEXT("delete ani;")
			, TEXT("auto a=12;")
			, TEXT("[&] (int x, int y) -> int { return x + y; }")
			, TEXT("static int count=0;")
			, TEXT("int c=a>b?a:b;")
			, TEXT("a=a^b;b=a^b;a=a^b;")
			, TEXT("#define ADD(a,b) ((a)+(b))")
			, TEXT("#ifndef ... #define ... #endif")
			, TEXT("#if ... #else ... #endif")
			, TEXT("#pragma once")
			, TEXT("#pragma comment(lib,\"gdiplus.lib\")")
			, TEXT("namespace Tools{}")
			, TEXT("std::for_each(it.begin(), it.end(),[](int a){cout << a <<endl;});")
			, TEXT("template<class T>")
			, TEXT("friend class Car;")
			, TEXT("friend void add(int a,int b);")
			, TEXT("inline")
			, TEXT("p->next")
			, TEXT("if(!fp)")
			, TEXT("ch[2]=0;")
			, TEXT("kbhit()")
			, TEXT("getch()")
			, TEXT("vec.push_back(a);")
			, TEXT("operator")
			, TEXT("int a=(1,2,3);")
			, TEXT("int a=1,2,b=3;")
			, TEXT("exit(0);")
			, TEXT("int Animal::count=0;")
			, TEXT("Animal():feet(4){}")
			, TEXT("Cat():Animal(4),weight(40){}")
			, TEXT("while(ch[i])i++;")
			, TEXT("*(p+2)")
			, TEXT("*(*(p+2)+6)")
			, TEXT("p[i*col+j]")
			, TEXT("锟斤拷烫烫烫")
			, TEXT("") };

		static int count = 0;
		if (count == 0){
			while (lstrcmp(CodingLangArray[count], TEXT("")) != 0)
				count++;
		}
		lstrcpy(mCharNode[i].ch,CodingLangArray[rand()%count]);
	}

}
void RaiseChar::CreateCharNode()
{
	for (int i = 0; i < mMaxCount; i++)
	{
		if (mCharNode[i].live == false)
		{
			if (rand() % 100 < 21)
			{
				ResetNodeArgs(i);
				mCharNode[i].live = true;
			}
		}
	}
}
void RaiseChar::DrawBackground(HDC hdc)
{
	SetBkMode(hdc,TRANSPARENT);
	for (int i = 0; i < mMaxCount; i++)
	{
		if (mCharNode[i].live)
		{
			SetTextColor(hdc,RGB(mCharNode[i].r, mCharNode[i].g, mCharNode[i].b));
			TextOut(hdc, mCharNode[i].x, mCharNode[i].y, mCharNode[i].ch, lstrlen(mCharNode[i].ch));
		}
		

		mCharNode[i].y -= mCharNode[i].speed;
		/*if (rand() % 100 < 30)
		{
			mCharNode[i].x += rand() % 5 - 2;
		}*/

		if (rand() % 1000 < 15)
		{
			if (mCharNode[i].y <= mWinHeight*0.70)
			{
				mCharNode[i].live = false;
				continue;
			}
		}

		if (mCharNode[i].x <= 0 || mCharNode[i].x > mWinWidth || mCharNode[i].y <= 0 || mCharNode[i].y > mWinHeight)
		{
			mCharNode[i].live = false;
		}

	}
	

	//记录上一次创建新的粒子的时间
	static DWORD last_create_time = GetTickCount();

	//判断是否有任何按键按下，如果有任何按键按下，就创建粒子
	bool isDown = false;
	//最小的虚拟键码就是VK_LBUTTON，值为0x01
	for (int i = 1; i < 256; i++)
	{
		if (GetAsyncKeyState(i) & 0x8000)
		{
			CreateCharNode();
			isDown = true;
			last_create_time = GetTickCount();
			break;
		}
	}

	//如果没有任何按键按下，如果距离上一次创建粒子时间超过了一个时间，那就创建一次
	if (isDown == false)
	{
		DWORD now_time = GetTickCount();
		int diff = rand() % 3000 + 2000;//时间随机到此区间
		if (now_time - last_create_time > diff)
		{
			CreateCharNode();
			last_create_time = now_time;
		}
	}
}
