
// Win10��͸��.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWin10��͸��App: 
// �йش����ʵ�֣������ Win10��͸��.cpp
//

class CWin10��͸��App : public CWinApp
{
public:
	CWin10��͸��App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWin10��͸��App theApp;