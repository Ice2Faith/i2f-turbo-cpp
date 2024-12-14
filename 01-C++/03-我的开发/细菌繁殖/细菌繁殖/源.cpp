#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

HWND g_hwnd;
bool g_allowClick = true;
bool g_drawLoop = true;
int g_layer = 180;
bool g_allowDraw = true;
int g_winWidth;
int g_winHeight;
int g_scrWidth;
int g_scrHeight;


POINT g_startPoint;
POINT g_endPoint;



//最前端半透明
void SetMyWindowStyle(HWND hwnd)
{
	SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, g_winWidth, g_winHeight, SWP_NOACTIVATE);
	//窗口透明
	LONG wlong = GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED | WS_EX_TOOLWINDOW;
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


bool isKeyDown(int vKey){
	return GetAsyncKeyState(vKey) & 0x8000;
}

void keyCheckCallback(){

	static long lastKeyPressTime = 0;
	if ((isKeyDown(VK_LWIN) || isKeyDown(VK_RWIN))){
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


	void drawTree(int level, POINT startPoint, double direction, int startLen){
		startColor = RGB(rand() % 100, rand() % 100, rand() % 100);
		endColor = RGB(rand() % 155 + 100, rand() % 155 + 100, rand() % 155 + 100);
		drawBole(level, level, startPoint, direction, startLen);
		POINT endPoint = getEndPoint(startPoint, startLen, direction);
		int nlen = nextLen(startLen);
		drawTreeNext(level - 1, level, endPoint, nlen, direction);


	}
private:
	void drawBole(int level, int sumLevel, POINT startPoint, double direction, int len){

		if (!g_allowDraw){
			keyCheckCallback();
			Sleep(1);
			return;
		}

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

		COLORREF color = RGB((int)cr, (int)cg, (int)cb);

		int width = log((double)level);
		if (width < 1){
			width = 1;
		}
		HPEN pen = CreatePen(0, width,color );
		HGDIOBJ oldpen=SelectObject(hdc, pen);
		POINT endPoint = getEndPoint(startPoint, len, direction);
		POINT points[4];
		points[0] = startPoint;
		points[3] = endPoint;

		for (int i = 1; i < 3; i++){

			int qlen = (rand() % (50 - 10 * i) + (30 + 10 * i))*1.0 / 100 * len;
			double qdirect = nextDirection(direction);
			POINT qend = getEndPoint(startPoint, qlen, qdirect);
			//Ellipse(hdc, qend.x - 3, qend.y - 3, qend.x + 3, qend.y + 3);
			points[i] = qend;
		}


		PolyBezier(hdc, points, 4);

		SelectObject(hdc, oldpen);
		DeleteObject(pen);

		keyCheckCallback();
		//Sleep(1);

	}
	int nextLen(int len){
		return len * ((rand() % 25 + 70)*1.0 / 100);
	}
	double nextDirection(double startDirection){
		double fac = AngleToRadian(rand() % 60 - 60);
		if (rand() % 100 < 50){
			fac = 0.0 - fac;
		}
		return startDirection + fac;
	}
	void drawTreeNext(int level, int sumLevel, POINT startEnd, int startLen, double startDirection){
		if (level <= 0){
			return;
		}
		if (startLen < 2){
			return;
		}
		if (startEnd.x < 0 || startEnd.x >= dcWidth || startEnd.y<0 || startEnd.y>dcHeight){
			return;
		}
		int boleCount = rand() % 2 + 2;
		for (int i = 0; i < boleCount; i++){
			double ndirect = nextDirection(startDirection);
			drawBole(level, sumLevel, startEnd, ndirect, startLen);

			double rate = level*1.0 / sumLevel;
			if (rand() % 100 < (1.0 - rate) * 30){
				continue;
			}
			POINT endPoint = getEndPoint(startEnd, startLen, ndirect);
			int nlen = nextLen(startLen);
			
			drawTreeNext(level - 1, sumLevel, endPoint, nlen, ndirect);
		}
		//Sleep(1);
	}
	COLORREF startColor;
	COLORREF endColor;
	HDC hdc;
	int dcWidth;
	int dcHeight;
};




int main(int argc, char * argv[]){

	g_scrWidth = GetSystemMetrics(SM_CXSCREEN);
	g_scrHeight = GetSystemMetrics(SM_CYSCREEN);
	g_winWidth = g_scrWidth;
	g_winHeight = g_scrHeight;

	


	g_hwnd = initgraph(g_winWidth, g_winHeight);
	//消除边框
	SetWindowLong(g_hwnd, GWL_STYLE, GetWindowLong(g_hwnd, GWL_STYLE) - WS_CAPTION);
	SetMyWindowStyle(g_hwnd);
	setbkmode(TRANSPARENT);
	HDC hdc = GetImageHDC();
	srand((unsigned int)time(NULL));

	CherryTree tree(hdc, g_winWidth, g_winHeight);
	while (g_drawLoop){
		cleardevice();

		
		int row = rand() % 3 + 5;
		for (int i = 0; i < row; i++){
			int col = rand() % 6 + 9;
			for (int j = 0; j < col; j++){

				g_startPoint.x = (g_winWidth / col)*(0.5 + j);
				g_startPoint.y = (g_winHeight / row)*(i + 1);

				g_endPoint.x = (g_winWidth / col)*(0.5 + j);
				g_endPoint.y = (g_winHeight / row)*(i + 1-0.23);

				double startDirection = tree.getLineDirection(g_startPoint, g_endPoint);
				int level = rand()%5+10;
				int startLen = (g_winWidth/col) / 5;
				tree.drawTree(level, g_startPoint, startDirection, startLen);

				for (int p = 0; p < 30; p++){
					keyCheckCallback();
					Sleep(1);
				}
			}
		}
		
		for (int p = 0; p < 5000; p++){
			keyCheckCallback();
			Sleep(1);
		}
	}

	closegraph();
	return 0;
}