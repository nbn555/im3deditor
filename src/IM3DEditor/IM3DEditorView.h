// IM3DEditorView.h : interface of the CIM3DEditorView class
//
#ifndef IM3DEDITOR_3DEDITOR_VIEW_H_
#define IM3DEDITOR_3DEDITOR_VIEW_H_

#pragma once

#include "imViewDefinitions.h"
#include <vector>
#include "ImPoint3Dd.h"
typedef ImPoint3Dd Point3Dd;
class ImCAMSim;

class CIM3DEditorView : public CView
{
protected: // create from serialization only
	CIM3DEditorView();
	DECLARE_DYNCREATE(CIM3DEditorView)

// Attributes
public:
	CIM3DEditorDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CIM3DEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
private:
	HWND m_pWnd;
	int m_cx;
	int m_cy;
	HGLRC	m_hRC;
	CDC*	m_pDC;
	GLfloat	m_f3RenderingCenter[3];
	GLfloat m_fRenderingRate;
	float   m_theta, m_phi;
	LIGHTSETTING	m_aLightSetting[9];
	ETRACKINGMODE	m_eTrackingMode;
	GLfloat			m_f3LastPos[3];
	CPoint			m_ptLast;
	GLfloat			m_objectXform[4][4];
	float m_objectColor[3];
	float m_backgrColor[3];
	float m_bkrTop[3];
	float m_bkrBottom[3];
	GLuint	m_uiDisplayAxis;
	std::vector<int> m_ObjIndex;
   int m_viewType;// 0: wire, 1: solid, 2: wire and solid
   Point3Dd m_ov; // origin of bounding box of all object in view
   Point3Dd m_size;// size of bounding box of all object in view
   int m_simulationStatus; // using to control simulation. 0 - stop; 1 - start; 2 - pause
   ImCAMSim* m_CamSim;
   // VIEW
   bool m_isViewMaterial;
   bool m_isViewToolPath;
   bool m_isViewTool;

public:
   HWND getHWnd();
	bool InitializeOpenGL(void);
	bool setupViewingFrustum(void);
	bool setupViewingTransform(void);
   void enableAntialias();
   void disableAntialias();
	bool setupPixelFormat(void);
	bool setupLight(void);
	void setupPosLighting(int pos);
	void	BeginTracking( CPoint point, ETRACKINGMODE eTrackingMode );
	void	EndTracking();
	void	DoTracking( CPoint point );
	void	ptov( GLfloat p[2], GLfloat v[3], GLfloat fWidth, GLfloat fHeight );
	void	DoRotation( const float fAngle, const float fX, const float fY, const float fZ );
	void RotateScene( CPoint point); 
	void MovingScene( CPoint point); 
	void ZoomScene ( CPoint point); 
	void renderStockScene();
	void renderBackground();
	void	renderAxis();
   void renderObject();
   void moveToCenterScreen();
   void fitToScreenSize(int axis = 3);
   void updateBoundingBox(double *ov, double *lv);
   void setupMaterial();
   ImCAMSim* getCAMSim(){ return m_CamSim; };
   void setCAMSim(ImCAMSim* sim){ m_CamSim = sim; };
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
public:

   // light position
	afx_msg void OnLighting(UINT nID);
	afx_msg void OnUpdateLighting(CCmdUI* pCmdUI);

   //shading
   afx_msg void OnDisplayStyleWire();
	afx_msg void OnDisplayStyleSolid();
   afx_msg void OnDisplayStyleSolidWire();

   //viewport
   afx_msg void OnViewTop();
	afx_msg void OnViewBottom();
	afx_msg void OnViewLeft();
	afx_msg void OnViewRight();
	afx_msg void OnViewFront();
	afx_msg void OnViewBack();
	afx_msg void OnViewIsometric();

   //edit view
   afx_msg void OnEditViewClear();

   //simulation
   afx_msg void OnStopSimulation();
   afx_msg void OnStartSimulation();
   afx_msg void OnUpdateStopSimulation(CCmdUI* pCmdUI);
   afx_msg void OnUpdateStartSimulation(CCmdUI* pCmdUI);

  

public:
   afx_msg void OnFemDelaunaymesh();
public:
   afx_msg void OnViewSimulationMaterial();
public:
   afx_msg void OnUpdateViewSimulationMaterial(CCmdUI *pCmdUI);
public:
   afx_msg void OnViewSimulationTool();
public:
   afx_msg void OnUpdateViewSimulationTool(CCmdUI *pCmdUI);
public:
   afx_msg void OnViewSimulationToolpath();
public:
   afx_msg void OnUpdateViewSimulationToolpath(CCmdUI *pCmdUI);
protected:
   virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // debug version in IM3DEditorView.cpp
inline CIM3DEditorDoc* CIM3DEditorView::GetDocument() const
   { return reinterpret_cast<CIM3DEditorDoc*>(m_pDocument); }
#endif

#endif