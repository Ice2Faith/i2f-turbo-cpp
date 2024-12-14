#pragma once
/*
一个简单封装的WIN API GDI 三缓冲绘图类
通过自动创建内存和缓存DC简化操作
*/
class WinBatchDraw
{
public:
	WinBatchDraw(HWND hwnd);
	WinBatchDraw(HDC hdc,int wid,int hei);
	~WinBatchDraw();
	HDC BeginBatchDraw();	//开始批量绘图
	void SubmitBatchDraw();	//将BDC中的内容提交到MDC中，并重置BDC中的内容
	void FlushBatchDraw();	//将MDC中的内容刷新到HDC中
	void EndBatchDraw();	//结束批量绘图，并将图形进行显示
	HDC GetHDC();
	int GetDCHeight();
	int GetDCWidth();
	void CenterOrg();
	void ResetOrg();
private:
	void InitDrawEnv();
	void BuildBackgroundImg();
	HWND m_hwnd;
	HDC hdc, mdc, bdc;
	HBITMAP mdimg, bdimg;
	int wWid, wHei;
};

