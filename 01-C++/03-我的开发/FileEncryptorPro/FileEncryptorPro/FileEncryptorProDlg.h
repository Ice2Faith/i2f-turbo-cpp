
// FileEncryptorProDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxeditbrowsectrl.h"
#include "afxcmn.h"
#include"EveryFileLocker.hpp"

#define UM_THREAD_PROCESS_INFO (WM_USER+0x25)//�Զ�����Ϣ�����������߳���Ϣ�ͽ��潻����
#define U_MAX_PATH_SIZE 2048//�Զ�������·������
typedef struct _EncrypteInfomation//�ӽ�����Ϣ��
{
	EveryFileLocker * locker;//���ܶ���
	HWND hWnd;//���ھ���������Զ�����Ϣ�Ĵ��ھ��
	CListBox * pWorkList;//��ȡ�б���Ŀ���б��ַ
	char szSavePath[U_MAX_PATH_SIZE];//��ǰ���ļ�����Ŀ¼
	char szPassword[MAXBYTE];//����
	bool bisEncrypte;//�Ƿ��Ǽ��ܣ���֮���ǽ���
	bool bisNoSuffix;//�Ƿ�ʹ��Ĭ�Ϻ�׺
	bool bisDelSource;//�Ƿ�ɾ��Դ�ļ�
}EncrypteInfomation, *PEncrypteInfomation;
typedef struct _ProcessInfo//��ǰ���������ݱ�
{
	char szSrcFileName[U_MAX_PATH_SIZE];//��ǰ������ļ�
	char szDstFileName[U_MAX_PATH_SIZE];//��ǰ������ļ�
	int nProcessCount;//���д�������
	int nSuccessCount;//�ɹ�����
	int nFailureCount;//ʧ������
	bool bisSuccess;//��ǰ�Ĵ����Ƿ�ɹ�
}ProcessInfo, *PProcessInfo;
// CFileEncryptorProDlg �Ի���
class CFileEncryptorProDlg : public CDialogEx
{
public:
	EveryFileLocker m_locker;
// ����
public:
	CFileEncryptorProDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FILEENCRYPTORPRO_DIALOG };

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
	PEncrypteInfomation m_pEncrypteInfo;//���ܽ�����Ϣ��
	bool m_isRunning;//�Ƿ��ڽ��мӽ��ܲ���
	HANDLE m_hThread;//�����߳̾��
	CString m_str_process_info;//��ʾ��Ϣ
	CString m_str_Password;//����
	CString m_str_SavePath;//����·��
	CString m_str_OpenFile;//�򿪵��ļ�
	CListBox m_lb_WorkList;//�б��
	CButton m_btn_StartWork;//��ʼ��ť
	CButton m_btn_ClearAllItem;//��հ�ť
	CButton m_btn_RemoveSelectItem;//�Ƴ���ť
	CButton m_btn_OpenFile;//�򿪰�ť
	CButton m_ckbtn_AddDefSuffix;//���Ĭ�Ϻ�׺ѡ��
	CButton m_ckbtn_DeleteSourceFile;//ɾ��Դ�ļ�ѡ��
	CMFCEditBrowseCtrl m_edit_OpenFile;//����ļ���
	CMFCEditBrowseCtrl m_edit_SavePath;//���Ŀ¼��
	CEdit m_edit_Password;//�����
	CProgressCtrl m_pro_Process;//��������
	void InitControls();//��ʼ���ռ亯��
	void RemoveSelectListItem();//�Ƴ�ѡ�к���
	void AddOpenFileToList();//�����Ŀ���б����
	void enableControls();//���ÿؼ�����
	void disableControls();//���ÿؼ�����
	void StartWorkProcess();//��ʼ������
	void AddOnePathToList(TCHAR * path);//���һ��·�����б����
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonOpenFile();
	afx_msg void OnBnClickedButtonOpenSavePath();
	afx_msg void OnBnClickedButtonRemoveSelectItem();
	afx_msg void OnBnClickedButtonClearAllItem();
	afx_msg void OnBnClickedButtonStartWork();
	afx_msg void OnDropFiles(HDROP hDropInfo);//�ļ�������Ӧ����
	afx_msg LRESULT EncryptMsgProc(WPARAM wParam, LPARAM lParam);//�Զ��崦���߳���Ϣ������
	virtual BOOL PreTranslateMessage(MSG* pMsg);//Ԥ������Ϣ��д
};
