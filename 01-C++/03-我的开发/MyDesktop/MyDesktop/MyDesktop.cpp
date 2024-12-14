#include<graphics.h>
#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<math.h>
#define MAXLIGHT 2000
int SX = GetSystemMetrics(SM_CXSCREEN);
int SY = GetSystemMetrics(SM_CYSCREEN);
int WX = SX *4/10;
int WY = SY *4/10;
const int LineFontCount = 18;
int FontWid = WX / LineFontCount;
int FontHei = FontWid * 3 / 2;
const int SmallLineFontCount = 30;
int SFontWid = WX / SmallLineFontCount;
int SFontHei = SFontWid * 3 / 2;
HWND hwndThis = NULL;
typedef struct
{
	int x;
	int y;
	double direc;
	float speed;
	bool live;
	int r;
	int b;
	int g;
}Light;
Light light[MAXLIGHT];
void InitLight()
{
	for (int i = 0; i < MAXLIGHT; i++)
	{
		if (3 > rand() % 100)
			light[i].live = true;
		else
			light[i].live = false;
		light[i].x = WX / 2;
		light[i].y = WY / 2;
		light[i].direc = atan2(rand() % 4096 - 2048.0, rand() % 4096 - 2048.0);
		light[i].speed = rand() % (WX * 1 / 100) + 1;
		if (light[i].speed == 1) light[i].speed = 2;
		light[i].r = rand() % 200 + 54;
		light[i].b = rand() % 200 + 54;
		light[i].g = rand() % 200 + 54;
	}
}
void CreateLight()
{
	for (int i = 0; i < MAXLIGHT; i++)
	{
		if (light[i].live == false)
		{
			if (rand() % 100 < 21)
			{
				light[i].live = true;
				light[i].x = WX / 2;
				light[i].y = WY / 2;
				light[i].direc = atan2(rand() % 4096 - 2048.0, rand() % 4096 - 2048.0);
				light[i].speed = rand() % (WX * 1 / 100) + 1;
				if (light[i].speed == 1) light[i].speed = 2;
				light[i].r = rand() % 200 + 54;
				light[i].b = rand() % 200 + 54;
				light[i].g = rand() % 200 + 54;
			}
		}
	}
}
void DrawBackground()
{
	POINT cursor = { 0 };
	GetCursorPos(&cursor);
	for (int i = 0; i < MAXLIGHT; i++)
	{
		if (light[i].live)
		{
			putpixel(light[i].x, light[i].y, RGB(light[i].r, light[i].g, light[i].b));

			putpixel(light[i].x - 1, light[i].y, RGB(light[i].r - 20, light[i].g - 20, light[i].b - 20));
			putpixel(light[i].x + 1, light[i].y, RGB(light[i].r - 20, light[i].g - 20, light[i].b - 20));
			putpixel(light[i].x, light[i].y - 1, RGB(light[i].r - 20, light[i].g - 20, light[i].b - 20));
			putpixel(light[i].x, light[i].y + 1, RGB(light[i].r - 20, light[i].g - 20, light[i].b - 20));
			
		}
		if (rand() % 100 < 5)
		{
			POINT point = { 0 };
			point.x = light[i].x;
			point.y = light[i].y;
			ClientToScreen(hwndThis, &point);
			double ndirect = atan2((double)cursor.y - point.y, (double)cursor.x - point.x);
			light[i].direc = (ndirect + light[i].direc) / 2.0;
			//light[i].direc += (rand() % 30) / 180.0*3.1415926535;
			
		}
	
		
		light[i].x += light[i].speed*cos(light[i].direc);
		light[i].y += light[i].speed*sin(light[i].direc);
		if (rand()%100<30)
		{
			light[i].x += rand() % 5 - 2;
			light[i].y += rand() % 5 - 2;
		}
		if (rand() % 100 < 7)
		{
			if (light[i].x <= 0 + FontWid * 3 / 4 || light[i].x > WX - FontWid * 3 / 4 || light[i].y <= 0 + FontHei * 3 / 4 || light[i].y > WY - FontHei * 3 / 4)
			{
				for (int j = 0; j < 7; j++)
				{
					putpixel(light[i].x - (j + 1), light[i].y, RGB(light[i].r - (j * 10), light[i].g - (j * 3), light[i].b - (j * 2)));
					putpixel(light[i].x + (j + 1), light[i].y, RGB(light[i].r - (j * 10), light[i].g - (j * 3), light[i].b - (j * 2)));
					putpixel(light[i].x, light[i].y - (j + 1), RGB(light[i].r - (j * 10), light[i].g - (j * 3), light[i].b - (j * 2)));
					putpixel(light[i].x, light[i].y + (j + 1), RGB(light[i].r - (j * 10), light[i].g - (j * 3), light[i].b - (j * 2)));
				}

				light[i].live = false;
				continue;
			}
		}
		
		if (light[i].x <= 0 || light[i].x>WX || light[i].y <= 0 || light[i].y > WY)
		{
			light[i].live = false;
		}

	}
	CreateLight();

}
void drawDate()
{

	static char weekday[7][5] = { "日", "一", "二", "三", "四", "五", "六" };
	time_t ptime;
	struct tm * nowtime;
	ptime = time(NULL);
	nowtime = localtime(&ptime);
	char temp[256] = { 0 };
	BeginBatchDraw();
	cleardevice();
	DrawBackground();
	setbkmode(TRANSPARENT);
	bool ismoney = true;
	if (nowtime->tm_hour > 12)
	{
		ismoney = false;
	}
	else
	{
		ismoney = true;
	}
	if (ismoney)
		sprintf(temp, "%02d:%02d:%02d am\0", nowtime->tm_hour, nowtime->tm_min, nowtime->tm_sec);
	else
		sprintf(temp, "%02d:%02d:%02d pm\0", nowtime->tm_hour - 12, nowtime->tm_min, nowtime->tm_sec);
	settextstyle(FontHei, FontWid, "黑体");
	static COLORREF startColor = RGB(rand() % 256, rand() % 256, rand() % 256);
	static COLORREF endColor = RGB(rand() % 256, rand() % 256, rand() % 256);
	static COLORREF presentColor = startColor;
	static const int changeTimes = 60;
	static int presentTimes = 0;
	
	int br = startColor & 0xff;
	int bg = (startColor >> 8) & 0xff;
	int bb = (startColor >> 16) & 0xff;
	int er = endColor & 0xff;
	int eg = (endColor >> 8) & 0xff;
	int eb = (endColor >> 16) & 0xff;
	int dr = er - br;
	int dg = eg - bg;
	int db = eb - bb;

	double rateEnd = presentTimes*1.0 / changeTimes;
	int pr = rateEnd*dr + br;
	int pg = rateEnd*dg + bg;
	int pb = rateEnd*db + bb;

	presentColor = RGB(pr,pg,pb);
	settextcolor(presentColor);
	
	presentTimes++;
	static char pstr[20] = { 0 };
	if (presentTimes == changeTimes)
	{
		char pch1 = (char)rand() % 256;
		char pch2 = pch1 > 0 ? 0 : (char)rand() % 256;
		if (pch2!=0)
			sprintf(pstr, "%c%c %02X%02X\0", pch1,pch2,(unsigned char)pch1,(unsigned char)pch2 );
		else
			sprintf(pstr, "%c %02X\0", pch1,  (unsigned char)pch1);

		startColor = endColor;
		endColor = RGB(rand() % 256, rand() % 256, rand() % 256);
		presentTimes = 0;
	}
	outtextxy((LineFontCount - strlen(pstr)) / 2 * FontWid, FontHei * 4.5, pstr);

	outtextxy((LineFontCount - strlen(temp)) / 2 * FontWid, FontHei * 1, temp);
	sprintf(temp, "%04d-%02d-%02d %s\0", nowtime->tm_year + 1900, nowtime->tm_mon + 1, nowtime->tm_mday, weekday[nowtime->tm_wday]);
	outtextxy((LineFontCount - strlen(temp)) / 2 * FontWid, FontHei * 3, temp);

	

	static char Tips[12][30] = { "凌晨了，注意休息哦！", "夜已经深了，赶快休息吧！", "还在忙吗？注意身体哦！", "早安！今天将是美好的一天。", "努力奋斗，这是人生的目标哦！", "努力就会有收获，进步多一点", \
		"午安！休息放松一下！", "为了理想，继续加油！", "下午茶时光开始啦！", "晚上好！今天进步了吗？", "收整一下，准备休息啦！", "将近子夜了，应该休息啦！" };
	settextstyle(SFontHei, SFontWid, "黑体");
	sprintf(temp, "%s\0", Tips[nowtime->tm_hour/2]);
	temp[29] = 0;
	outtextxy((SmallLineFontCount - strlen(temp)) / 2 * SFontWid, WY-SFontHei*3/2, temp);

	sprintf(temp, "#%02x%02x%02x", pr, pg, pb);
	outtextxy((SmallLineFontCount - strlen(temp))  * SFontWid, 0, temp);
	FlushBatchDraw();
	EndBatchDraw();
}
int main()
{
	srand((unsigned int)time(NULL));
	//创建窗口
	HWND phwnd = initgraph(WX, WY, NOCLOSE|NOMINIMIZE);
	hwndThis = phwnd;
	//获取桌面窗口
	HWND fhwnd = GetDesktopWindow();
	//设置为子窗口
	SetParent(phwnd, fhwnd);
	//设置窗口透明
	LONG wlong = GetWindowLong(phwnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TRANSPARENT;
	SetWindowLong(phwnd, GWL_EXSTYLE, wlong);
	SetLayeredWindowAttributes(phwnd, RGB(0, 0, 0), 254, LWA_COLORKEY);
	//设置窗口最底部
	SetWindowPos(phwnd, HWND_BOTTOM, SX/2-(WX/2), SY/2-(WY/2), WX, WY, SWP_SHOWWINDOW);
	//消除窗口边框
	SetWindowLong(phwnd, GWL_STYLE, GetWindowLong(phwnd, GWL_STYLE) - WS_CAPTION);
	InitLight();
	
	while (1)
	{
		drawDate();
		Sleep(40);
	}
	return 0;
}