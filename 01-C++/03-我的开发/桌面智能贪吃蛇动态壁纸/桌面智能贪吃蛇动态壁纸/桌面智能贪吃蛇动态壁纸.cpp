// 桌面智能贪吃蛇动态壁纸.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "桌面智能贪吃蛇动态壁纸.h"

//由于stdafx.h中定义了宏#define WIN32_LEAN_AND_MEAN  会导致gdiplus中的很多类型找不到，因此这里需要添加comdef.h
//当然你也可以去掉这个宏，去掉这个宏之后，原本的windows.h就已经包含了comdef.h
//重要说明，不管是去掉宏还是添加comdef.h,都要在include gdiplus之前，否则依然无效，编译会报错很多

/*
全局控制按键说明：
F5+L:中心散射绘制开关切换
F5+C:上升字符绘制开关切换
F5+S:鼠标跟随散射星星绘制开关切换
F5+V:鼠标跟随星涡绘制开关切换
F5+T:流星雨特效开关切换
F5+M:背景图片渲染开关
F5+I:浮游网络绘制开关切换
F5+E:3D图形网格
F5+Shift+E:切换3D图形
F5+Q:关闭上述所有特效

F5+H:隐藏、显示桌面图标

F5+TAB:切换游戏模式：贪吃蛇、2048
F5+G:游戏模式开关

F5+P:切换2048游戏显示风格

F5+UP +Shift +Control +Alt:实现二倍，三倍，四倍，五倍速
必须按键：F5+UP,其他键(Shift/Control/Alt)按得数量越多，倍速越高

F1:按住期间进入用户操作模式
在此期间你可以自己玩贪吃蛇游戏，蛇速度会变慢
通过UP/DOWN/LEFT/RIGHT进行方向控制
前提是你得按住F1

F5+A:使用自动纯色背景
F5+B:使用黑色背景
F5+W:使用白色背景

F5+O:蛇身体颜色渐变开关切换

F5+空格+K：当桌面被重启时，可以重新出发动态壁纸
*/
//F5+F1
void writeConfigHelpInfo()
{
	static long befInvoke = 0;
	long nowInvoke = GetTickCount();
	if (befInvoke!=0 && nowInvoke - befInvoke < 3 * 1000)
	{
		return;
	}
	befInvoke = nowInvoke;
	TCHAR helpInfo[] = { TEXT("当前为纯色时间渐变背景\n\
如果需要使用图片背景\n\
请将 bgimg.png 文件放置于本程序同目录下，并重新启动本程序\n\
重新启动请先打开任务管理器(Ctrl+Shift+Esc)找到本程序，选择结束进程\n\
之后再重新运行本程序\n\
但是注意，这将会导致占用较高的CPU资源\n\
虽然如此，但是如果你正在使用的软件处于最大化或者全屏状态\n\
那么本软件将会暂停，以释放出CPU，CPU占用将会接近0%\n\
温馨提示：\n\
F5+L/C/S/V/T/I/E:可以开启或者禁用部分特效，从而达到你想要的桌面效果\n\
上诉特效，我分别称之为：\n\
\t中子辐射，上升文明，追星火花，星流漩涡，时间流星，波动天网，3D形状\n\
F5+A/B/W:可以自由切换纯色背景颜色为自动、黑色、白色\n\
F5+M：切换是否使用背景图片还是纯色背景\n\
F5+O：切换蛇的颜色控制系统\n\
F5+Q：关闭所有特效\n\
F5+H:隐藏、显示桌面图标\n\
F5+Tab：切换游戏：2048/贪吃蛇\n\
F5+G：切换游戏显示/隐藏\n\
F5+P：切换2048方块绘制风格\n\
F5 + Shift + E:切换3D图形\n\
F5+UP[+Control[+Shift[+Alt]]]：游戏加速2/3/4/5倍速\n\
F1+UP/DOWN/LEFT/RIGHT:你可以自己玩游戏，取消后继续电脑自动玩\n\
") };
	MessageBox(NULL, helpInfo, TEXT("配置帮助 -- 桌面智能贪吃蛇动态壁纸"), MB_OK);
}

//背景图片设置依赖，使用GDI+
#include<comdef.h>	
#include<GdiPlus.h>
#pragma comment(lib,"gdiplus.lib")
#define BGIMG_PATH (L".\\bgimg.png")	//背景图片路径定义
bool g_hasExistBgImgFile = false;	//记录背景图片文件是否存在，不存在则不初始化GDI+ 库，减少使用CPU资源


#include"VideoWallpaperHelper.h"
#include"SysListViewHelp.h"

#include"Snack.h"
#include"WinBatchDraw.h"
#include"ScatteringLight.h"
#include"RaiseChar.h"
#include"TraceMouseStar.h"
#include"StarVortex.h"
#include"MeteorShower.h"
#include"IntelligentNetwork.h"
#include"Game2048.h"

#include"D3EmitBall.h"
#define ID_TIMER_FLASH_DRAW 0x101 //定时器ID
#define TIMER_FLASH_TIMEOUT 24 //刷新间隔 帧率=1000/刷新间隔 当刷新间隔==24时，帧率为41FPS

int g_WinWidth = 720; //记录窗口最大化之后的窗口大小，这里的初始值其实是没什么用的,后面会更改
int g_WinHeight = 480;

#define MAX_LIGHT_COUNT 2000
ScatteringLight g_light;

#define MAX_CHAR_COUNT 200
RaiseChar g_raiseChar;

#define MAX_STAR_COUNT 120
TraceMouseStar g_traceStar;

#define MAX_STAR_VORTEX_COUNT 2000
StarVortex g_startVortext;

#define MAX_METEROR_COUNT 30
MeteorShower g_meteorShower;

#define MAX_INTELNET_COUNT 200
IntelligentNetwork m_intelNet;

#define MAX_EMITBALL_COUNT 200
D3EmitBall g_emitBall;

//判断是不是贪吃蛇游戏在运行，否则就是2048游戏
bool isSnakeMode = true;
Game2048 * g_my2048 = NULL;
int g_maxNum = 2;
MoveDirect g_direcs[4] = { MOV_UP, MOV_DOWN, MOV_LEFT, MOV_RIGHT };
MoveDirect g_auto2048MoveMainDirect = MOV_DOWN;
int g_auto2048MainIndex=1;


#define BLOCK_COUNT_ONE_LINE 80 //定义贪吃蛇的列数，行数会根据屏幕大小等比例计算出

bool g_isOpenWall = false;	//定义贪吃蛇是否拥有四边墙体
Snack * g_mygame = NULL; //贪吃蛇游戏对象

int g_cols = 0;	//真正的保存贪吃蛇行列数量的变量，后面会计算出来，因此初始值没用
int g_rows = 0;
COLORREF g_giftColor = 0x00aaff;
COLORREF g_specialGiftColor = RGB(255, 0, 0);
COLORREF g_snackBodyColor = 0x000000;
COLORREF g_bgColor = 0xeeeeee;
int g_maxLen = 1;
int g_maxScore = 0;
int g_deadTimes = 0;

bool g_useBgImg = true;
bool g_useSmoothSnackColor = true;

enum BgColorMode{ BGC_AUTO, BGC_BLACK, BGC_WHITE };
BgColorMode g_bgColor_mode = BGC_AUTO;

void InitSnackGame()
{
	if (g_mygame == NULL){
		g_mygame = new Snack(g_cols, g_rows, g_isOpenWall);
	}
	g_mygame->Clear();
}
void Init2048Game()
{
	if (g_my2048 == NULL){
		g_my2048 = new Game2048(10, 15);
	}
	g_my2048->clear();

	g_auto2048MainIndex = rand() % (sizeof(g_direcs) / sizeof(g_direcs[0]));
	g_auto2048MoveMainDirect = g_direcs[g_auto2048MainIndex];
}
void InitGame()
{
	if (isSnakeMode){
		InitSnackGame();
	}
	else
	{
		Init2048Game();
	}
}

void OnGameOver()
{
	g_deadTimes++;
	InitGame();
}
COLORREF g_lastColor = 0x0000ff;
COLORREF g_last2Color = 0x777777;
void drawSnackSmooth(HDC hdc, double blockWid, double blockHei)
{
	if (isSnakeMode == false)
	{
		return;
	}

	PointNode * snack = g_mygame->GetSnackBody();
	int count = 0;
	int maxCount = g_mygame->GetSnackLen();
	while (snack->next)
	{
		PointNode * p = snack->next;
		count++;
		int r = (g_lastColor)& 0xff;
		int g = (g_lastColor >> 8) & 0xff;
		int b = (g_lastColor >> 16) & 0xff;
		int r2 = (g_last2Color)& 0xff;
		int g2 = (g_last2Color >> 8) & 0xff;
		int b2 = (g_last2Color >> 16) & 0xff;
		int br = r2 - r;
		int bg = g2 - g;
		int bb = b2 - b;
		double rate = count*1.0 / maxCount;
		int er = r + br*rate;
		int eg = g + bg*rate;
		int eb = b + bb*rate;

		COLORREF fillColor = RGB(er, eg, eb);


		int j = p->point.col - 1;
		int i = p->point.line - 1;
		int elem = g_mygame->MapAt(i, j);

		if (elem == ELEM_SNACK_HEAD)
		{
			fillColor = RGB(255, 0, 0);
		}
		else if (elem == ELEM_SNACK_TAIL)
		{
			fillColor = RGB(100, 100, 100);
		}
		HPEN pen = CreatePen(0, 1, fillColor);
		HGDIOBJ op = SelectObject(hdc, pen);
		HBRUSH brush = CreateSolidBrush(fillColor);
		HGDIOBJ oldobj = SelectObject(hdc, brush);

		Ellipse(hdc, j*blockWid, i*blockHei, (j + 1)*blockWid, (i + 1)*blockHei);

		DeleteObject(op);
		DeleteObject(pen);
		DeleteObject(oldobj);
		DeleteObject(brush);

		snack = snack->next;
	}

}

void RunSnackGame()
{

	if (g_mygame == NULL)
	{
		return;
	}


	int beflen = g_mygame->GetSnackLen();

	//允许用户操作控制，期间进行减速，更好的用户体验
	bool isUserControl = false;
	static int userSpeedControlTime = 0;
	if ((GetAsyncKeyState(VK_F1) & 0x8000))
	{
		isUserControl = true;
		userSpeedControlTime = (userSpeedControlTime + 1) % 3;
		if ((GetAsyncKeyState(VK_UP) & 0x8000))
		{
			g_mygame->Run(MOV_UP);
		}
		else if ((GetAsyncKeyState(VK_DOWN) & 0x8000))
		{
			g_mygame->Run(MOV_DOWN);
		}
		else if ((GetAsyncKeyState(VK_LEFT) & 0x8000))
		{
			g_mygame->Run(MOV_LEFT);
		}
		else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000))
		{
			g_mygame->Run(MOV_RIGHT);
		}
		else{

			if (userSpeedControlTime == 0)
				g_mygame->Run(MOV_NULL);

		}
	}


	if (isUserControl == false)
	{
		if (!g_mygame->AutoRun())
		{
			OnGameOver();
		}
	}

	if (g_mygame->GetSnackLen() > g_maxLen){
		g_maxLen = g_mygame->GetSnackLen();
	}
	if (g_mygame->GetScore() > g_maxScore){
		g_maxScore = g_mygame->GetScore();
	}

	int nowlen = g_mygame->GetSnackLen();
	if (beflen != nowlen){
		if (g_useSmoothSnackColor)
		{
			g_last2Color = g_lastColor;
			g_lastColor = g_giftColor;
		}

		if (g_mygame->IsNormalGift())
			g_giftColor = RGB(rand() % 255, rand() % 256, rand() % 256);
		else
			g_giftColor = g_specialGiftColor;
		int rc = ((g_snackBodyColor & 0xff) + (g_giftColor & 0xff)) % 256;
		int gc = (((g_snackBodyColor & 0xff00) >> 8) + ((g_giftColor & 0xff00) >> 8)) % 256;
		int bc = (((g_snackBodyColor & 0xff0000) >> 16) + ((g_giftColor & 0xff0000) >> 16)) % 256;
		g_snackBodyColor = RGB(rc, gc, bc);
	}

}
void Run2048Game()
{
	if (g_my2048 == NULL){
		return;
	}

	//允许用户操作控制，期间进行减速，更好的用户体验
	bool isUserControl = false;
	static int userSpeedControlTime = 0;
	if ((GetAsyncKeyState(VK_F1) & 0x8000))
	{
		isUserControl = true;
		userSpeedControlTime = (userSpeedControlTime + 1) % 3;
		if ((GetAsyncKeyState(VK_UP) & 0x8000))
		{
			g_my2048->Run(MOV_UP);
		}
		else if ((GetAsyncKeyState(VK_DOWN) & 0x8000))
		{
			g_my2048->Run(MOV_DOWN);
		}
		else if ((GetAsyncKeyState(VK_LEFT) & 0x8000))
		{
			g_my2048->Run(MOV_LEFT);
		}
		else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000))
		{
			g_my2048->Run(MOV_RIGHT);
		}

	}
	static int autoRunTimeControl = 0;
	if (isUserControl == false)
	{
		autoRunTimeControl = (autoRunTimeControl + 1) % 6;
		if (autoRunTimeControl == 0)
		{
			bool islive = false;
			if (rand() % 100 < 90)
				islive = g_my2048->Run(g_auto2048MoveMainDirect);
			else
			{
				int index = g_auto2048MainIndex;
				while (index == g_auto2048MainIndex)
				{
					index = rand() % (sizeof(g_direcs)/sizeof(g_direcs[0]));
				}
				islive = g_my2048->Run(g_direcs[index]);
			}
			if (islive == false){
				OnGameOver();
			}
		}

	}

	if (g_maxNum < g_my2048->GetMaxNum())
	{
		g_maxNum = g_my2048->GetMaxNum();
	}

}
void RunGame()
{
	if (isSnakeMode)
	{
		RunSnackGame();
	}
	else
	{
		Run2048Game();
	}

}
void setTextColorSmooth(HDC hdc)
{
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

	presentColor = RGB(pr, pg, pb);
	SetTextColor(hdc, presentColor);

	presentTimes++;
	static char pstr[20] = { 0 };
	if (presentTimes == changeTimes)
	{
		startColor = endColor;
		endColor = RGB(rand() % 256, rand() % 256, rand() % 256);
		presentTimes = 0;
	}
}
void drawBackground(HDC hdc)
{
	if (g_useBgImg && g_hasExistBgImgFile)
	{
		static WCHAR bgimg[] = { BGIMG_PATH };
		static Gdiplus::Image image(bgimg);
		Gdiplus::Graphics graphics(hdc);
		graphics.DrawImage(&image, 0, 0, g_WinWidth, g_WinHeight);
	}
	else
	{
		HBRUSH brush = CreateSolidBrush(g_bgColor);
		HGDIOBJ oldbrush = SelectObject(hdc, brush);
		Rectangle(hdc, -1, -1, g_WinWidth, g_WinHeight);
		DeleteObject(oldbrush);
		DeleteObject(brush);
	}
}
void drawTextInfo(HDC hdc)
{

	LOGFONT tf = { 0 };
	tf.lfWidth = g_WinWidth / 120;
	tf.lfHeight = tf.lfWidth*1.33;
	HFONT font = CreateFontIndirect(&tf);
	HGDIOBJ oldobj = SelectObject(hdc, font);
	DeleteObject(oldobj);

	SetBkMode(hdc, TRANSPARENT);
	TCHAR infoStr[120] = { 0 };
	if (isSnakeMode)
	{
		_stprintf(infoStr, TEXT("Len:%d  /  %d    Score:%d  /  %d    Dead:%d\0"), g_mygame->GetSnackLen(), g_maxLen, g_mygame->GetScore(), g_maxScore, g_deadTimes);
	}
	else
	{
		_stprintf(infoStr, TEXT("Step:%d     Score:%d    Max:%d  /  %d    Dead:%d    Time:%d\0"), g_my2048->GetStep(), g_my2048->GetScore(), g_my2048->GetMaxNum(), g_maxNum, g_deadTimes, g_my2048->GetUsedTime());
	}

	TextOut(hdc, g_WinWidth - (lstrlen(infoStr) + 8)*tf.lfWidth, 0, infoStr, lstrlen(infoStr));

	static TCHAR weekday[7][5] = { TEXT("日"), TEXT("一"), TEXT("二"), TEXT("三"), TEXT("四"), TEXT("五"), TEXT("六") };
	time_t ptime;
	struct tm * nowtime;
	ptime = time(NULL);
	nowtime = localtime(&ptime);
	char temp[256] = { 0 };
	bool ismoney = true;
	if (nowtime->tm_hour > 12)
	{
		ismoney = false;
	}
	else
	{
		ismoney = true;
	}
	TCHAR dateInfo[256] = { 0 };
	if (ismoney)
		_stprintf(dateInfo, TEXT("%02d:%02d:%02d am  %04d-%02d-%02d %s\0"), nowtime->tm_hour, nowtime->tm_min, nowtime->tm_sec, nowtime->tm_year + 1900, nowtime->tm_mon + 1, nowtime->tm_mday, weekday[nowtime->tm_wday]);
	else
		_stprintf(dateInfo, TEXT("%02d:%02d:%02d pm  %04d-%02d-%02d %s\0"), nowtime->tm_hour - 12, nowtime->tm_min, nowtime->tm_sec, nowtime->tm_year + 1900, nowtime->tm_mon + 1, nowtime->tm_mday, weekday[nowtime->tm_wday]);
	TextOut(hdc, g_WinWidth - (lstrlen(dateInfo) + 8)*tf.lfWidth, tf.lfHeight * 2, dateInfo, lstrlen(dateInfo));

	if (g_bgColor_mode == BGC_AUTO)
	{
		int colorBgLevel = 255;
		if (nowtime->tm_hour < 12)
		{
			colorBgLevel = (nowtime->tm_hour + (nowtime->tm_min / 60.0)) / 12.0 * 255;
		}
		else{
			colorBgLevel = (24.0 - (nowtime->tm_hour + (nowtime->tm_min / 60.0))) / 12.0 * 255;
		}
		g_bgColor = RGB((colorBgLevel + colorBgLevel / 255.0 * 30>255 ? 255 : colorBgLevel + colorBgLevel / 255.0 * 30), (colorBgLevel + colorBgLevel / 255.0 * 40 > 255 ? 255 : colorBgLevel + colorBgLevel / 255.0 * 40), colorBgLevel);

	}
	else if (g_bgColor_mode == BGC_BLACK)
	{
		g_bgColor = 0x000000;
	}
	else if (g_bgColor_mode == BGC_WHITE)
	{
		g_bgColor = 0xffffff;
	}




	static TCHAR Tips[12][30] = { TEXT("凌晨了，注意休息哦！"),
		TEXT("夜已经深了，赶快休息吧！"),
		TEXT("还在忙吗？注意身体哦！"),
		TEXT("早安！今天将是美好的一天。"),
		TEXT("努力奋斗，这是人生的目标哦！"),
		TEXT("努力就会有收获，进步多一点"),
		TEXT("午安！休息放松一下！"),
		TEXT("为了理想，继续加油！"),
		TEXT("下午茶时光开始啦！"),
		TEXT("晚上好！今天进步了吗？"),
		TEXT("收整一下，准备休息啦！"),
		TEXT("将近子夜了，应该休息啦！") };

	TextOut(hdc, g_WinWidth - (lstrlen(Tips[nowtime->tm_hour / 2]) * 2 + 8)*tf.lfWidth, tf.lfHeight * 4, Tips[nowtime->tm_hour / 2], lstrlen(Tips[nowtime->tm_hour / 2]));

	static TCHAR outCodeStr[50] = { 0 };
	static int loopNextChar = 0;
	if (loopNextChar == 0)
	{
		if (sizeof(TCHAR) == 8){
			TCHAR pch1 = (TCHAR)rand() % 256;
			TCHAR pch2 = pch1 > 0 ? 0 : (TCHAR)rand() % 256;
			if (pch2 != 0)
				_stprintf(outCodeStr, TEXT("%c%c   0X%02X%02X\0"), pch1, pch2, (unsigned char)pch1, (unsigned char)pch2);
			else
				_stprintf(outCodeStr, TEXT("%c   0X%02X\0"), pch1, (unsigned char)pch1);
		}
		else
		{
			TCHAR pch = (TCHAR)rand() % (0x10000);
			_stprintf(outCodeStr, TEXT("%c   0X%04X\0"), pch, (unsigned short)pch);
		}
	}
	TextOut(hdc, g_WinWidth - (lstrlen(outCodeStr) + 8)*tf.lfWidth, tf.lfHeight * 6, outCodeStr, lstrlen(outCodeStr));
	loopNextChar = (loopNextChar + 1) % 90;

	DeleteObject(font);

	DeleteObject(oldobj);
}
void switchGameMode()
{
	isSnakeMode = !isSnakeMode;
	InitGame();
}
bool g_needDrawGame = true;

bool g_needDrawLight = false;
bool g_needDrawRaiseChar = false;
bool g_needDrawTraceStar = false;
bool g_needDrawStarVortex = false;
bool g_needDrawMeteorShower = false;
bool g_needDrawIntelNet = false;
bool g_needDrawEmitBall = true;

bool g_is2048SimpleBlockMode = true;

void checkBackgroundState()
{
	g_useBgImg = false;

	if ((GetAsyncKeyState(VK_F5) & 0x8000))
	{
		if ((GetAsyncKeyState(VK_F1) & 0x8000))
		{
			writeConfigHelpInfo();
		}
		if ((GetAsyncKeyState('P') & 0x8000))
		{
			g_is2048SimpleBlockMode = !g_is2048SimpleBlockMode;
		}
		if ((GetAsyncKeyState('G') & 0x8000))
		{
			g_needDrawGame = !g_needDrawGame;
		}
		if ((GetAsyncKeyState('L') & 0x8000))
		{
			g_needDrawLight = !g_needDrawLight;
		}
		if ((GetAsyncKeyState('C') & 0x8000))
		{
			g_needDrawRaiseChar = !g_needDrawRaiseChar;
		}
		if ((GetAsyncKeyState('S') & 0x8000))
		{
			g_needDrawTraceStar = !g_needDrawTraceStar;
		}
		if ((GetAsyncKeyState('V') & 0x8000))
		{
			g_needDrawStarVortex = !g_needDrawStarVortex;
		}
		if ((GetAsyncKeyState('T') & 0x8000))
		{
			g_needDrawMeteorShower = !g_needDrawMeteorShower;
		}
		if ((GetAsyncKeyState('I') & 0x8000))
		{
			g_needDrawIntelNet = !g_needDrawIntelNet;
		}
		if ((GetAsyncKeyState('E') & 0x8000))
		{
			//限制一下，每一段时间允许切换一次
			if ((GetAsyncKeyState(VK_SHIFT) & 0x8000)){
				static long lastTick = GetTickCount();
				long nowTick = GetTickCount();
				if (nowTick - lastTick > 500){
					g_emitBall.makeUniqueStereo();
					lastTick = nowTick;
				}
				
			}
			else{
				g_needDrawEmitBall = !g_needDrawEmitBall;
			}
		}
		if ((GetAsyncKeyState(VK_TAB) & 0x8000))
		{
			switchGameMode();
		}
		if ((GetAsyncKeyState('Q') & 0x8000))
		{
			g_needDrawStarVortex = false;
			g_needDrawLight = false;
			g_needDrawRaiseChar = false;
			g_needDrawTraceStar = false;
			g_needDrawMeteorShower = false;
			g_needDrawIntelNet = false;
			g_needDrawEmitBall = false;
			g_useBgImg = false;

		}
		if ((GetAsyncKeyState('H') & 0x8000))
		{
			BOOL visible = IsWindowVisible(getSysListView32Window());
			setSysListView32ShowState(!visible);
		}
		if ((GetAsyncKeyState('A') & 0x8000))
		{
			g_bgColor_mode = BGC_AUTO;
		}
		if ((GetAsyncKeyState('B') & 0x8000))
		{
			g_bgColor_mode = BGC_BLACK;
		}
		if ((GetAsyncKeyState('W') & 0x8000))
		{
			g_bgColor_mode = BGC_WHITE;
		}

		if ((GetAsyncKeyState('M') & 0x8000))
		{
			g_useBgImg = !g_useBgImg;
		}

		if ((GetAsyncKeyState('O') & 0x8000))
		{
			g_useSmoothSnackColor = !g_useSmoothSnackColor;
		}

	}
}
void clearDraw(HDC hdc)
{
	setTextColorSmooth(hdc);
	drawBackground(hdc);
	checkBackgroundState();
	if (g_needDrawLight)
		g_light.DrawBackground(hdc);
	if (g_needDrawRaiseChar)
		g_raiseChar.DrawBackground(hdc);
	if (g_needDrawTraceStar)
		g_traceStar.DrawBackground(hdc);
	if (g_needDrawStarVortex)
		g_startVortext.DrawBackground(hdc);
	if (g_needDrawMeteorShower)
		g_meteorShower.DrawBackground(hdc);
	if (g_needDrawIntelNet)
		m_intelNet.DrawBackground(hdc);
	if (g_needDrawEmitBall)
		g_emitBall.DrawBackground(hdc);
}
void DrawSnackGame(HDC hdc)
{
	if (g_mygame == NULL)
	{
		return;
	}



	double blockWid = g_WinWidth*1.0 / g_mygame->GetCols();
	double blockHei = g_WinHeight*1.0 / g_mygame->GetLines();


	COLORREF fillColor = 0xffffff;

	bool isSpecialGift = false;
	for (int i = 0; i < g_mygame->GetLines(); i++)
	{
		for (int j = 0; j < g_mygame->GetCols(); j++)
		{
			int elem = g_mygame->MapAt(i, j);

			if (elem == ELEM_VECANT)
			{
				fillColor = RGB(255, 255, 255);
				continue;
			}
			else if (elem == ELEM_GIFT)
			{
				fillColor = g_giftColor;
				if (g_giftColor == g_specialGiftColor){
					isSpecialGift = true;
				}
			}
			else if (elem == ELEM_SNACK)
			{
				fillColor = g_snackBodyColor;
				if (g_useSmoothSnackColor)
				{
					continue;
				}
			}
			else if (elem == ELEM_SNACK_HEAD)
			{
				fillColor = RGB(255, 0, 0);
			}
			else if (elem == ELEM_SNACK_TAIL)
			{
				fillColor = RGB(100, 100, 100);
			}
			else if (elem == ELEM_WALL)
			{
				fillColor = RGB(0, 0, 0);
			}
			HPEN pen = CreatePen(0, 1, fillColor);
			HGDIOBJ op = SelectObject(hdc, pen);
			HBRUSH brush = CreateSolidBrush(fillColor);
			HGDIOBJ oldobj = SelectObject(hdc, brush);

			Ellipse(hdc, j*blockWid, i*blockHei, (j + 1)*blockWid, (i + 1)*blockHei);
			if (isSpecialGift)
			{
				Rectangle(hdc, j*blockWid, i*blockHei, (j + 1)*blockWid, (i + 1)*blockHei);
				isSpecialGift = false;
			}

			DeleteObject(op);
			DeleteObject(pen);
			DeleteObject(oldobj);
			DeleteObject(brush);

		}
	}
	if (g_useSmoothSnackColor)
	{
		drawSnackSmooth(hdc, blockWid, blockHei);
	}


}
void Draw2048Game(HDC hdc)
{

	if (g_my2048 == NULL)
	{
		return;
	}



	double blockWid = g_WinWidth*1.0 / g_my2048->GetCols();
	double blockHei = g_WinHeight*1.0 / g_my2048->GetLines();
	for (int i = 0; i < g_my2048->GetLines(); i++)
	{
		for (int j = 0; j < g_my2048->GetCols(); j++)
		{
			double elem = g_my2048->MapAt(i, j);
			COLORREF fillColor = RGB(200, 200, 200);
			if (elem != 0)
			{
				int pr = (128 + (15 * (log(elem) / log(2.0))));
				int po = (256 - (15 * (log(elem) / log(2.0))));
				if (pr>255)pr = 255;
				if (po < 0)po = 0;
				fillColor = RGB(pr, po, po);
			}

			HPEN pen = CreatePen(0, 1, fillColor);
			HGDIOBJ op = SelectObject(hdc, pen);
			HBRUSH brush = NULL;
			
			if (g_is2048SimpleBlockMode)
			{
				brush = (HBRUSH)GetStockObject(NULL_BRUSH);
				SetBkMode(hdc, OPAQUE);
				SetBkColor(hdc, fillColor);
			}
			else
			{
				SetBkMode(hdc, TRANSPARENT);
				brush=CreateSolidBrush(fillColor);
			}
			HGDIOBJ ob = SelectObject(hdc, brush);

			//Rectangle(hdc, j*blockWid, i*blockHei, (j + 1)*blockWid, (i + 1)*blockHei);
			if (elem != 0)
			{
				Rectangle(hdc, j*blockWid, i*blockHei, (j + 1)*blockWid, (i + 1)*blockHei);

				TCHAR buf[20] = { 0 };
				_stprintf(buf, TEXT("%d"), (int)elem);
				int buflen = lstrlen(buf);

				LOGFONT lfont = { 0 };
				lfont.lfWidth = blockWid * 8 / 10 / 7;
				HFONT font = CreateFontIndirect(&lfont);
				HGDIOBJ of = SelectObject(hdc, font);



				TextOut(hdc, j*blockWid + blockWid * 1 / 10, i*blockHei + blockHei * 1 / 10, buf, buflen);

				SelectObject(hdc, of);
				DeleteObject(font);
				DeleteObject(of);
			}

			DeleteObject(op);
			DeleteObject(pen);
			DeleteObject(ob);
			if (g_is2048SimpleBlockMode == false)
			{
				DeleteObject(brush);
			}
		}
	}

}
void DrawGame(HDC hdc)
{
	WinBatchDraw batchDraw(hdc, g_WinWidth, g_WinHeight);
	hdc = batchDraw.BeginBatchDraw();

	SetBkMode(hdc, TRANSPARENT);

	clearDraw(hdc);

	if (g_needDrawGame)
	{
		if (isSnakeMode)
		{
			DrawSnackGame(hdc);
		}
		else
		{
			Draw2048Game(hdc);
		}
	}
	

	drawTextInfo(hdc);
	batchDraw.EndBatchDraw();
}
bool hasFullScreenWindow(HWND hSelf)
{
	HWND hfg = GetForegroundWindow();

	if (hfg == hSelf)
	{
		return false;
	}


	HWND hdesk = GetDesktopWindow();
	HWND hshell = GetShellWindow();

	if (hfg == hdesk || hfg == hshell)
	{
		return false;
	}

	TCHAR clsName[256] = { 0 };
	GetClassName(hfg, clsName, sizeof(clsName) / sizeof(TCHAR));
	if (lstrcmp(TEXT("WorkerW"), clsName) == 0 || lstrcmp(TEXT("SysListView32"), clsName) == 0)
	{
		return false;
	}

	if (IsZoomed(hfg))
	{
		return true;
	}


	RECT fgrect;
	GetWindowRect(hfg, &fgrect);

	RECT dkrect;
	GetWindowRect(hdesk, &dkrect);

	int borderAllowWidth = (dkrect.right - dkrect.left)*0.05;
	if (fgrect.top - borderAllowWidth <= dkrect.top
		&& fgrect.left - borderAllowWidth <= dkrect.left
		&& fgrect.bottom + borderAllowWidth >= dkrect.bottom
		&& fgrect.right + borderAllowWidth >= dkrect.right)
	{
		return true;
	}

	return false;
}

bool checkFileExist(TCHAR * fileName)
{
	WIN32_FIND_DATA  FindFileData;
	HANDLE hFind;
	hFind = FindFirstFile(fileName, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	else
	{
		FindClose(hFind);
		return true;
	}
}
#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO:  在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);


	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));
	if (checkFileExist(BGIMG_PATH)){
		g_hasExistBgImgFile = true;
	}
	else{
		g_hasExistBgImgFile = false;
		writeConfigHelpInfo();
	}


	Gdiplus::GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_gdiplusToken;
	if (g_hasExistBgImgFile)
	{
		//使用GDI+ 需要初始化库 和释放（见主函数返回前）
		Gdiplus::GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);
	}

	// 主消息循环: 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	if (g_hasExistBgImgFile)
	{
		Gdiplus::GdiplusShutdown(m_gdiplusToken);
	}
	return (int)msg.wParam;
}



//
//  函数:  MyRegisterClass()
//
//  目的:  注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;// MAKEINTRESOURCE(IDC_MY);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数:  InitInstance(HINSTANCE, int)
//
//   目的:  保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // 将实例句柄存储在全局变量中

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		0, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	UpdateWindow(hWnd);
	HWND wallHwnd = GetDesktopWallpaperWorkerHwnd();
	if (wallHwnd != NULL){
		SetParent(hWnd, wallHwnd);
	}
	//消除边框
	SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) - WS_CAPTION);
	ShowWindow(hWnd, SW_MAXIMIZE);

	SetTimer(hWnd, ID_TIMER_FLASH_DRAW, TIMER_FLASH_TIMEOUT, NULL);


	return TRUE;
}

//
//  函数:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	static RECT rect = { 0 };

	if (g_mygame == NULL && g_my2048 == NULL)
	{
		isSnakeMode = (rand() % 100<70);
	}

	if (g_mygame == NULL)
	{
		int pwid = GetSystemMetrics(SM_CXFULLSCREEN);
		int phei = GetSystemMetrics(SM_CYFULLSCREEN);
		double whrate = pwid*1.0 / phei;
		g_cols = BLOCK_COUNT_ONE_LINE;
		g_rows = BLOCK_COUNT_ONE_LINE * whrate;
		InitSnackGame();
	}

	if (g_my2048 == NULL)
	{
		int pwid = GetSystemMetrics(SM_CXFULLSCREEN);
		int phei = GetSystemMetrics(SM_CYFULLSCREEN);
		double whrate = pwid*1.0 / phei;
		g_cols = BLOCK_COUNT_ONE_LINE;
		g_rows = BLOCK_COUNT_ONE_LINE * whrate;
		Init2048Game();
	}





	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择: 
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_SIZE:
		GetWindowRect(hWnd, &rect);
		g_WinWidth = rect.right - rect.left;
		g_WinHeight = rect.bottom - rect.top;

		g_light.SetMaxCount(MAX_LIGHT_COUNT);
		g_light.SetWindowSize(g_WinWidth, g_WinHeight);
		g_light.InitLight();

		g_raiseChar.SetMaxCount(MAX_CHAR_COUNT);
		g_raiseChar.SetWindowSize(g_WinWidth, g_WinHeight);
		g_raiseChar.InitCharNode();

		g_traceStar.SetMaxCount(MAX_STAR_COUNT);
		g_traceStar.SetWindowSize(g_WinWidth, g_WinHeight);
		g_traceStar.InitNode();

		g_startVortext.SetMaxCount(MAX_STAR_VORTEX_COUNT);
		g_startVortext.SetWindowSize(g_WinWidth, g_WinHeight);
		g_startVortext.InitLight();

		g_meteorShower.SetMaxCount(MAX_METEROR_COUNT);
		g_meteorShower.SetWindowSize(g_WinWidth, g_WinHeight);
		g_meteorShower.InitLight();

		m_intelNet.SetMaxCount(MAX_INTELNET_COUNT);
		m_intelNet.SetWindowSize(g_WinWidth, g_WinHeight);
		m_intelNet.InitLight();

		g_emitBall.SetMaxCount(MAX_EMITBALL_COUNT);
		g_emitBall.SetWindowSize(g_WinWidth, g_WinHeight);
		g_emitBall.InitLight();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps); //闪频的主要原因，目前看起来就是 BeginPaint和EndPaint捣鬼，具体真实原因不详
		// TODO:  在此添加任意绘图代码...
		//DrawGame(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_TIMER:
		RunGame();
		if ((GetAsyncKeyState(VK_F5) & 0x8000) && (GetAsyncKeyState(VK_UP) & 0x8000))
		{
			RunGame();
			if ((GetAsyncKeyState(VK_SHIFT) & 0x8000))
			{
				RunGame();
			}
			if ((GetAsyncKeyState(VK_CONTROL) & 0x8000))
			{
				RunGame();
			}
			if ((GetAsyncKeyState(VK_MENU) & 0x8000))
			{
				RunGame();
			}
		}
		if (hasFullScreenWindow(hWnd)) //减少前台全屏（含最大化）软件（主要是打游戏）运行时，占用CPU资源，CPU占用基本为0%
			break;
		DrawGame(GetDC(hWnd));		//因此解决方式为，直接在定时器中绘制，不发送消息了，然后，竟然很好的运行，不会闪频，并且帧率也能提高很多
		//InvalidateRect(hWnd, NULL, TRUE);  //使用此方法激发的WM_PAINT消息，在WM_PAINT处理中会导致闪频
		{
			if (GetAsyncKeyState(VK_F5) & 0x8000 && GetAsyncKeyState(VK_SPACE) & 0x8000 && GetAsyncKeyState('K') & 0x8000)
			{
				HWND videoHwnd = GetDesktopWallpaperWorkerHwnd();
				SetParent(hWnd, videoHwnd);
				ShowWindow(hWnd, SW_MAXIMIZE);
			}
		}
		break;
	case WM_DESTROY:
		if (g_mygame != NULL)
		{
			delete g_mygame;
		}
		if (g_my2048 != NULL)
		{
			delete g_my2048;
		}
		KillTimer(hWnd, ID_TIMER_FLASH_DRAW);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
