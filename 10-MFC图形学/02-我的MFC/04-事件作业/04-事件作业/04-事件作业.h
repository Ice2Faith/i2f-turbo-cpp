
// 04-�¼���ҵ.h : 04-�¼���ҵ Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy04�¼���ҵApp:
// �йش����ʵ�֣������ 04-�¼���ҵ.cpp
//

class CMy04�¼���ҵApp : public CWinAppEx
{
public:
	CMy04�¼���ҵApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy04�¼���ҵApp theApp;
