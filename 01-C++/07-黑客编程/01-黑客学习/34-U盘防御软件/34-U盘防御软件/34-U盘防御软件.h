
// 34-U�̷������.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy34U�̷������App: 
// �йش����ʵ�֣������ 34-U�̷������.cpp
//

class CMy34U�̷������App : public CWinApp
{
public:
	CMy34U�̷������App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy34U�̷������App theApp;