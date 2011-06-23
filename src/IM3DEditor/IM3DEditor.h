// IM3DEditor.h : main header file for the IM3DEditor application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CIM3DEditorApp:
// See IM3DEditor.cpp for the implementation of this class
//

class CIM3DEditorApp : public CWinApp
{
public:
	CIM3DEditorApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CIM3DEditorApp theApp;