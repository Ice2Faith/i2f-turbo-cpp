
// 01-Win��Ϣʾ��.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy01Win��Ϣʾ��App: 
// �йش����ʵ�֣������ 01-Win��Ϣʾ��.cpp
//

class CMy01Win��Ϣʾ��App : public CWinApp
{
public:
	CMy01Win��Ϣʾ��App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy01Win��Ϣʾ��App theApp;