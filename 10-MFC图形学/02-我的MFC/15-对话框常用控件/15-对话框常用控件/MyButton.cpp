// MyButton.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "15-�Ի����ÿؼ�.h"
#include "MyButton.h"


// MyButton

IMPLEMENT_DYNAMIC(MyButton, CButton)

MyButton::MyButton()
{

}

MyButton::~MyButton()
{
}


BEGIN_MESSAGE_MAP(MyButton, CButton)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// MyButton ��Ϣ�������




void MyButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int x = rand() % 400;
	int y = rand() % 400;
	this->MoveWindow(x,y,134,134);
	CButton::OnMouseMove(nFlags, point);
}
