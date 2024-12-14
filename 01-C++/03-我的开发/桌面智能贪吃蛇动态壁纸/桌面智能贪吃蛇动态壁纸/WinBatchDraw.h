#pragma once
/*
һ���򵥷�װ��WIN API GDI �������ͼ��
ͨ���Զ������ڴ�ͻ���DC�򻯲���
*/
class WinBatchDraw
{
public:
	WinBatchDraw(HWND hwnd);
	WinBatchDraw(HDC hdc,int wid,int hei);
	~WinBatchDraw();
	HDC BeginBatchDraw();	//��ʼ������ͼ
	void SubmitBatchDraw();	//��BDC�е������ύ��MDC�У�������BDC�е�����
	void FlushBatchDraw();	//��MDC�е�����ˢ�µ�HDC��
	void EndBatchDraw();	//����������ͼ������ͼ�ν�����ʾ
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

