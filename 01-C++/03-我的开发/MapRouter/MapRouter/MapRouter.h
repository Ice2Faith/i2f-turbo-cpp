
// MapRouter.h : MapRouter Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMapRouterApp:
// �йش����ʵ�֣������ MapRouter.cpp
//

class CMapRouterApp : public CWinApp
{
public:
	CMapRouterApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMapRouterApp theApp;
