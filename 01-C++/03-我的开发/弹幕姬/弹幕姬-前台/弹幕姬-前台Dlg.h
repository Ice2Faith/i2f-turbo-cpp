
// ��Ļ��-ǰ̨Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// C��Ļ��ǰ̨Dlg �Ի���
class C��Ļ��ǰ̨Dlg : public CDialogEx
{
// ����
public:
	C��Ļ��ǰ̨Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

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
	CString m_strFoText;
	afx_msg void OnBnClickedButtonShootFt();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CButton m_btnShoot;
	CEdit m_edt_inMsg;
	afx_msg void OnBnClickedButtonExitbgservice();
	CButton m_btnOpenMsg;
	CButton m_btnCloseMsg;
	CButton m_btnClearMsg;
	CButton m_btnShowMsgWnd;
	CButton m_btnHideMsgWnd;
	BOOL m_bRandomSize;
	BOOL m_bRandomColor;
	BOOL m_bRandomSpeed;
	CSliderCtrl m_scSize;
	CSliderCtrl m_scCRed;
	CSliderCtrl m_scCGreen;
	CSliderCtrl m_scCBlue;
	CSliderCtrl m_scSpeed;
	afx_msg void OnBnClickedButtonOpenmsg();
	afx_msg void OnBnClickedButtonClosemsg();
	afx_msg void OnBnClickedButtonClearmsg();
	afx_msg void OnBnClickedButtonShowmsgwnd();
	afx_msg void OnBnClickedButtonHidemsgwnd();
	afx_msg void OnBnClickedCheckRandomsize();
	afx_msg void OnBnClickedCheckRandomcolor();
	afx_msg void OnBnClickedCheckRandomspeed();
};
