
// 01-Win��Ϣʾ��Dlg.h : ͷ�ļ�
//

#pragma once


// CMy01Win��Ϣʾ��Dlg �Ի���
class CMy01Win��Ϣʾ��Dlg : public CDialogEx
{
// ����
public:
	CMy01Win��Ϣʾ��Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY01WIN_DIALOG };

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
	afx_msg void OnBnClickedButtonCloseNotepad();
	afx_msg void OnBnClickedButtonOpenNotepad();
	afx_msg void OnBnClickedButtonSetNotepadTitle();
	afx_msg void OnBnClickedButtonGetNotepadTitle();
	CString m_title;
};
