
// 19-���̹�����.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy19���̹�����App: 
// �йش����ʵ�֣������ 19-���̹�����.cpp
//

class CMy19���̹�����App : public CWinApp
{
public:
	CMy19���̹�����App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy19���̹�����App theApp;