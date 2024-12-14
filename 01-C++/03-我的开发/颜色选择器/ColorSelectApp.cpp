#include<graphics.h>
#include<conio.h>
#include<cstdlib>
#include<windows.h>
#include<stdio.h>
#include<iostream>
#include<thread>
using namespace std;
enum Mode{ m_Red, m_Green, m_Blue };
//��ǰ��ɫģʽ
Mode preMode = m_Red;
//��ǰ��ɫģʽ��ֵ
int preValue = 0;
//�����Ϣ����
MOUSEMSG msg;
//������ѡ����ɫ����
int preRed = 150;
int preGreen = 255;
int preBlue = 255;
//��ʾ����Ļ��С
int ScreenX = GetSystemMetrics(SM_CXSCREEN);
int ScreenY = GetSystemMetrics(SM_CYSCREEN);
//��С��ʾ��
int MinScreen = (ScreenX > ScreenY ? ScreenY : ScreenX);
//���ڴ�С
int WindowX = MinScreen * 2 / 3;
int WindowY = WindowX;
//����ͼչʾ��
int DisplayX = 0;
int DisplayY = 0;
int DisplayWid = WindowX * 2 / 3;
int DisplayHei = WindowY * 2 / 3;
//�Ҷ���
int GrayX = 0;
int GrayY = DisplayY + DisplayHei;
int GrayWid = DisplayWid;
int GrayHei = (WindowY * 1 / 3) * 1 / 3;
//��Ϣ��ʾ��
int InfoX = 0;
int InfoY = GrayY + GrayHei;
int InfoWid = DisplayWid;
int InfoHei = (WindowY * 1 / 3) * 2 / 3;
//������ť��
int ButtonX = InfoX + InfoWid * 8 / 10.0;
int ButtonY = InfoY + InfoHei * 2 / 10.0;
int ButtonWid = InfoWid*1.5 / 10.0;
int ButtonHei = InfoHei * 6 / 10.0;
//��ɫģ����
int RedBarX = DisplayX + DisplayWid;
int RedBarY = 0;
int RedBarWid = (WindowX * 1 / 3) * 1 / 3;
int RedBarHei = DisplayHei;
//��ɫģ����
int GreenBarX = RedBarX + RedBarWid;
int GreenBarY = 0;
int GreenBarWid = (WindowX * 1 / 3) * 1 / 3;
int GreenBarHei = DisplayHei;
//��ɫģ����
int BlueBarX = GreenBarX + GreenBarWid;
int BlueBarY = 0;
int BlueBarWid = (WindowX * 1 / 3) * 1 / 3;
int BlueBarHei = DisplayHei;
//ѡ����ɫԤ����
int SelectColorX = InfoX + InfoWid;
int SelectColorY = InfoY;
int SelectColorWid = WindowX - InfoWid;
int SelectColorHei = InfoHei;
//��ɫ����ɫѡ��ť��
int MainRedX = RedBarX;
int MainRedY = RedBarY + RedBarHei;
int MainRedWid = RedBarWid;
int MainRedHei = GrayHei;
//��ɫ����ɫ��ť��
int MainGreenX = GreenBarX;
int MainGreenY = GreenBarY + GreenBarHei;
int MainGreenWid = GreenBarWid;
int MainGreenHei = GrayHei;
//��ɫ����ɫѡ����
int MainBlueX = BlueBarX;
int MainBlueY = BlueBarY + BlueBarHei;
int MainBlueWid = BlueBarWid;
int MainBlueHei = GrayHei;
//���ƻ���
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
//���ƻҶ�
void DrawGray()
{
	float wid = GrayWid / 256.0;
	for (int i = 0; i < 256; i++)
	{
		setfillcolor(RGB(i, i, i));
		solidrectangle(GrayX + i*wid, GrayY, GrayX + i*wid + wid, GrayY + GrayHei);
	}
}
//������Ϣ�͵�����ť
void DrawInfo()
{
	setbkmode(TRANSPARENT);
	int FontWid = InfoWid / 30.0;
	int FontHei = InfoHei / 3.0;
	settextstyle(FontHei, FontWid, "����");
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
	outtextxy(ButtonX, InfoY + InfoHei * 1 / 3, "����");
}
//���ƺ�ɫģ��
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
//������ɫģ��
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
//������ɫģ��
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
//������ɫԤ��
void DrawSelectColor()
{
	setfillcolor(RGB(preRed, preGreen, preBlue));
	solidrectangle(SelectColorX, SelectColorY, SelectColorX + SelectColorWid, SelectColorY + SelectColorHei);
}
//���ƺ�ɫ����ɫѡ��
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
//������ɫ����ɫѡ��
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
//������ɫ����ɫѡ��
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
//�����Ϣ��ȡ���⣬��ťʶ���,�����Ƿ����������Ϣ
//ֻ�д�������Ч�������Ϣ����Ҫ���»��ƻ��壬������Ҫ���»��ƣ���Сϵͳ��֧
bool ChoiceMainColor()
{
	while (MouseHit())
	{
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN)
		{
			//�̶�ɫ���ü��
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
			//�̶�ɫ��ֵ�趨���
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
			//ѡɫ��ѡɫ����
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
			//�Ҷ�ѡɫ
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
			//������ɫ
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
	cout << "	ѡɫ��ʹ��˵��" << endl;
	cout << "�����Ϊ�����֣�" << endl;
	cout << "	ѡɫ���ӻ�ѡɫ���ֺͿ���̨���ݲ���" << endl;
	cout << "���ӻ�ѡɫ���֣�" << endl;
	cout << "	�ƶ���굽��Ҫѡɫ��λ�����ѡȡ��ɫ" << endl;
	cout << "	�������·���ʾ��ɫ��������ɫ��ͼԤ��" << endl;
	cout << "����ֽ�˵����" << endl;
	cout << "	���Ͻ����ڵ�ǰ����ɫ�̶��µ���ɫ����" << endl;
	cout << "	���Ͻ�������ɫ�飬�������������ɫֵ��ͨ�������" << endl;
	cout << "	���в����ǻҶ���ɫģ�ͣ�����Խ�������" << endl;
	cout << "	���в���������ɫ������������ɫ����Ϊ����ɫ���������������" << endl;
	cout << "	���²�������ɫ������ʾ����" << endl;
	cout << "	���²�����ѡ����ɫԤ��" << endl;
	cout << "	���� ��ť ���Խ�������Ϣ���������̨�ϣ����㸴��" << endl;
	cout << "����˵����" << endl;
	cout << "	ESC���˳����б�����" << endl;
	cout << "	ALT+H:�鿴���˰���" << endl;
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
	cout << "������ʾ��" << endl;
	cout << "�� ESC ��������" << endl;
	cout << "�� ALT + H �鿴����" << endl;
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
			//�����̴߳�����������
			thread help(Help);
			help.detach();
		}
		//��Сϵͳ��֧�����û���˵ûʲôӰ��
		Sleep(5);

	}
	return 0;
}
