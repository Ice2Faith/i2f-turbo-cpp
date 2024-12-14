#include<graphics.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
typedef struct _point
{
	int x;
	int y;
}GPOINT;
double GetDistance(GPOINT p1, GPOINT p2)
{
	return sqrt(pow(p2.x - p1.x, 2.0) + pow(p2.y - p1.y, 2.0));;
}
GPOINT GetLineRatePoint(GPOINT sp,GPOINT ep,double rate)
{
	GPOINT ret = {0};
	int dx = ep.x - sp.x;
	int dy = ep.y - sp.y;
	ret.x = sp.x + dx*rate;
	ret.y = sp.y + dy*rate;
	return ret;
}
IMAGE GraphRect(IMAGE  img, GPOINT leftTop, GPOINT leftDown, GPOINT rightTop, GPOINT rightDown)
{
	int minLeft = leftTop.x < leftDown.x ? leftTop.x : leftDown.x;
	int minTop = leftTop.y < rightTop.y ? leftTop.y : rightTop.y;
	int maxRight = rightTop.x > rightDown.x ? rightTop.x : rightDown.x;
	int maxDown = leftDown.y > rightDown.y ? leftDown.y : rightDown.y;
	int wid = maxRight - minLeft;
	int hei = maxDown - minTop;
	IMAGE ret(wid, hei);
	HDC srcdc = GetImageHDC(&img);
	HDC drtdc = GetImageHDC(&ret);
	for (int i = 0; i < hei; i++)
	{
		for (int j = 0; j < wid; j++)
		{
			double ratex = j*1.0 /wid;
			double ratey = i*1.0 / hei;
			GPOINT toptp = GetLineRatePoint(leftTop,rightTop,ratex);
			GPOINT downtp = GetLineRatePoint(leftDown,rightDown,ratex);
			GPOINT target = GetLineRatePoint(toptp,downtp,ratey);

			COLORREF color = GetPixel(srcdc, target.x, target.y);
			SetPixelV(drtdc, j, i, color);
		}
	}
	return ret;
}
void getIllegalRect(IMAGE img,int imghei,int imgwid,GPOINT * lefttop,GPOINT * leftdown,GPOINT * righttop,GPOINT * rightdown)
{
	initgraph(720,480);
	putimage(0, 0, &img);
	MOUSEMSG msg = { 0 };
	int count = 0;
	POINT arr[5];
	while (true)
	{
		if (MouseHit())
		{
			msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN)
			{
				switch (count)
				{
				case 0:
					lefttop->x = msg.x/720.0*imgwid;
					lefttop->y = msg.y/480.0*imghei;
					arr[0].x = msg.x;
					arr[0].y = msg.y;
					break;
				case 1:
					leftdown->x = msg.x / 720.0*imgwid;
					leftdown->y = msg.y / 480.0*imghei;
					arr[1].x = msg.x;
					arr[1].y = msg.y;
					break;
				case 2:
					rightdown->x = msg.x / 720.0*imgwid;
					rightdown->y = msg.y / 480.0*imghei;
					arr[2].x = msg.x;
					arr[2].y = msg.y;
					break;
				case 3:
					righttop->x = msg.x / 720.0*imgwid;
					righttop->y = msg.y / 480.0*imghei;
					arr[3].x = msg.x;
					arr[3].y = msg.y;
					arr[4] = arr[0];
					putimage(0, 0, &img);
					setlinecolor(0x0000ff);
					polyline(arr, 5);
					break;
				}
				count=(count+1)%4;
			}
		}
		if (kbhit())
		{
			if (getch() == ' ')
				break;
		}
	}
	closegraph();
}
int main(int argc, char * argv[])
{
	if (argc >= 3)
	{
		IMAGE img;
		loadimage(&img, argv[1]);
		GPOINT lefttop = { 0, 0 };
		GPOINT leftdown = { 0, 0 };
		GPOINT righttop = { 0, 0 };
		GPOINT rightdown = { 0, 0 };
		leftdown.y = img.getheight();
		rightdown.y = img.getheight();
		rightdown.x = img.getwidth();
		righttop.x = img.getwidth();
		if (argc >= 4)
			sscanf(argv[3],"%d",&lefttop.x);
		if (argc >= 5)
			sscanf(argv[4], "%d", &lefttop.y);
		if (argc >= 6)
			sscanf(argv[5], "%d", &leftdown.x);
		if (argc >= 7)
			sscanf(argv[6], "%d", &leftdown.y);
		if (argc >= 8)
			sscanf(argv[7], "%d", &righttop.x);
		if (argc >= 9)
			sscanf(argv[8], "%d", &righttop.y);
		if (argc >= 10)
			sscanf(argv[9], "%d", &rightdown.x);
		if (argc >= 11)
			sscanf(argv[10], "%d", &rightdown.y);
		printf("���ڴ���ͼƬ...\n");
		IMAGE ret = GraphRect(img, lefttop, leftdown, righttop, rightdown);
		saveimage(argv[2], &ret);
		printf("�ļ�������ϡ�(%s)\n",argv[2]);
		
	}
	else if(argc == 2)
	{
		IMAGE img;
		loadimage(&img, argv[1]);
		GPOINT lefttop = { 0, 0 };
		GPOINT leftdown = { 0, 0 };
		GPOINT righttop = { 0, 0 };
		GPOINT rightdown = { 0, 0 };
		char newname[1024] = { 0 };
		printf("���������ļ�����(��Ҫ�ļ���׺���ļ������ɺ�׺����������ͼƬ��ʽjpg,png,bmp��)\n>/ ");
		scanf("%s", newname);
		IMAGE simg;
		loadimage(&simg,argv[1],720,480,true);
		printf("������ʼ����ͼ��ѡȡ���Ƶ㣬���ǲ�����ʾ��\n\
ʹ��������˳������Ҫ���ı�����������ϣ����£����£����ϣ���ʱ�룩\n\
ѡȡ���֮�����ʾ��ѡȡ������\n\
����������Ҫ���������̵Ŀո��ȷ�Ͻ��д���\n\
��������⣬����Լ���˳����������Ƶ�\n\
��ȷ����ѡȡ��������һ���ı��Σ�����X�ͻ���������͹������\n\
����������������ѡȡ\n>/");
		fflush(stdin);
		getch();
		printf("\n");
		getIllegalRect(simg,img.getheight(),img.getwidth(),&lefttop,&leftdown,&righttop,&rightdown);
		printf("���ڴ���ͼƬ...\n");
		IMAGE ret = GraphRect(img, lefttop, leftdown, righttop, rightdown);
		saveimage(newname, &ret);
		printf("�ļ�������ϡ�(%s)\n", newname);
		char cmd[1024] = { "explorer " };
		strcat(cmd,newname);
		system(cmd);
	}
	else
	{
		printf("ʹ���򵼼�˵����\n\
˵��������ͼƬ��һ���������ı��εĵ��ĸ����Ƶ㣬���򽫻������ı�����������Ϊ����������б��档\n\
����̨������\n\
Դ�ļ��� Ŀ���ļ��� ���Ͻǿ��Ƶ����� ���½ǿ��Ƶ����� ���Ͻǿ��Ƶ����� ���½ǿ��Ƶ�����\n\
���Ƶ������Ϊ�����֣���ͼƬX�᷽����Ļ������Ϊ�����򣩣�ͼƬY�᷽����Ļ���ϵ���Ϊ������\n\
��ˣ��������ܻ���������ӣ�\n\
test.png test_rect.png 100 100 100 480 320 120 480 360\n\
������������ʡ�ԣ�Ĭ���Ƕ�Ӧ��ͼƬ�Ķ�������\n\
����ʽʹ�ã�\n\
��ͼƬ�ļ��϶����������ļ��ϣ��������ɣ����߿���ֻ̨����Դ�ļ������ɣ�\n\
����ĸ�ʽ������������ļ�����׺������֧�ִ����ͼƬ��ʽ��jpg,png,bmp�ȣ�\n\
\n");
		system("pause");
	}
	
	return 0;
}
