
// 03-�������ģ��Dlg.h : ͷ�ļ�
//

#pragma once


// CMy03�������ģ��Dlg �Ի���
class CMy03�������ģ��Dlg : public CDialogEx
{
// ����
public:
	CMy03�������ģ��Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY03_DIALOG };

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
	afx_msg void OnBnClickedButtonPostA();
	afx_msg void OnBnClickedButtonPostTaskPanel();
	afx_msg void OnBnClickedButtonFuncShift();
	afx_msg void OnBnClickedButtonFuncWin();
};
