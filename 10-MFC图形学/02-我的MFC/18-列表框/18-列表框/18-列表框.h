
// 18-�б��.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy18�б��App: 
// �йش����ʵ�֣������ 18-�б��.cpp
//

class CMy18�б��App : public CWinApp
{
public:
	CMy18�б��App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy18�б��App theApp;