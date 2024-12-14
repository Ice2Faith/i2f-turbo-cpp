
// 图片隐写术Dlg.h : 头文件
//

#pragma once
#include "afxeditbrowsectrl.h"
#include "afxwin.h"
#include"ImageHideData.hpp"



// C图片隐写术Dlg 对话框
class C图片隐写术Dlg : public CDialogEx
{
public:
	ImageHideData m_hide;
// 构造
public:
	C图片隐写术Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
