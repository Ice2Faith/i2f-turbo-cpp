#include<graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include<vector>
#include<algorithm>
#include"PhysicalReflect.h"
#include"VideoWallpaperHelper.h"

#include<ShlObj.h>
#define META_FILE_PATH "PhysicalHole.meta"
#pragma comment(lib,"shell32.lib")

using namespace std;
using namespace PhysicalReflect;

// 定义程序信息
typedef struct _application
{
	HWND hwnd;
	int width;
	int height;
	HDC hdc;
}Application;

// 定义RGB颜色
typedef struct _rgb{
	int r;
	int g;
	int b;
}Rgb;

// 定义二维物体
typedef struct _shape{
	double x;
	double y;
	double radius;
	double direct;
	double speed;
	double a;
	Rgb color;
	int link;
	Rgb nextColor;
	int nextCnt;
	int curCnt;
}Shape;

// 构造RGB颜色
Rgb rgb(int r, int g, int b){
	Rgb ret;
	ret.r = r;
	ret.g = g;
	ret.b = b;
	return ret;
}

// 定义GDI体
typedef struct _gdi_obj{
	HDC hdc;
	HGDIOBJ old;
	HGDIOBJ cur;
}GdiObj;

// win32颜色转RGB颜色
Rgb color2rgb(COLORREF& c){
	Rgb ret;
	ret.r = c & 0x0ff;
	ret.g = (c >> 8) & 0x0ff;
	ret.b = (c >> 16) & 0x0ff;
	return ret;
}

// RGB颜色转win32颜色
COLORREF rgb2color(Rgb& rgb){
	return ((rgb.b & 0x0ff) << 16) | ((rgb.g & 0x0ff) << 8) | (rgb.r & 0x0ff);
}

// 生成GDI画笔
GdiObj gdiPen(HDC hdc, int ps_style, int p_width, Rgb& p_color){
	HPEN pen = CreatePen(ps_style, p_width, rgb2color(p_color));
	HGDIOBJ oldPen = SelectObject(hdc, pen);
	GdiObj ret;
	ret.cur = pen;
	ret.hdc = hdc;
	ret.old = oldPen;
	return ret;
}

// 生成GDI画刷
GdiObj gdiSolidBrush(HDC hdc, Rgb& p_color){
	HBRUSH brush = CreateSolidBrush(rgb2color(p_color));
	HGDIOBJ oldBrush = SelectObject(hdc, brush);
	GdiObj ret;
	ret.cur = brush;
	ret.hdc = hdc;
	ret.old = oldBrush;
	return ret;
}

// 销毁GDI对象
void gdiDelete(GdiObj& obj){
	HGDIOBJ old = SelectObject(obj.hdc, obj.old);
	DeleteObject(old);
	DeleteObject(obj.cur);
}

// 绘制GDI直线
void gdiLine(HDC hdc, int x1, int y1, int x2, int y2){
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

// 绘制GDI圆形
void gdiCenterCircle(HDC hdc, int x, int y, int r){
	Ellipse(hdc, x - r, y - r, x + r, y + r);
}

// 绘制GDI圆形
void gdiCircle(HDC hdc, int x, int y, int r){
	Ellipse(hdc, x, y, x + r * 2, y + r * 2);
}

// 绘制GDI正方形
void gdiSqure(HDC hdc, int x, int y, int len){
	Rectangle(hdc, x, y, x + len, y + len);
}

// 随机值
int randInt(){
	return rand();
}

// 随机0-x
int randInt(int x){
	return rand() % x;
}

// 随机x-y
int randInt(int x, int y){
	return rand() % (y - x) + x;
}

// 随机小数
double randDouble(){
	return (rand() % RAND_MAX)*1.0 / RAND_MAX;
}

// 睡眠
void sleep(int ms){
	Sleep(ms);
}

// 距离计算
template<typename T>
double distance(T x1, T y1, T x2, T y2){
	return sqrt(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
}

// 计算差值
template<typename T>
T length(T v1, T v2){
	return abs(v2 - v1);
}

// 计算平滑插值微分
template<typename T>
T smooth(T begin, double rate, T end){
	return begin*rate + end*(1.0 - rate);
}

// 计算平滑渐变颜色
Rgb smoothRgb(Rgb& begin, double rate, Rgb end){
	int r = smooth(begin.r, rate, end.r);
	int g = smooth(begin.g, rate, end.g);
	int b = smooth(begin.b, rate, end.b);
	return rgb(r, g, b);
}

// 是否按键按下
bool isKeyDownEx(int keyCode){
	return GetAsyncKeyState(keyCode) & 0x08000;
}

// 获取屏幕鼠标位置
POINT mouseScreenPoint(){
	POINT p;
	GetCursorPos(&p);
	return p;
}

// 获取程序鼠标位置
POINT mouseAppPoint(HWND hwnd){
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hwnd, &p);
	return p;
}

// 程序内检测按键按下，必须同时按下CAPSLock键
bool isKeyDown(int keyCode){
	return isKeyDownEx(VK_CAPITAL) && isKeyDownEx(keyCode);
}

// 初始化随机
void initRandom(){
	srand((unsigned int)time(NULL));
}

// 计算圆形面积
double circleArea(double r){
	return PI*r*r;
}

// 计算向量
Point vectorLine(double x1, double y1, double x2, double y2){
	return Point(x2 - x1, y2 - y1);
}

// 计算直线的法向量
// 两向量点积为0
// p.x*a+p.y*b=0
// p.x*a=-b*p.y
// 设a=p.y
// 则p.x*p.y=-b*p.y
// 即，p.x=-b
// 得到：a=p.y,b=-p.x
Point normalLine(Point p){
	return Point(p.y, 0 - p.x);
}

void setAsDesktopBackgroundApp(Application& app){

	// 获取桌面背景窗口为父窗口
	HWND wallHwnd = GetDesktopWallpaperWorkerHwnd();
	// 第一次设置父窗口，在EasyX中，多次initgraph返回的hwnd不变
	// 因此，第一次设为为父窗口后，通过获取尺寸函数，就能获得父窗口模式下的正确窗口尺寸
	if (wallHwnd != NULL){
		SetParent(app.hwnd, wallHwnd);
	}


	// 获取全屏尺寸
	app.width = GetSystemMetrics(SM_CXSCREEN) + 2;
	app.height = GetSystemMetrics(SM_CYSCREEN) + 2;
	app.hwnd = initgraph(app.width, app.height);

	if (wallHwnd != NULL){
		SetParent(app.hwnd, wallHwnd);
	}

	//消除边框
	SetWindowLong(app.hwnd, GWL_STYLE, GetWindowLong(app.hwnd, GWL_STYLE) - WS_CAPTION);
	ShowWindow(app.hwnd, SW_MAXIMIZE);

	// 固定到屏幕左上角对其
	SetWindowPos(app.hwnd, NULL, -1, -1, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

// 初始化程序
Application initApp(int wid, int hei, bool asDesk){

	int winWid = wid;
	int winHei = hei;

	HWND hwnd = initgraph(winWid, winHei);

	HDC hdc = GetImageHDC(NULL);

	Application ret;
	ret.hwnd = hwnd;
	ret.width = winWid;
	ret.height = winHei;
	ret.hdc = hdc;

	if (asDesk){
		setAsDesktopBackgroundApp(ret);
	}

	return ret;
}

// 添加一个形状
void addShape(Application& app, vector<Shape>& vec){
	Shape shape;
	shape.x = rand() % app.width;
	shape.y = rand() % app.height;
	shape.color = rgb(randInt(256), randInt(256), randInt(256));
	shape.direct = AngleToRadian(randDouble() * 360);
	shape.radius = randDouble() * 10 + 1;
	shape.speed = randDouble() * 5 + 1;
	shape.a = 0;
	shape.link = 0;
	shape.nextColor = rgb(randInt(256), randInt(256), randInt(256));
	shape.nextCnt = randInt(10, 200);
	shape.curCnt = shape.nextCnt;
	vec.push_back(shape);
}

// 随机移除一个形状
void removeShape(vector<Shape>& vec){
	int size = vec.size();
	if (size > 0){
		vec.erase(vec.begin() + randInt(size));
	}
}

// 初始化形状
void makeShapes(Application& app, vector<Shape>& vec){
	int cnt = rand() % 70 + 30;
	for (int i = 0; i < cnt; i++){
		addShape(app, vec);
	}
}

void gdiHole(HDC hdc, int x, int y, int radius, int step){
	for (int i = 0; i < 360; i += step){
		Point end = getEndPoint(x, y, radius, AngleToRadian(i));
		gdiLine(hdc, x, y, end.x, end.y);
	}
}

void frameShapes(Application& app, vector<Shape> & vec){
	// 最大速度质量积
	double maxWeight = circleArea(10) * 5;
	// 最大连线距离
	double maxLineDistance = distance(0, 0, app.width, app.height) / 10;
	// 每个小球最大连线数量
	int maxLineCount = 4;
	// 定义最大加速度
	int maxSpeedA = 10;
	// 定义黑洞大小
	int holeRadius = randInt(maxLineDistance / 2) + 20;
	// 定义黑洞的step偏转
	int holeStep = randInt(15) + 5;
	// 定义黑洞颜色
	Rgb blackHoleColor = rgb(randInt(100), randInt(100), randInt(100));
	// 定义白洞颜色
	Rgb whiteHoleColor = rgb(randInt(155, 255), randInt(155, 255), randInt(155, 255));
	// 定义黑洞线型
	int psType = randInt(PS_DASHDOTDOT + 1);
	// 重置连线
	for (vector<Shape>::iterator it = vec.begin(); it != vec.end(); it++){
		it->link = 0;
	}
	// 获取鼠标位置
	POINT cp = mouseAppPoint(app.hwnd);
	// 元素遍历
	for (vector<Shape>::iterator it = vec.begin(); it != vec.end(); it++){

		double rate = it->curCnt*1.0 / it->nextCnt;
		Rgb bc = smoothRgb(it->color,rate, it->nextColor);
		it->curCnt--;
		if (it->curCnt == 0){
			it->color = it->nextColor;
			it->nextColor = rgb(randInt(256), randInt(256), randInt(256));
			it->nextCnt = randInt(10, 200);
			it->curCnt = it->nextCnt;
		}

		// 绘制小球
		GdiObj brush = gdiSolidBrush(app.hdc, bc);
		GdiObj pen = gdiPen(app.hdc, psType, 1, bc);
		gdiCenterCircle(app.hdc, it->x, it->y, it->radius);
		gdiDelete(pen);
		gdiDelete(brush);

		// 绘制小球运动方向
		GdiObj pd = gdiPen(app.hdc, psType, 1, rgb(255, 0, 0));
		Point ep = getEndPoint(it->x, it->y, it->radius + 3, it->direct);
		gdiLine(app.hdc, it->x, it->y, ep.x, ep.y);
		gdiDelete(pd);

		// 移动小球
		Point p = getEndPoint(it->x, it->y, max(it->speed + it->a,0), it->direct);
		it->x = p.x;
		it->y = p.y;
		// 偏向鼠标
		if (randDouble() < 0.5){
			// 按下CapsLock+B键，为黑洞，吸引小球
			if (isKeyDown('B')){
				double direct = getRadianFromLine(it->x, it->y, cp.x, cp.y);
				it->direct = smooth(it->direct, 0.9, direct);
				GdiObj tp = gdiPen(app.hdc, PS_DASHDOT, 1, blackHoleColor);
				gdiHole(app.hdc, cp.x, cp.y, holeRadius, holeStep);
				gdiDelete(tp);
			}
			// 按下CapsLock+W键，为白洞，排斥小球
			if (isKeyDown('W')){
				double direct = getRadianFromLine(cp.x, cp.y, it->x, it->y);
				it->direct = smooth(it->direct, 0.9, direct);
				GdiObj tp = gdiPen(app.hdc, PS_DASHDOT, 1, whiteHoleColor);
				gdiHole(app.hdc, cp.x, cp.y, holeRadius, holeStep);
				gdiDelete(tp);
			}
		}
		if (isKeyDown(VK_UP) || isKeyDown('8') || isKeyDown(VK_NUMPAD8)){
			it->a += randInt(3);
		}
		if (isKeyDown(VK_DOWN) || isKeyDown('2') || isKeyDown(VK_NUMPAD2)){
			it->a -= randInt(3);
		}
		if (isKeyDown(VK_SPACE) || isKeyDown('0') || isKeyDown(VK_NUMPAD0)){
			it->a = 0;
		}
		double deltA = (it->a > 0) ? (-0.5) : (0.5);
		// 加速度降低
		it->a = min(it->a + deltA,100);
		// 边缘宽度定义
		double border = 0;
		// 碰撞检测
		bool isBounce = false;
		// 上边界
		if (it->y - it->radius <= border){
			double direct = getRadianFromLine(0, 0, app.width, 0);
			it->direct = getReflectRadian(it->direct, direct);
			isBounce = true;
		}
		// 下边界
		if (it->y + it->radius >= app.height - border){
			double direct = getRadianFromLine(0, app.height, app.width, app.height);
			it->direct = getReflectRadian(it->direct, direct);
			isBounce = true;
		}
		// 左边界
		if (it->x - it->radius <= border){
			double direct = getRadianFromLine(0, 0, 0, app.height);
			it->direct = getReflectRadian(it->direct, direct);
			isBounce = true;
		}
		// 右边界
		if (it->x + it->radius >= app.width - border){
			double direct = getRadianFromLine(app.width, 0, app.width, app.height);
			it->direct = getReflectRadian(it->direct, direct);
			isBounce = true;
		}

		// 预先计算，减少计算量
		double itDirect = it->direct;
		double itWeight = circleArea(it->radius)*it->speed;
		double itFlatDirect = getRegularRadian(it->direct + AngleToRadian(90));

		// 实现最近线连接与小球见碰撞计算
		for (vector<Shape>::iterator pit = vec.begin(); pit != vec.end(); pit++){
			if (pit == it){
				continue;
			}
			double dis = distance(it->x, it->y, pit->x, pit->y);
			if (dis < maxLineDistance){
				if (it->link < maxLineCount && pit->link < maxLineCount){
					Rgb c = bc;
					if (pit->radius>it->radius){
						double tpr = pit->curCnt*1.0 / pit->nextCnt;
						c = smoothRgb(pit->color, tpr, pit->nextColor);
					}
					GdiObj pld = gdiPen(app.hdc, PS_SOLID, 1, c);
					gdiLine(app.hdc, it->x, it->y, pit->x, pit->y);
					gdiDelete(pld);
					it->link++;
					pit->link++;
				}
			}

			// 发生碰撞
			if (dis < (it->radius + pit->radius)){
				double pitDirect = pit->direct;
				double pitFlatDirect = getRegularRadian(pit->direct + AngleToRadian(90));
				// 小球之间发生碰撞，则按照圆形碰撞反射角度弹射
				it->direct = getReflectRadian(itDirect, pitFlatDirect);
				pit->direct = getReflectRadian(pitDirect, itFlatDirect);

				// 小球之间发生碰撞，按照速度质量比反比进行加速度弹射
				// 也就是质量越大，弹射越小

				double pitWeight = circleArea(pit->radius)*pit->speed;
				double sumWeight = itWeight + pitWeight;
				it->a += (1.0 - itWeight / sumWeight) * maxSpeedA;
				pit->a += (1.0 - pitWeight / sumWeight) * maxSpeedA;
			}
		}

		// 如果碰撞边界，加速度按照速度质量比增大，弹射开
		if (isBounce){
			double rate = itWeight / maxWeight;
			it->a += rate * maxSpeedA*0.7;
			// 有一定概率碰撞边界加速度会降低
			if (randDouble() < 0.3){
				it->a *= 0.618;
			}
		}

		// 防止在边界反复弹跳，卡在边界
		double fixDiff = 5;
		// 位置修正
		it->x = max(it->x, border + fixDiff);
		it->y = max(it->y, border + fixDiff);

		it->x = min(it->x, app.width - border - fixDiff);
		it->y = min(it->y, app.height - border - fixDiff);
	}
}


void showHelpMsgBox(Application& app){
	char path[_MAX_PATH*2] = { 0 };
	SHGetSpecialFolderPathA(app.hwnd, path,CSIDL_APPDATA, FALSE);

	char filePath[MAX_PATH * 5] = { 0 };
	sprintf(filePath, "%s\\%s\0", path, META_FILE_PATH);

	FILE * file = fopen(filePath, "r");
	if (file != NULL){
		fclose(file);
		return;
	}
	MessageBox(app.hwnd, TEXT("物理/黑洞\r\nCapsLock+B:黑洞模式，吸引向鼠标\r\nCapsLock+W:白洞模式，排斥自鼠标\r\nCapsLock+Up/8:增加加速度\r\nCapsLock+Down/2:降低加速度\r\nCapsLock+Space/0:重置加速度\r\nCapsLock+Enter/Return:刷新元素\r\nCapsLock+A:添加小球\r\nCapsLock+X:减少小球\r\nCapsLock+Q:加速随机一个小球\r\nCapsLock+G:切换背景颜色（自动，黑，白）"), TEXT("PhysicalHole"), MB_OK);

	file = fopen(filePath, "w");
	fprintf(file, "initialed");
	fclose(file);
}

int main(int argc, char * argv){
	initRandom();

	Application app = initApp(1080, 720, true);

	// 开启全局缓冲绘图
	BeginBatchDraw();

	vector<Shape> shapes;

	makeShapes(app, shapes);

	double minus=12 * 60;
	bool firstLoad = true;
	int bgMode = 0; // 0 自动，1 黑色，2 白色
	while (true){

		if (bgMode == 0){
			//获取系统时间  
			time_t now_time = time(NULL);
			//获取本地时间  
			tm*  t_tm = localtime(&now_time);

			// 根据时间，自动背景颜色，中午纯白，夜晚纯黑
			// 算法，计算距离中午12点的距离与半天的比例
			// 比例越小，说明距离中午越近
			// 则亮度应该越高
			double rate = (length(minus, t_tm->tm_hour*60.0 + t_tm->tm_min))*1.0 / minus;
			rate = 1.0 - rate;
			int gy = rate * 255;
			setbkcolor(rgb2color(rgb(gy, gy, gy)));
		}
		else if(bgMode==1){
			setbkcolor(RGB(0, 0, 0));
		}
		else if (bgMode == 2){
			setbkcolor(RGB(255, 255, 255));
		}
		cleardevice();

		frameShapes(app, shapes);

		FlushBatchDraw();

		if (isKeyDown(VK_RETURN)){
			shapes.clear();
			makeShapes(app, shapes);
		}

		if (isKeyDown('A')){
			addShape(app, shapes);
		}

		if (isKeyDown('X')){
			removeShape(shapes);
		}

		if (isKeyDown('Q')){
			if (shapes.size() > 0){
				shapes[randInt(shapes.size())].a += 10;
			}
		}

		if (isKeyDown('G')){
			bgMode = (bgMode + 1) % 3;
		}

		sleep(30);
		if (firstLoad){
			showHelpMsgBox(app);
		}
		firstLoad = false;
	}


	EndBatchDraw();
	closegraph();
	return 0;
}