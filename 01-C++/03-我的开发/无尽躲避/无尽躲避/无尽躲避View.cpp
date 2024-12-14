
// �޾����View.cpp : C�޾����View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "�޾����.h"
#endif

#include "�޾����Doc.h"
#include "�޾����View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C�޾����View

IMPLEMENT_DYNCREATE(C�޾����View, CView)

BEGIN_MESSAGE_MAP(C�޾����View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_COMMAND(ID_GAME_START, &C�޾����View::OnGameStart)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_GAME_CONTINUE, &C�޾����View::OnGameContinue)
END_MESSAGE_MAP()

// C�޾����View ����/����

C�޾����View::C�޾����View()
{
	// TODO:  �ڴ˴���ӹ������
	game = new EvadeEndless();
	
}

C�޾����View::~C�޾����View()
{
}

BOOL C�޾����View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	
	return CView::PreCreateWindow(cs);
}

// C�޾����View ����

void C�޾����View::OnDraw(CDC* pDC)
{
	C�޾����Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
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
	str.Format(TEXT("Ѫ����%3d �÷֣�%5d"),(int)player.getBlood(),(int)game->getScore());
	pDC->TextOut(0, 0, str);
}


// C�޾����View ��ӡ

BOOL C�޾����View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void C�޾����View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void C�޾����View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// C�޾����View ���

#ifdef _DEBUG
void C�޾����View::AssertValid() const
{
	CView::AssertValid();
}

void C�޾����View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C�޾����Doc* C�޾����View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C�޾����Doc)));
	return (C�޾����Doc*)m_pDocument;
}
#endif //_DEBUG


// C�޾����View ��Ϣ�������


void C�޾����View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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


void C�޾����View::OnGameStart()
{
	// TODO:  �ڴ���������������
	SetTimer(ID_TIMER_GAME_FLUSH, 60, NULL);
}


void C�޾����View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void C�޾����View::OnGameContinue()
{
	game->continueGame();
}
