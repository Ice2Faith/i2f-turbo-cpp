/** Name: KeyBordLight*/
#include<iostream>
#include<windows.h>
#include<stdlib.h>
using namespace std;
void KeyboardLight(int sleepms,int maxrunms,bool bounce=false)
{
	int lightnum =0;
	bool add = true;
	int keys[] = { VK_NUMLOCK, VK_CAPITAL, VK_SCROLL };
	long stime = GetTickCount();
	while (true)
	{
		if (GetTickCount() - stime > maxrunms)
			break;
		for (int i = 0; i < 3; i++)
		{
			if (GetKeyState(keys[i])&0xff)
			{
				keybd_event(keys[i], 0, 0, 0);
				keybd_event(keys[i], 0, KEYEVENTF_KEYUP, 0);
			}
		}
		keybd_event(keys[lightnum], 0, 0, 0);
		keybd_event(keys[lightnum], 0, KEYEVENTF_KEYUP, 0);
		Sleep(sleepms);
		keybd_event(keys[lightnum], 0, 0, 0);
		keybd_event(keys[lightnum], 0, KEYEVENTF_KEYUP, 0);
		if (bounce == false)
		{
			lightnum = (lightnum + 1) % 3;
		}
		else
		{
			if (add == true)
			{
				if (lightnum < 2)
					lightnum++;
				else
					add = !add;
			}
			else
			{
				if (lightnum > 0)
					lightnum--;
				else
					add = !add;
			}
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			if (!GetKeyState(keys[i]) & 0xff)
			{
				keybd_event(keys[i], 0, 0, 0);
				keybd_event(keys[i], 0, KEYEVENTF_KEYUP, 0);
			}
			continue;
		}
		if (GetKeyState(keys[i]) & 0xff)
		{
			keybd_event(keys[i], 0, 0, 0);
			keybd_event(keys[i], 0, KEYEVENTF_KEYUP, 0);
		}
	}
}
int main(int argc, char * argv[])
{
	system("title Keyboard Light by Ugex.Savelar");
	system("color f1");
	system("mode con lines=20 cols=50");
	cout << "欢迎来到键盘灯跑马灯小程序" << endl << endl;
	int stime = 90;
	int rtime = 5000;
	cout << "请输入亮灯时间间隔（毫秒）：\n>/ ";
	cin >> stime;
	cout << "请输入跑马灯运行时长（毫秒）：\n>/ ";
	cin >> rtime;
	KeyboardLight(stime,rtime);
	return 0;
}
