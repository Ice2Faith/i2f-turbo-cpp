
// 05-DrawLine.h : 05-DrawLine Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy05DrawLineApp:
// �йش����ʵ�֣������ 05-DrawLine.cpp
//

class CMy05DrawLineApp : public CWinAppEx
{
public:
	CMy05DrawLineApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy05DrawLineApp theApp;
