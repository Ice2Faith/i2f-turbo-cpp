#pragma once
/*
����Win32Ӧ�ó�������ѡ���ڹ������ʹ��MFC��������벻ͨ��
*/
#include<afxwin.h>
///////////////////////////////////////////
//Ӧ�ó����࣬CWinApp������������
class myApp:public CWinApp
{
public:
	virtual BOOL InitInstance();

private:

};
///////////////////////////////////////////
//����࣬CFrameWnd������������
class myFrame:public CFrameWnd
{
public:
	myFrame();

	afx_msg void OnLButtonDown(UINT, CPoint);
	afx_msg void OnPaint();
	//������Ϣӳ���
	DECLARE_MESSAGE_MAP()
private:

};
//������Ϣ��
BEGIN_MESSAGE_MAP(myFrame, CFrameWnd)
	ON_WM_LBUTTONDOWN()//�Ͷ�Ӧ�ĺ���ԭ�Ͱ󶨣�afx_msg void OnLButtonDown(UINT, CPoint);
	ON_WM_PAINT()
END_MESSAGE_MAP()