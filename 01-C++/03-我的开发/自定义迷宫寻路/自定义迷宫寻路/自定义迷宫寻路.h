
// �Զ����Թ�Ѱ·.h : �Զ����Թ�Ѱ· Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// C�Զ����Թ�Ѱ·App:
// �йش����ʵ�֣������ �Զ����Թ�Ѱ·.cpp
//

class C�Զ����Թ�Ѱ·App : public CWinAppEx
{
public:
	C�Զ����Թ�Ѱ·App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern C�Զ����Թ�Ѱ·App theApp;
