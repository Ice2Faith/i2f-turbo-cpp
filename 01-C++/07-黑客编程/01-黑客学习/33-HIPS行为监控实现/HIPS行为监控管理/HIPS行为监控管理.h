
// HIPS��Ϊ��ع���.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHIPS��Ϊ��ع���App: 
// �йش����ʵ�֣������ HIPS��Ϊ��ع���.cpp
//

class CHIPS��Ϊ��ع���App : public CWinApp
{
public:
	CHIPS��Ϊ��ع���App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHIPS��Ϊ��ع���App theApp;