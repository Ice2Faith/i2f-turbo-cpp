
// �ƽ���.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C�ƽ���App: 
// �йش����ʵ�֣������ �ƽ���.cpp
//

class C�ƽ���App : public CWinApp
{
public:
	C�ƽ���App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C�ƽ���App theApp;