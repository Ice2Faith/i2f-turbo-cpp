#pragma once
/*
һ���򵥷�װʵ�ֵ�MFC�������ͼ
ֻ��Ҫ����CDC���ߴ���CWnd����
��������ϵ�������ͼ�и�������ϵ��
���ڽ�����ͼ�����ύ��ͼ֮ǰ��������ϵ
������Ƶ�ͼ�ν��������ʾ��ȫ��
ʹ��ʾ����

***view.cpp��
MFCBatchDraw draw(this);//����CClientDC ��OnDraw�����п��ԣ�MFCBatchDraw draw(pDC);
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
	CDC * GetCDC();	//��ȡ��bdc
	CDC * GetMDC();	//��ȡ��MDC
	CDC * BeginBatchDraw();	//��ʼ������ͼ
	void SubmitBatchDraw();	//��BDC�е����ݵ�У��MDC�У������BDC
	void FlushBatchDraw();	//��MDC�е�����ˢ�µ�HDC����ʾ
	void EndBatchDraw();	//������ͼ������ʾ��������
	void ResetOrg();		//��������ϵ
	void CenterOrg();		//������ѧ��������
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

