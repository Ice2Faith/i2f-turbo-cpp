
// 04-���������ǻ�.h : 04-���������ǻ� Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy04���������ǻ�App:
// �йش����ʵ�֣������ 04-���������ǻ�.cpp
//

class CMy04���������ǻ�App : public CWinApp
{
public:
	CMy04���������ǻ�App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy04���������ǻ�App theApp;
