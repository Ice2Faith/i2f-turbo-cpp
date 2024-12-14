// DlgLightSetting.cpp : implementation file
//

#include "stdafx.h"
#include "ComputerGraphics.h"
#include "DlgLightSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgLightSetting dialog


DlgLightSetting::DlgLightSetting(CWnd* pParent /*=NULL*/)
	: CDialog(DlgLightSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgLightSetting)
	m_gold = TRUE;
	m_greenstone = FALSE;
	m_redstone = FALSE;
	m_siver = FALSE;
	m_c2 = 0.99;
	m_c1 = 0.8;
	m_c0 = 0.5;
	m_x = 1000;
	m_y = 0;
	m_z = 0;
	lg_mate=GD3Light::GetGreenGemstoneMaterial();
	//}}AFX_DATA_INIT
}


void DlgLightSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgLightSetting)
	DDX_Check(pDX, IDC_CHECK_GOLD, m_gold);
	DDX_Check(pDX, IDC_CHECK_GREENSTONE, m_greenstone);
	DDX_Check(pDX, IDC_CHECK_REDSTONE, m_redstone);
	DDX_Check(pDX, IDC_CHECK_SIVIR, m_siver);
	DDX_Text(pDX, IDC_EDIT_CTWO, m_c2);
	DDX_Text(pDX, IDC_EDIT_CONE, m_c1);
	DDX_Text(pDX, IDC_EDIT_CZERO, m_c0);
	DDX_Text(pDX, IDC_EDIT_PX, m_x);
	DDX_Text(pDX, IDC_EDIT_PY, m_y);
	DDX_Text(pDX, IDC_EDIT_PZ, m_z);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgLightSetting, CDialog)
	//{{AFX_MSG_MAP(DlgLightSetting)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgLightSetting message handlers

void DlgLightSetting::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void DlgLightSetting::OnOK() 
{
	// TODO: Add extra validation here
	this->UpdateData(TRUE);
	if(this->m_gold)
	{
		this->lg_mate=GD3Light::GetGoldMaterial();
		this->m_siver=FALSE;
		this->m_greenstone=FALSE;
		this->m_redstone=FALSE;
	}
	else
	if(this->m_siver)
	{
		this->lg_mate=GD3Light::GetSilverMaterial();
		this->m_gold=FALSE;
		this->m_greenstone=FALSE;
		this->m_redstone=FALSE;
	}
	else if(this->m_greenstone)
	{
		this->lg_mate=GD3Light::GetGreenGemstoneMaterial();
		this->m_gold=FALSE;
		this->m_siver=FALSE;
		this->m_redstone=FALSE;
	}
	else if(this->m_redstone)
	{
		this->lg_mate=GD3Light::GetRedGemstoneMaterial();
		this->m_gold=FALSE;
		this->m_siver=FALSE;
		this->m_greenstone=FALSE;
	}
	this->UpdateData(FALSE);
	CDialog::OnOK();
}

D3Light DlgLightSetting::GetLight()
{
	D3Light retl;
	retl.diff_red=lg_mate.diff_red;
	retl.diff_green=lg_mate.diff_green;
	retl.diff_blue=lg_mate.diff_blue;
	retl.spec_red=lg_mate.spec_red;
	retl.spec_green=lg_mate.spec_green;
	retl.spec_blue=lg_mate.spec_blue;
	retl.c0=m_c0;
	retl.c1=m_c1;
	retl.c2=m_c2;
	retl.point.x=m_x;
	retl.point.y=m_y;
	retl.point.z=m_z;
	return retl;
}
