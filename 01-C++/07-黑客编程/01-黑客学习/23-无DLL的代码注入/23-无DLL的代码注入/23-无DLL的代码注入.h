
// 23-��DLL�Ĵ���ע��.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy23��DLL�Ĵ���ע��App: 
// �йش����ʵ�֣������ 23-��DLL�Ĵ���ע��.cpp
//

class CMy23��DLL�Ĵ���ע��App : public CWinApp
{
public:
	CMy23��DLL�Ĵ���ע��App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy23��DLL�Ĵ���ע��App theApp;