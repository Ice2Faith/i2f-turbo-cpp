
// 20-�б�ؼ�.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy20�б�ؼ�App: 
// �йش����ʵ�֣������ 20-�б�ؼ�.cpp
//

class CMy20�б�ؼ�App : public CWinApp
{
public:
	CMy20�б�ؼ�App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy20�б�ؼ�App theApp;