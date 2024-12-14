
// 相同相似文件识别Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"




typedef struct __equals_files_struct
{
	TCHAR fzName[MAX_PATH];
	LARGE_INTEGER fzSize;
}EqualsFilesInfo, *PEqualsFilesInfo;

typedef struct __equals_files_data_struct
{
	TCHAR fzName[MAX_PATH];
	FILE * fp;
	long checkSum;
}EqualsFilesDataInfo, *PEqualsFilesDataInfo;

// C相同相似文件识别Dlg 对话框
class C相同相似文件识别Dlg : public CDialogEx
{
// 构造
public:
	C相同相似文件识别Dlg(CWnd* pParent = NULL);	// 标准构造函数

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
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonRemove();
	CButton m_btn_begin;
	CButton m_btn_clear;
	CButton m_btn_remove;
	CButton m_ckb_fileEquals;
	CButton m_ckb_fileSize;
	CListBox m_lsb_similarFiles;
	CListBox m_lsb_srcFiles;
	afx_msg void OnBnClickedButtonBegin();
	void checkFileSize();
	void checkFilesEquals();
	CString m_str_moveToDir;
	afx_msg void OnBnClickedButtonMove2();
	afx_msg void OnBnClickedButtonCopy2();
	CString m_str_all_count;
	CString m_str_group_count;
	CString m_str_src_count;
	CButton m_ckb_dontOk;
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	CString m_str_useTime;
	CButton m_ckb_needUniqueDropFile;
	afx_msg void OnBnClickedButtonDeleteRepeat();
	CButton m_ckb_OnlyRepeat;
	CButton m_ckb_similarImage;
	CButton m_ckb_verifyImgSize;
	CSliderCtrl m_sld_similarRate;
	afx_msg void OnBnClickedCheckOnlyFileSize();
	afx_msg void OnBnClickedCheckFileEqauls();
	afx_msg void OnBnClickedCheckSimiliarImage();
	afx_msg void OnBnClickedCheckVerifyImgsize();
	void InitControls();
	void checkImageSimilar();
	int m_int_pixelStep;
	CButton m_ckb_useImgGray;
	CButton m_btn_deleteRepeat;
	CSliderCtrl m_sld_pixelAllowRate;
};
