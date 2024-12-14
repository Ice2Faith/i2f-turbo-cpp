
// U�̷�������Dlg.h : ͷ�ļ�
//

#pragma once


// CU�̷�������Dlg �Ի���
class CU�̷�������Dlg : public CDialogEx
{
// ����
public:
	CU�̷�������Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_U_DIALOG };

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
	afx_msg void OnBnClickedCancel();

	//afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD dwData);//�ֶ�����豸�仯��Ӧ��������Ϣӳ��
	afx_msg LRESULT OnDeviceChange(WPARAM nEventType, LPARAM dwData);

	afx_msg void OnBnClickedButtonSafeOpen();
	afx_msg void OnBnClickedButtonImmuneAutorun();
	afx_msg void OnBnClickedExitPro();
	afx_msg void OnBnClickedHideToBack();

	char GetDriverDisk(DWORD dwData);
	void ShowWindowInDeskRightDown(bool fullDisplay=true);
	void DeleteAutoRunOpenFile(CString autorunDirPath);
	CString m_SafeOpenPath;
	char m_curDiskFlag;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonPlugoutUdisk();
	afx_msg void OnBnClickedButtonChoicePlugDevice();
};
