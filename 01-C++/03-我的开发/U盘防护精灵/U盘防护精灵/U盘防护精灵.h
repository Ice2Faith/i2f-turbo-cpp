
// U�̷�������.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CU�̷�������App: 
// �йش����ʵ�֣������ U�̷�������.cpp
//

class CU�̷�������App : public CWinApp
{
public:
	CU�̷�������App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CU�̷�������App theApp;