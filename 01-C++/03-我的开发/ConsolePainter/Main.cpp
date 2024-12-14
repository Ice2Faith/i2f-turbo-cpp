#include"ConsoleControl.h"
#include<iostream>
using namespace std;

void ConsolePainter(void);

int main(int argc, char * argv[])
{
	ConsolePainter();
	return 0;
}

void ConsolePainter(void)
{
	ConsoleControl CON;
	CON.SetConsoleTitleW("ConsolePainter Designed by Ice2Faith");
	CON.SetConsoleColor();
	cout << "USING GUID" << endl;
	CON.SleepPrint(30,"准备时：\n5.选择画板背景颜色\n");
	CON.SleepPrint(20, "画图时：\n1.进行画图。\n2.不进行画图。\n3.选择画笔样式。\n4.选择画笔颜色。\n6.清空画板。\n");
	CON.SleepPrint(20, "Tips：\n在执行切换操作时，选择完毕按其他键确认即可。\nWarning：\n全程请不要用鼠标点击屏幕，否则你只能重新打开程序了\n阅读完毕后，任意键继续\n\n");
	CON.Getchf();
	cout << "你可以按 \"5\"切换背景颜色，其他键确认选择." << endl;
	int bgcolor = 15,ftcolor=0,pentype=0,sptype=0;
	CON.SetConsoleColor(ftcolor, bgcolor);
	int i = 0;
	while ((_getch()) == '5')
	{
		bgcolor = i;
		if (bgcolor == ftcolor)
			ftcolor = 0;
		CON.SetConsoleColor(ftcolor, bgcolor);
		ftcolor = 15;
		i = (i + 1) % 16;
	}
	CON.ConsoleCls();
	char Pen[20] = { "*.,:;\'\"^-|+/\\@#$%&?" };
	int penlen = strlen(Pen);
	int x = 0, y = 0, bx = 0, by = 0;
	char exit = '1';
	char pain = '1';
	while (true)
	{
		CON.GetClientCursorPos(&x, &y);
		CON.SetGotoxy(x, y);
		if (x != bx || y != by)
		if (pain == '1')
			cout << Pen[pentype];
		bx = x;
		by = y;
		Sleep(10);
		exit = CON.Getchif();
		if (exit == '6')
			CON.ConsoleCls();
		if (exit == '1' || exit == '2')
			pain = exit;
		if (exit == '3')
		while ((_getch()) == '3')
		{
			CON.SetGotoxy(1, 0);
			pentype = sptype;
			cout << "Pen:" << Pen[pentype] << endl;
			sptype = (sptype + 1) % penlen;
		}
		if (exit == '4')
		while ((_getch()) == '4')
		{

			CON.SetGotoxy(0, 0);
			if (ftcolor==bgcolor)
				ftcolor = (ftcolor + 1) % 16;
			CON.SetTextColor(ftcolor, bgcolor);
			cout << "Color" << endl;
			ftcolor = (ftcolor + 1) % 16;
		}
	}

}