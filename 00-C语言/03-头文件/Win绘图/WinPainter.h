#pragma once
/*
一个进行简单封装的WIN API 绘图类
包含常用的绘图函数和一些设置
目的是为了简化用WIN API GDI 绘图的繁琐操作

使用示例：
WinPainter pain(hWnd);//WinPainter pain(hdc);
pain.CircleP(0,0,100);
*/
class WinPainter
{
public:
	WinPainter(HWND hwnd);
	WinPainter(HDC hdc);
	BOOL EllipseP(int left, int top, int right, int buttom);
	BOOL SquareP(int x, int y, int len);
	BOOL RectangleP(int left, int top, int right, int buttom);
	BOOL CircleP(int x, int y, int r);
	int SetBackModeP(int mode);
	COLORREF SetPixelP(int x, int y, COLORREF color);
	BOOL SetPixelVP(int x, int y, COLORREF color);
	COLORREF GetPixelP(int x, int y, COLORREF color);
	void SetFillColorP(COLORREF color);
	BOOL LineP(int x1, int y1, int x2, int y2);
	BOOL PolyLineP(POINT * points, int count);
	BOOL PolygonP(POINT * points, int count);
	BOOL RoundRectangleP(int left, int top, int right, int buttom, int width, int height);
	BOOL TextOutP(int x, int y, TCHAR * str);
	void SetBrushColorP(COLORREF color);
	void SetPenColorP(COLORREF color);
	void SetBmpBrushP(HBITMAP bmp);
	void SetBrushP(UINT style, COLORREF color, LONG hatch);
	void SetPenP(UINT style, int width, COLORREF color);
	void SetTextStyleP(int height, int width = 0, LONG wight = 0, BYTE italic = 0, BYTE underline = 0, TCHAR * facename = L"微软雅黑");
	COLORREF SetTextColorP(COLORREF color);
	COLORREF SetTextBackColor(COLORREF color);
	HBRUSH GetOldBrush();
	HPEN GetOldPen();
	HFONT GetOldFont();
private:
	HDC hdc;
	HBRUSH oldBrush;
	HFONT oldFont;
	HPEN oldPen;
};
