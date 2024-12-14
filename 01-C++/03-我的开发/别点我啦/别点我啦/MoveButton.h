#pragma once
#include "afxwin.h"
class MoveButton :
	public CButton
{
public:
	MoveButton();
	~MoveButton();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

