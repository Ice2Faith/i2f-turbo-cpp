
// 35-�˿�ɨ�輼��.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy35�˿�ɨ�輼��App: 
// �йش����ʵ�֣������ 35-�˿�ɨ�輼��.cpp
//

class CMy35�˿�ɨ�輼��App : public CWinApp
{
public:
	CMy35�˿�ɨ�輼��App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy35�˿�ɨ�輼��App theApp;