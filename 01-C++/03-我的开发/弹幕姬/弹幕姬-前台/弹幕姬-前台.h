
// ��Ļ��-ǰ̨.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C��Ļ��ǰ̨App: 
// �йش����ʵ�֣������ ��Ļ��-ǰ̨.cpp
//

class C��Ļ��ǰ̨App : public CWinApp
{
public:
	C��Ļ��ǰ̨App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C��Ļ��ǰ̨App theApp;