#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"AlgoContainer.hpp"

HWND g_hwnd;
bool g_allowClick = true;
bool g_drawLoop = true;
int g_layer = 180;
bool g_allowDraw = true;
int g_winWidth;
int g_winHeight;
int g_scrWidth;
int g_scrHeight;
double g_winScaleRate = 0.2857;

int g_winPosX=0;
int g_winPosY=0;

POINT g_startPoint;
POINT g_endPoint;

class Bole{
public:
	POINT startPoint;
	POINT points[4];
	int width;
	int len;
	double direction;
	COLORREF color;
	int level;
	int maxLevel;
	bool downMode;
	bool isDead;
	Bole(){
		downMode = false;
		isDead = false;
	}
	Bole(const Bole & bole){
		copyFormBole(bole);
	}
	Bole& operator=(const Bole & bole){
		copyFormBole(bole);
		return *this;
	}
private:
	void copyFormBole(const Bole & bole){
		this->startPoint = bole.startPoint;
		this->width = bole.width;
		this->len = bole.len;
		this->direction = bole.direction;
		this->color = bole.color;
		this->level = bole.level;
		this->maxLevel = bole.maxLevel;
		this->downMode = bole.downMode;
		this->isDead = bole.isDead;
		for (int i = 0; i < 4; i++){
			this->points[i] = bole.points[i];
		}
	}
};

AlgoList<Bole, int> g_treeBoles;

void calculatePointLocation(){
	int maxX = g_scrWidth - g_winWidth;
	int midX = maxX / 2;
	int maxY = g_scrHeight - g_winHeight;
	int midY = maxY / 2;
	if (g_winPosX == 0 && g_winPosY == 0){
		g_startPoint.x = 0;
		g_startPoint.y = 0;
		g_endPoint.x = g_winWidth / 8;
		g_endPoint.y = g_winHeight*0.3 + g_winHeight*(rand() % 3) *1.0/ 10;
	}
	if (g_winPosX == 0 && g_winPosY == midY){
		g_startPoint.x = 0;
		g_startPoint.y = g_winHeight / 2;
		g_endPoint.x = g_winWidth / 8;
		g_endPoint.y = g_winHeight/2+(rand()%10-10)*1.0/10*(g_winHeight/3);
	}
	if (g_winPosX == 0 && g_winPosY == maxY){
		g_startPoint.x = 0;
		g_startPoint.y = g_winHeight;
		g_endPoint.x = g_winWidth / 8;
		g_endPoint.y = g_winHeight *0.3 + (rand() % 3)*1.0 / 10 * g_winHeight;
	}
	if (g_winPosX == midX && g_winPosY == 0){
		g_startPoint.x = g_winWidth/2;
		g_startPoint.y = 0;
		g_endPoint.x = g_winWidth *0.3 + (rand() % 3)*1.0 / 10 * g_winWidth;
		g_endPoint.y = g_winHeight / 5;
	}
	if (g_winPosX == midX && g_winPosY == midY){
		g_startPoint.x = g_winWidth / 2;
		g_startPoint.y = g_winHeight;
		g_endPoint.x = g_winWidth *0.2 + (rand() % 6)*1.0 / 10 * g_winWidth;
		g_endPoint.y = g_winHeight * (10-rand()%5)*1.0/10;
	}
	if (g_winPosX == midX && g_winPosY == maxY){
		g_startPoint.x = g_winWidth / 2;
		g_startPoint.y = g_winHeight;
		g_endPoint.x = g_winWidth *0.3 + (rand() % 3)*1.0 / 10 * g_winWidth;
		g_endPoint.y = g_winHeight *4/ 5;
	}
	if (g_winPosX == maxX && g_winPosY == 0){
		g_startPoint.x = g_winWidth;
		g_startPoint.y = 0;
		g_endPoint.x = g_winWidth*7/8;
		g_endPoint.y = g_winHeight *0.3 + (rand() % 3)*1.0 / 10 * g_winHeight;
	}
	if (g_winPosX == maxX && g_winPosY == midY){
		g_startPoint.x = g_winWidth;
		g_startPoint.y = g_winHeight/2;
		g_endPoint.x = g_winWidth * 7 / 8;
		g_endPoint.y = g_winHeight *0.3 + (rand() % 3)*1.0 / 10 * g_winHeight;
	}
	if (g_winPosX == maxX && g_winPosY == maxY){
		g_startPoint.x = g_winWidth;
		g_startPoint.y = g_winHeight;
		g_endPoint.x = g_winWidth * 7 / 8;
		g_endPoint.y = g_winHeight *0.3 + (rand() % 3)*1.0 / 10 * g_winHeight;
	}
}

//最前端半透明
void SetMyWindowStyle(HWND hwnd)
{
	SetWindowPos(hwnd, HWND_TOPMOST, g_winPosX, g_winPosY, g_winWidth, g_winHeight, SWP_NOACTIVATE);
	//窗口透明
	LONG wlong = GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED| WS_EX_TOOLWINDOW;
	SetWindowLong(hwnd, GWL_EXSTYLE, wlong);
	if (g_allowClick){
		//穿透点击
		SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
	}
	else{
		//不穿透点击
		SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), g_layer, LWA_ALPHA);
	}

}

void showHelpTips(){
	char helpInfo[1024] = { "\
程序说明：\n\
\t随机绘制随机颜色的海草，或者也可以认为是树\n\
\t树的过程：生成--成熟--衰老--凋零\n\
\t树凋零的时候，枝干会掉落，并且会掉落向鼠标的一方\n\
全局控制按键：\n\
\tWin+CapsLock:切换透明模式(全透明穿透点击、半透明不穿透点击)\n\
\tWin+空格：暂停绘制\n\
\tWin+Shift+空格：暂停绘制并清空画板\n\
\tWin+Esc:退出本程序\n\
\tWin+回车：保存当前绘图\n\
\tCapsLock+加号：增价不透明度\n\
\tCapsLock+减号：降低不透明度\n\
\tAlt+上/下/左/右：调整绘制窗口在屏幕中四角的位置\n\
\tShift+上下/左右：调整绘制窗口在屏幕中居中的位置\n\
" };
	MessageBox(g_hwnd, helpInfo, "海草--操作提示 by ugex",MB_OK);
}

bool isKeyDown(int vKey){
	return GetAsyncKeyState(vKey) & 0x8000;
}

void keyCheckCallback(){
	
	static long lastKeyPressTime = 0;
	if ((isKeyDown(VK_LWIN) || isKeyDown(VK_RWIN)) ){
		if (isKeyDown(VK_CAPITAL)){
			long nowTime = GetTickCount();
			if (nowTime - lastKeyPressTime < 300){
				return;
			}
			lastKeyPressTime = nowTime;
			g_allowClick = !g_allowClick;
		}
		if (isKeyDown(VK_SPACE)){
			if (isKeyDown(VK_SHIFT)){
				cleardevice();
			}
			g_allowDraw = !g_allowDraw;
		}
		if (isKeyDown(VK_ESCAPE)){
			g_drawLoop = false;
			exit(0);
		}

		static long lastSaveTime = 0;
		if (isKeyDown(VK_RETURN)){
			long nowTime = GetTickCount();
			if (nowTime - lastSaveTime < 500){
				return;
			}
			lastSaveTime = nowTime;
			char saveFile[1024] = { 0 };
			sprintf(saveFile, ".\\tree-%d.png\0", time(NULL));
			saveimage(saveFile, NULL);
		}
		SetMyWindowStyle(g_hwnd);
	}
	if (isKeyDown(VK_CAPITAL)){
		if (isKeyDown(VK_ADD)){
			if (g_layer < 255){
				g_layer++;
			}
		}
		if (isKeyDown(VK_SUBTRACT)){
			if (g_layer >1){
				g_layer--;
			}
		}
		SetMyWindowStyle(g_hwnd);
	}
	if (isKeyDown(VK_MENU)){
		if (isKeyDown('A') || isKeyDown(VK_LEFT)){
			g_winPosX = 0;
		}
		if (isKeyDown('D') || isKeyDown(VK_RIGHT)){
			g_winPosX = g_scrWidth - g_winWidth;
		}
		if (isKeyDown('S') || isKeyDown(VK_DOWN)){
			g_winPosY = g_scrHeight - g_winHeight;
		}
		if (isKeyDown('W') || isKeyDown(VK_UP)){
			g_winPosY = 0;
		}
		SetMyWindowStyle(g_hwnd);
	}
	if (isKeyDown(VK_SHIFT)){
		if ((isKeyDown('A') || isKeyDown(VK_LEFT))
			&& (isKeyDown('D') || isKeyDown(VK_RIGHT))){
			g_winPosX = (g_scrWidth - g_winWidth)/2;
		}
		
		if ((isKeyDown('S') || isKeyDown(VK_DOWN))
			&& (isKeyDown('W') || isKeyDown(VK_UP))){
			g_winPosY = (g_scrHeight - g_winHeight)/2;
		}

		SetMyWindowStyle(g_hwnd);
	}
}

class CherryTree{
public:
	CherryTree(HDC hdc, int dcWidth, int dcHeight){
		this->hdc = hdc;
		this->dcWidth = dcWidth;
		this->dcHeight = dcHeight;
	}

	static double  getLineDirection(const POINT & startPoint, const POINT & endPoint)
	{
		int dx = endPoint.x - startPoint.x;
		int dy = endPoint.y - startPoint.y;
		return atan2(dy*1.0, dx*1.0);
	}

	static POINT getEndPoint(const POINT & startPoint, int length, double direction)
	{
		POINT ret;
		ret.x = startPoint.x + length*cos(direction);
		ret.y = startPoint.y + length*sin(direction);
		return ret;
	}

	static double AngleToRadian(double angle)
	{
		return angle / 180 * 3.1415926535;
	}

	static double CherryTree::RadianToAngle(double radian)
	{
		return radian / 3.1415926535 * 180;
	}

	
	void drawTree(int level,POINT startPoint,double direction,int startLen){
		startColor = RGB(rand()%100,rand()%100,rand()%100);
		endColor = RGB(rand()%155+100,rand()%155+100,rand()%155+100);
		drawBole(level,level,startPoint, direction, startLen);
		POINT endPoint = getEndPoint(startPoint, startLen, direction);
		int nlen = nextLen(startLen);
		drawTreeNext(level - 1,level, endPoint, nlen,direction);
	}
private:
	void drawBole(int level,int sumLevel,POINT startPoint, double direction, int len){

		/*if (!g_allowDraw){
			keyCheckCallback();
			Sleep(1);
			return;
		}*/

		double cr = 0, cg = 0, cb = 0;

		double sr = startColor & 0xff;
		double sg = (startColor >> 8) & 0xff;
		double sb = (startColor >> 16) & 0xff;

		double er = endColor & 0xff;
		double eg = (endColor >> 8) & 0xff;
		double eb = (endColor >> 16) & 0xff;

		double rate = level*1.0 / sumLevel;

		cr = sr*rate + er*(1.0 - rate);
		cg = sg*rate + eg*(1.0 - rate);
		cb = sb*rate + eb*(1.0 - rate);

		COLORREF color = RGB((int)cr,(int)cg,(int)cb);
		
		int width = log((double)level);
		if (width < 1){
			width = 1;
		}
		//HPEN pen = CreatePen(0, width,color );
		//HGDIOBJ oldpen=SelectObject(hdc, pen);
		POINT endPoint = getEndPoint(startPoint, len, direction);
		POINT points[4];
		points[0] = startPoint;
		points[3] = endPoint;

		for (int i = 1; i < 3; i++){

			int qlen = (rand() % (50-10*i) + (30+10*i))*1.0 / 100 * len;
			double qdirect = nextDirection(direction);
			POINT qend = getEndPoint(startPoint, qlen, qdirect);
			//Ellipse(hdc, qend.x - 3, qend.y - 3, qend.x + 3, qend.y + 3);
			points[i] = qend;
		}
		
		Bole bole;
		bole.color = color;
		bole.direction = direction;
		bole.len = len;
		bole.startPoint = startPoint;
		bole.level = level;
		bole.maxLevel = sumLevel;
		for (int i = 0; i < 4; i++){
			bole.points[i] = points[i];
		}
		bole.width = width;
		g_treeBoles.pushBack(bole);

		//PolyBezier(hdc, points, 4);

		/*SelectObject(hdc, oldpen);
		DeleteObject(pen);*/

		//keyCheckCallback();
		//Sleep(1);

	}
	int nextLen(int len){
		return len * ((rand()%25+70)*1.0/100);
	}
	double nextDirection(double startDirection){
		double fac = AngleToRadian(rand() % 60 - 60);
		if (rand() % 100 < 50){
			fac = 0.0 - fac;
		}
		return startDirection + fac;
	}
	void drawTreeNext(int level,int sumLevel,POINT startEnd,int startLen,double startDirection){
		if (level <= 0){
			return;
		}
		int boleCount =  rand() % 2 + 2;
		for (int i = 0; i < boleCount; i++){
			double ndirect = nextDirection(startDirection);
			drawBole(level,sumLevel,startEnd, ndirect, startLen);
			
			double rate = level*1.0 / sumLevel;
			if (rand() % 100 < (1.0 - rate) * 30){
				continue;
			}
			POINT endPoint = getEndPoint(startEnd, startLen, ndirect);
			int nlen = nextLen(startLen);
			drawTreeNext(level - 1,sumLevel, endPoint, nlen, ndirect);
		}
	}
	COLORREF startColor;
	COLORREF endColor;
	HDC hdc;
	int dcWidth;
	int dcHeight;
};




int main(int argc, char * argv[]){
	
	g_scrWidth= GetSystemMetrics(SM_CXSCREEN);
	g_scrHeight= GetSystemMetrics(SM_CYSCREEN);
	g_winWidth = g_scrWidth*g_winScaleRate;
	g_winHeight = g_scrHeight * g_winScaleRate;
	g_winPosX =  g_scrWidth - g_winWidth;
	g_winPosY =  g_scrHeight - g_winHeight;

	g_startPoint.x = g_winWidth / 2;
	g_startPoint.y = g_winHeight;
	g_endPoint.x = g_startPoint.x;
	g_endPoint.y = g_startPoint.y / 2;

	//g_winPosX = (g_scrWidth - g_winWidth) / 2;
	//g_winPosY = (g_scrHeight - g_winHeight);

	//g_startPoint.x = g_winWidth / 2;
	//g_startPoint.y = g_winHeight;
	//g_endPoint.x = g_winWidth *0.3 + (rand() % 3)*1.0 / 10 * g_winWidth;
	//g_endPoint.y = g_winHeight * 4 / 5;

	g_hwnd = initgraph(g_winWidth, g_winHeight);
	//消除边框
	SetWindowLong(g_hwnd, GWL_STYLE, GetWindowLong(g_hwnd, GWL_STYLE) - WS_CAPTION);
	SetMyWindowStyle(g_hwnd);
	setbkmode(TRANSPARENT);
	HDC hdc = GetImageHDC();
	srand((unsigned int)time(NULL));

	showHelpTips();
	CherryTree tree(hdc, g_winWidth, g_winHeight);
	while (g_drawLoop){
		cleardevice();
		calculatePointLocation();
		int yr = rand() % 55 + 200;
		int yg = rand() % 105 + 150;
		
		COLORREF yellow = RGB(yr, yg, 0);
		double startDirection = tree.getLineDirection(g_startPoint, g_endPoint);
		int level = 12;
		int startLen = g_winHeight / 5;
		g_treeBoles.clear();
		tree.drawTree(level, g_startPoint, startDirection, startLen);
		int size = g_treeBoles.size();
		g_treeBoles.setCursorToBegin();
		while (g_treeBoles.hasNext()){
			if (!g_allowDraw){
				keyCheckCallback();
				Sleep(1);
				continue;
			}
			
			Bole& bole = g_treeBoles.getCursorData();
			HPEN pen = CreatePen(0, bole.width, bole.color);
			HGDIOBJ oldpen = SelectObject(hdc, pen);
			PolyBezier(hdc, bole.points, 4);

			SelectObject(hdc, oldpen);
			DeleteObject(pen);
			g_treeBoles.nextCursor();
			
			keyCheckCallback();
			Sleep(1);
		}
		
		Sleep(3000);

		int curSize = size;
		while (curSize>0){
			if (!g_allowDraw){
				keyCheckCallback();
				Sleep(1);
				continue;
			}
			
			BeginBatchDraw();
			cleardevice();
			g_treeBoles.setCursorToBegin();
			int psize = 0;
			while (g_treeBoles.hasNext()){
				Bole& bole = g_treeBoles.getCursorData();
				if (bole.isDead){
					g_treeBoles.nextCursor();
					continue;
				}
				COLORREF startColor = bole.color;
				double cr = 0, cg = 0, cb = 0;

				double sr = startColor & 0xff;
				double sg = (startColor >> 8) & 0xff;
				double sb = (startColor >> 16) & 0xff;

				double er = yellow & 0xff;
				double eg = (yellow >> 8) & 0xff;
				double eb = (yellow >> 16) & 0xff;

				double rate = curSize*1.0 / size;

				cr = sr*rate + er*(1.0 - rate);
				cg = sg*rate + eg*(1.0 - rate);
				cb = sb*rate + eb*(1.0 - rate);

				COLORREF color = RGB((int)cr, (int)cg, (int)cb);

				int shouldDownBoleLevel = (1.0-rate)*bole.maxLevel;
				if (bole.downMode || ((bole.level<=shouldDownBoleLevel+1) && (rand()%1000<5))){
					
					if (rand() % 100 < 15){
						if (rand() % 100 < (10*rate)){
							double fac = CherryTree::AngleToRadian(rand() % 15-15);
							if (rand() % 100 < 50){
								fac = 0 - fac;
							}
							double direction = bole.direction + fac;
							bole.direction = direction;
						}
						if (rand() % 100 < (45*rate)){
							POINT endPoint = CherryTree::getEndPoint(bole.startPoint,bole.len,bole.direction);
							bole.points[0] = bole.startPoint;
							bole.points[3] = endPoint;

							for (int i = 1; i < 3; i++){

								int qlen = (rand() % (50 - 10 * i) + (30 + 10 * i))*1.0 / 100 * bole.len;
								double fac = CherryTree::AngleToRadian(rand() % 60-60);
								if (rand() % 100 < 50){
									fac = 0 - fac;
								}
								double qdirect = bole.direction+fac;
								POINT qend = CherryTree::getEndPoint(bole.startPoint, qlen, qdirect);
								//Ellipse(hdc, qend.x - 3, qend.y - 3, qend.x + 3, qend.y + 3);
								bole.points[i] = qend;
							}
						}
						
					}
					
					int fullOutCount = 0;
					int yadd = rand() % (bole.width+1) ;
					int xadd = rand() % 5 - 2;

					if (rand() % 100 < 25){
						POINT pcursor;
						GetCursorPos(&pcursor);
						POINT pcur = bole.points[0];
						ClientToScreen(g_hwnd, &pcur);
						int stepX = (rand() % 5)*rate;
						if (pcursor.x > pcur.x){
							xadd += stepX;
						}
						else{
							xadd -= stepX;
						}
						yadd -= rand() % 2;

					}

					bole.startPoint.y += yadd;
					bole.startPoint.x += xadd;
					
					
					for (int i = 0; i < 4; i++){
						bole.points[i].y += yadd;
						bole.points[i].x += xadd;
						if (bole.points[i].y>g_winHeight){
							fullOutCount++;
						}
						
					}
					if (fullOutCount == 4){
						bole.isDead = true;
					}

					if (rand() % 1000 < 5){
						bole.isDead=true;
					}
						
					bole.downMode = true;
				}

				HPEN pen = CreatePen(0, bole.width, color);
				HGDIOBJ oldpen = SelectObject(hdc, pen);
				PolyBezier(hdc, bole.points, 4);

				SelectObject(hdc, oldpen);
				DeleteObject(pen);
				
				
				g_treeBoles.nextCursor();
				psize++;
			}
			EndBatchDraw();
			keyCheckCallback();
			Sleep(20);
			curSize--;
		}
	}

	closegraph();
	return 0;
}