#include "stdafx.h"
#include "WinPainter.h"

WinPainter::WinPainter(HWND hwnd)
{
	this->hdc = GetDC(hwnd);
}
WinPainter::WinPainter(HDC hdc)
{
	this->hdc = hdc;
}
BOOL WinPainter::EllipseP(int left, int top, int right, int buttom)
{
	return Ellipse(hdc, left, top, right, buttom);
}
BOOL WinPainter::RectangleP(int left, int top, int right, int buttom)
{
	return Rectangle(hdc, left, top, right, buttom);
}
BOOL WinPainter::CircleP(int x, int y, int r)
{
	return Ellipse(hdc, x - r, y - r, x + r, y + r);
}
int WinPainter::SetBackModeP(int mode)
{
	return SetBkMode(hdc, mode);
}
COLORREF WinPainter::SetPixelP(int x, int y, COLORREF color)
{
	return SetPixel(hdc, x, y, color);
}
BOOL WinPainter::SetPixelVP(int x, int y, COLORREF color)
{
	return SetPixelV(hdc, x, y, color);
}
COLORREF WinPainter::GetPixelP(int x, int y, COLORREF color)
{
	return GetPixel(hdc, x, y);
}
void WinPainter::SetFillColorP(COLORREF color)
{
	HBRUSH brush = CreateSolidBrush(color);
	oldBrush=(HBRUSH)SelectObject(hdc, brush);
}
BOOL WinPainter::LineP(int x1, int y1, int x2, int y2)
{
	POINT p;
	MoveToEx(hdc, x1, y1, &p);
	return LineTo(hdc, x2, y2);
}
BOOL WinPainter::PolyLineP(POINT * points, int count)
{
	return Polyline(hdc, points, count);
}
BOOL WinPainter::PolygonP(POINT * points, int count)
{
	return Polygon(hdc, points, count);
}
BOOL WinPainter::RoundRectangleP(int left, int top, int right, int buttom, int width, int height)
{
	return RoundRect(hdc, left, top, right, buttom, width, height);
}
BOOL WinPainter::SquareP(int x, int y, int len)
{
	return Rectangle(hdc, x, y, x + len, y + len);
}
BOOL WinPainter::TextOutP(int x, int y, TCHAR * str)
{
	return TextOut(hdc, x, y, str, lstrlen(str));
}
void WinPainter::SetBrushColorP(COLORREF color)
{
	HBRUSH brush = CreateSolidBrush(color);
	oldBrush=(HBRUSH)SelectObject(hdc, brush);
}
void WinPainter::SetPenColorP(COLORREF color)
{
	HPEN pen = CreatePen(PS_SOLID, 1, color);
	oldPen=(HPEN)SelectObject(hdc, pen);
}
void WinPainter::SetBmpBrushP(HBITMAP bmp)
{
	HBRUSH brush = CreatePatternBrush(bmp);
	oldBrush=(HBRUSH)SelectObject(hdc, brush);
}
void WinPainter::SetBrushP(UINT style, COLORREF color, LONG hatch)
{
	LOGBRUSH lb;
	lb.lbStyle = style;
	lb.lbColor = color;
	lb.lbHatch = hatch;
	HBRUSH brush = CreateBrushIndirect(&lb);
	oldBrush=(HBRUSH)SelectObject(hdc, brush);
}
void WinPainter::SetPenP(UINT style, int width, COLORREF color)
{
	HPEN pen = CreatePen(style, width, color);
	SelectObject(hdc, pen);
}
void WinPainter::SetTextStyleP(int height, int width, LONG wight, BYTE italic, BYTE underline, TCHAR * facename)
{
	LOGFONT lf;
	memset(&lf, 0, sizeof(lf));
	lf.lfWidth = width;
	lf.lfHeight = height;
	lf.lfWeight = wight;
	lf.lfItalic = italic;
	lf.lfUnderline = underline;
	_stprintf_s(lf.lfFaceName, TEXT("%s"), facename);
	HFONT font = CreateFontIndirect(&lf);
	oldFont=(HFONT)SelectObject(hdc, font);
}
COLORREF WinPainter::SetTextColorP(COLORREF color)
{
	return SetTextColor(hdc, color);
}
COLORREF WinPainter::SetTextBackColor(COLORREF color)
{
	return SetBkColor(hdc, color);
}
HBRUSH WinPainter::GetOldBrush()
{
	return oldBrush;
}
HPEN WinPainter::GetOldPen()
{
	return oldPen;
}
HFONT WinPainter::GetOldFont()
{
	return oldFont;
}
