
// 06-λͼ����.h : 06-λͼ���� Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy06λͼ����App:
// �йش����ʵ�֣������ 06-λͼ����.cpp
//

class CMy06λͼ����App : public CWinApp
{
public:
	CMy06λͼ����App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy06λͼ����App theApp;
