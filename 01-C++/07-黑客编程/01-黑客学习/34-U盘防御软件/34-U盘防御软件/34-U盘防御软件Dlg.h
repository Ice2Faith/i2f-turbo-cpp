
// 34-U�̷������Dlg.h : ͷ�ļ�
//

#pragma once
#define TIMER_FRIST_LOAD 0x101

// CMy34U�̷������Dlg �Ի���
class CMy34U�̷������Dlg : public CDialogEx
{
// ����
public:
	CMy34U�̷������Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY34U_DIALOG };

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
	//afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD dwData);//�ֶ�����豸�仯��Ӧ��������Ϣӳ��
	afx_msg LRESULT OnDeviceChange(WPARAM nEventType, LPARAM dwData);
	char GetDriverDisk(DWORD dwData);
	afx_msg void OnBnClickedButtonSafeOpen();
	CString m_SafeOpenPath;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void ShowWindowInDeskRightDown();
	afx_msg void OnBnClickedButtonTrulyClose();
	afx_msg void OnBnClickedButtonHidewnd();
	void DeleteAutoRunOpenFile(CString autorunDirPath);
};
