// ��������̰���߶�̬��ֽ.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "��������̰���߶�̬��ֽ.h"

//����stdafx.h�ж����˺�#define WIN32_LEAN_AND_MEAN  �ᵼ��gdiplus�еĺܶ������Ҳ��������������Ҫ���comdef.h
//��Ȼ��Ҳ����ȥ������꣬ȥ�������֮��ԭ����windows.h���Ѿ�������comdef.h
//��Ҫ˵����������ȥ���껹�����comdef.h,��Ҫ��include gdiplus֮ǰ��������Ȼ��Ч������ᱨ��ܶ�

/*
ȫ�ֿ��ư���˵����
F5+L:����ɢ����ƿ����л�
F5+C:�����ַ����ƿ����л�
F5+S:������ɢ�����ǻ��ƿ����л�
F5+V:���������л��ƿ����л�
F5+T:��������Ч�����л�
F5+M:����ͼƬ��Ⱦ����
F5+I:����������ƿ����л�
F5+E:3Dͼ������
F5+Shift+E:�л�3Dͼ��
F5+Q:�ر�����������Ч

F5+H:���ء���ʾ����ͼ��

F5+TAB:�л���Ϸģʽ��̰���ߡ�2048
F5+G:��Ϸģʽ����

F5+P:�л�2048��Ϸ��ʾ���

F5+UP +Shift +Control +Alt:ʵ�ֶ������������ı����屶��
���밴����F5+UP,������(Shift/Control/Alt)��������Խ�࣬����Խ��

F1:��ס�ڼ�����û�����ģʽ
�ڴ��ڼ�������Լ���̰������Ϸ�����ٶȻ����
ͨ��UP/DOWN/LEFT/RIGHT���з������
ǰ������ð�סF1

F5+A:ʹ���Զ���ɫ����
F5+B:ʹ�ú�ɫ����
F5+W:ʹ�ð�ɫ����

F5+O:��������ɫ���俪���л�

F5+�ո�+K�������汻����ʱ���������³�����̬��ֽ
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
	TCHAR helpInfo[] = { TEXT("��ǰΪ��ɫʱ�佥�䱳��\n\
�����Ҫʹ��ͼƬ����\n\
�뽫 bgimg.png �ļ������ڱ�����ͬĿ¼�£�����������������\n\
�����������ȴ����������(Ctrl+Shift+Esc)�ҵ�������ѡ���������\n\
֮�����������б�����\n\
����ע�⣬�⽫�ᵼ��ռ�ýϸߵ�CPU��Դ\n\
��Ȼ��ˣ��������������ʹ�õ����������󻯻���ȫ��״̬\n\
��ô�����������ͣ�����ͷų�CPU��CPUռ�ý���ӽ�0%\n\
��ܰ��ʾ��\n\
F5+L/C/S/V/T/I/E:���Կ������߽��ò�����Ч���Ӷ��ﵽ����Ҫ������Ч��\n\
������Ч���ҷֱ��֮Ϊ��\n\
\t���ӷ��䣬����������׷�ǻ𻨣��������У�ʱ�����ǣ�����������3D��״\n\
F5+A/B/W:���������л���ɫ������ɫΪ�Զ�����ɫ����ɫ\n\
F5+M���л��Ƿ�ʹ�ñ���ͼƬ���Ǵ�ɫ����\n\
F5+O���л��ߵ���ɫ����ϵͳ\n\
F5+Q���ر�������Ч\n\
F5+H:���ء���ʾ����ͼ��\n\
F5+Tab���л���Ϸ��2048/̰����\n\
F5+G���л���Ϸ��ʾ/����\n\
F5+P���л�2048������Ʒ��\n\
F5 + Shift + E:�л�3Dͼ��\n\
F5+UP[+Control[+Shift[+Alt]]]����Ϸ����2/3/4/5����\n\
F1+UP/DOWN/LEFT/RIGHT:������Լ�����Ϸ��ȡ������������Զ���\n\
") };
	MessageBox(NULL, helpInfo, TEXT("���ð��� -- ��������̰���߶�̬��ֽ"), MB_OK);
}

//����ͼƬ����������ʹ��GDI+
#include<comdef.h>	
#include<GdiPlus.h>
#pragma comment(lib,"gdiplus.lib")
#define BGIMG_PATH (L".\\bgimg.png")	//����ͼƬ·������
bool g_hasExistBgImgFile = false;	//��¼����ͼƬ�ļ��Ƿ���ڣ��������򲻳�ʼ��GDI+ �⣬����ʹ��CPU��Դ


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
#define ID_TIMER_FLASH_DRAW 0x101 //��ʱ��ID
#define TIMER_FLASH_TIMEOUT 24 //ˢ�¼�� ֡��=1000/ˢ�¼�� ��ˢ�¼��==24ʱ��֡��Ϊ41FPS

int g_WinWidth = 720; //��¼�������֮��Ĵ��ڴ�С������ĳ�ʼֵ��ʵ��ûʲô�õ�,��������
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

//�ж��ǲ���̰������Ϸ�����У��������2048��Ϸ
bool isSnakeMode = true;
Game2048 * g_my2048 = NULL;
int g_maxNum = 2;
MoveDirect g_direcs[4] = { MOV_UP, MOV_DOWN, MOV_LEFT, MOV_RIGHT };
MoveDirect g_auto2048MoveMainDirect = MOV_DOWN;
int g_auto2048MainIndex=1;


#define BLOCK_COUNT_ONE_LINE 80 //����̰���ߵ������������������Ļ��С�ȱ��������

bool g_isOpenWall = false;	//����̰�����Ƿ�ӵ���ı�ǽ��
Snack * g_mygame = NULL; //̰������Ϸ����

int g_cols = 0;	//�����ı���̰�������������ı��������������������˳�ʼֵû��
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

	//�����û��������ƣ��ڼ���м��٣����õ��û�����
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

	//�����û��������ƣ��ڼ���м��٣����õ��û�����
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

	static TCHAR weekday[7][5] = { TEXT("��"), TEXT("һ"), TEXT("��"), TEXT("��"), TEXT("��"), TEXT("��"), TEXT("��") };
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




	static TCHAR Tips[12][30] = { TEXT("�賿�ˣ�ע����ϢŶ��"),
		TEXT("ҹ�Ѿ����ˣ��Ͽ���Ϣ�ɣ�"),
		TEXT("����æ��ע������Ŷ��"),
		TEXT("�簲�����콫�����õ�һ�졣"),
		TEXT("Ŭ���ܶ�������������Ŀ��Ŷ��"),
		TEXT("Ŭ���ͻ����ջ񣬽�����һ��"),
		TEXT("�簲����Ϣ����һ�£�"),
		TEXT("Ϊ�����룬�������ͣ�"),
		TEXT("�����ʱ�⿪ʼ����"),
		TEXT("���Ϻã������������"),
		TEXT("����һ�£�׼����Ϣ����"),
		TEXT("������ҹ�ˣ�Ӧ����Ϣ����") };

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
			//����һ�£�ÿһ��ʱ�������л�һ��
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

// ȫ�ֱ���: 
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������: 
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

	// TODO:  �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);


	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
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
		//ʹ��GDI+ ��Ҫ��ʼ���� ���ͷţ�������������ǰ��
		Gdiplus::GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);
	}

	// ����Ϣѭ��: 
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
//  ����:  MyRegisterClass()
//
//  Ŀ��:  ע�ᴰ���ࡣ
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
//   ����:  InitInstance(HINSTANCE, int)
//
//   Ŀ��:  ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
	//�����߿�
	SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) - WS_CAPTION);
	ShowWindow(hWnd, SW_MAXIMIZE);

	SetTimer(hWnd, ID_TIMER_FLASH_DRAW, TIMER_FLASH_TIMEOUT, NULL);


	return TRUE;
}

//
//  ����:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
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
		// �����˵�ѡ��: 
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
		hdc = BeginPaint(hWnd, &ps); //��Ƶ����Ҫԭ��Ŀǰ���������� BeginPaint��EndPaint����������ʵԭ����
		// TODO:  �ڴ���������ͼ����...
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
		if (hasFullScreenWindow(hWnd)) //����ǰ̨ȫ��������󻯣��������Ҫ�Ǵ���Ϸ������ʱ��ռ��CPU��Դ��CPUռ�û���Ϊ0%
			break;
		DrawGame(GetDC(hWnd));		//��˽����ʽΪ��ֱ���ڶ�ʱ���л��ƣ���������Ϣ�ˣ�Ȼ�󣬾�Ȼ�ܺõ����У�������Ƶ������֡��Ҳ����ߺܶ�
		//InvalidateRect(hWnd, NULL, TRUE);  //ʹ�ô˷���������WM_PAINT��Ϣ����WM_PAINT�����лᵼ����Ƶ
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
