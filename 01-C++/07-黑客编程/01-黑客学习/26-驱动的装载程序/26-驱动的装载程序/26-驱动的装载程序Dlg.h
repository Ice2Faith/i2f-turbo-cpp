
// 26-������װ�س���Dlg.h : ͷ�ļ�
//

#pragma once


// CMy26������װ�س���Dlg �Ի���
class CMy26������װ�س���Dlg : public CDialogEx
{
// ����
public:
	CMy26������װ�س���Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY26_DIALOG };

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
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonInstall();
	afx_msg void OnBnClickedButtonUninstall();
};
