
// 02_StartMFC.h : 02_StartMFC Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy02_StartMFCApp:
// �йش����ʵ�֣������ 02_StartMFC.cpp
//

class CMy02_StartMFCApp : public CWinApp
{
public:
	CMy02_StartMFCApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy02_StartMFCApp theApp;
