
// ��Ȱ׿��.h : ��Ȱ׿�� Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// C��Ȱ׿��App:
// �йش����ʵ�֣������ ��Ȱ׿��.cpp
//

class C��Ȱ׿��App : public CWinApp
{
public:
	C��Ȱ׿��App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern C��Ȱ׿��App theApp;
