#ifndef _ALGO_WIN_BATCH_DRAW_HPP_
#define _ALGO_WIN_BATCH_DRAW_HPP_
#include<Windows.h>

class AlgoWinBatchDraw
{
public:
	void CenterOrg()
	{
		SetMapMode(bdc, MM_ANISOTROPIC);
		SetViewportOrgEx(bdc, wWid / 2, wHei / 2, NULL);
		SetViewportExtEx(bdc, wWid, wHei, NULL);
		SetWindowOrgEx(bdc, 0, 0, NULL);
		SetWindowExtEx(bdc, wWid, -wHei, NULL);


		//SetViewportOrg(mWid / 2, mHei / 2);
		//SetViewportExt(mWid, mHei);
		//SetWindowOrg(0, 0);
		//SetWindowExt(mWid, -mHei);

	}
	void ResetOrg()
	{
		SetMapMode(bdc, MM_ANISOTROPIC);
		SetViewportOrgEx(bdc, 0, 0, NULL);
		SetViewportExtEx(bdc, wWid, wHei, NULL);
		SetWindowOrgEx(bdc, 0, 0, NULL);
		SetWindowExtEx(bdc, wWid, wHei, NULL);

		//SetViewportOrg(0, 0);
		//SetViewportExt(mWid, mHei);
		//SetWindowOrg(0, 0);
		//SetWindowExt(mWid, mHei);
	}

	AlgoWinBatchDraw(HWND hwnd)
	{
		m_hwnd = hwnd;
		hdc = GetDC(m_hwnd);
		InitDrawEnv();
		BuildBackgroundImg();
	}
	AlgoWinBatchDraw(HDC hdc, int wid, int hei)
	{
		m_hwnd = NULL;
		this->hdc = hdc;
		this->wWid = wid;
		this->wHei = hei;
		InitDrawEnv();
		BuildBackgroundImg();
	}
	~AlgoWinBatchDraw()
	{
		DeleteDC(bdc);
		DeleteDC(mdc);
		DeleteDC(hdc);
		if (m_hwnd != NULL)
		{
			ReleaseDC(m_hwnd, hdc);
		}
		ReleaseDC(NULL, mdc);
		ReleaseDC(NULL, bdc);
		DeleteObject(bdimg);
		DeleteObject(mdimg);
	}
	HDC BeginBatchDraw()
	{
		SelectObject(mdc, mdimg);
		SelectObject(bdc, bdimg);
		return bdc;
	}
	void SubmitBatchDraw()
	{
		BitBlt(mdc, 0, 0, wWid, wHei, bdc, 0, 0, SRCCOPY);
		SelectObject(bdc, bdimg);
	}
	void FlushBatchDraw()
	{
		BitBlt(hdc, 0, 0, wWid, wHei, mdc, 0, 0, SRCCOPY);
	}
	void EndBatchDraw()
	{
		BitBlt(mdc, 0, 0, wWid, wHei, bdc, 0, 0, SRCCOPY);
		SelectObject(bdc, bdimg);
		BitBlt(hdc, 0, 0, wWid, wHei, mdc, 0, 0, SRCCOPY);
	}
	HDC GetHDC()
	{
		return bdc;
	}
	int GetDCHeight()
	{
		return wHei;
	}
	int GetDCWidth()
	{
		return wWid;
	}
	HDC getMDC()
	{
		return mdc;
	}
	void clearHDC(COLORREF bgcolor = 0xffffff)
	{
		HBRUSH bkb = CreateSolidBrush(bgcolor);
		HGDIOBJ obk = SelectObject(bdc,bkb);
		HPEN pen = CreatePen(0, 0, bgcolor);
		HGDIOBJ oldpen = SelectObject(bdc,pen);
		Rectangle(bdc,0, 0, wWid, wHei);
		DeleteObject(SelectObject(bdc, obk));
		DeleteObject(SelectObject(bdc, oldpen));
	}
private:
	void InitDrawEnv()
	{
		mdc = CreateCompatibleDC(hdc);
		bdc = CreateCompatibleDC(hdc);
		if (m_hwnd != NULL)
		{
			RECT rect;
			GetWindowRect(m_hwnd, &rect);
			wWid = rect.right - rect.left;
			wHei = rect.bottom - rect.top;
		}
		mdimg = CreateCompatibleBitmap(hdc, wWid, wHei);
	}
	void BuildBackgroundImg()
	{
		BITMAPINFOHEADER stBmpInfoHeader = { 0 };
		int nBytesPerLine = ((wWid * 32 + 31) & (~31)) >> 3;
		stBmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
		stBmpInfoHeader.biWidth = wWid;
		stBmpInfoHeader.biHeight = wHei;
		stBmpInfoHeader.biPlanes = 1;
		stBmpInfoHeader.biBitCount = 32;
		stBmpInfoHeader.biCompression = BI_RGB;
		stBmpInfoHeader.biClrUsed = 0;
		stBmpInfoHeader.biSizeImage = nBytesPerLine * wHei;
		PVOID pvBits = NULL;
		bdimg = ::CreateDIBSection(NULL, (PBITMAPINFO)&stBmpInfoHeader, DIB_RGB_COLORS, &pvBits, NULL, 0);
		SelectObject(bdc, bdimg);
	}
private:
	HWND m_hwnd;
	HDC hdc, mdc, bdc;
	HBITMAP mdimg, bdimg;
	int wWid, wHei;
};

#endif // _ALGO_WIN_BATCH_DRAW_HPP_