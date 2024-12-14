/** Name: �����Ч
Shift+Space:�л��Ƿ���ʹ��
*/
#include<stdio.h>
#include<graphics.h>
#include"WordsLayer.h"
#define WORDS_FILE_NAME ".\\words.txt"

void setWindowStyle(HWND hwnd,COLORREF bkColor)
{
	LONG wlong = GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TOOLWINDOW;//���͸��������������ʾͼ������
	SetWindowLong(hwnd, GWL_EXSTYLE, wlong);
	SetLayeredWindowAttributes(hwnd, bkColor, 0, LWA_COLORKEY);
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);//ȥ���߿�����

	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE);//���ô�����ǰ�ˣ�����ȫ��
}
int main(int argc, char * argv[])
{

	int winWid = GetSystemMetrics(SM_CXSCREEN);
	int winHei = GetSystemMetrics(SM_CYSCREEN);

	HWND hwnd=initgraph(winWid,winHei);
	COLORREF bkColor = 0xffffff;

	setWindowStyle(hwnd,bkColor);

	setbkcolor(bkColor);
	setbkmode(TRANSPARENT);
	cleardevice();

	LOGFONT font = { 0 };
	font.lfHeight = winHei / 30;
	settextstyle(&font);

	FILE * pf = fopen(WORDS_FILE_NAME, "r");
	if (pf == NULL)
	{
		settextcolor(0x0000ff);
		int i = 3;
		outtextxy(winWid*1/3,(i++)*font.lfHeight,"��Ļ�ı���\n\n");
		outtextxy(winWid*1/3,(i++)*font.lfHeight,"��ȡ�ļ�������:  ");
		outtextxy(winWid*1/3,(i++)*font.lfHeight,WORDS_FILE_NAME);
		outtextxy(winWid*1/3,(i++)*font.lfHeight,"\n");
		outtextxy(winWid*1/3,(i++)*font.lfHeight,"�뽫���ļ����õ�Ŀ��λ�ã����������б�����\n");
		outtextxy(winWid*1/3,(i++)*font.lfHeight,"���ļ��е�һ�����ݻᱻ����ĳ�ȡ������ʾ����Ļ��\n");
		outtextxy(winWid*1/3,(i++)*font.lfHeight,"���ո������");
		while (!(GetAsyncKeyState(VK_SPACE) & 0x8000)){
			Sleep(30);  
		}

		closegraph();
		return 0;
	}
	else
	{
		fclose(pf);
	}

	WordsLayer layer(WORDS_FILE_NAME);

	int SleepMillSec = 30;
	bool isPowerState = true;

	int distWid = winWid * 1 / 20;
	int distHei = winHei * 1 / 10;
	int distHei_d2 = distHei/2;

	int maxTimes = 100;
	int curTimes = 0;

	int diffX = (rand() % distWid );
	int diffY = (rand() % distHei - distHei_d2);
	std::string line = layer.getRandomWordsLine();
	

	int lr = rand() % 255;
	int lg = rand() % 255;
	int lb = rand() % 255;

	int cr = rand() % 255;
	int cg = rand() % 255;
	int cb = rand() % 255;

	
	while (1)
	{
		BeginBatchDraw();
		
		if (isPowerState)
		{
			SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);//ʼ�ձ�����ǰ��
			cleardevice();
			HDC hdc = GetImageHDC();	
			double rate = curTimes*1.0 / maxTimes;
			int dr = lr*(1.0-rate) + cr*rate;
			int dg = lg*(1.0-rate) + cg*rate;
			int db = lb*(1.0-rate) + cb*rate;
			settextcolor(RGB(dr, dg, db));
			
			POINT cursor = { 0 };
			GetCursorPos(&cursor);

			outtextxy(cursor.x + diffX, cursor.y + diffY, line.c_str());

			curTimes = (curTimes + 1) % maxTimes;
			if (curTimes == 0)
			{
				diffX = (rand() % distWid);
				diffY = (rand() % distHei - distHei_d2);
				line = layer.getRandomWordsLine();
				lr = cr;
				lg = cg;
				lb = cb;
				cr=rand()%255;
				cg=rand()%255;
				cb=rand()%255;

			}

		}
		if ((GetAsyncKeyState(VK_CAPITAL) & 0x8000) && (GetAsyncKeyState(VK_SPACE) & 0x8000)){
			isPowerState = !isPowerState;
			cleardevice();
		}
			
		EndBatchDraw();
		Sleep(SleepMillSec);
	}

	closegraph();
	return 0;
}