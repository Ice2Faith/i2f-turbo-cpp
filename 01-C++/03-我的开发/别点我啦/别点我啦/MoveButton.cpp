#include "stdafx.h"
#include "MoveButton.h"


MoveButton::MoveButton()
{
}


MoveButton::~MoveButton()
{
}
BEGIN_MESSAGE_MAP(MoveButton, CButton)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


void MoveButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CRect frect,srect;
	GetParent()->GetWindowRect(&frect);
	this->GetWindowRect(&srect);
	int wid = frect.right- srect.right ;
	int hei = frect.bottom-srect.bottom -50;
	
	this->SetWindowPos(0,rand()%wid , rand() % hei+50, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	CButton::OnMouseMove(nFlags, point);
}
