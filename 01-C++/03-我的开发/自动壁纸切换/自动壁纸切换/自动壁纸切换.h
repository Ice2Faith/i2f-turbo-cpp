
// �Զ���ֽ�л�.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C�Զ���ֽ�л�App: 
// �йش����ʵ�֣������ �Զ���ֽ�л�.cpp
//

class C�Զ���ֽ�л�App : public CWinApp
{
public:
	C�Զ���ֽ�л�App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C�Զ���ֽ�л�App theApp;