
// 03-������εĻ���.h : 03-������εĻ��� Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy03������εĻ���App:
// �йش����ʵ�֣������ 03-������εĻ���.cpp
//

class CMy03������εĻ���App : public CWinApp
{
public:
	CMy03������εĻ���App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy03������εĻ���App theApp;
