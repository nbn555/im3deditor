#pragma once
#include "afxwin.h"

class CColorBox :
	public CStatic
{
public:
	CColorBox(void);
public:
	~CColorBox(void);
	void SetBackColor(COLORREF rgb);
	COLORREF m_crBackGnd;
	CBrush m_brBackGnd;

public:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
};
