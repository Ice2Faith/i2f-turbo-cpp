
// 05-Bezier���߻���.h : 05-Bezier���߻��� Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy05Bezier���߻���App:
// �йش����ʵ�֣������ 05-Bezier���߻���.cpp
//

class CMy05Bezier���߻���App : public CWinApp
{
public:
	CMy05Bezier���߻���App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy05Bezier���߻���App theApp;
