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
		printf("正在处理图片...\n");
		IMAGE ret = GraphRect(img, lefttop, leftdown, righttop, rightdown);
		saveimage(argv[2], &ret);
		printf("文件处理完毕。(%s)\n",argv[2]);
		
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
		printf("请输入新文件名：(需要文件后缀，文件类型由后缀决定，常见图片格式jpg,png,bmp等)\n>/ ");
		scanf("%s", newname);
		IMAGE simg;
		loadimage(&simg,argv[1],720,480,true);
		printf("即将开始进行图形选取控制点，这是操作提示：\n\
使用鼠标左键顺序点击你要的四边形区域的左上，左下，右下，右上（逆时针）\n\
选取完毕之后会显示您选取的区域\n\
如果区域符合要求，则点击键盘的空格键确认进行处理\n\
如果不满意，则可以继续顺序点击重设控制点\n\
请确保您选取的区域是一个四边形，不是X型或者其他非凸四面体\n\
点击键盘任意键进入选取\n>/");
		fflush(stdin);
		getch();
		printf("\n");
		getIllegalRect(simg,img.getheight(),img.getwidth(),&lefttop,&leftdown,&righttop,&rightdown);
		printf("正在处理图片...\n");
		IMAGE ret = GraphRect(img, lefttop, leftdown, righttop, rightdown);
		saveimage(newname, &ret);
		printf("文件处理完毕。(%s)\n", newname);
		char cmd[1024] = { "explorer " };
		strcat(cmd,newname);
		system(cmd);
	}
	else
	{
		printf("使用向导及说明：\n\
说明：给定图片和一个不规则四边形的的四个控制点，程序将会把这个四边形区域拉伸为矩形区域进行保存。\n\
控制台参数：\n\
源文件名 目标文件名 左上角控制点坐标 左下角控制点坐标 右上角控制点坐标 右下角控制点坐标\n\
控制点坐标分为两部分，及图片X轴方向（屏幕从左到右为正方向），图片Y轴方向（屏幕从上到下为正方向）\n\
因此，参数可能会是这个样子：\n\
test.png test_rect.png 100 100 100 480 320 120 480 360\n\
后面的坐标可以省略，默认是对应的图片的顶点坐标\n\
交互式使用：\n\
将图片文件拖动到本程序文件上，启动即可（或者控制台只传递源文件名即可）\n\
保存的格式有你的输入新文件名后缀决定，支持大多数图片格式（jpg,png,bmp等）\n\
\n");
		system("pause");
	}
	
	return 0;
}
