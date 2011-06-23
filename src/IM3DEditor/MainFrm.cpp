// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "IM3DEditor.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// Lighting toolbar
	if (!m_wndLightingToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndLightingToolBar.LoadToolBar(IDR_TOOLBAR_LIGHTING))
	{
		TRACE0("Failed to create form view toolbar\n");
		return -1;      // fail to create
	}

	// Shading 
	if (!m_wndShadingToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndShadingToolBar.LoadToolBar(IDR_TOOLBAR_SHADING_STYLE))
	{
		TRACE0("Failed to create form view toolbar\n");
		return -1;      // fail to create
	}
   m_wndShadingToolBar.SetButtonStyle(m_wndShadingToolBar.CommandToIndex(IDR_TOOLBAR_SHADING_STYLE_WIRE),TBBS_CHECKGROUP);
	m_wndShadingToolBar.SetButtonStyle(m_wndShadingToolBar.CommandToIndex(IDR_TOOLBAR_SHADING_STYLE_SOLID),TBBS_CHECKGROUP);
   m_wndShadingToolBar.SetButtonStyle(m_wndShadingToolBar.CommandToIndex(IDR_TOOLBAR_SHADING_STYLE_SOLID_WIRE),TBBS_CHECKGROUP);
	m_wndShadingToolBar.SetWindowText(_T("Shading"));

	// Form View
	if (!m_wndFormViewToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndFormViewToolBar.LoadToolBar(IDR_TOOLBAR_FORM_VIEW))
	{
		TRACE0("Failed to create form view toolbar\n");
		return -1;      // fail to create
	}

   // Form View
	if (!m_wndEditViewToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndEditViewToolBar.LoadToolBar(IDR_TOOLBAR_EDIT_VIEW))
	{
		TRACE0("Failed to create form view toolbar\n");
		return -1;      // fail to create
	}

   // Simulation bar
   if(!m_wndSimulationBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndSimulationBar.LoadToolBar(IDR_TOOLBAR_SIMULATION))
	{
		TRACE0("Failed to create form view toolbar\n");
		return -1;      // fail to create
	}
   m_wndSimulationBar.LoadBitmapW(IDB_BITMAP_SIMULATION_ICON);
   //m_wndEditViewToolBar.SetButtonStyle(m_wndEditViewToolBar.CommandToIndex(ID_TOOLBAR_EIDT_VIEW_CLEAR),TBBS_CHECKGROUP);


   // Setup Simulation
   if(!m_wndSetupSimulation.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndSetupSimulation.LoadToolBar(IDR_TOOLBAR_SETUP_SIMULATION))
	{
		TRACE0("Failed to create form view toolbar\n");
		return -1;      // fail to create
	}


	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
   m_wndLightingToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndShadingToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndFormViewToolBar.EnableDocking(CBRS_ALIGN_ANY);
   m_wndEditViewToolBar.EnableDocking(CBRS_ALIGN_ANY);
   m_wndSimulationBar.EnableDocking(CBRS_ALIGN_ANY);
   m_wndSetupSimulation.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);

//Set ToolBar Position
	RecalcLayout();
	DockControlBar(&m_wndToolBar);
   CRect rBar;
	m_wndToolBar.GetWindowRect(rBar);
	rBar.OffsetRect(1, 0);
	DockControlBar(&m_wndLightingToolBar,AFX_IDW_DOCKBAR_TOP,rBar);
   DockControlBar(&m_wndShadingToolBar,AFX_IDW_DOCKBAR_TOP,rBar);
   DockControlBar(&m_wndFormViewToolBar,AFX_IDW_DOCKBAR_TOP,rBar);
   DockControlBar(&m_wndEditViewToolBar,AFX_IDW_DOCKBAR_TOP,rBar);
   DockControlBar(&m_wndSimulationBar,AFX_IDW_DOCKBAR_TOP,rBar);
   DockControlBar(&m_wndSetupSimulation,AFX_IDW_DOCKBAR_TOP,rBar);
   

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::updateSimulationBarIcon(const int ind)
{
    UINT nID=0;
    UINT nStyle=0;
    int  nImage=-1;
    //m_wndSimulationBar.LoadBitmapW(IDB_BITMAP_SIMULATION_ICON);
    int bIndex = m_wndSimulationBar.CommandToIndex(ID_TOOLBAR_SIMULATION_START);
   // m_wndSimulationBar.GetButtonInfo(bIndex, nID, nStyle, ind);
    m_wndSimulationBar.SetButtonInfo(bIndex, ID_TOOLBAR_SIMULATION_START, 0  , ind);
    m_wndSimulationBar.Invalidate();
    
}

