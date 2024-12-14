
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "11-菜单静态操作.h"

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
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
: m_isUpdate(false)
{
	// TODO:  在此添加成员初始化代码
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

	//标志
	//获取菜单
	//获取主菜单
	CMenu * menu = GetMenu();
	//获取文件子菜单
	CMenu * filemenu = menu->GetSubMenu(0);

	//标志新建，参数：0由MF_BYPOSITION决定
	filemenu->CheckMenuItem(0,MF_BYPOSITION|MF_CHECKED);
	filemenu->CheckMenuItem(ID_FILE_OPEN, MF_BYCOMMAND | MF_CHECKED);
	//设置默认项，加粗，一个菜单项只有一个默认选项菜单，参数决定类似上
	//ID:False,位置：TRUE
	filemenu->SetDefaultItem(ID_FILE_SAVE,FALSE);
	//变灰，不可选中
	//首先需要设置变量CFrameWnd::m_bAutoMenuEnable为false，构造函数设置
	filemenu->EnableMenuItem(ID_FILE_SAVE_AS, MF_BYCOMMAND | MF_DISABLED);
	//移除菜单
	SetMenu(NULL);
	//加载菜单
	CMenu menumy;
	menumy.LoadMenuW(IDR_MENU1);//加载菜单资源
	SetMenu(&menumy);//现在菜单加进去了，可是点击就会挂掉，菜单是局部变量
	//分离
	menumy.Detach();//不进行释放资源处理，即可解决
	//菜单自动更新机制
	//通过标志位进行自动更新

	//右键菜单View处理
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


//a的更新,根据b点击变化
void CMainFrame::OnUpdateTestA(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	//自动更新功能
	if (m_isUpdate == TRUE)
	{
		pCmdUI->Enable(TRUE);
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

//b的处理
void CMainFrame::OnTestB()
{
	// TODO:  在此添加命令处理程序代码
	m_isUpdate = !m_isUpdate;
}
