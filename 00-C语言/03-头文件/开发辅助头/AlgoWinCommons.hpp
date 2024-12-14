#ifndef _ALGO_WIN_COMMONS_HPP_
#define _ALGO_WIN_COMMONS_HPP_
#include<Windows.h>
#include<stdio.h>

class AlgoWinCommons{
public:
	int getDesktopAbsWidth(){
		HDC ddc = GetDC(NULL);
		int pwid = GetDeviceCaps(ddc, DESKTOPHORZRES);
		return pwid;
	}
	int getDesktopAbsHeight(){
		HDC ddc = GetDC(NULL);
		int phei = GetDeviceCaps(ddc, DESKTOPVERTRES);
		return phei;
	}
	int stretchBltSmooth(HDC dstDC){
		//使用HALFTONE进行高精度的图形缩放
		int oldMode = GetStretchBltMode(dstDC);
		SetStretchBltMode(dstDC, HALFTONE);
		return oldMode;
	}
	bool copyBitmap2Clipboard(HWND ower,HBITMAP bmp){
		bool ret = false;
		if (OpenClipboard(ower)){
			if (EmptyClipboard()){
				SetClipboardData(CF_BITMAP, bmp);
				ret = true;
			}
			CloseClipboard();
		}
		return ret;
	}
	HBITMAP buildBitmap(int wid, int hei)
	{
		BITMAPINFOHEADER stBmpInfoHeader = { 0 };
		int nBytesPerLine = ((wid * 32 + 31) & (~31)) >> 3;
		stBmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
		stBmpInfoHeader.biWidth = wid;
		stBmpInfoHeader.biHeight = hei;
		stBmpInfoHeader.biPlanes = 1;
		stBmpInfoHeader.biBitCount = 32;
		stBmpInfoHeader.biCompression = BI_RGB;
		stBmpInfoHeader.biClrUsed = 0;
		stBmpInfoHeader.biSizeImage = nBytesPerLine * hei;
		PVOID pvBits = NULL;
		HBITMAP bmp = ::CreateDIBSection(NULL, (PBITMAPINFO)&stBmpInfoHeader, DIB_RGB_COLORS, &pvBits, NULL, 0);
		return bmp;
	}
	

private:

};

#endif // _ALGO_WIN_COMMONS_HPP_