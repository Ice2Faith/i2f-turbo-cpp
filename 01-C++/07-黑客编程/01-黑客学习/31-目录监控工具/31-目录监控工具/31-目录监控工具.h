
// 31-Ŀ¼��ع���.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy31Ŀ¼��ع���App: 
// �йش����ʵ�֣������ 31-Ŀ¼��ع���.cpp
//

class CMy31Ŀ¼��ع���App : public CWinApp
{
public:
	CMy31Ŀ¼��ع���App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy31Ŀ¼��ع���App theApp;