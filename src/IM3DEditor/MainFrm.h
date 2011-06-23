// MainFrm.h : interface of the CMainFrame class
//


#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CToolBar    m_wndLightingToolBar;
	CToolBar    m_wndShadingToolBar;
	CToolBar    m_wndFormViewToolBar;
   CToolBar    m_wndEditViewToolBar;
   CToolBar    m_wndSimulationBar;
   CToolBar    m_wndSetupSimulation;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
   void updateSimulationBarIcon(const int ind);
};


