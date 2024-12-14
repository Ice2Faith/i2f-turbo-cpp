
// ����������ͻ���View.cpp : C����������ͻ���View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "����������ͻ���.h"
#endif

#include "����������ͻ���Doc.h"
#include "����������ͻ���View.h"
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
LRESULT C����������ͻ���View::OnUserAcceptMsg(WPARAM wParam, LPARAM lParam)
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
				if (IDYES == MessageBox(L"�Է�������壬�Ƿ�����", L"��Ϸ����", MB_YESNO))
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
				MyMessageDlg dlg(L"�Է��ܾ�����Ļ��壡", L"��Ϸ��ʾ", 1500, this);
				dlg.DoModal();
			}
			
		}
		else if (strcmp(mind, "exit") == 0)
		{
			MessageBox(L"�Է��˳�����Ϸ��", L"��Ϸ��ʾ", MB_OK);
			exit(0);
		}
		else if (strcmp(mind, "new") == 0)
		{
			char param[80] = { 0 };
			sscanf(info, "game new %s", param);
			if (strcmp(param, "require") == 0)
			{
				if (IDYES == MessageBox(L"�Է���������Ϸ���Ƿ�����", L"����Ϸ", MB_YESNO))
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
				MyMessageDlg dlg(L"�Է��ܾ����������Ϸ��", L"��Ϸ��ʾ", 1500, this);
				dlg.DoModal();
			}

		}
	}
	else if (strcmp(flag, "chat") == 0)
	{
		WCHAR msg[2048];
		Char2Wchar_tp(&info[5],msg);
		MyMessageDlg dlg(msg, L"�������", 1500, this);
		dlg.DoModal();
	}
	else if (strcmp(flag, "broad") == 0)
	{
		WCHAR msg[2048];
		Char2Wchar_tp(&info[5], msg);
		MyMessageDlg dlg(msg, L"��ҹ㲥", 1500, this);
		dlg.DoModal();
	}
	return 0;
}
// C����������ͻ���View

IMPLEMENT_DYNCREATE(C����������ͻ���View, CView)

BEGIN_MESSAGE_MAP(C����������ͻ���View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_USER_ACCEPTMSG,OnUserAcceptMsg)
	ON_COMMAND(ID_32771, &C����������ͻ���View::OnNewGame)
	ON_COMMAND(ID_32772, &C����������ͻ���View::OnUndoGame)
	ON_COMMAND(ID_32773, &C����������ͻ���View::OnExitGame)
	ON_COMMAND(ID_32774, &C����������ͻ���View::OnSendTextMsg)
	ON_COMMAND(ID_32775, &C����������ͻ���View::OnBroadcastPlayer)
END_MESSAGE_MAP()

// C����������ͻ���View ����/����

C����������ͻ���View::C����������ͻ���View()
{
	// TODO:  �ڴ˴���ӹ������
	OfflineGame = true;
	game = new Gobang();
}

C����������ͻ���View::~C����������ͻ���View()
{
}
BOOL C����������ͻ���View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
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

// C����������ͻ���View ����

void C����������ͻ���View::OnDraw(CDC* pDC)
{
	C����������ͻ���Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	outerHwnd = GetSafeHwnd();
	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
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


// C����������ͻ���View ��ӡ

BOOL C����������ͻ���View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void C����������ͻ���View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void C����������ͻ���View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// C����������ͻ���View ���

#ifdef _DEBUG
void C����������ͻ���View::AssertValid() const
{
	CView::AssertValid();
}

void C����������ͻ���View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C����������ͻ���Doc* C����������ͻ���View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C����������ͻ���Doc)));
	return (C����������ͻ���Doc*)m_pDocument;
}
#endif //_DEBUG

void C����������ͻ���View::DrawChess(int xIndex, int yIndex, COLORREF color)
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
// C����������ͻ���View ��Ϣ�������


void C����������ͻ���View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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


void C����������ͻ���View::OnNewGame()
{
	// TODO:  �ڴ���������������
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


void C����������ͻ���View::OnUndoGame()
{
	// TODO:  �ڴ���������������
	if (OfflineGame)
		game->Undo();
	else
	{
		char sendinfo[] = "game undo require ";
		client->SendMsg(sendinfo, strlen(sendinfo));
	}
	Invalidate();
}


void C����������ͻ���View::OnExitGame()
{
	// TODO:  �ڴ���������������
	if (!OfflineGame)
	{
		char sendinfo[] = "game exit";
		client->SendMsg(sendinfo, strlen(sendinfo));
	}
	exit(0);
}

void C����������ͻ���View::OnSendTextMsg()
{
	// TODO:  �ڴ���������������
	if (!OfflineGame)
	{
		MyInputBox ib(L"������Ҫ���͵����ݣ�");
		ib.DoModal();
		char input[2048];
		Wchar_t2Charp(ib.m_inputContext.GetBuffer(),input);
		char sendinfo[2048];
		sprintf(sendinfo,"chat %s\0",input);
		client->SendMsg(sendinfo, strlen(sendinfo));
	}
}


void C����������ͻ���View::OnBroadcastPlayer()
{
	// TODO:  �ڴ���������������
	if (!OfflineGame)
	{
		MyInputBox ib(L"������Ҫ�㲥�����ݣ�");
		ib.DoModal();
		char input[2048];
		Wchar_t2Charp(ib.m_inputContext.GetBuffer(), input);
		char sendinfo[2048];
		sprintf(sendinfo, "broad %s\0", input);
		client->SendMsg(sendinfo, strlen(sendinfo));
	}
}
