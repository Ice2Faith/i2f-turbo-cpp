
// 26-������װ�س���.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy26������װ�س���App: 
// �йش����ʵ�֣������ 26-������װ�س���.cpp
//

class CMy26������װ�س���App : public CWinApp
{
public:
	CMy26������װ�س���App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy26������װ�س���App theApp;