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
	CON.SleepPrint(30,"׼��ʱ��\n5.ѡ�񻭰屳����ɫ\n");
	CON.SleepPrint(20, "��ͼʱ��\n1.���л�ͼ��\n2.�����л�ͼ��\n3.ѡ�񻭱���ʽ��\n4.ѡ�񻭱���ɫ��\n6.��ջ��塣\n");
	CON.SleepPrint(20, "Tips��\n��ִ���л�����ʱ��ѡ����ϰ�������ȷ�ϼ��ɡ�\nWarning��\nȫ���벻Ҫ���������Ļ��������ֻ�����´򿪳�����\n�Ķ���Ϻ����������\n\n");
	CON.Getchf();
	cout << "����԰� \"5\"�л�������ɫ��������ȷ��ѡ��." << endl;
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