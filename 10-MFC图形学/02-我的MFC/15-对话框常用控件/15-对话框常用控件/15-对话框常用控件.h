
// 15-�Ի����ÿؼ�.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy15�Ի����ÿؼ�App: 
// �йش����ʵ�֣������ 15-�Ի����ÿؼ�.cpp
//

class CMy15�Ի����ÿؼ�App : public CWinApp
{
public:
	CMy15�Ի����ÿؼ�App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy15�Ի����ÿؼ�App theApp;