
// 06-ͼ�εĹ�դɨ����ʾ.h : 06-ͼ�εĹ�դɨ����ʾ Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy06ͼ�εĹ�դɨ����ʾApp:
// �йش����ʵ�֣������ 06-ͼ�εĹ�դɨ����ʾ.cpp
//

class CMy06ͼ�εĹ�դɨ����ʾApp : public CWinApp
{
public:
	CMy06ͼ�εĹ�դɨ����ʾApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy06ͼ�εĹ�դɨ����ʾApp theApp;
