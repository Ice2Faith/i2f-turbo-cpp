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

// ���������Ϣ
typedef struct _application
{
	HWND hwnd;
	int width;
	int height;
	HDC hdc;
}Application;

// ����RGB��ɫ
typedef struct _rgb{
	int r;
	int g;
	int b;
}Rgb;

// �����ά����
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

// ����RGB��ɫ
Rgb rgb(int r, int g, int b){
	Rgb ret;
	ret.r = r;
	ret.g = g;
	ret.b = b;
	return ret;
}

// ����GDI��
typedef struct _gdi_obj{
	HDC hdc;
	HGDIOBJ old;
	HGDIOBJ cur;
}GdiObj;

// win32��ɫתRGB��ɫ
Rgb color2rgb(COLORREF& c){
	Rgb ret;
	ret.r = c & 0x0ff;
	ret.g = (c >> 8) & 0x0ff;
	ret.b = (c >> 16) & 0x0ff;
	return ret;
}

// RGB��ɫתwin32��ɫ
COLORREF rgb2color(Rgb& rgb){
	return ((rgb.b & 0x0ff) << 16) | ((rgb.g & 0x0ff) << 8) | (rgb.r & 0x0ff);
}

// ����GDI����
GdiObj gdiPen(HDC hdc, int ps_style, int p_width, Rgb& p_color){
	HPEN pen = CreatePen(ps_style, p_width, rgb2color(p_color));
	HGDIOBJ oldPen = SelectObject(hdc, pen);
	GdiObj ret;
	ret.cur = pen;
	ret.hdc = hdc;
	ret.old = oldPen;
	return ret;
}

// ����GDI��ˢ
GdiObj gdiSolidBrush(HDC hdc, Rgb& p_color){
	HBRUSH brush = CreateSolidBrush(rgb2color(p_color));
	HGDIOBJ oldBrush = SelectObject(hdc, brush);
	GdiObj ret;
	ret.cur = brush;
	ret.hdc = hdc;
	ret.old = oldBrush;
	return ret;
}

// ����GDI����
void gdiDelete(GdiObj& obj){
	HGDIOBJ old = SelectObject(obj.hdc, obj.old);
	DeleteObject(old);
	DeleteObject(obj.cur);
}

// ����GDIֱ��
void gdiLine(HDC hdc, int x1, int y1, int x2, int y2){
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

// ����GDIԲ��
void gdiCenterCircle(HDC hdc, int x, int y, int r){
	Ellipse(hdc, x - r, y - r, x + r, y + r);
}

// ����GDIԲ��
void gdiCircle(HDC hdc, int x, int y, int r){
	Ellipse(hdc, x, y, x + r * 2, y + r * 2);
}

// ����GDI������
void gdiSqure(HDC hdc, int x, int y, int len){
	Rectangle(hdc, x, y, x + len, y + len);
}

// ���ֵ
int randInt(){
	return rand();
}

// ���0-x
int randInt(int x){
	return rand() % x;
}

// ���x-y
int randInt(int x, int y){
	return rand() % (y - x) + x;
}

// ���С��
double randDouble(){
	return (rand() % RAND_MAX)*1.0 / RAND_MAX;
}

// ˯��
void sleep(int ms){
	Sleep(ms);
}

// �������
template<typename T>
double distance(T x1, T y1, T x2, T y2){
	return sqrt(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
}

// �����ֵ
template<typename T>
T length(T v1, T v2){
	return abs(v2 - v1);
}

// ����ƽ����ֵ΢��
template<typename T>
T smooth(T begin, double rate, T end){
	return begin*rate + end*(1.0 - rate);
}

// ����ƽ��������ɫ
Rgb smoothRgb(Rgb& begin, double rate, Rgb end){
	int r = smooth(begin.r, rate, end.r);
	int g = smooth(begin.g, rate, end.g);
	int b = smooth(begin.b, rate, end.b);
	return rgb(r, g, b);
}

// �Ƿ񰴼�����
bool isKeyDownEx(int keyCode){
	return GetAsyncKeyState(keyCode) & 0x08000;
}

// ��ȡ��Ļ���λ��
POINT mouseScreenPoint(){
	POINT p;
	GetCursorPos(&p);
	return p;
}

// ��ȡ�������λ��
POINT mouseAppPoint(HWND hwnd){
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hwnd, &p);
	return p;
}

// �����ڼ�ⰴ�����£�����ͬʱ����CAPSLock��
bool isKeyDown(int keyCode){
	return isKeyDownEx(VK_CAPITAL) && isKeyDownEx(keyCode);
}

// ��ʼ�����
void initRandom(){
	srand((unsigned int)time(NULL));
}

// ����Բ�����
double circleArea(double r){
	return PI*r*r;
}

// ��������
Point vectorLine(double x1, double y1, double x2, double y2){
	return Point(x2 - x1, y2 - y1);
}

// ����ֱ�ߵķ�����
// ���������Ϊ0
// p.x*a+p.y*b=0
// p.x*a=-b*p.y
// ��a=p.y
// ��p.x*p.y=-b*p.y
// ����p.x=-b
// �õ���a=p.y,b=-p.x
Point normalLine(Point p){
	return Point(p.y, 0 - p.x);
}

void setAsDesktopBackgroundApp(Application& app){

	// ��ȡ���汳������Ϊ������
	HWND wallHwnd = GetDesktopWallpaperWorkerHwnd();
	// ��һ�����ø����ڣ���EasyX�У����initgraph���ص�hwnd����
	// ��ˣ���һ����ΪΪ�����ں�ͨ����ȡ�ߴ纯�������ܻ�ø�����ģʽ�µ���ȷ���ڳߴ�
	if (wallHwnd != NULL){
		SetParent(app.hwnd, wallHwnd);
	}


	// ��ȡȫ���ߴ�
	app.width = GetSystemMetrics(SM_CXSCREEN) + 2;
	app.height = GetSystemMetrics(SM_CYSCREEN) + 2;
	app.hwnd = initgraph(app.width, app.height);

	if (wallHwnd != NULL){
		SetParent(app.hwnd, wallHwnd);
	}

	//�����߿�
	SetWindowLong(app.hwnd, GWL_STYLE, GetWindowLong(app.hwnd, GWL_STYLE) - WS_CAPTION);
	ShowWindow(app.hwnd, SW_MAXIMIZE);

	// �̶�����Ļ���ϽǶ���
	SetWindowPos(app.hwnd, NULL, -1, -1, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

// ��ʼ������
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

// ���һ����״
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

// ����Ƴ�һ����״
void removeShape(vector<Shape>& vec){
	int size = vec.size();
	if (size > 0){
		vec.erase(vec.begin() + randInt(size));
	}
}

// ��ʼ����״
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
	// ����ٶ�������
	double maxWeight = circleArea(10) * 5;
	// ������߾���
	double maxLineDistance = distance(0, 0, app.width, app.height) / 10;
	// ÿ��С�������������
	int maxLineCount = 4;
	// ���������ٶ�
	int maxSpeedA = 10;
	// ����ڶ���С
	int holeRadius = randInt(maxLineDistance / 2) + 20;
	// ����ڶ���stepƫת
	int holeStep = randInt(15) + 5;
	// ����ڶ���ɫ
	Rgb blackHoleColor = rgb(randInt(100), randInt(100), randInt(100));
	// ����׶���ɫ
	Rgb whiteHoleColor = rgb(randInt(155, 255), randInt(155, 255), randInt(155, 255));
	// ����ڶ�����
	int psType = randInt(PS_DASHDOTDOT + 1);
	// ��������
	for (vector<Shape>::iterator it = vec.begin(); it != vec.end(); it++){
		it->link = 0;
	}
	// ��ȡ���λ��
	POINT cp = mouseAppPoint(app.hwnd);
	// Ԫ�ر���
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

		// ����С��
		GdiObj brush = gdiSolidBrush(app.hdc, bc);
		GdiObj pen = gdiPen(app.hdc, psType, 1, bc);
		gdiCenterCircle(app.hdc, it->x, it->y, it->radius);
		gdiDelete(pen);
		gdiDelete(brush);

		// ����С���˶�����
		GdiObj pd = gdiPen(app.hdc, psType, 1, rgb(255, 0, 0));
		Point ep = getEndPoint(it->x, it->y, it->radius + 3, it->direct);
		gdiLine(app.hdc, it->x, it->y, ep.x, ep.y);
		gdiDelete(pd);

		// �ƶ�С��
		Point p = getEndPoint(it->x, it->y, max(it->speed + it->a,0), it->direct);
		it->x = p.x;
		it->y = p.y;
		// ƫ�����
		if (randDouble() < 0.5){
			// ����CapsLock+B����Ϊ�ڶ�������С��
			if (isKeyDown('B')){
				double direct = getRadianFromLine(it->x, it->y, cp.x, cp.y);
				it->direct = smooth(it->direct, 0.9, direct);
				GdiObj tp = gdiPen(app.hdc, PS_DASHDOT, 1, blackHoleColor);
				gdiHole(app.hdc, cp.x, cp.y, holeRadius, holeStep);
				gdiDelete(tp);
			}
			// ����CapsLock+W����Ϊ�׶����ų�С��
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
		// ���ٶȽ���
		it->a = min(it->a + deltA,100);
		// ��Ե��ȶ���
		double border = 0;
		// ��ײ���
		bool isBounce = false;
		// �ϱ߽�
		if (it->y - it->radius <= border){
			double direct = getRadianFromLine(0, 0, app.width, 0);
			it->direct = getReflectRadian(it->direct, direct);
			isBounce = true;
		}
		// �±߽�
		if (it->y + it->radius >= app.height - border){
			double direct = getRadianFromLine(0, app.height, app.width, app.height);
			it->direct = getReflectRadian(it->direct, direct);
			isBounce = true;
		}
		// ��߽�
		if (it->x - it->radius <= border){
			double direct = getRadianFromLine(0, 0, 0, app.height);
			it->direct = getReflectRadian(it->direct, direct);
			isBounce = true;
		}
		// �ұ߽�
		if (it->x + it->radius >= app.width - border){
			double direct = getRadianFromLine(app.width, 0, app.width, app.height);
			it->direct = getReflectRadian(it->direct, direct);
			isBounce = true;
		}

		// Ԥ�ȼ��㣬���ټ�����
		double itDirect = it->direct;
		double itWeight = circleArea(it->radius)*it->speed;
		double itFlatDirect = getRegularRadian(it->direct + AngleToRadian(90));

		// ʵ�������������С�����ײ����
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

			// ������ײ
			if (dis < (it->radius + pit->radius)){
				double pitDirect = pit->direct;
				double pitFlatDirect = getRegularRadian(pit->direct + AngleToRadian(90));
				// С��֮�䷢����ײ������Բ����ײ����Ƕȵ���
				it->direct = getReflectRadian(itDirect, pitFlatDirect);
				pit->direct = getReflectRadian(pitDirect, itFlatDirect);

				// С��֮�䷢����ײ�������ٶ������ȷ��Ƚ��м��ٶȵ���
				// Ҳ��������Խ�󣬵���ԽС

				double pitWeight = circleArea(pit->radius)*pit->speed;
				double sumWeight = itWeight + pitWeight;
				it->a += (1.0 - itWeight / sumWeight) * maxSpeedA;
				pit->a += (1.0 - pitWeight / sumWeight) * maxSpeedA;
			}
		}

		// �����ײ�߽磬���ٶȰ����ٶ����������󣬵��俪
		if (isBounce){
			double rate = itWeight / maxWeight;
			it->a += rate * maxSpeedA*0.7;
			// ��һ��������ײ�߽���ٶȻή��
			if (randDouble() < 0.3){
				it->a *= 0.618;
			}
		}

		// ��ֹ�ڱ߽練�����������ڱ߽�
		double fixDiff = 5;
		// λ������
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
	MessageBox(app.hwnd, TEXT("����/�ڶ�\r\nCapsLock+B:�ڶ�ģʽ�����������\r\nCapsLock+W:�׶�ģʽ���ų������\r\nCapsLock+Up/8:���Ӽ��ٶ�\r\nCapsLock+Down/2:���ͼ��ٶ�\r\nCapsLock+Space/0:���ü��ٶ�\r\nCapsLock+Enter/Return:ˢ��Ԫ��\r\nCapsLock+A:���С��\r\nCapsLock+X:����С��\r\nCapsLock+Q:�������һ��С��\r\nCapsLock+G:�л�������ɫ���Զ����ڣ��ף�"), TEXT("PhysicalHole"), MB_OK);

	file = fopen(filePath, "w");
	fprintf(file, "initialed");
	fclose(file);
}

int main(int argc, char * argv){
	initRandom();

	Application app = initApp(1080, 720, true);

	// ����ȫ�ֻ����ͼ
	BeginBatchDraw();

	vector<Shape> shapes;

	makeShapes(app, shapes);

	double minus=12 * 60;
	bool firstLoad = true;
	int bgMode = 0; // 0 �Զ���1 ��ɫ��2 ��ɫ
	while (true){

		if (bgMode == 0){
			//��ȡϵͳʱ��  
			time_t now_time = time(NULL);
			//��ȡ����ʱ��  
			tm*  t_tm = localtime(&now_time);

			// ����ʱ�䣬�Զ�������ɫ�����紿�ף�ҹ����
			// �㷨�������������12��ľ��������ı���
			// ����ԽС��˵����������Խ��
			// ������Ӧ��Խ��
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