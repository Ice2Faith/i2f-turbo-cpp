#include<graphics.h>
#include<conio.h>
#include<cstdlib>
#include<windows.h>
#include<stdio.h>
#include<iostream>
#include<thread>
using namespace std;
enum Mode{ m_Red, m_Green, m_Blue };
//当前颜色模式
Mode preMode = m_Red;
//当前颜色模式的值
int preValue = 0;
//鼠标消息接收
MOUSEMSG msg;
//当期那选中颜色参数
int preRed = 150;
int preGreen = 255;
int preBlue = 255;
//显示器屏幕大小
int ScreenX = GetSystemMetrics(SM_CXSCREEN);
int ScreenY = GetSystemMetrics(SM_CYSCREEN);
//最小显示边
int MinScreen = (ScreenX > ScreenY ? ScreenY : ScreenX);
//窗口大小
int WindowX = MinScreen * 2 / 3;
int WindowY = WindowX;
//主绘图展示区
int DisplayX = 0;
int DisplayY = 0;
int DisplayWid = WindowX * 2 / 3;
int DisplayHei = WindowY * 2 / 3;
//灰度区
int GrayX = 0;
int GrayY = DisplayY + DisplayHei;
int GrayWid = DisplayWid;
int GrayHei = (WindowY * 1 / 3) * 1 / 3;
//信息显示区
int InfoX = 0;
int InfoY = GrayY + GrayHei;
int InfoWid = DisplayWid;
int InfoHei = (WindowY * 1 / 3) * 2 / 3;
//导出按钮区
int ButtonX = InfoX + InfoWid * 8 / 10.0;
int ButtonY = InfoY + InfoHei * 2 / 10.0;
int ButtonWid = InfoWid*1.5 / 10.0;
int ButtonHei = InfoHei * 6 / 10.0;
//红色模型区
int RedBarX = DisplayX + DisplayWid;
int RedBarY = 0;
int RedBarWid = (WindowX * 1 / 3) * 1 / 3;
int RedBarHei = DisplayHei;
//绿色模型区
int GreenBarX = RedBarX + RedBarWid;
int GreenBarY = 0;
int GreenBarWid = (WindowX * 1 / 3) * 1 / 3;
int GreenBarHei = DisplayHei;
//蓝色模型区
int BlueBarX = GreenBarX + GreenBarWid;
int BlueBarY = 0;
int BlueBarWid = (WindowX * 1 / 3) * 1 / 3;
int BlueBarHei = DisplayHei;
//选中颜色预览区
int SelectColorX = InfoX + InfoWid;
int SelectColorY = InfoY;
int SelectColorWid = WindowX - InfoWid;
int SelectColorHei = InfoHei;
//红色主颜色选择按钮区
int MainRedX = RedBarX;
int MainRedY = RedBarY + RedBarHei;
int MainRedWid = RedBarWid;
int MainRedHei = GrayHei;
//绿色主颜色按钮区
int MainGreenX = GreenBarX;
int MainGreenY = GreenBarY + GreenBarHei;
int MainGreenWid = GreenBarWid;
int MainGreenHei = GrayHei;
//蓝色主颜色选中区
int MainBlueX = BlueBarX;
int MainBlueY = BlueBarY + BlueBarHei;
int MainBlueWid = BlueBarWid;
int MainBlueHei = GrayHei;
//绘制画板
void DrawDisplay()
{
	float wid = DisplayWid / 256.0;
	float hei = DisplayHei / 256.0;
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			if (preMode == m_Red)
			{
				setfillcolor(RGB(preValue, i, j));
			}
			else if (preMode == m_Green)
			{
				setfillcolor(RGB(i, preValue, j));
			}
			else if (preMode == m_Blue)
			{
				setfillcolor(RGB(i, j, preValue));
			}
			solidrectangle(DisplayX + i*wid, DisplayY + j*hei, DisplayX + i*wid + wid, DisplayY + j*hei + hei);
		}
	}
}
//绘制灰度
void DrawGray()
{
	float wid = GrayWid / 256.0;
	for (int i = 0; i < 256; i++)
	{
		setfillcolor(RGB(i, i, i));
		solidrectangle(GrayX + i*wid, GrayY, GrayX + i*wid + wid, GrayY + GrayHei);
	}
}
//绘制信息和导出按钮
void DrawInfo()
{
	setbkmode(TRANSPARENT);
	int FontWid = InfoWid / 30.0;
	int FontHei = InfoHei / 3.0;
	settextstyle(FontHei, FontWid, "黑体");
	setfillcolor(RGB(128, 128, 128));
	solidrectangle(InfoX, InfoY, InfoX + InfoWid, InfoY + InfoHei);
	char out[40] = { 0 };
	sprintf(out, "RGB:%7d %5d %5d\0", preRed, preGreen, preBlue);
	outtextxy(InfoX, InfoY, out);
	float H = 0, S = 0, L = 0, V = 0;
	RGBtoHSL(RGB(preRed, preGreen, preBlue), &H, &S, &L);
	sprintf(out, "HSL:%7.3f %5.3f %5.3f\0", H, S, L);
	outtextxy(InfoX, InfoY + InfoHei * 1 / 3, out);
	RGBtoHSV(RGB(preRed, preGreen, preBlue), &H, &S, &V);
	sprintf(out, "HSV:%7.3f %5.3f %5.3f\0", H, S, V);
	outtextxy(InfoX, InfoY + InfoHei * 2 / 3, out);
	setfillcolor(RGB(180, 180, 0));
	solidrectangle(ButtonX, ButtonY, ButtonX + ButtonWid, ButtonY + ButtonHei);
	outtextxy(ButtonX, InfoY + InfoHei * 1 / 3, "导出");
}
//绘制红色模型
void DrawRedBar()
{
	float hei = RedBarHei / 256.0;
	for (int i = 0; i < 256; i++)
	{
		setfillcolor(RGB(i, 0, 0));
		solidrectangle(RedBarX, RedBarY + i*hei, RedBarX + RedBarWid, RedBarY + i*hei + hei);
	}
	int lineWid = hei;
	if (lineWid < 2) lineWid = 2;
	if (lineWid>10) lineWid = hei / 2;
	setlinestyle(PS_SOLID | PS_JOIN_ROUND, lineWid);
	line(RedBarX + 1, preRed*hei, RedBarX + RedBarWid*1.0 / 3, preRed*hei);
}
//绘制绿色模型
void DrawGreenBar()
{
	float hei = GreenBarHei / 256.0;
	for (int i = 0; i < 256; i++)
	{
		setfillcolor(RGB(0, i, 0));
		solidrectangle(GreenBarX, GreenBarY + i*hei, GreenBarX + GreenBarWid, GreenBarY + i*hei + hei);
	}
	int lineWid = hei;
	if (lineWid < 2) lineWid = 2;
	if (lineWid>10) lineWid = hei / 2;
	setlinestyle(PS_SOLID | PS_JOIN_ROUND, lineWid);
	line(GreenBarX + 1, preGreen*hei, GreenBarX + GreenBarWid*1.0 / 3, preGreen*hei);
}
//绘制蓝色模型
void DrawBlueBar()
{
	float hei = GreenBarHei / 256.0;
	for (int i = 0; i < 256; i++)
	{
		setfillcolor(RGB(0, 0, i));
		solidrectangle(BlueBarX, BlueBarY + i*hei, BlueBarX + BlueBarWid, BlueBarY + i*hei + hei);
	}
	int lineWid = hei;
	if (lineWid < 2) lineWid = 2;
	if (lineWid>10) lineWid = hei / 2;
	setlinestyle(PS_SOLID | PS_JOIN_ROUND, lineWid);
	line(BlueBarX + 1, preBlue*hei, BlueBarX + BlueBarWid*1.0 / 3, preBlue*hei);
}
//绘制颜色预览
void DrawSelectColor()
{
	setfillcolor(RGB(preRed, preGreen, preBlue));
	solidrectangle(SelectColorX, SelectColorY, SelectColorX + SelectColorWid, SelectColorY + SelectColorHei);
}
//绘制红色主颜色选中
void DrawMainRed()
{
	setfillcolor(RGB(0, 0, 0));
	solidrectangle(MainRedX, MainRedY, MainRedX + MainRedWid, MainRedY + MainRedHei);
	if (preMode == m_Red)
	{
		float wid = MainRedWid * 2.0 / 10;
		float hei = MainRedHei*2.0 / 10;
		setfillcolor(RGB(0, 255, 255));
		solidrectangle(MainRedX + wid, MainRedY + hei, MainRedX + MainRedWid - wid, MainRedY + MainRedHei - hei);
	}
}
//绘制绿色主颜色选中
void DrawMainGreen()
{
	setfillcolor(RGB(0, 0, 0));
	solidrectangle(MainGreenX, MainGreenY, MainGreenX + MainGreenWid, MainGreenY + MainGreenHei);
	if (preMode == m_Green)
	{
		float wid = MainGreenWid * 2.0 / 10;
		float hei = MainGreenHei*2.0 / 10;
		setfillcolor(RGB(0, 255, 255));
		solidrectangle(MainGreenX + wid, MainGreenY + hei, MainGreenX + MainGreenWid - wid, MainGreenY + MainGreenHei - hei);
	}
}
//绘制蓝色主颜色选中
void DrawMainBlue()
{
	setfillcolor(RGB(0, 0, 0));
	solidrectangle(MainBlueX, MainBlueY, MainBlueX + MainBlueWid, MainBlueY + MainBlueHei);
	if (preMode == m_Blue)
	{
		float wid = MainBlueWid * 2.0 / 10;
		float hei = MainBlueHei*2.0 / 10;
		setfillcolor(RGB(0, 255, 255));
		solidrectangle(MainBlueX + wid, MainBlueY + hei, MainBlueX + MainBlueWid - wid, MainBlueY + MainBlueHei - hei);
	}
}
//鼠标信息获取与检测，按钮识别等,返回是否处理了鼠标消息
//只有处理了有效的鼠标消息才需要重新绘制画板，否则不需要重新绘制，减小系统开支
bool ChoiceMainColor()
{
	while (MouseHit())
	{
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			//固定色设置检测
			if (msg.x >= MainRedX
				&& msg.y >= MainRedY
				&& msg.x <= MainRedX + MainRedWid
				&& msg.y <= MainRedY + MainRedHei)
			{
				preMode = m_Red;
			}
			else if (msg.x >= MainGreenX
				&& msg.y >= MainGreenY
				&& msg.x <= MainGreenX + MainGreenWid
				&& msg.y <= MainGreenY + MainGreenHei)
			{
				preMode = m_Green;
			}
			else if (msg.x >= MainBlueX
				&& msg.y >= MainBlueY
				&& msg.x <= MainBlueX + MainBlueWid
				&& msg.y <= MainBlueY + MainBlueHei)
			{
				preMode = m_Blue;
			}
			//固定色数值设定检测
			if (preMode == m_Red
				&& msg.x >= RedBarX
				&& msg.y >= RedBarY
				&& msg.x <= RedBarX + RedBarWid
				&& msg.y <= RedBarY + RedBarHei)
			{
				preValue = 256 * (msg.y - RedBarY)*1.0 / RedBarHei;
				preRed = preValue;
			}
			else
			if (preMode == m_Green
				&& msg.x >= GreenBarX
				&& msg.y >= GreenBarY
				&& msg.x <= GreenBarX + GreenBarWid
				&& msg.y <= GreenBarY + GreenBarHei)
			{
				preValue = 256 * (msg.y - GreenBarY)*1.0 / GreenBarHei;
				preGreen = preValue;
			}
			else
			if (preMode == m_Blue
				&& msg.x >= BlueBarX
				&& msg.y >= BlueBarY
				&& msg.x <= BlueBarX + BlueBarWid
				&& msg.y <= BlueBarY + BlueBarHei)
			{
				preValue = 256 * (msg.y - BlueBarY)*1.0 / BlueBarHei;
				preBlue = preValue;
			}
			//选色板选色设置
			if (msg.x >= DisplayX
				&& msg.y >= DisplayY
				&& msg.x <= DisplayX + DisplayWid
				&&msg.y <= DisplayY + DisplayHei)
			{
				if (preMode == m_Red)
				{
					preRed = preValue;
					preGreen = 256 * (msg.x - DisplayX)*1.0 / DisplayWid;
					preBlue = 256 * (msg.y - DisplayY)*1.0 / DisplayHei;
				}
				else if (preMode == m_Green)
				{
					preGreen = preValue;
					preRed = 256 * (msg.x - DisplayX)*1.0 / DisplayWid;
					preBlue = 256 * (msg.y - DisplayY)*1.0 / DisplayHei;
				}
				else if (preMode == m_Blue)
				{
					preBlue = preValue;
					preRed = 256 * (msg.x - DisplayX)*1.0 / DisplayWid;
					preGreen = 256 * (msg.y - DisplayY)*1.0 / DisplayHei;
				}
			}
			//灰度选色
			if (msg.x >= GrayX
				&& msg.y >= GrayY
				&& msg.x <= GrayX + GrayWid
				&&msg.y <= GrayY + GrayHei)
			{
				preRed = 256 * (msg.x - GrayX)*1.0 / GrayWid;
				preGreen = preRed;
				preBlue = preRed;
				preValue = preRed;
			}
			//导出颜色
			if (msg.x >= ButtonX
				&& msg.y >= ButtonY
				&& msg.x <= ButtonX + ButtonWid
				&&msg.y <= ButtonY + ButtonHei)
			{
				system("cls");
				float H = 0, S = 0, L = 0, V = 0;
				printf("RGB:%7d %5d %5d\n", preRed, preGreen, preBlue);
				RGBtoHSL(RGB(preRed, preGreen, preBlue), &H, &S, &L);
				printf("HSL:%7.3f %5.3f %5.3f\n", H, S, L);
				RGBtoHSV(RGB(preRed, preGreen, preBlue), &H, &S, &V);
				printf("HSV:%7.3f %5.3f %5.3f\n", H, S, V);
				cout << "Designer : Ice2Faith" << endl;
			}
			return true;
		}
		else
		{
			return false;
		}

	}
}
void Help()
{
	system("cls");
	system("mode con lines=40 cols=80");
	cout << "	选色板使用说明" << endl;
	cout << "程序分为两部分：" << endl;
	cout << "	选色可视化选色部分和控制台数据部分" << endl;
	cout << "可视化选色部分：" << endl;
	cout << "	移动鼠标到你要选色的位置左键选取颜色" << endl;
	cout << "	将会在下方显示颜色参数和颜色大图预览" << endl;
	cout << "界面分解说明：" << endl;
	cout << "	左上角是在当前主颜色固定下的颜色总览" << endl;
	cout << "	右上角是三颜色块，你可以设置主颜色值，通过鼠标点击" << endl;
	cout << "	左中部分是灰度颜色模型，你可以进行设置" << endl;
	cout << "	右中部分是主颜色设置区，主颜色会标记为蓝绿色，鼠标点击进行设置" << endl;
	cout << "	左下部分是颜色参数显示区域" << endl;
	cout << "	右下部分是选中颜色预览" << endl;
	cout << "	导出 按钮 可以将参数信息输出到控制台上，方便复制" << endl;
	cout << "操作说明：" << endl;
	cout << "	ESC：退出运行本程序" << endl;
	cout << "	ALT+H:查看到此帮助" << endl;
	cout << "	Designer	Ice2Faith" << endl;
	system("pause");
	system("mode con lines=5 cols=30");
}
int main()
{
	initgraph(WindowX, WindowY, SHOWCONSOLE);
	system("title ColorSelectApp Designer Ice2Faith");
	system("color f1");
	system("mode con lines=5 cols=30");
	cout << "操作提示：" << endl;
	cout << "按 ESC 结束程序" << endl;
	cout << "按 ALT + H 查看帮助" << endl;
	bool needDraw = true;
	while (true)
	{
		if (needDraw)
		{
			BeginBatchDraw();
			DrawDisplay();
			DrawGray();
			DrawInfo();
			DrawRedBar();
			DrawGreenBar();
			DrawBlueBar();
			DrawSelectColor();
			DrawMainRed();
			DrawMainGreen();
			DrawMainBlue();
			EndBatchDraw();
		}
		needDraw = ChoiceMainColor();
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			break;
		}
		if ((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('H') & 0x8000))
		{
			//启用线程处理，并行运行
			thread help(Help);
			help.detach();
		}
		//减小系统开支，对用户来说没什么影响
		Sleep(5);

	}
	return 0;
}
