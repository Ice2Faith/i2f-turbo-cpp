
// 02-TM�ļ�������ͼ.h : 02-TM�ļ�������ͼ Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy02TM�ļ�������ͼApp:
// �йش����ʵ�֣������ 02-TM�ļ�������ͼ.cpp
//

class CMy02TM�ļ�������ͼApp : public CWinApp
{
public:
	CMy02TM�ļ�������ͼApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy02TM�ļ�������ͼApp theApp;
