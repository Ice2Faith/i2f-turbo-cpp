
// 15-�Ի����ÿؼ�Dlg.h : ͷ�ļ�
//

#pragma once
#include "MyButton.h"


// CMy15�Ի����ÿؼ�Dlg �Ի���
class CMy15�Ի����ÿؼ�Dlg : public CDialogEx
{
// ����
public:
	CMy15�Ի����ÿؼ�Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY15_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
private:
	MyButton m_button;
	CString m_str;
public:
	afx_msg void OnBnClickedButton3();
private:
	MyButton m_Clickme;
};
