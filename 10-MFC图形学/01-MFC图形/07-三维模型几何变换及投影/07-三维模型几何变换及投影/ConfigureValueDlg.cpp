// ConfigureValueDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "07-三维模型几何变换及投影.h"
#include "ConfigureValueDlg.h"
#include "afxdialogex.h"


// ConfigureValueDlg 对话框

IMPLEMENT_DYNAMIC(ConfigureValueDlg, CDialogEx)

ConfigureValueDlg::ConfigureValueDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ConfigureValueDlg::IDD, pParent)
	, m_b_loadFile(FALSE)
	, m_filePath(_T(""))
{
	m_applyed = false;
	m_aAngle = 0;
	m_bAngle = 0;
	m_R = 500;
	m_d = 200;
	m_Near = 20;
	m_Far = 800;
	m_b_move = FALSE;
	m_move_x = 0;
	m_move_y = 0;
	m_move_z = 0;
	m_b_scale = FALSE;
	m_scale_x = 1;
	m_scale_y = 1;
	m_scale_z = 1;
	m_b_spin = FALSE;
	m_spin_x = 0;
	m_spin_y = 0;
	m_spin_z = 0;
	m_b_reflact_x = FALSE;
	m_b_reflact = FALSE;
	m_b_reflact_y = FALSE;
	m_b_reflact_z = FALSE;
	m_b_flat_reflact = FALSE;
	m_b_flat_reflact_xoy = FALSE;
	m_b_flat_reflact_yoz = FALSE;
	m_b_flat_reflact_xoz = FALSE;
	m_b_miscut = FALSE;
	m_miscut_xgz = 0;
	m_miscut_xdy = 0;
	m_miscut_yhz = 0;
	m_miscut_ybx = 0;
	m_miscut_zfy = 0;
	m_miscut_zcx = 0;
}

ConfigureValueDlg::~ConfigureValueDlg()
{
}

void ConfigureValueDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_aAngle);
	DDX_Text(pDX, IDC_EDIT2, m_bAngle);
	DDX_Text(pDX, IDC_EDIT3, m_R);
	DDX_Text(pDX, IDC_EDIT4, m_d);
	DDX_Text(pDX, IDC_EDIT5, m_Near);
	DDX_Text(pDX, IDC_EDIT6, m_Far);
	DDX_Check(pDX, IDC_CHECK1, m_b_move);
	DDX_Text(pDX, IDC_EDIT10, m_move_x);
	DDX_Text(pDX, IDC_EDIT11, m_move_y);
	DDX_Text(pDX, IDC_EDIT12, m_move_z);
	DDX_Check(pDX, IDC_CHECK7, m_b_scale);
	DDX_Text(pDX, IDC_EDIT13, m_scale_x);
	DDX_Text(pDX, IDC_EDIT14, m_scale_y);
	DDX_Text(pDX, IDC_EDIT15, m_scale_z);
	DDX_Check(pDX, IDC_CHECK3, m_b_spin);
	DDX_Text(pDX, IDC_EDIT7, m_spin_x);
	DDX_Text(pDX, IDC_EDIT8, m_spin_y);
	DDX_Text(pDX, IDC_EDIT9, m_spin_z);
	DDX_Check(pDX, IDC_CHECK8, m_b_reflact_x);
	DDX_Check(pDX, IDC_CHECK9, m_b_reflact);
	DDX_Check(pDX, IDC_CHECK10, m_b_reflact_y);
	DDX_Check(pDX, IDC_CHECK11, m_b_reflact_z);
	DDX_Check(pDX, IDC_CHECK12, m_b_flat_reflact);
	DDX_Check(pDX, IDC_CHECK13, m_b_flat_reflact_xoy);
	DDX_Check(pDX, IDC_CHECK14, m_b_flat_reflact_yoz);
	DDX_Check(pDX, IDC_CHECK15, m_b_flat_reflact_xoz);
	DDX_Check(pDX, IDC_CHECK6, m_b_miscut);
	DDX_Text(pDX, IDC_EDIT16, m_miscut_xgz);
	DDX_Text(pDX, IDC_EDIT19, m_miscut_xdy);
	DDX_Text(pDX, IDC_EDIT17, m_miscut_yhz);
	DDX_Text(pDX, IDC_EDIT20, m_miscut_ybx);
	DDX_Text(pDX, IDC_EDIT18, m_miscut_zfy);
	DDX_Text(pDX, IDC_EDIT21, m_miscut_zcx);
	DDX_Check(pDX, IDC_CHECK17, m_b_loadFile);
	DDX_Text(pDX, IDC_MFCEDITBROWSE1, m_filePath);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_fileBrowser);
}


BEGIN_MESSAGE_MAP(ConfigureValueDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ConfigureValueDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ConfigureValueDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &ConfigureValueDlg::OnBnClickedButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &ConfigureValueDlg::OnBnClickedButtonClose)
END_MESSAGE_MAP()


// ConfigureValueDlg 消息处理程序


void ConfigureValueDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void ConfigureValueDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnCancel();
}


void ConfigureValueDlg::OnBnClickedButtonApply()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_applyed = true;
	CDialogEx::OnOK();
}


void ConfigureValueDlg::OnBnClickedButtonClose()
{
	// TODO:  在此添加控件通知处理程序代码
	m_applyed = false;
	CDialogEx::OnCancel();
}


BOOL ConfigureValueDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_fileBrowser.EnableFileBrowseButton();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
