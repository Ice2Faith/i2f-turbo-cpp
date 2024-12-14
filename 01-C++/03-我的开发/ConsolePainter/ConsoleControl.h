#ifndef _CONSOLECONTROL_H_
#define _CONSOLECONTROL_H_
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<string.h>

namespace ConCI2F
{
class ConsoleControl
{
protected:
    char mind[1024];

public:
	__declspec(dllexport)void SetConsoleSize(int lines = 25, int cols = 85);
	__declspec(dllexport)void SetConsoleTitle(char title[]);
	__declspec(dllexport)void SetGotoxy(int lines, int cols);
	__declspec(dllexport)void SetTextColor(int ForeColor = 15, int BackGroundColor = 0);
	__declspec(dllexport)void SetConsoleColor(int TextColor = 5, int BackGroundColor = 15);
	__declspec(dllexport)void ConsoleCls(void);
	__declspec(dllexport)void GetHelp();
	__declspec(dllexport)void SleepPrint(int time, const char * text);
	__declspec(dllexport)char Getchf(void);
	__declspec(dllexport)char Getchif(void);
	__declspec(dllexport)void ScreenTips(int mode, int time, int BeforeTextColor, int BeforeBackGroundColor);
	__declspec(dllexport)void GetClientCursorPos(int * x, int * y);

};
}
#pragma comment(lib, "ConsoleControl.lib")
using namespace ConCI2F;
#endif // _CONSOLECONTROL_H_
