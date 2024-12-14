#ifndef _ALGO_WIN_PAINTER_HPP_
#define _ALGO_WIN_PAINTER_HPP_
#include<Windows.h>

#include<gdiplus.h>
#pragma comment(lib,"gdiplus.lib")

class AlgoWinPainter
{
private:
	static ULONG_PTR m_gdiplusToken;
public:
	static Gdiplus::Status InitGdiPlus()
	{
		Gdiplus::GdiplusStartupInput m_gdiplusStartupInput;
		return Gdiplus::GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);
	}
	static void ReleaseGdiPlus()
	{
		Gdiplus::GdiplusShutdown(m_gdiplusToken);
	}
	static Gdiplus::Bitmap * loadBitmapFile(WCHAR * fileName)
	{
		return Gdiplus::Bitmap::FromFile(fileName);
	}
	static Gdiplus::Bitmap * fromHBITMAP(HBITMAP bmp)
	{
		return Gdiplus::Bitmap::FromHBITMAP(bmp, NULL);
	}
	
	static Gdiplus::Status saveImage(Gdiplus::Bitmap * img, WCHAR * fileName, WCHAR * format = L"image/png")
	{
		CLSID id;
		GetEncoderClsid(format, &id);
		return img->Save(fileName, &id, NULL);
	}
	static int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
	{
		UINT num = 0;
		UINT size = 0;

		Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

		Gdiplus::GetImageEncodersSize(&num, &size);
		if (size == 0)
		{
			return -1;
		}
		pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
		if (pImageCodecInfo == NULL)
		{
			return -1;
		}

		GetImageEncoders(num, size, pImageCodecInfo);

		for (UINT j = 0; j< num; ++j)
		{
			if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
			{
				*pClsid = pImageCodecInfo[j].Clsid;
				free(pImageCodecInfo);
				return j;
			}
		}

		free(pImageCodecInfo);
		return -1;
	}
public:
	static HBITMAP loadBitmapFile(HINSTANCE hIns, TCHAR * filePath)
	{
		return LoadBitmap(hIns, filePath);
	}
	static HBITMAP createBitmap(int width, int height)
	{
		BITMAPINFOHEADER stBmpInfoHeader = { 0 };
		int nBytesPerLine = ((width * 32 + 31) & (~31)) >> 3;
		stBmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
		stBmpInfoHeader.biWidth = width;
		stBmpInfoHeader.biHeight = height;
		stBmpInfoHeader.biPlanes = 1;
		stBmpInfoHeader.biBitCount = 32;
		stBmpInfoHeader.biCompression = BI_RGB;
		stBmpInfoHeader.biClrUsed = 0;
		stBmpInfoHeader.biSizeImage = nBytesPerLine * height;
		PVOID pvBits = NULL;
		return ::CreateDIBSection(NULL, (PBITMAPINFO)&stBmpInfoHeader, DIB_RGB_COLORS, &pvBits, NULL, 0);
	}
	static HBRUSH createBitmapBrush(HBITMAP bmp)
	{
		return CreatePatternBrush(bmp);
	}
	static HBRUSH createBrush(COLORREF color, UINT style = BS_SOLID, LONG hatch = HS_HORIZONTAL)
	{
		LOGBRUSH lb;
		lb.lbStyle = style;
		lb.lbColor = color;
		lb.lbHatch = hatch;
		return CreateBrushIndirect(&lb);
	}
	static HPEN createPen(COLORREF color, int width = 1, UINT style = PS_SOLID)
	{
		return CreatePen(style, width, color);
	}
	static HFONT createFont(int width, int height = 0, LONG weight = 0, BYTE italic = 0, BYTE underline = 0, TCHAR * facename = NULL)
	{
		LOGFONT lf;
		memset(&lf, 0, sizeof(lf));
		lf.lfWidth = width;
		lf.lfHeight = height;
		lf.lfWeight = weight;
		lf.lfItalic = italic;
		lf.lfUnderline = underline;
		if (facename != NULL)
			lstrcpy(lf.lfFaceName, facename);
		return  CreateFontIndirect(&lf);
	}
	/*
	获取Windows的RGB颜色分量
	*/
	static int getR(COLORREF c)
	{
		return (c)& 0xff;
	}
	static int getG(COLORREF c)
	{
		return (c >> 8) & 0xff;
	}
	static int getB(COLORREF c)
	{
		return (c >> 16) & 0xff;
	}
	template<typename T>
	static void getRgbPart(COLORREF ic, T * or, T * og, T * ob)
	{
		*or = c & 0xff;
		*og = (c >> 8) & 0xff;
		*ob = (c >> 16) & 0xff;
	}
	template<typename T>
	static COLORREF getRgbFrom(T r, T g, T b)
	{
		COLORREF c = 0;
		c = 0 | (r & 0xff) | ((g & 0xff) << 8) | ((b & 0xff) << 16);
		return c;
	}
public:
	AlgoWinPainter(HWND hwnd)
	{
		this->hwnd = hwnd;
		this->hdc = GetDC(hwnd);
	}
	AlgoWinPainter(HDC hdc)
	{
		hwnd = NULL;
		this->hdc = hdc;
	}
	~AlgoWinPainter()
	{
		if (hwnd != NULL)
			ReleaseDC(hwnd, hdc);
	}
	BOOL drawEllipse(int left, int top, int right, int buttom)
	{
		return Ellipse(hdc, left, top, right, buttom);
	}
	BOOL drawCircle(int x, int y, int r)
	{
		return Ellipse(hdc, x-r,y-r,x+r,y+r);
	}
	BOOL drawEllipse(RECT rect)
	{
		return Ellipse(hdc, rect.left,rect.top,rect.right,rect.bottom);
	}
	BOOL drawRectangle(int left, int top, int right, int buttom)
	{
		return Rectangle(hdc, left, top, right, buttom);
	}
	BOOL drawRectangle(RECT rect)
	{
		return Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
	}
	BOOL drawSquare(int left, int top, int len)
	{
		return Rectangle(hdc, left, top, left+len, top+len);
	}
	BOOL drawPolyBezier(POINT * points,int count)
	{
		return PolyBezier(hdc, points, count);
	}
	BOOL drawArc(int left, int top, int right, int buttom,int beginx,int beginy,int endx,int endy)
	{
		return ArcTo(hdc, left, top, right, buttom, beginx, beginy, endx, endy);
	}
	BOOL drawArc(RECT rect, int beginx, int beginy, int endx, int endy)
	{
		return ArcTo(hdc, rect.left, rect.top, rect.right, rect.bottom, beginx, beginy, endx, endy);
	}
	int setBackModeTransparent()
	{
		return SetBkMode(hdc, TRANSPARENT);
	}
	int setBackModeBrush()
	{
		return SetBkMode(hdc, OPAQUE);
	}
	COLORREF drawPixel(int x, int y, COLORREF color)
	{
		return SetPixel(hdc, x, y, color);
	}
	BOOL drawPixelV(int x, int y, COLORREF color)
	{
		return SetPixelV(hdc, x, y, color);
	}
	COLORREF getPixel(int x, int y)
	{
		return GetPixel(hdc, x, y);
	}
	BOOL drawLine(int x1, int y1, int x2, int y2)
	{
		POINT p;
		MoveToEx(hdc, x1, y1, &p);
		return LineTo(hdc, x2, y2);
	}
	BOOL drawPolyline(POINT * points, int count)
	{
		return Polyline(hdc, points, count);
	}
	BOOL drawPolygon(POINT * points, int count)
	{
		return Polygon(hdc, points, count);
	}
	BOOL drawRoundRect(int left, int top, int right, int buttom, int width, int height)
	{
		return RoundRect(hdc, left, top, right, buttom, width, height);
	}
	BOOL drawTextOut(int x, int y, TCHAR * str)
	{
		return TextOut(hdc, x, y, str, lstrlen(str));
	}
	COLORREF setTextColor(COLORREF color)
	{
		return SetTextColor(hdc, color);
	}
	COLORREF setBgColor(COLORREF color)
	{
		return SetBkColor(hdc, color);
	}
private:
	HDC hdc;

	HWND hwnd;
};
ULONG_PTR AlgoWinPainter::m_gdiplusToken = NULL;

#endif // _ALGO_WIN_PAINTER_HPP_