
// 12-��̬ͼ��.h : 12-��̬ͼ�� Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy12��̬ͼ��App:
// �йش����ʵ�֣������ 12-��̬ͼ��.cpp
//

class CMy12��̬ͼ��App : public CWinApp
{
public:
	CMy12��̬ͼ��App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy12��̬ͼ��App theApp;
