
// ��ʷ���а�.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C��ʷ���а�App: 
// �йش����ʵ�֣������ ��ʷ���а�.cpp
//

class C��ʷ���а�App : public CWinApp
{
public:
	C��ʷ���а�App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C��ʷ���а�App theApp;