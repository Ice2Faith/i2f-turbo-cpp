#include "stdafx.h"
#include "MFCBatchDraw.h"
void MFCBatchDraw::CenterOrg()
{
	bdc.SetMapMode(MM_ANISOTROPIC);
	bdc.SetViewportOrg(mWid / 2, mHei / 2);
	bdc.SetViewportExt(mWid, mHei);
	bdc.SetWindowOrg(0, 0);
	bdc.SetWindowExt(mWid, -mHei);
}
void MFCBatchDraw::ResetOrg()
{
	bdc.SetMapMode(MM_ANISOTROPIC);
	bdc.SetViewportOrg(0, 0);
	bdc.SetViewportExt(mWid, mHei);
	bdc.SetWindowOrg(0, 0);
	bdc.SetWindowExt(mWid,mHei);
}
MFCBatchDraw::MFCBatchDraw(CDC * pDC)
{
	hdc = pDC;
	InitDrawEnv();
}
MFCBatchDraw::MFCBatchDraw(CWnd * cwnd)
{
	hdc = cwnd->GetDC();
	InitDrawEnv();
}
int MFCBatchDraw::getDcWidth()
{
	return mWid;
}
int MFCBatchDraw::getDcHeight()
{
	return mHei;
}
void MFCBatchDraw::clearDc(COLORREF bkcolor)
{
	CBrush bkb(bkcolor);
	CBrush * obk = bdc.SelectObject(&bkb);
	CPen pen(0, 0, (COLORREF)0xeeeeee);
	CPen* oldpen = bdc.SelectObject(&pen);
	bdc.Rectangle(0, 0, mWid, mHei);
	bdc.SelectObject(obk);
	bdc.SelectObject(oldpen);
}
void MFCBatchDraw::InitDrawEnv()
{
	mdc.CreateCompatibleDC(hdc);
	bdc.CreateCompatibleDC(hdc);
	CRect rect;
	CWnd * cwnd = hdc->GetWindow();
	cwnd->GetWindowRect(rect);
	mWid = rect.Width();
	mHei = rect.Height();
	bdimg.CreateCompatibleBitmap(hdc, mWid, mHei);
	mdimg.CreateCompatibleBitmap(hdc, mWid, mHei);
	bdc.SelectObject(&bdimg);
}

MFCBatchDraw::~MFCBatchDraw()
{
	mdc.DeleteDC();
	bdc.DeleteDC();
	bdimg.DeleteObject();
	mdimg.DeleteObject();
}
CDC * MFCBatchDraw::GetCDC()
{
	return &bdc;
}
CDC * MFCBatchDraw::GetMDC()
{
	return &mdc;
}
CDC * MFCBatchDraw::BeginBatchDraw()
{
	bdc.SelectObject(&bdimg);
	mdc.SelectObject(&mdimg);
	return &bdc;
}
void MFCBatchDraw::SubmitBatchDraw()
{
	mdc.BitBlt(0, 0, mWid, mHei, &bdc, 0, 0, SRCCOPY);
	bdc.SelectObject(&bdimg);
}
void MFCBatchDraw::FlushBatchDraw()
{
	hdc->BitBlt(0, 0, mWid, mHei, &mdc, 0, 0, SRCCOPY);
}
void MFCBatchDraw::EndBatchDraw()
{
	mdc.BitBlt(0, 0, mWid, mHei, &bdc, 0, 0, SRCCOPY);
	bdc.SelectObject(&bdimg);
	hdc->BitBlt(0, 0, mWid, mHei, &mdc, 0, 0, SRCCOPY);
}
