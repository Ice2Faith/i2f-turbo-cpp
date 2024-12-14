#pragma once
#include "afxeditbrowsectrl.h"


// ConfigureValueDlg 对话框

class ConfigureValueDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ConfigureValueDlg)

public:
	ConfigureValueDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ConfigureValueDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	bool m_applyed;
	double m_aAngle;
	double m_bAngle;
	double m_R;
	double m_d;
	double m_Near;
	double m_Far;
	BOOL m_b_move;
	double m_move_x;
	double m_move_y;
	double m_move_z;
	BOOL m_b_scale;
	double m_scale_x;
	double m_scale_y;
	double m_scale_z;
	BOOL m_b_spin;
	double m_spin_x;
	double m_spin_y;
	double m_spin_z;
	BOOL m_b_reflact_x;
	BOOL m_b_reflact;
	BOOL m_b_reflact_y;
	BOOL m_b_reflact_z;
	BOOL m_b_flat_reflact;
	BOOL m_b_flat_reflact_xoy;
	BOOL m_b_flat_reflact_yoz;
	BOOL m_b_flat_reflact_xoz;
	BOOL m_b_miscut;
	double m_miscut_xgz;
	double m_miscut_xdy;
	double m_miscut_yhz;
	double m_miscut_ybx;
	double m_miscut_zfy;
	double m_miscut_zcx;
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnBnClickedButtonClose();
	virtual BOOL OnInitDialog();
	BOOL m_b_loadFile;
	CString m_filePath;
	CMFCEditBrowseCtrl m_fileBrowser;
};
