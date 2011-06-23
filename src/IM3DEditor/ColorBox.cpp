#include "StdAfx.h"
#include "ColorBox.h"

CColorBox::CColorBox(void)
{
	
}

CColorBox::~CColorBox(void)
{
	if (m_brBackGnd.GetSafeHandle())
		m_brBackGnd.DeleteObject();
}

BEGIN_MESSAGE_MAP(CColorBox, CStatic)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

HBRUSH CColorBox::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO:  Change any attributes of the DC here

	// TODO:  Return a non-NULL brush if the parent's handler should not be called
	pDC->SetBkColor(m_crBackGnd);
	//return the brush used for background this sets control background
	return m_brBackGnd;
}
void CColorBox::SetBackColor(COLORREF rgb)
{
	//set background color ref (used for text's background)
	m_crBackGnd = rgb;

	//free brush
	if (m_brBackGnd.GetSafeHandle())
		m_brBackGnd.DeleteObject();
	//set brush to new color
	m_brBackGnd.CreateSolidBrush(rgb);

	//redraw
	Invalidate(TRUE);
}