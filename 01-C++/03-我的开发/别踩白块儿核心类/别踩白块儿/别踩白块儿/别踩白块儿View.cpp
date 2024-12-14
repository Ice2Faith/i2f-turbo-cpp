
// ��Ȱ׿��View.cpp : C��Ȱ׿��View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "��Ȱ׿��.h"
#endif

#include "��Ȱ׿��Doc.h"
#include "��Ȱ׿��View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include<thread>
// C��Ȱ׿��View

IMPLEMENT_DYNCREATE(C��Ȱ׿��View, CView)

BEGIN_MESSAGE_MAP(C��Ȱ׿��View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_START_GAME, &C��Ȱ׿��View::OnStartGame)
	ON_COMMAND(ID_MODE_CLASS, &C��Ȱ׿��View::OnModeClass)
	ON_COMMAND(ID_MODE_DHAND, &C��Ȱ׿��View::OnModeDhand)
	ON_COMMAND(ID_MODE_KEYBORD, &C��Ȱ׿��View::OnModeKeybord)
	ON_COMMAND(ID_STATIC_COLOR, &C��Ȱ׿��View::OnStaticColor)
	ON_COMMAND(ID_RANDOM_COLOR, &C��Ȱ׿��View::OnRandomColor)
	ON_COMMAND(ID_OPEN_FINISH_TIPS, &C��Ȱ׿��View::OnOpenFinishTips)
	ON_COMMAND(ID_CLOSE_FINISH_TIPS, &C��Ȱ׿��View::OnCloseFinishTips)
END_MESSAGE_MAP()

// C��Ȱ׿��View ����/����

C��Ȱ׿��View::C��Ȱ׿��View()
: m_useTime(0)
, m_gameMode(GM_CLASS)
, m_randomColor(true)
, m_openFinishTips(true)
{
	// TODO:  �ڴ˴���ӹ������
	game = new DontTouchIt(4, 6);
	m_useTime = GetTickCount();
}

C��Ȱ׿��View::~C��Ȱ׿��View()
{
}

BOOL C��Ȱ׿��View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	game->beginGame();
	return CView::PreCreateWindow(cs);
}

// C��Ȱ׿��View ����

void C��Ȱ׿��View::OnDraw(CDC* pDC)
{
	C��Ȱ׿��Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	static CString class_tipsArr[] = { TEXT("1QAZ"), TEXT("2WSX"), TEXT("3EDC"), TEXT("4RFV") };
	static COLORREF class_colorArr[] = { 0x7070ff, 0x70ff70, 0xff7070, 0x70ffee };
	static CString dbhand_tipsArr[] = { TEXT("1QAZ"), TEXT("2WSX"), TEXT("3EDC"), TEXT("4RFV"), TEXT("7UJM"), TEXT("8IK<"), TEXT("9OL>"), TEXT("0P:?") };
	static COLORREF dbhand_colorArr[] = { 0x7070ff, 0x70ff70, 0xff7070, 0x70ffee, 0xff70ff, 0x44ff22, 0xddff22,0x2277ee };
	static CString keybord_tipsArr[] = { TEXT("1QAZ"), TEXT("2WSX"), TEXT("3EDC"), TEXT("4RFV"), TEXT("5TGB"), TEXT("6YHN"), TEXT("7UJM"), TEXT("8IK<"), TEXT("9OL>"), TEXT("0P:?") };
	static COLORREF keybord_colorArr[] = { 0x7070ff, 0x70ff70, 0xff7070, 0x70ffee, 0xaaff00, 0xffdd00, 0xff70ff, 0x44ff22, 0xddff22, 0x2277ee };
	CString * tipsArr;  
	COLORREF * colorArr;
	if (m_gameMode == GM_CLASS)
	{
		tipsArr = class_tipsArr;
		colorArr = class_colorArr;
	}
	else if (m_gameMode == GM_DBHAND)
	{
		tipsArr = dbhand_tipsArr;
		colorArr = dbhand_colorArr;
	}
	else if (m_gameMode == GM_KEYBORD)
	{
		tipsArr = keybord_tipsArr;
		colorArr = keybord_colorArr;
	}
	COLORREF lineColor = 0xbbbbbb;
	COLORREF touchColor = 0x000000;
	COLORREF dangerColor = 0xffffff;
	CPen pen(0, 1, lineColor);
	CBrush bhDanger(dangerColor);
	CWnd * wnd = pDC->GetWindow();
	wnd->GetWindowRect(rect);
	int row = game->getRowCount();
	int col = game->getColCount();
	int bkwid = rect.Width() / col;
	int bkhei = rect.Height() / row;
	CPen * pe=pDC->SelectObject(&pen);
	pDC->SetBkMode(TRANSPARENT);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			short tp = game->getElement(i, j);
			if (m_randomColor)
				touchColor = RGB(rand() % 135 + 100, rand() % 135 + 100, rand() % 135 + 100);
			else
				touchColor= colorArr[j];
			CBrush bhTouch(touchColor);
			if (tp == DTIGE_TOUCH_BLOCK)
			{
				CBrush * old=pDC->SelectObject(&bhTouch);
			}
			else if (tp==DTIGE_DANGER_BLOCK)
			{
				CBrush * old = pDC->SelectObject(&bhDanger);
			}	
			pDC->Rectangle(j*bkwid, i*bkhei, (j + 1)*bkwid, (i + 1)*bkhei);
			if (i == 0)
			{
				pDC->TextOut(j*bkwid, i*bkhei, tipsArr[j]);
			}
			if (i == row - 1 && tp == DTIGE_TOUCH_BLOCK)
			{
				pDC->TextOut(j*bkwid, i*bkhei, tipsArr[j]);
			}
		}
		
	}
	if (game->getScore() == 1)
	{
		m_useTime = GetTickCount();
	}
	CString str;
	str.Format(TEXT("Score:%6d Dead:%4d time:%3.3lfs"), game->getScore(), game->getDeadCount(), (GetTickCount() - m_useTime)/1000.0);
	pDC->TextOut(0, (0.5)*bkhei, str);
}


// C��Ȱ׿��View ��ӡ

BOOL C��Ȱ׿��View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void C��Ȱ׿��View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void C��Ȱ׿��View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// C��Ȱ׿��View ���

#ifdef _DEBUG
void C��Ȱ׿��View::AssertValid() const
{
	CView::AssertValid();
}

void C��Ȱ׿��View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C��Ȱ׿��Doc* C��Ȱ׿��View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C��Ȱ׿��Doc)));
	return (C��Ȱ׿��Doc*)m_pDocument;
}
#endif //_DEBUG


// C��Ȱ׿��View ��Ϣ�������
void PlayPianoSound(TCHAR * fileName, int tsleep)
{
	TCHAR mind[1024] = { 0 };
	_stprintf(mind, TEXT("open %s alias song"), fileName);
	mciSendString(mind, NULL, NULL, NULL);
	mciSendString(TEXT("play song"), NULL, NULL, NULL);
	Sleep(tsleep);
	mciSendString(TEXT("close song"), NULL, NULL, NULL);
}


void C��Ȱ׿��View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	bool success = false;
	bool otherKey = false;
	switch (m_gameMode)
	{
	case GM_CLASS:
	case GM_KEYBORD:
		switch (nChar)
		{
		case '1':
		case 'Q':
		case 'A':
		case 'Z':
			success = game->touchIt(game->getRowCount() - 1, 0);
			Invalidate();
			break;
		case '2':
		case 'W':
		case 'S':
		case 'X':
			success = game->touchIt(game->getRowCount() - 1, 1);
			Invalidate();
			break;
		case '3':
		case 'E':
		case 'D':
		case 'C':
			success = game->touchIt(game->getRowCount() - 1, 2);
			Invalidate();
			break;
		case '4':
		case 'R':
		case 'F':
		case 'V':
			success = game->touchIt(game->getRowCount() - 1, 3);
			Invalidate();
			break;
		case '5':
		case 'T':
		case 'G':
		case 'B':
			success = game->touchIt(game->getRowCount() - 1, 4);
			Invalidate();
			break;
		case '6':
		case 'Y':
		case 'H':
		case 'N':
			success = game->touchIt(game->getRowCount() - 1, 5);
			Invalidate();
			break;
		case '7':
		case 'U':
		case 'J':
		case 'M':
			success = game->touchIt(game->getRowCount() - 1, 6);
			Invalidate();
			break;
		case '8':
		case 'I':
		case 'K':
		case VK_OEM_COMMA:
			success = game->touchIt(game->getRowCount() - 1, 7);
			Invalidate();
			break;
		case '9':
		case 'O':
		case 'L':
		case VK_OEM_PERIOD:
			success = game->touchIt(game->getRowCount() - 1, 8);
			Invalidate();
			break;
		case '0':
		case 'P':
		case VK_OEM_1:
		case VK_OEM_2:
			success = game->touchIt(game->getRowCount() - 1, 9);
			Invalidate();
			break;
		default:
			otherKey = true;
			break;
		}
		break;
	case GM_DBHAND:
		switch (nChar)
		{
		case '1':
		case 'Q':
		case 'A':
		case 'Z':
			success = game->touchIt(game->getRowCount() - 1, 0);
			Invalidate();
			break;
		case '2':
		case 'W':
		case 'S':
		case 'X':
			success = game->touchIt(game->getRowCount() - 1, 1);
			Invalidate();
			break;
		case '3':
		case 'E':
		case 'D':
		case 'C':
			success = game->touchIt(game->getRowCount() - 1, 2);
			Invalidate();
			break;
		case '4':
		case 'R':
		case 'F':
		case 'V':
			success = game->touchIt(game->getRowCount() - 1, 3);
			Invalidate();
			break;
		case '7':
		case 'U':
		case 'J':
		case 'M':
			success = game->touchIt(game->getRowCount() - 1, 4);
			Invalidate();
			break;
		case '8':
		case 'I':
		case 'K':
		case VK_OEM_COMMA:
			success = game->touchIt(game->getRowCount() - 1, 5);
			Invalidate();
			break;
		case '9':
		case 'O':
		case 'L':
		case VK_OEM_PERIOD:
			success = game->touchIt(game->getRowCount() - 1, 6);
			Invalidate();
			break;
		case '0':
		case 'P':
		case VK_OEM_1:
		case VK_OEM_2:
			success = game->touchIt(game->getRowCount() - 1, 7);
			Invalidate();
			break;
		default:
			otherKey = true;
			break;
		}
		break;
	}
	
	if (success || otherKey)
	{
		TCHAR filename[1024];
		_stprintf(filename, TEXT(".\\pianoSound\\sound-%d.mp3"), rand() % 14 + 40);
		std::thread temp(PlayPianoSound, filename, 2000);
		temp.detach();
	}
	else
	{
		std::thread temp(PlayPianoSound, (TCHAR *)TEXT(".\\pianoSound\\error.mp3"), 2000);
		temp.detach();
	}
	if (game->isGameOvered())
	{
		if (m_openFinishTips)
			MessageBox(TEXT("Game Over!!"), TEXT("��Ϸ��ʾ"));
		game->continueGame();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void C��Ȱ׿��View::OnStartGame()
{
	game->beginGame();
	Invalidate();
}


void C��Ȱ׿��View::OnModeClass()
{
	m_gameMode = GM_CLASS;
	game->setSize(4, 6);
	game->beginGame();
	Invalidate();
}


void C��Ȱ׿��View::OnModeDhand()
{
	m_gameMode = GM_DBHAND;
	game->setSize(8, 6);
	game->beginGame();
	Invalidate();
}


void C��Ȱ׿��View::OnModeKeybord()
{
	m_gameMode = GM_KEYBORD;
	game->setSize(10, 6);
	game->beginGame();
	Invalidate();
}


void C��Ȱ׿��View::OnStaticColor()
{
	m_randomColor = false;
	Invalidate();
}


void C��Ȱ׿��View::OnRandomColor()
{
	m_randomColor = true;
	Invalidate();
}


void C��Ȱ׿��View::OnOpenFinishTips()
{
	m_openFinishTips = true;
}


void C��Ȱ׿��View::OnCloseFinishTips()
{
	m_openFinishTips = false;
}
