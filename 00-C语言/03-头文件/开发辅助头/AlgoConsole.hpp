#ifndef _ALGO_CONSOLE_HPP_
#define _ALGO_CONSOLE_HPP_
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include<stdio.h>
class AlgoConsole
{
public:
	/*
	 0 = 黑色       8 = 灰色
    1 = 蓝色       9 = 淡蓝色
    2 = 绿色       A = 淡绿色
    3 = 浅绿色     B = 淡浅绿色
    4 = 红色       C = 淡红色
    5 = 紫色       D = 淡紫色
    6 = 黄色       E = 淡黄色
    7 = 白色       F = 亮白色
	*/
	enum CONSOLE_COLOR_ENUM{CCE_BLACK=0,CCE_BLUE,CCE_GREEN,CCE_LIGHTGREEN,CCE_RED,CCE_PURPLE,CCE_YELLOW,CCE_WHITE,
	CCE_GRAY,CCE_LBLUE,CCE_LGREEN,CCE_LLIGHTGREEN,CCE_LRED,CCE_LPURPLE,CCE_LYELLOW,CCE_LWHITE};
	static void cls()
	{
		system("cls");
	}
	static void pause()
	{
		system("pause");
	}
	static void minWindow()
	{
		HWND hWnd = GetForegroundWindow();
		ShowWindow(hWnd, SW_MINIMIZE);
	}
	static void maxWindow()
	{
		HWND hWnd = GetForegroundWindow();
		ShowWindow(hWnd, SW_MAXIMIZE);
	}
	static void hideWindow()
	{
		HWND hWnd = GetForegroundWindow();
		ShowWindow(hWnd, SW_HIDE);
	}
	static void showWindow()
	{
		HWND hWnd = GetForegroundWindow();
		ShowWindow(hWnd, SW_SHOW);
	}
	static void gotoXY(int lines, int cols)
	{
		COORD ord = { cols, lines };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ord);
	}
	/*
	values between 0-15
	*/
	static void textColor(int foreColor,int backColor)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), foreColor + backColor * 0x10);
	}
	/*
	values between 0-15
	*/
	static void backColor(int foreColor, int backColor)
	{
		char buf[100] = { 0 };
		sprintf(buf, "color %c%c\0", (char)(backColor + '0'), (char)(foreColor + '0'));
		system(buf);
	}
	static void printReapet(char * str,int count=1, bool endLine = false)
	{
		for (int i = 0; i < count; i++)
		{
			printf("%s",str);
		}
		printf("\n");
	}
	static void printLine(char * str)
	{
		printf(str);
		printf("\n");
	}
	static void printInputTips(char * str)
	{
		printf(str);
		printf("\n>/ ");
	}
	static void printSleep(char * str, int sleepTime = 30)
	{
		while (*str)
		{
			printf("%c",(*str));
			str++;
			Sleep(sleepTime);
		}
	}
	static char getIfCh(char defCh = 0)
	{
		if (kbhit())
			return getch();
		return defCh;
	}
	static bool isKeyDown(char vkCode)
	{
		return (GetAsyncKeyState(vkCode)&0x8000);
	}
	static char getBetweenCh(char lowCh, char heighCh)
	{
		char ret = 0;
		while (ret<lowCh || ret>heighCh)
			ret = getch();
		return ret;
	}
	static void flushIn()
	{
		fflush(stdin);
	}
	static void printXY(int line, int col, char * str)
	{
		gotoXY(line, col);
		printf(str);
	}
	static char * getStr(char * buf,bool needFlush=false, bool whenSpace = true)
	{
		if (needFlush)
			fflush(stdin);
		if (whenSpace)
			scanf("%s", buf);
		else
			gets(buf);
		return buf;
	}
	static char * getStrUntil(char * buf, char endCh = ' ')
	{
		char ch = 0;
		int i = 0;
		do
		{
			ch = getch();
			buf[i] = ch;
			i++;
		} while (ch != endCh);
		buf[i] = 0;
		return buf;
	}


};
#endif // _ALGO_CONSOLE_HPP_