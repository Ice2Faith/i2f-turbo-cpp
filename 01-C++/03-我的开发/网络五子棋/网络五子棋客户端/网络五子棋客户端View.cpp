
// 网络五子棋客户端View.cpp : C网络五子棋客户端View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "网络五子棋客户端.h"
#endif

#include "网络五子棋客户端Doc.h"
#include "网络五子棋客户端View.h"
#include"MyMessageDlg.h"
#include"MyInputBox.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
void Wchar_t2Charp(wchar_t Wchar[], char Char[])
{
	int size = WideCharToMultiByte(CP_ACP, 0, Wchar, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, Wchar, -1, Char, size, NULL, NULL);
}
void Char2Wchar_tp(char Char[], wchar_t Wchar[])
{
	int size = MultiByteToWideChar(CP_ACP, 0, Char, -1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, Char, -1, Wchar, size);
}
Client * outerClient;
HWND outerHwnd;
bool needAcceptMsg = true;
void AcceptMsgProc()
{
	char outerBuffer[1024];
	while (true)
	{
		if (needAcceptMsg)
		{
			outerClient->AcceptMsg(outerBuffer, 1024 - 1);
			SendMessage(outerHwnd, WM_USER_ACCEPTMSG, (WPARAM)outerBuffer, 0);
			outerBuffer[0] = 0;
		}
		Sleep(20);
	}
}
LRESULT C网络五子棋客户端View::OnUserAcceptMsg(WPARAM wParam, LPARAM lParam)
{
	char info[2048];
	strcpy(info,(char *)wParam);
	char flag[80] = { 0 };
	sscanf(info,"%s ",flag);
	if (strcmp(flag, "down") == 0)
	{
		int c = 0, x = 0, y = 0;
		sscanf(info, "down %d %d %d", &c, &x, &y);
		if (game->BlockDown(c, x, y))
			Invalidate();
	}
	else if (strcmp(flag, "game") == 0)
	{
		char mind[80] = { 0 };
		sscanf(info,"game %s",mind);
		if (strcmp(mind, "undo") == 0)
		{
			char param[80] = { 0 };
			sscanf(info, "game undo %s", param);
			if (strcmp(param, "require") == 0)
			{
				if (IDYES == MessageBox(L"对方请求悔棋，是否允许？", L"游戏悔棋", MB_YESNO))
				{
					game->Undo();
					char sendinfo[] = { "game undo agreen " };
					client->SendMsg(sendinfo, strlen(sendinfo));
					Invalidate();
				}
				else
				{
					char sendinfo[] = {"game undo reduce "};
					client->SendMsg(sendinfo,strlen(sendinfo));
				}
			}
			else if (strcmp(param, "agreen") == 0)
			{
				game->Undo();
				Invalidate();
			}
			else if (strcmp(param, "reduce") == 0)
			{
				MyMessageDlg dlg(L"对方拒绝了你的悔棋！", L"游戏提示", 1500, this);
				dlg.DoModal();
			}
			
		}
		else if (strcmp(mind, "exit") == 0)
		{
			MessageBox(L"对方退出了游戏！", L"游戏提示", MB_OK);
			exit(0);
		}
		else if (strcmp(mind, "new") == 0)
		{
			char param[80] = { 0 };
			sscanf(info, "game new %s", param);
			if (strcmp(param, "require") == 0)
			{
				if (IDYES == MessageBox(L"对方请求新游戏，是否允许？", L"新游戏", MB_YESNO))
				{
					delete game;
					game = new Gobang();
					char sendinfo[] = { "game new agreen " };
					client->SendMsg(sendinfo, strlen(sendinfo));
					Invalidate();
				}
				else
				{
					char sendinfo[] = { "game new reduce " };
					client->SendMsg(sendinfo, strlen(sendinfo));
				}
			}
			else if (strcmp(param, "agreen") == 0)
			{
				delete game;
				game = new Gobang();
				Invalidate();
			}
			else if (strcmp(param, "reduce") == 0)
			{
				MyMessageDlg dlg(L"对方拒绝了你的新游戏！", L"游戏提示", 1500, this);
				dlg.DoModal();
			}

		}
	}
	else if (strcmp(flag, "chat") == 0)
	{
		WCHAR msg[2048];
		Char2Wchar_tp(&info[5],msg);
		MyMessageDlg dlg(msg, L"玩家聊天", 1500, this);
		dlg.DoModal();
	}
	else if (strcmp(flag, "broad") == 0)
	{
		WCHAR msg[2048];
		Char2Wchar_tp(&info[5], msg);
		MyMessageDlg dlg(msg, L"玩家广播", 1500, this);
		dlg.DoModal();
	}
	return 0;
}
// C网络五子棋客户端View

IMPLEMENT_DYNCREATE(C网络五子棋客户端View, CView)

BEGIN_MESSAGE_MAP(C网络五子棋客户端View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_USER_ACCEPTMSG,OnUserAcceptMsg)
	ON_COMMAND(ID_32771, &C网络五子棋客户端View::OnNewGame)
	ON_COMMAND(ID_32772, &C网络五子棋客户端View::OnUndoGame)
	ON_COMMAND(ID_32773, &C网络五子棋客户端View::OnExitGame)
	ON_COMMAND(ID_32774, &C网络五子棋客户端View::OnSendTextMsg)
	ON_COMMAND(ID_32775, &C网络五子棋客户端View::OnBroadcastPlayer)
END_MESSAGE_MAP()

// C网络五子棋客户端View 构造/析构

C网络五子棋客户端View::C网络五子棋客户端View()
{
	// TODO:  在此处添加构造代码
	OfflineGame = true;
	game = new Gobang();
}

C网络五子棋客户端View::~C网络五子棋客户端View()
{
}
BOOL C网络五子棋客户端View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	WelComeFace dlg;
	dlg.DoModal();
	m_isTrunBlack = dlg.isFrist;
	client = dlg.client;
	outerClient = client;
	if (dlg.up == UP_OFFLINE)
		OfflineGame = true;
	else
	{
		OfflineGame = false;
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AcceptMsgProc, NULL, 0, NULL);
	}
	return CView::PreCreateWindow(cs);
}

// C网络五子棋客户端View 绘制

void C网络五子棋客户端View::OnDraw(CDC* pDC)
{
	C网络五子棋客户端Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	outerHwnd = GetSafeHwnd();
	// TODO:  在此处为本机数据添加绘制代码
	CRect rect;
	CWnd * wind = pDC->GetWindow();
	wind->GetWindowRect(rect);
	int wid = rect.Width() / game->GetSizeCol();
	int hei = rect.Height() / game->GetSizeRow();
	for (int i = 0; i < game->GetSizeRow(); i++)
	{
		for (int j = 0; j < game->GetSizeCol(); j++)
		{
			pDC->Rectangle(i*wid, j*hei, (i + 1)*wid, (j + 1)*hei);
			int chess = game->AtIndex(i, j);
			if (chess == -1)
				DrawChess(i, j, 0x000000);
			else if (chess == 1)
				DrawChess(i, j, 0x0000ff);
		}
	}
	if (game->IsWin())
	{
		for (int i = 0; i < 5; i++)
		{
			DrawChess(game->winsort[i][0], game->winsort[i][1], 0x00ffff);
		}
		MessageBox(L"Player Win");
	}
}


// C网络五子棋客户端View 打印

BOOL C网络五子棋客户端View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void C网络五子棋客户端View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void C网络五子棋客户端View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// C网络五子棋客户端View 诊断

#ifdef _DEBUG
void C网络五子棋客户端View::AssertValid() const
{
	CView::AssertValid();
}

void C网络五子棋客户端View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C网络五子棋客户端Doc* C网络五子棋客户端View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C网络五子棋客户端Doc)));
	return (C网络五子棋客户端Doc*)m_pDocument;
}
#endif //_DEBUG

void C网络五子棋客户端View::DrawChess(int xIndex, int yIndex, COLORREF color)
{
	CClientDC dc(this);
	CRect rect;
	CWnd * wind = dc.GetWindow();
	wind->GetWindowRect(rect);
	int wid = rect.Width() / game->GetSizeCol();
	int hei = rect.Height() / game->GetSizeRow();
	CBrush brush(color);
	CBrush* old = dc.SelectObject(&brush);
	dc.Ellipse(xIndex*wid, yIndex*hei, (xIndex + 1)*wid, (yIndex + 1)*hei);
	dc.SelectObject(old);
}
// C网络五子棋客户端View 消息处理程序


void C网络五子棋客户端View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	CRect rect;
	CWnd * wind = dc.GetWindow();
	wind->GetWindowRect(rect);
	int wid = rect.Width() / game->GetSizeCol();
	int hei = rect.Height() / game->GetSizeRow();
	int x = point.x / wid;
	int y = point.y / hei;
	int c=0;
	
	if (OfflineGame)
	{
		if (m_isTrunBlack)
			c = -1;
		else
			c = 1;
		game->BlockDown(c, x, y);
		m_isTrunBlack = !m_isTrunBlack;
	}
	else
	{
		if (m_isTrunBlack)
		{
			
			if (game->BlockDown(-1, x, y))
			{
				Invalidate();
				char tempRet[1024];
				sprintf(tempRet, "down -1 %d %d \0", x, y);
				client->SendMsg(tempRet, strlen(tempRet));
			}

		}
		else
		{
			

			if (game->BlockDown(1, x, y))
			{
				Invalidate();
				char tempRet[1024];
				sprintf(tempRet, "down 1 %d %d \0", x, y);
				client->SendMsg(tempRet, strlen(tempRet));
			}
			
		}
		
	}
	Invalidate();
	CView::OnLButtonDown(nFlags, point);
}


void C网络五子棋客户端View::OnNewGame()
{
	// TODO:  在此添加命令处理程序代码
	if (OfflineGame)
	{
		delete game;
		game = new Gobang();
	}
	else
	{
		char sendinfo[] = "game new require ";
		client->SendMsg(sendinfo, strlen(sendinfo));
	}
	Invalidate();
}


void C网络五子棋客户端View::OnUndoGame()
{
	// TODO:  在此添加命令处理程序代码
	if (OfflineGame)
		game->Undo();
	else
	{
		char sendinfo[] = "game undo require ";
		client->SendMsg(sendinfo, strlen(sendinfo));
	}
	Invalidate();
}


void C网络五子棋客户端View::OnExitGame()
{
	// TODO:  在此添加命令处理程序代码
	if (!OfflineGame)
	{
		char sendinfo[] = "game exit";
		client->SendMsg(sendinfo, strlen(sendinfo));
	}
	exit(0);
}

void C网络五子棋客户端View::OnSendTextMsg()
{
	// TODO:  在此添加命令处理程序代码
	if (!OfflineGame)
	{
		MyInputBox ib(L"请输入要发送的内容：");
		ib.DoModal();
		char input[2048];
		Wchar_t2Charp(ib.m_inputContext.GetBuffer(),input);
		char sendinfo[2048];
		sprintf(sendinfo,"chat %s\0",input);
		client->SendMsg(sendinfo, strlen(sendinfo));
	}
}


void C网络五子棋客户端View::OnBroadcastPlayer()
{
	// TODO:  在此添加命令处理程序代码
	if (!OfflineGame)
	{
		MyInputBox ib(L"请输入要广播的内容：");
		ib.DoModal();
		char input[2048];
		Wchar_t2Charp(ib.m_inputContext.GetBuffer(), input);
		char sendinfo[2048];
		sprintf(sendinfo, "broad %s\0", input);
		client->SendMsg(sendinfo, strlen(sendinfo));
	}
}
