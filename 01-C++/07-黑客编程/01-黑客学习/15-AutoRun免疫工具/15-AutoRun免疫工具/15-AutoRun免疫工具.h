
// 15-AutoRun���߹���.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy15AutoRun���߹���App: 
// �йش����ʵ�֣������ 15-AutoRun���߹���.cpp
//

class CMy15AutoRun���߹���App : public CWinApp
{
public:
	CMy15AutoRun���߹���App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy15AutoRun���߹���App theApp;