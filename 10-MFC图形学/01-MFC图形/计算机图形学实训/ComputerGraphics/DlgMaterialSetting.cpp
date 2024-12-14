// DlgMaterialSetting.cpp : implementation file
//

#include "stdafx.h"
#include "ComputerGraphics.h"
#include "DlgMaterialSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgMaterialSetting dialog


DlgMaterialSetting::DlgMaterialSetting(CWnd* pParent /*=NULL*/)
	: CDialog(DlgMaterialSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgMaterialSetting)
	m_gold = FALSE;
	m_greenstone = TRUE;
	m_redstone = FALSE;
	m_siver = FALSE;
	//}}AFX_DATA_INIT
	lg_mate=GD3Light::GetGreenGemstoneMaterial();
}


void DlgMaterialSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgMaterialSetting)
	DDX_Check(pDX, IDC_CHECK_GOLD, m_gold);
	DDX_Check(pDX, IDC_CHECK_GREENSTONE, m_greenstone);
	DDX_Check(pDX, IDC_CHECK_REDSTONE, m_redstone);
	DDX_Check(pDX, IDC_CHECK_SIVER, m_siver);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgMaterialSetting, CDialog)
	//{{AFX_MSG_MAP(DlgMaterialSetting)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgMaterialSetting message handlers

void DlgMaterialSetting::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void DlgMaterialSetting::OnOK() 
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

D3Material DlgMaterialSetting::GetMaterial()
{
	return lg_mate;
}
