
// 08-ͼ����������Ȼ���.h : 08-ͼ����������Ȼ��� Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy08ͼ����������Ȼ���App:
// �йش����ʵ�֣������ 08-ͼ����������Ȼ���.cpp
//

class CMy08ͼ����������Ȼ���App : public CWinApp
{
public:
	CMy08ͼ����������Ȼ���App();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy08ͼ����������Ȼ���App theApp;
