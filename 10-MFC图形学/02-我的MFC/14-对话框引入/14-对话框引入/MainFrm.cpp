
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "14-对话框引入.h"

#include "MainFrm.h"
#include"myDlgIdentity.h"
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
	ON_COMMAND(ID_32771, &CMainFrame::OnSelectExec)
	ON_COMMAND(ID_32772, &CMainFrame::OnSelectShow)
	ON_COMMAND(ID_32773, &CMainFrame::OnMyDlgIdentity)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO:  在此添加成员初始化代码
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
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO:  如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	//创建非模态窗口
	mdlg.Create(IDD_DIALOG2);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

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


// CMainFrame 消息处理程序


//模态对话框
void CMainFrame::OnSelectExec()
{
	// TODO:  在此添加命令处理程序代码
	//创建对话框对象
	CDialog dlg(IDD_DIALOG1);
	//运行
	dlg.DoModal();//这里会阻塞，窗口不会消失
}

//非模态对话框
void CMainFrame::OnSelectShow()
{
	// TODO:  在此添加命令处理程序代码
	//成员变量，构建一次在oncreate，调用时show
	mdlg.ShowWindow(SW_SHOWNORMAL);
}


void CMainFrame::OnMyDlgIdentity()
{
	// TODO:  在此添加命令处理程序代码
	//添加对话框，选择对话框，添加类，头文件声明
	myDlgIdentity dlg;
	dlg.DoModal();
}
