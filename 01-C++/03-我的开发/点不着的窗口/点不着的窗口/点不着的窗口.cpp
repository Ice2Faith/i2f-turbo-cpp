#include<windows.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdio.h>
#include<conio.h>
#include<math.h>
#define WAITTIME (10*1000)	//�ȴ�����ʱ��
#define RUNTIME (5*60*1000)	//������������ʱ��
//���ؿ���̨���ں�������ͼ��
#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
//�����Ļ�ߴ�
int SX = GetSystemMetrics(SM_CXSCREEN);
int SY = GetSystemMetrics(SM_CYSCREEN);
//���һ��������������Ŀ����Ŀ����Ϊname����������·��Ϊbootpath
void RegAddBootItem(char * name, char * bootpath)
{
	HKEY hkey;
	char path[] = { "Software\\Microsoft\\Windows\\CurrentVersion\\Run" };
	RegOpenKey(HKEY_CURRENT_USER, path, &hkey);
	RegSetValueEx(hkey, name, 0, REG_SZ, (unsigned char *)bootpath, strlen(bootpath) + 1);
}
//����޷�ѡ�д��ڣ�������
void MoveAwayCursorForegroundWindow()
{
	long begintime = GetTickCount();
	long nowtime = begintime;
	while (1)
	{
		nowtime = GetTickCount();
		if (nowtime - begintime > RUNTIME)
			break;
		HWND hwnd = GetForegroundWindow();
		HWND selfhwnd = FindWindow(NULL, "�㲻�ŵĴ���");
		if (hwnd == selfhwnd)
		{
			continue;
		}
		POINT cursor = { 0 };
		RECT wrect = { 0 };
		GetWindowRect(hwnd, &wrect);
		GetCursorPos(&cursor);
		int WndWid = wrect.right - wrect.left;
		int WndHei = wrect.bottom - wrect.top;
		if (WndWid > SX * 9 / 10)
		{
			WndWid = SX * 9 / 10;
		}
		if (WndHei > SY * 9 / 10)
		{
			WndHei = SY * 9 / 10;
		}
		if (cursor.x >= wrect.left&&cursor.x <= wrect.right&&
			cursor.y >= wrect.top&&cursor.y <= wrect.bottom)
		{
			int w_newx = rand() % (SX - WndWid);
			int w_newy = rand() % (SY - WndHei);
			MoveWindow(hwnd, w_newx, w_newy, WndWid, WndHei, true);
		}
		Sleep(30);
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			break;
	}
}
//�������ⷽ��ײ����Ļ��Ե��������ƶ�����
void MoveAnyDirectForegroundWindow()
{
	long begintime = GetTickCount();
	long nowtime = begintime;
	double direct = atan2(rand() % 100 - 50.0, rand() % 100 - 50.0);;
	begintime = nowtime = GetTickCount();
	while (1)
	{
		nowtime = GetTickCount();
		if (nowtime - begintime > RUNTIME)
			break;
		HWND hwnd = GetForegroundWindow();
		HWND selfhwnd = FindWindow(NULL, "�㲻�ŵĴ���");
		if (hwnd == selfhwnd)
		{
			continue;
		}
		RECT wrect = { 0 };
		GetWindowRect(hwnd, &wrect);
		int WndWid = wrect.right - wrect.left;
		int WndHei = wrect.bottom - wrect.top;
		if (WndWid > SX * 9 / 10)
		{
			WndWid = SX * 9 / 10;
		}
		if (WndHei > SY * 9 / 10)
		{
			WndHei = SY * 9 / 10;
		}
		int w_newx = wrect.left + 3 * sin(direct);
		int w_newy = wrect.top + 3 * cos(direct);
		if (w_newx <= 0 || w_newx >= SX - WndWid||
			w_newy <= 0 || w_newy >= SY - WndHei)
		{
			direct = atan2(rand() % 100 - 50.0, rand() % 100 - 50.0);
		}
		MoveWindow(hwnd, w_newx, w_newy, WndWid, WndHei, true);
		Sleep(30);
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			break;
	}
}
//�����ڷŵ�����λ�ý��������С����
void ExtendShrinkWindow()
{
	long begintime = GetTickCount();
	long nowtime = begintime;
	begintime = nowtime = GetTickCount();
	while (1)
	{
		nowtime = GetTickCount();
		if (nowtime - begintime > RUNTIME)
			break;
		HWND hwnd = GetForegroundWindow();
		HWND selfhwnd = FindWindow(NULL, "�㲻�ŵĴ���");
		if (hwnd == selfhwnd||hwnd==NULL)
		{
			continue;
		}
		RECT wrect = { 0 };
		GetWindowRect(hwnd, &wrect);
		int WndWid = wrect.right - wrect.left;
		int WndHei = wrect.bottom - wrect.top;
		MoveWindow(hwnd, rand()%(SX/2), rand()%(SY/2), rand()%SX, rand()%SY, true);
		Sleep(30);
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			break;
	}
}
int main(int argc, char * argv[])
{
	system("title �㲻�ŵĴ���");	//�����Ϊ�Լ��������ƣ���ֹ������Խ׶��޷��ж��˳�
	system("mode con lines=5 cols=20");	//�ڲ����ش��ڵ�ʱ����ʾһ��С���ڣ��ܹ�����˳�
	srand((unsigned int)time(NULL));
	//RegAddBootItem("WindowBugs",argv[0]);
	Sleep(WAITTIME);	//�ȴ�һ��ʱ�������У���ֹ��һ��Ӧ���Ǹմ򿪵ĳ��������
	int choice = rand() % 3;	//���һ��״̬
	switch (choice)
	{
	case 0:
		MoveAwayCursorForegroundWindow();
		break;
	case 1:
		MoveAnyDirectForegroundWindow();
		break;
	case 2:
		ExtendShrinkWindow();
		break;
	}
	return 0;
}