#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"AlgoContainer.hpp"

HWND g_hwnd;
bool g_allowClick =  true;
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

class Light{
public:
	POINT startPoint;
	double width;
	double direction;
	COLORREF color;
	bool isDead;
	double finalDirection;
	double maxLen;
	bool isGrowthMode;
	double step;
	double curLen;
	int type;


	Light(){
		isGrowthMode = true;
		isDead = false;
		curLen = 0;
	}
	Light(const Light & bole){
		copyForm(bole);
	}
	Light& operator=(const Light & bole){
		copyForm(bole);
		return *this;
	}
private:
	void copyForm(const Light & bole){
		this->startPoint = bole.startPoint;
		this->width = bole.width;
		this->maxLen = bole.maxLen;
		this->direction = bole.direction;
		this->color = bole.color;
		this->finalDirection = bole.finalDirection;
		this->isGrowthMode = bole.isGrowthMode;
		this->step = bole.step;
		this->isDead = bole.isDead;
		this->curLen = bole.curLen;
		this->type = bole.type;
	}
};

AlgoList<Light, int> g_Lights;
AlgoList<Light, int> g_SubLights;

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
\t烟花的过程：发射-爆开-散灭\n\
\t放烟花应该是一件非常让人喜爱的事，所以，在这里，可以放烟花！\n\
全局控制按键：\n\
\t空格：有较大概率会放出一只烟花\n\
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
	MessageBox(g_hwnd, helpInfo, "烟花--操作提示 by ugex",MB_OK);
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




double randDouble(){
	return (rand() % 10000) / 10000.0;
}
int randInt(int max){
	return rand() % max;
}
int randIntBetween(int min, int max){
	return rand() % (max - min) + min;
}
double angle2Radian(double angle){
	return angle / 180.0*3.1415926535;
}
double getRadianByPoint(double x1, double y1, double x2, double y2){
	return atan2(y2 - y1, x2 - x1);
}

COLORREF getRandomColorGtAvg(int avg){
	int pavg = 0;
	int r = 0;
	int g = 0;
	int b = 0;
	do{
		r = randInt(256);
		g = randInt(256);
		b = randInt(256);
		pavg = (r + g + b) / 3.0;
	} while (pavg<avg);
	return RGB(r,g,b);
}

void buildLight(){
	Light light;
	light.startPoint.x = g_winWidth*randDouble();
	light.startPoint.y = g_winHeight;
	light.width = randIntBetween(3, 8);
	light.color = RGB(getRandomColorGtAvg(64), getRandomColorGtAvg(64), getRandomColorGtAvg(64));
	light.direction =  getRadianByPoint(light.startPoint.x, light.startPoint.y, light.startPoint.x + randIntBetween(-5, 5), light.startPoint.y - 100);
	light.finalDirection = light.direction +angle2Radian(randIntBetween(-15, 15));
	light.isDead = false;
	light.isGrowthMode = true;
	light.maxLen = randIntBetween(g_winHeight / 4, g_winHeight / 2);
	light.step = randIntBetween(1, 5);
	light.curLen = 0;
	light.type = randInt(3);
	g_Lights.add(light);
}

void buildSubLights(Light & slight){
	Light light;
	light.startPoint.x = slight.startPoint.x;
	light.startPoint.y = slight.startPoint.y;
	light.width = randIntBetween(3, 5);
	light.color = RGB(getRandomColorGtAvg(64), getRandomColorGtAvg(64), getRandomColorGtAvg(64));
	light.direction = angle2Radian(randDouble()*360);
	light.finalDirection = getRadianByPoint(light.startPoint.x,light.startPoint.y,light.startPoint.x+randIntBetween(-15,15),light.startPoint.y+100);
	light.isDead = false;
	light.isGrowthMode = true;
	light.maxLen = randIntBetween(g_winHeight / 8, g_winHeight / 4);
	light.step = randIntBetween(1, 3);
	light.curLen = 0;
	light.type = slight.type;
	g_SubLights.add(light);
}

void drawLight(Light & light){
	double rate = light.curLen*1.0 / light.maxLen;
	double r = light.color & 0xff;
	double g = (light.color >> 8) & 0xff;
	double b = (light.color >> 16) & 0xff;

	r = r*rate;
	g = g*rate;
	b = b*rate;

	COLORREF color = RGB(r, g, b);
	
	if (light.type == 0){
		setfillcolor(color);

		int pcount = rand() % 100<17 ? randIntBetween(13, 23) : randIntBetween(5, 11);
		for (int i = 0; i < pcount; i++){
			double prate = i*1.0 / pcount;
			double plen = light.curLen*prate;
			double direct = light.direction*(1.0 - prate) + light.finalDirection*prate;
			double dwid = light.width*rate*prate;
			int endx = light.startPoint.x + plen*cos(direct);
			int endy = light.startPoint.y + plen *sin(direct);
			
			solidcircle(endx, endy, dwid);
			
			
			
			
		}
	}
	else if (light.type == 1){
		int pcount = rand() % 100<17 ? randIntBetween(13, 23) : randIntBetween(5, 11);
		for (int i = 0; i < pcount; i++){
			double prate = i*1.0 / pcount;
			double plen = light.curLen*prate;
			double direct = light.direction*(1.0 - prate) + light.finalDirection*prate;
			double dwid = light.width*rate*prate;
			int endx = light.startPoint.x + plen*cos(direct);
			int endy = light.startPoint.y + plen *sin(direct);


			setlinecolor(color);
			setlinestyle(PS_DOT, dwid);

			line(endx - dwid * 2, endy, endx + dwid * 2, endy);
			line(endx, endy - dwid * 2, endx, endy + dwid * 2);

		}
	}
	else if (light.type == 2){
		int pcount = rand() % 100<17 ? randIntBetween(13, 23) : randIntBetween(5, 11);
		for (int i = 0; i < pcount; i++){
			double prate =  i*1.0 / pcount;
			double plen = light.curLen*prate;
			double direct = light.direction *(1.0 - prate) + light.finalDirection*prate;
			double dwid = light.width*rate*prate;
			int endx = light.startPoint.x + plen*cos(direct);
			int endy = light.startPoint.y + plen *sin(direct);


			setlinecolor(color);
			setlinestyle(PS_DASHDOT, 1);

			line(endx - dwid * 2, endy, endx + dwid * 2, endy);
			line(endx, endy - dwid * 2, endx, endy + dwid * 2);

		}
	}
}

int main(int argc, char * argv[]){
	
	g_scrWidth= GetSystemMetrics(SM_CXSCREEN);
	g_scrHeight= GetSystemMetrics(SM_CYSCREEN);
	g_winWidth = g_scrWidth*g_winScaleRate;
	g_winHeight = g_scrHeight * g_winScaleRate;
	/*g_winPosX =  g_scrWidth - g_winWidth;
	g_winPosY =  g_scrHeight - g_winHeight;*/

	g_winPosX = 0;// g_scrWidth - g_winWidth;
	g_winPosY = g_scrHeight - g_winHeight;

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
	while (g_drawLoop){
		cleardevice();
		BeginBatchDraw();
		calculatePointLocation();
		

		if (g_Lights.size() < 5){
			int lightCount = randInt(100)<21?randIntBetween(2,8):randIntBetween(1, 5);
			for (int i = 0; i < lightCount; i++){
				buildLight();
			}
		}

	
			int i = 0;
			while (i<g_Lights.size()){
				Light& light = g_Lights.get(i);
				
				if (light.isGrowthMode){
					if (light.curLen >= light.maxLen){
						light.isGrowthMode = false;
					}
					light.curLen += light.step;
				}
				else{
					if (light.curLen <= 0){
						light.isDead = true;
					}
					light.curLen -= light.step;
				}

				light.direction = light.direction*0.97 + light.finalDirection*0.03;
				light.startPoint.x += light.step*cos(light.direction);
				light.startPoint.y += light.step*sin(light.direction);
				


				drawLight(light);

				if (light.isDead){
					Light deadLight;
					g_Lights.remove(i,&deadLight);
					if (randInt(100) < 95){
						int subCount = randInt(100)<17 ? randIntBetween(30, 80) : randIntBetween(15, 50);
						for (int i = 0; i < subCount; i++){
							buildSubLights(deadLight);
						}
					}
					i--;
				}
				i++;
			}

		
			i=0;
			while (i<g_SubLights.size()){
				Light& light = g_SubLights.get(i);

				if (light.isGrowthMode){
					if (light.curLen >= light.maxLen){
						light.isGrowthMode = false;
					}
					light.curLen += light.step;
				}
				else{
					if (light.curLen <= 0){
						light.isDead = true;
					}
					light.curLen -= light.step;
				}

				if (light.type!=2)
				light.direction = light.direction*0.97 + light.finalDirection*0.03;
				light.startPoint.x += light.step*cos(light.direction);
				light.startPoint.y += light.step*sin(light.direction);

				if (light.type == 2){
					light.direction += angle2Radian(randInt(18)-9);
				}
				

				drawLight(light);

				if (light.isDead){
				
					g_SubLights.remove(i, NULL);
				
					i--;
				}
				i++;
			}

			EndBatchDraw();

			if (isKeyDown(VK_SPACE)){
				if (randInt(100) < 60){
					buildLight();
				}
			}
			keyCheckCallback();
			Sleep(30);
		
	}

	closegraph();
	return 0;
}