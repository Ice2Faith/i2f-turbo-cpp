// MyButton.cpp : 实现文件
//

#include "stdafx.h"
#include "15-对话框常用控件.h"
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



// MyButton 消息处理程序




void MyButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	int x = rand() % 400;
	int y = rand() % 400;
	this->MoveWindow(x,y,134,134);
	CButton::OnMouseMove(nFlags, point);
}
