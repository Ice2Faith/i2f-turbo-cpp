#include"mymfc.h"
//����ֻ��һ��ȫ�ֶ���
myApp mApp;

////////////////////////////////////////////
//myApp ʵ��
//�������ڵ�ַ
BOOL myApp::InitInstance()
{
	//���������
	myFrame * frame = new myFrame();
	//��ʾ����
	frame->ShowWindow(SW_SHOWNORMAL);
	//���´���
	frame->UpdateWindow();
	//��������ָ��
	m_pMainWnd = frame;
	return TRUE;
}

///////////////////////////////////////////
//myFrame ʵ��
myFrame::myFrame()
{
	//CWnd��ĳ�Ա���� CWnd::Create

	//CFrameWnd�̳���CWnd
	Create(NULL,L"MFC");

}
void myFrame::OnLButtonDown(UINT uint, CPoint cpint)
{
	MessageBox(L"LBUTTONDOWN",L"Tips",MB_OK);
}
void myFrame::OnPaint()
{
	CPaintDC cdc(this);
	cdc.TextOutW(0, 0, L"Hello,Win32App");
}