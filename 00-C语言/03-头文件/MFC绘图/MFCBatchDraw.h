#pragma once
/*
一个简单封装实现的MFC三缓冲绘图
只需要告诉CDC或者窗口CWnd即可
关于坐标系，如果绘图有更改坐标系，
请在结束绘图或者提交绘图之前重置坐标系
否则绘制的图形将会出错，显示不全等
使用示例：

***view.cpp中
MFCBatchDraw draw(this);//参照CClientDC 在OnDraw函数中可以：MFCBatchDraw draw(pDC);
CDC * dc=draw.BeginBatchDraw();
....

draw.EndBatchDraw();
*/
class MFCBatchDraw
{
public:
	MFCBatchDraw(CDC * pDC);
	MFCBatchDraw(CWnd * cwnd);
	~MFCBatchDraw();
	CDC * GetCDC();	//获取到bdc
	CDC * GetMDC();	//获取到MDC
	CDC * BeginBatchDraw();	//开始批量绘图
	void SubmitBatchDraw();	//将BDC中的内容调校到MDC中，并清空BDC
	void FlushBatchDraw();	//将MDC中的内容刷新到HDC上显示
	void EndBatchDraw();	//结束绘图，并显示所有内容
	void ResetOrg();		//重置坐标系
	void CenterOrg();		//设置数学中心坐标
	int getDcWidth();
	int getDcHeight();
	void clearDc(COLORREF bkcolor=0xffffff);
private:
	CDC * hdc;
	CDC mdc;
	CDC bdc;
	CBitmap bdimg;
	CBitmap mdimg;
	int mWid;
	int mHei;
	void InitDrawEnv();
};

