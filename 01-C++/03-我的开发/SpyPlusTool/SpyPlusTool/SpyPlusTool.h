
// SpyPlusTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSpyPlusToolApp: 
// �йش����ʵ�֣������ SpyPlusTool.cpp
//

class CSpyPlusToolApp : public CWinApp
{
public:
	CSpyPlusToolApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSpyPlusToolApp theApp;