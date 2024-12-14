#include<graphics.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>
#include<vector>
#include <algorithm>
#include"VideoWallpaperHelper.h"

using namespace std;

// �����ͼ��������
// �տ�
#define BLK_EMPTY 0
// ǽ��
#define BLK_BLOCK -1
// ����
#define BLK_OPEN 1
// �ر�
#define BLK_CLOSE 2

// �Ƿ���ʾ��Ȩ������
bool isShowText = false;

// Ѱ·����
typedef struct _step{
	int x;
	int y;
	struct _step * pre;
	double f;
	double g;
	double h;
} Step;

// ��ͼ
typedef struct _map{
	char * map;
	int wid;
	int hei;
	// ��ʼ������
	int beginX;
	int beginY;
	int endX;
	int endY;
} Map;

// �������
double distance(int x1, int y1, int x2, int y2){
	return sqrt(pow(x2 - x1, 2.0) + pow(y2 - y1, 2.0));
}

double length(double v1, double v2){
	return abs(v2 - v1);
}

//������ͼ
Map createMap(int wid, int hei){
	char * map = (char*)malloc(sizeof(char)*(wid*hei));
	Map ret;
	ret.wid = wid;
	ret.hei = hei;
	ret.map = map;
	return ret;
}

// �ͷŵ�ͼ�ռ�
void releaseMap(Map& map){
	if (map.map != NULL){
		free(map.map);
		map.map = NULL;
	}
	map.wid = 0;
	map.hei = 0;
}

// ���Ե�ͼ�Ķ�άת��
char* mapAt(Map& map, int x, int y)
{
	return &(map.map[y*map.wid + x]);
}

void blockMap(Map& map, int x, int y, int val, int level){
	if (level < 0){
		return;
	}
	// ��һ��ƫ�ƶ���
	int offset[][2] = {
		{ -1, 0 },
		{ 1, 0 },
		{ 0, -1 },
		{ 0, 1 },
		{ 0, 0 }, // ������������
		{ -1, -1 },
		{ -1, 1 },
		{ 1, -1 },
		{ 1, 1 },
		{ -999, -999 } // �Խǰ���
	};

	// �����ʹ������Ѱ·
	if (rand() % 100 < 80){
		offset[4][0] = -999;
	}

	int i = 0;
	while (offset[i][0] != -999){
		if (rand() % 100 < 50){
			int nx = x + offset[i][0];
			int ny = y + offset[i][1];
			if (nx < 0 || nx >= map.wid || ny < 0 || ny >= map.hei){
				continue;
			}
			if (*mapAt(map, nx, ny) == val){
				continue;
			}
			*mapAt(map, nx, ny) = val;
			blockMap(map, nx, ny, val, level - 1);
		}
		i++;
	}
}

// ��ʼ����ͼ
void initMap(Map& map)
{
	// ǽ�����
	int rate = rand() % 5 + 3;
	// ���ɵ�ͼ
	for (int y = 0; y < map.hei; y++){
		for (int x = 0; x < map.wid; x++){
			*mapAt(map, x, y) = BLK_EMPTY;
			if (rand() % 100 < rate){
				*mapAt(map, x, y) = BLK_BLOCK;
			}
		}
	}
	// ���ɿ�
	int blkCnt = rand() % 10 + 1;
	for (int i = 0; i < blkCnt; i++){
		blockMap(map, rand() % map.wid, rand() % map.hei, BLK_BLOCK, rand() % 100);
	}
	blkCnt = rand() % 10 + 1;
	for (int i = 0; i < blkCnt; i++){
		blockMap(map, rand() % map.wid, rand() % map.hei, BLK_EMPTY, rand() % 100);
	}

	// ���ɿ�ʼ������
	int wd = distance(0, 0, map.wid, map.hei);
	bool startOk = false;
	bool endOk = false;
	int endCnt = 0;
	while (!startOk || !endOk){
		int x = rand() % map.wid;
		int y = rand() % map.hei;
		if (*mapAt(map, x, y) == BLK_EMPTY){
			if (!startOk){
				map.beginX = x;
				map.beginY = y;
				startOk = true;
				continue;
			}
			if (!endOk){
				map.endX = x;
				map.endY = y;
				endCnt++;
				if (distance(map.beginX, map.beginY, map.endX, map.endY) > wd / (1.5 + (0.2*(endCnt / 20)))){
					endOk = true;
				}
			}
		}
	}
}

// ���ƿ�ʼ������
void drawSEP(Map& map, HDC hdc, int hdcWid, int hdcHei){
	int blkWid = hdcWid / map.wid;
	int blkHei = hdcHei / map.hei;

	if (map.beginX >= 0){
		HGDIOBJ oldBrush = NULL;
		HBRUSH brush = CreateSolidBrush(RGB(0, 255, 0));
		oldBrush = SelectObject(hdc, brush);
		Rectangle(hdc, map.beginX*blkWid, map.beginY*blkHei, (map.beginX + 1)*blkWid, (map.beginY + 1)*blkHei);
		HGDIOBJ obj = SelectObject(hdc, oldBrush);
		DeleteObject(obj);
		DeleteObject(brush);
	}
	if (map.endX >= 0){
		HGDIOBJ oldBrush = NULL;
		HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
		oldBrush = SelectObject(hdc, brush);
		Rectangle(hdc, map.endX*blkWid, map.endY*blkHei, (map.endX + 1)*blkWid, (map.endY + 1)*blkHei);
		HGDIOBJ obj = SelectObject(hdc, oldBrush);
		DeleteObject(obj);
		DeleteObject(brush);
	}
	HGDIOBJ oldPen = NULL;
	HPEN pen = CreatePen(PS_DOT, 1, RGB(255, 0, 0));
	oldPen = SelectObject(hdc, pen);
	MoveToEx(hdc, (map.beginX+0.5)*blkWid, (map.beginY+0.5)*blkHei, NULL);
	LineTo(hdc, (map.endX+0.5)*blkWid, (map.endY+0.5)*blkHei);
	HGDIOBJ obj = SelectObject(hdc, oldPen);
	DeleteObject(obj);
	DeleteObject(pen);
}

COLORREF blockColor = 0x0;
// ���Ƶ�ͼ
void drawMap(Map& map, HDC hdc, int hdcWid, int hdcHei)
{
	int blkWid = hdcWid / map.wid;
	int blkHei = hdcHei / map.hei;
	for (int y = 0; y < map.hei; y++){
		for (int x = 0; x < map.wid; x++){
			char ch = *mapAt(map, x, y);
			HGDIOBJ oldBrush = NULL;
			HBRUSH brush = NULL;

			if (ch == BLK_EMPTY){
				brush = CreateSolidBrush(RGB(255, 255, 255));
				oldBrush = SelectObject(hdc, brush);
			}
			else if (ch == BLK_BLOCK){
				brush = CreateSolidBrush(blockColor);
				oldBrush = SelectObject(hdc, brush);
			}
			else if (ch > BLK_EMPTY){
				char pch = ch - 1;
				brush = CreateSolidBrush(RGB((220 - min(150, pch * 20)), (255 - min(200, pch * 10)), 0));
				oldBrush = SelectObject(hdc, brush);
			}


			Rectangle(hdc, x*blkWid, y*blkHei, (x + 1)*blkWid, (y + 1)*blkHei);
			HGDIOBJ brushObj = SelectObject(hdc, oldBrush);
			DeleteObject(brushObj);
			DeleteObject(brush);

			// ���Ƶ�ͼ����
			if (isShowText && ch > 0){
				COLORREF textColor = 0xeeddaa;
				if (ch < 8){
					textColor = 0x443366;
				}
				SetTextColor(hdc, textColor);
				SetBkMode(hdc, TRANSPARENT);

				TCHAR buf[20];
				_stprintf(buf, TEXT("%d"), (int)ch);
				TextOut(hdc, x*blkWid, y*blkHei, buf, _tcslen(buf));
			}

		}
	}
	drawSEP(map, hdc, hdcWid, hdcHei);
}

// ����Ƚ���
bool comStepDistance(Step * step1, Step * step2){
	return step1->f < step2->f;
}

// ����·��
void drawPath(Step * cur, COLORREF color, HDC hdc, double blkWid, double blkHei, double rate = 1.0){
	Step* rp = cur;
	Step* last = NULL;
	double drate = 1.0 - rate;
	while (rp != NULL){
		HGDIOBJ oldBrush = NULL;
		HGDIOBJ oldPen = NULL;

		HBRUSH brush = CreateSolidBrush(color);
		oldBrush = SelectObject(hdc, brush);

		HPEN pen = CreatePen(PS_SOLID, 1, 0xffffff);
		oldPen = SelectObject(hdc, pen);

		Rectangle(hdc, (rp->x + drate / 2)*blkWid, (rp->y + drate / 2)*blkHei, (rp->x + rate + drate / 2)*blkWid, (rp->y + rate + drate / 2)*blkHei);
		HGDIOBJ brushObj = SelectObject(hdc, oldBrush);
		DeleteObject(brushObj);
		DeleteObject(brush);

		HGDIOBJ penObj = SelectObject(hdc, oldPen);
		DeleteObject(penObj);
		DeleteObject(pen);

		if (last != NULL){
			HPEN pen = CreatePen(PS_SOLID, 1, 0x0);
			HGDIOBJ oldPen = SelectObject(hdc, pen);
			MoveToEx(hdc, (rp->x + 0.5)*blkWid, (rp->y + 0.5)*blkHei, NULL);
			LineTo(hdc, (last->x + 0.5)*blkWid, (last->y + 0.5)*blkHei);
			HGDIOBJ delPen = SelectObject(hdc, oldPen);
			DeleteObject(delPen);
			DeleteObject(pen);
		}

		last = rp;
		rp = rp->pre;
	}
}



// �Ƿ񰴼�����
bool isKeyDownEx(int keyCode){
	return GetAsyncKeyState(keyCode) & 0x08000;
}

// �����ڼ�ⰴ�����£�����ͬʱ����CAPSLock��
bool isKeyDown(int keyCode){
	return isKeyDownEx(VK_CAPITAL) && isKeyDownEx(keyCode);
}

int boostCount = 0;
// �Ƿ����ģʽ
bool isBoostMode(){
	return isKeyDown(VK_RETURN) || (rand() % 100 < 5 ? false : true);
}

// �ڵ�ͼ���ֶ����÷�����Ƴ�����
void exchangeBlocks(Map& map, int hdcWid, int hdcHei){
	POINT p;
	GetCursorPos(&p);

	int px = p.x / (hdcWid / map.wid);
	int py = p.y / (hdcHei / map.hei);

	if (px < 0 || py < 0 || px >= map.wid || py >= map.hei){
		return;
	}

	if (px == map.beginX && py == map.beginY){
		return;
	}

	if (px == map.endX && py == map.endY){
		return;
	}

	if (*mapAt(map, px, py) > 0){
		return;
	}

	if (isKeyDown('E') || isKeyDown('e')){
		*mapAt(map, px, py) = BLK_EMPTY;
	}
	if (isKeyDown('R') || isKeyDown('r')){
		*mapAt(map, px, py) = BLK_BLOCK;
	}

}

int main(int argc, char * argv[]){
	// ��ʼ�������
	srand((unsigned int)time(NULL));

	int blkWid = 20;
	int blkHei = 20;

	int winWid = 1080;
	int winHei = 720;


	HWND hwnd = initgraph(winWid, winHei);
	
		blkWid = 15;
		blkHei = 15;
	// ��ȡ���汳������Ϊ������
	HWND wallHwnd = GetDesktopWallpaperWorkerHwnd();
	// ��һ�����ø����ڣ���EasyX�У����initgraph���ص�hwnd����
	// ��ˣ���һ����ΪΪ�����ں�ͨ����ȡ�ߴ纯�������ܻ�ø�����ģʽ�µ���ȷ���ڳߴ�
	if (wallHwnd != NULL){
		SetParent(hwnd, wallHwnd);
	}


	// ��ȡȫ���ߴ�
	winWid = GetSystemMetrics(SM_CXSCREEN) + 2;
	winHei = GetSystemMetrics(SM_CYSCREEN) + 2;
	hwnd = initgraph(winWid, winHei);

	if (wallHwnd != NULL){
		SetParent(hwnd, wallHwnd);
	}

	//�����߿�
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION);
	ShowWindow(hwnd, SW_MAXIMIZE);

	// �̶�����Ļ���ϽǶ���
	SetWindowPos(hwnd, NULL, -1, -1, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	HDC hdc = GetImageHDC(NULL);

	// ����ȫ�ֻ����ͼ
	BeginBatchDraw();

	// ��ʼ����ջ
	int cols = winWid / blkWid;
	int rows = winHei / blkHei;
	// ����ͼ
	Map map = createMap(cols, rows);
	// ��ʼ�����ͼ
	initMap(map);

	// ���Ƴ�ʼͼ��
	drawMap(map, hdc, winWid, winHei);

	// ˢ��һ�λ���
	FlushBatchDraw();

	// ���Ƴ���ָ��
	settextstyle(24, 16, NULL);
	setbkmode(TRANSPARENT);
	settextcolor(0x0055ff);
	setfillcolor(0xffffff);
	fillrectangle(winWid / 8, winHei / 2 - 50, winWid * 7 / 8, winHei / 2 + 7 * 24 + 50);
	outtextxy(winWid / 5, winHei / 2 + 0 * 24, TEXT("��ӭ����Ѱ·�㷨��ʾ����"));
	outtextxy(winWid / 5, winHei / 2 + 1 * 24, TEXT("�밴���������"));
	outtextxy(winWid / 5, winHei / 2 + 3 * 24, TEXT("Caps+Enter/Return/�س���:����Ѱ·����"));
	outtextxy(winWid / 5, winHei / 2 + 4 * 24, TEXT("Caps+Space/�ո�����˳�Ѱ·����"));
	outtextxy(winWid / 5, winHei / 2 + 5 * 24, TEXT("Caps+T/t/T������ʾ��������"));
	outtextxy(winWid / 5, winHei / 2 + 6 * 24, TEXT("Caps+E/e/E�������λ���Ƴ�����"));
	outtextxy(winWid / 5, winHei / 2 + 7 * 24, TEXT("Caps+R/r/R�������λ����ӷ���"));

	FlushBatchDraw();
	Sleep(4000);

	settextstyle(12, 8, NULL);
	settextcolor(0x0);


	while (true)
	{
		blockColor = RGB((rand() % 100), (rand() % 100), (rand() % 100));

		int stat = IDCANCEL;
		// ��ʼ�����ͼ
		initMap(map);

		// ���Ƴ�ʼͼ��
		drawMap(map, hdc, winWid, winHei);

		FlushBatchDraw();
		Sleep(1000);

		// �Ƿ�ʹ��A*Ѱ·ģʽ
		bool aStarMode = true;


		// ��һ��ƫ�ƶ���
		int offset[][2] = {
			{ -1, 0 },
			{ 1, 0 },
			{ 0, -1 },
			{ 0, 1 },
			{ 0, 0 }, // ������������
			{ -1, -1 },
			{ -1, 1 },
			{ 1, -1 },
			{ 1, 1 },
			{ -999, -999 } // �Խǰ���
		};

		// �����ʹ������Ѱ·
		if (rand() % 100 < 80){
			offset[4][0] = -999;
		}

		// һ�������ʾ����
		if (rand() % 100 < 50){
			isShowText = !isShowText;
		}

		// �ҵ�������·����ʼ��һ�ŵ�ͼ
		int breakCount = rand() % 10 + 1;
		if (rand() % 100 < 75){
			breakCount = rand() % 3 + 1;
		}
		breakCount = 1;

		// Ѱ·�б�
		vector<Step*> lst;
		// Ѱ·���ȣ���ǰѰ·����
		int idx = 0;

		// ������С����
		double minDis = distance(map.beginX, map.beginY, map.endX, map.endY);

		// ��ӿ�ʼ�㵽Ѱ·�У���ʼѰ·
		Step* step = new Step();
		step->x = map.beginX;
		step->y = map.beginY;
		step->g = 0;
		step->h = distance(map.beginX, map.beginY, map.endX, map.endY);
		step->f = step->g + step->h;
		
		step->pre = NULL;
		lst.push_back(step);

		// �ɹ���Ѱ··����ֹ�ڵ�
		vector<Step*> succ;

		// ֱ��û���µĵ������Ϊֹ
		while (idx < lst.size())
		{
			// ��ȡ��ǰ����
			Step* cur = lst[idx];

			// �Ѿ��߹�+1
			*mapAt(map, cur->x, cur->y) = BLK_CLOSE;

			// ������յ����꣬���ҵ�һ��·��
			if (cur->x == map.endX && cur->y == map.endY){
				succ.push_back(cur);

				// ���Ƴɹ�·��
				drawPath(cur, RGB(0, 200, 255), hdc, blkWid, blkHei);
				drawSEP(map, hdc, winWid, winHei);

				// ��ʾ�ɹ�����
				settextstyle(24, 16, NULL);
				setbkmode(OPAQUE);
				settextcolor(0x0055ff);
				setfillcolor(0xffffff);
				TCHAR buf[20];
				_stprintf(buf, TEXT("****��  %d  ��ͨ·****"), (int)succ.size());

				outtextxy(winWid - _tcslen(buf) * 24, 0, buf);

				settextstyle(12, 8, NULL);
				settextcolor(0x0);
				setbkmode(TRANSPARENT);

				FlushBatchDraw();
				//Sleep(3000);
				// �������¼�������
				int time = 3000;
				while (time > 0){
					if (isKeyDown(' ') || isKeyDown(VK_SPACE)){
						goto pass_end_tag;
					}
					Sleep(10);
					time -= 10;
				}

				// ���ڴ������˳�������һ����ͼ
				if (succ.size() >= breakCount){
					break;
				}
				idx++;
				continue;
			}


			// ��һ������
			vector<Step*> nexts;
			// ö����һ�����ߵ�����
			int i = 0;
			while (offset[i][0] != -999){
				// ������һ����ƫ��������ƫ�ƣ��õ���һ��������
				Step* nst = new Step();
				nst->x = cur->x + offset[i][0];
				nst->y = cur->y + offset[i][1];
				// ���ٵ�ͼ������
				if (nst->x < 0 || nst->x >= map.wid || nst->y < 0 || nst->y >= map.hei){
					i++;
					continue;
				}
				// �����ǽ�壬����
				char ch = *mapAt(map, nst->x, nst->y);
				if (ch == BLK_BLOCK){
					i++;
					continue;
				}

				// ����ѹرգ�����
				if (ch == BLK_CLOSE){
					i++;
					continue;
				}

				// ����ʹ����������������ˣ�·������ʼ��������ʼ��ͽ����������
				// Ϊ�������������⣬����ƫ��ϵ����ʹ�þ�����ƫ��ǰ��������������
				// �������ϵ��ƫ�󣬽��ᵼ��ĳЩ����£�Ѱ·Ч��������
				double hrate = 0.618;
				// ��¼��һ������һ��������ӵ�����
				nst->pre = cur;
				nst->g = distance(nst->x, nst->y, map.beginX, map.beginY)*(1.0-hrate);
				nst->h = distance(nst->x, nst->y, map.endX, map.endY)*hrate;
				nst->f = nst->g + nst->h;

				// ����Ƿ��Ѿ��ڿ����б��У��ڣ�����Ҫ�Ƚ�Gֵ��ѡ���С��Gֵ
				if (ch == BLK_OPEN){
					// ͨ����ǰ���񣬵�����һ�������Gֵ
					double pass_g = cur->g + distance(cur->x, cur->y, nst->x, nst->y)*(1.0-hrate);
					// ���ҿ����б��У��õ��Gֵ��������ڵĸ��ã���ԭ���ĵ�ĸ��ڵ㣬��Ϊ��ǰ�ڵ�
					Step* his = NULL;
					for (vector<Step*>::iterator it = lst.begin()+idx+1; it != lst.end(); it++){
						if ((*it)->x == nst->x && (*it)->y == nst->y){
							his = *it;
							break;
						}
					}
					if (his != NULL){
						if (pass_g < his->g){
							his->pre = nst;
							his->f = nst->f;
							lst.push_back(nst);
						}
					}
				}
				else{
					// ���ٴ��б��У���ֱ�����
					*mapAt(map, nst->x, nst->y) = BLK_OPEN;
					lst.push_back(nst);
				}
				
				
				if (boostCount % (boostCount / 10 + 1) == 0){
					// ����·��·��

					drawMap(map, hdc, winWid, winHei);

					drawPath(nst, RGB(255, 0, 255), hdc, blkWid, blkHei);


					drawSEP(map, hdc, winWid, winHei);

					FlushBatchDraw();
				}
				//MessageBox(hwnd, TEXT("Next"), TEXT("��һ��ȷ��"), MB_OK);
				if (isBoostMode()){
					//Sleep(1);
					boostCount++;
				}
				else{
					boostCount = 0;
					Sleep(max(1, min(200 - max(cols, rows), 35)));
				}

				if (boostCount > 0x0fffff){
					boostCount = 0;
				}


				i++;
			}


			// �����ҳ���̾������ȣ��Ե�ǰ����֮������в��������ҳ���С���룬��Ϊ��һ��
			if (aStarMode){
				sort(lst.begin() + idx + 1, lst.end(), comStepDistance);
			}


			// ����ͼ��
			drawMap(map, hdc, winWid, winHei);

			FlushBatchDraw();
			idx++;
			if (isBoostMode()){
				//Sleep(1);
			}
			else{
				Sleep(60);
			}

			if (isKeyDown(' ') || isKeyDown(VK_SPACE)){
				goto pass_end_tag;
			}
			if (isKeyDown('T') || isKeyDown('t')){
				isShowText = !isShowText;
			}
			if (isKeyDown('E') || isKeyDown('e') || isKeyDown('R') || isKeyDown('r')){
				exchangeBlocks(map, winWid, winHei);
			}
		}

		drawMap(map, hdc, winWid, winHei);
		FlushBatchDraw();

		// �ּ���ȷ��
		//Sleep(2000);
	pass_end_tag:

		// �ͷŲ���������ڴ�
		for (vector<Step*>::iterator it = lst.begin(); it != lst.end(); it++){
			delete *it;
		}
	}

	// �ͷſռ�
	releaseMap(map);

	EndBatchDraw();
	closegraph();
	return 0;
}