
// 无尽躲避View.cpp : C无尽躲避View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "无尽躲避.h"
#endif

#include "无尽躲避Doc.h"
#include "无尽躲避View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C无尽躲避View

IMPLEMENT_DYNCREATE(C无尽躲避View, CView)

BEGIN_MESSAGE_MAP(C无尽躲避View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_COMMAND(ID_GAME_START, &C无尽躲避View::OnGameStart)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_GAME_CONTINUE, &C无尽躲避View::OnGameContinue)
END_MESSAGE_MAP()

// C无尽躲避View 构造/析构

C无尽躲避View::C无尽躲避View()
{
	// TODO:  在此处添加构造代码
	game = new EvadeEndless();
	
}

C无尽躲避View::~C无尽躲避View()
{
}

BOOL C无尽躲避View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	
	return CView::PreCreateWindow(cs);
}

// C无尽躲避View 绘制

void C无尽躲避View::OnDraw(CDC* pDC)
{
	C无尽躲避Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	pDC->SetBkMode(TRANSPARENT);
	CRect rect;
	this->GetClientRect(rect);
	game->setSize(rect.Width(), rect.Height());
	static CPen enemypen(0, 1, 0x0000ff);
	pDC->SelectObject(&enemypen);
	int size = game->getEnemyCount();
	for (int i = 0; i < size; i++)
	{
		ModelEntity me = game->getEnemy(i);
		pDC->Rectangle(me.getPosX() - me.getRadius(), me.getPosY() - me.getRadius(), 
			me.getPosX() + me.getRadius(), me.getPosY() + me.getRadius());
	}
	static CPen bulletpen(0, 1, 0x00ff00);
	pDC->SelectObject(&bulletpen);
	size = game->getBulletCount();
	for (int i = 0; i < size; i++)
	{
		ModelEntity me = game->getBullet(i);
		pDC->Ellipse(me.getPosX() - me.getRadius(), me.getPosY() - me.getRadius(),
			me.getPosX() + me.getRadius(), me.getPosY() + me.getRadius());
	}
	static CPen playertpen(0, 1, 0xff0000);
	pDC->SelectObject(&playertpen);
	ModelEntity player = game->getPlayer();
	pDC->Ellipse(player.getPosX() - player.getRadius(), player.getPosY() - player.getRadius(), 
		player.getPosX() + player.getRadius(), player.getPosY() + player.getRadius());
	CString str;
	str.Format(TEXT("血量：%3d 得分：%5d"),(int)player.getBlood(),(int)game->getScore());
	pDC->TextOut(0, 0, str);
}


// C无尽躲避View 打印

BOOL C无尽躲避View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void C无尽躲避View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void C无尽躲避View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// C无尽躲避View 诊断

#ifdef _DEBUG
void C无尽躲避View::AssertValid() const
{
	CView::AssertValid();
}

void C无尽躲避View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C无尽躲避Doc* C无尽躲避View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C无尽躲避Doc)));
	return (C无尽躲避Doc*)m_pDocument;
}
#endif //_DEBUG


// C无尽躲避View 消息处理程序


void C无尽躲避View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == ID_TIMER_GAME_FLUSH)
	{
		if (GetAsyncKeyState(VK_SPACE)&0x8000)
			game->shootBullet();
		if (GetAsyncKeyState(VK_UP)&0x8000)
			game->movePlayer(3.14159 * 3 / 2);
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			game->movePlayer(3.14159 * 1 / 2);
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			game->movePlayer(3.14159 * 2 / 2);
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			game->movePlayer(3.14159 * 0 / 2);
		game->flushGame();
		Invalidate();
	}
	CView::OnTimer(nIDEvent);
}


void C无尽躲避View::OnGameStart()
{
	// TODO:  在此添加命令处理程序代码
	SetTimer(ID_TIMER_GAME_FLUSH, 60, NULL);
}


void C无尽躲避View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void C无尽躲避View::OnGameContinue()
{
	game->continueGame();
}
