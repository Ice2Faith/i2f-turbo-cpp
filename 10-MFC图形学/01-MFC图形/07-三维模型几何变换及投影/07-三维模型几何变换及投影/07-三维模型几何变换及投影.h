
// 07-��άģ�ͼ��α任��ͶӰ.h : 07-��άģ�ͼ��α任��ͶӰ Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMy07��άģ�ͼ��α任��ͶӰApp:
// �йش����ʵ�֣������ 07-��άģ�ͼ��α任��ͶӰ.cpp
//

class CMy07��άģ�ͼ��α任��ͶӰApp : public CWinApp
{
public:
	CMy07��άģ�ͼ��α任��ͶӰApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy07��άģ�ͼ��α任��ͶӰApp theApp;
