
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "11-�˵���̬����.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_TEST_A, &CMainFrame::OnUpdateTestA)
	ON_COMMAND(ID_TEST_B, &CMainFrame::OnTestB)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
: m_isUpdate(false)
{
	// TODO:  �ڴ���ӳ�Ա��ʼ������
	m_bAutoMenuEnable = false;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO:  �������Ҫ��ͣ������������ɾ��������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	//��־
	//��ȡ�˵�
	//��ȡ���˵�
	CMenu * menu = GetMenu();
	//��ȡ�ļ��Ӳ˵�
	CMenu * filemenu = menu->GetSubMenu(0);

	//��־�½���������0��MF_BYPOSITION����
	filemenu->CheckMenuItem(0,MF_BYPOSITION|MF_CHECKED);
	filemenu->CheckMenuItem(ID_FILE_OPEN, MF_BYCOMMAND | MF_CHECKED);
	//����Ĭ����Ӵ֣�һ���˵���ֻ��һ��Ĭ��ѡ��˵�����������������
	//ID:False,λ�ã�TRUE
	filemenu->SetDefaultItem(ID_FILE_SAVE,FALSE);
	//��ң�����ѡ��
	//������Ҫ���ñ���CFrameWnd::m_bAutoMenuEnableΪfalse�����캯������
	filemenu->EnableMenuItem(ID_FILE_SAVE_AS, MF_BYCOMMAND | MF_DISABLED);
	//�Ƴ��˵�
	SetMenu(NULL);
	//���ز˵�
	CMenu menumy;
	menumy.LoadMenuW(IDR_MENU1);//���ز˵���Դ
	SetMenu(&menumy);//���ڲ˵��ӽ�ȥ�ˣ����ǵ���ͻ�ҵ����˵��Ǿֲ�����
	//����
	menumy.Detach();//�������ͷ���Դ�������ɽ��
	//�˵��Զ����»���
	//ͨ����־λ�����Զ�����

	//�Ҽ��˵�View����
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������


//a�ĸ���,����b����仯
void CMainFrame::OnUpdateTestA(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	//�Զ����¹���
	if (m_isUpdate == TRUE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

//b�Ĵ���
void CMainFrame::OnTestB()
{
	// TODO:  �ڴ���������������
	m_isUpdate = !m_isUpdate;
}
