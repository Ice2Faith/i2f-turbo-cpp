
// ͼƬ��д��Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxeditbrowsectrl.h"
#include "afxwin.h"
#include"ImageHideData.hpp"



// CͼƬ��д��Dlg �Ի���
class CͼƬ��д��Dlg : public CDialogEx
{
public:
	ImageHideData m_hide;
// ����
public:
	CͼƬ��д��Dlg(CWnd* pParent = NULL);	// ��׼���캯��

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
	afx_msg void OnBnClickedCancel();
	CMFCEditBrowseCtrl m_edtViewPicture;
	CEdit m_edtImgSize;
	CEdit m_edtImgMaxByte;
	CEdit m_edtHideData;
	CEdit m_edtTipResult;
	afx_msg void OnBnClickedButtonReadHideData();
	afx_msg void OnBnClickedButtonWriteHideData();
	CString m_strPicturePath;
	CString m_strPictureSize;
	CString m_strMaxHideByteSize;
	CString m_strHideDatas;
	CString m_strTipsResult;
	CMFCEditBrowseCtrl m_edtSavePicture;
	CString m_strSavePath;
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonDataSize();
};
