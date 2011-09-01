// IM3DEditorView.cpp : implementation of the CIM3DEditorView class
//

#include "stdafx.h"
#include "IM3DEditor.h"
#include "MainFrm.h"
#include "IM3DEditorDoc.h"
#include "IM3DEditorView.h"
#include <math.h>
#include "objStore.h"
#include "CAMSim.h"
#include "ClGenObject.h"
#include "StlObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )
//#pragma comment( lib, "glaux.lib" )

// CIM3DEditorView

IMPLEMENT_DYNCREATE(CIM3DEditorView, CView)

BEGIN_MESSAGE_MAP(CIM3DEditorView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()

   // light position
	ON_COMMAND_RANGE(IDR_TOOLBAR_LIGHTING_TOP,IDR_TOOLBAR_LIGHTING_FRONT,&CIM3DEditorView::OnLighting)
	//ON_UPDATE_COMMAND_UI(ID_LIGHTING_TOPVIEW,&CIM3DEditorView::OnUpdateLighting)
	ON_UPDATE_COMMAND_UI_RANGE(IDR_TOOLBAR_LIGHTING_TOP,IDR_TOOLBAR_LIGHTING_FRONT,&CIM3DEditorView::OnUpdateLighting)
   
   // shading
   ON_COMMAND(IDR_TOOLBAR_SHADING_STYLE_WIRE, &CIM3DEditorView::OnDisplayStyleWire)
   ON_COMMAND(IDR_TOOLBAR_SHADING_STYLE_SOLID, &CIM3DEditorView::OnDisplayStyleSolid)
   ON_COMMAND(IDR_TOOLBAR_SHADING_STYLE_SOLID_WIRE, &CIM3DEditorView::OnDisplayStyleSolidWire)

   // viewport
   ON_COMMAND(IDR_FORM_VIEW_FRONT,&CIM3DEditorView::OnViewFront)
   ON_COMMAND(IDR_FORM_VIEW_BACK,&CIM3DEditorView::OnViewBack)
   ON_COMMAND(IDR_FORM_VIEW_LEFT,&CIM3DEditorView::OnViewLeft)
   ON_COMMAND(IDR_FORM_VIEW_RIGHT,&CIM3DEditorView::OnViewRight)
   ON_COMMAND(IDR_FORM_VIEW_TOP, &CIM3DEditorView::OnViewTop)
   ON_COMMAND(IDR_FORM_VIEW_BOTTOM,&CIM3DEditorView::OnViewBottom)
   ON_COMMAND(IDR_FORM_VIEW_ISOMETRIC,&CIM3DEditorView::OnViewIsometric)

   //edit view
   ON_COMMAND(ID_TOOLBAR_EIDT_VIEW_CLEAR,&CIM3DEditorView::OnEditViewClear)

   //simulation
   ON_COMMAND(ID_TOOLBAR_SIMULATION_STOP,&CIM3DEditorView::OnStopSimulation)
   ON_COMMAND(ID_TOOLBAR_SIMULATION_START,&CIM3DEditorView::OnStartSimulation)
   ON_UPDATE_COMMAND_UI(ID_TOOLBAR_SIMULATION_STOP,&CIM3DEditorView::OnUpdateStopSimulation)
   ON_UPDATE_COMMAND_UI(ID_TOOLBAR_SIMULATION_START,&CIM3DEditorView::OnUpdateStartSimulation)

   

   ON_COMMAND(ID_FEM_DELAUNAYMESH, &CIM3DEditorView::OnFemDelaunaymesh)


   //View simulation
   ON_COMMAND(ID_VIEW_SIMULATION_MATERIAL, &CIM3DEditorView::OnViewSimulationMaterial)
   ON_UPDATE_COMMAND_UI(ID_VIEW_SIMULATION_MATERIAL, &CIM3DEditorView::OnUpdateViewSimulationMaterial)
   ON_COMMAND(ID_VIEW_SIMULATION_TOOL, &CIM3DEditorView::OnViewSimulationTool)
   ON_UPDATE_COMMAND_UI(ID_VIEW_SIMULATION_TOOL, &CIM3DEditorView::OnUpdateViewSimulationTool)
   ON_COMMAND(ID_VIEW_SIMULATION_TOOLPATH, &CIM3DEditorView::OnViewSimulationToolpath)
   ON_UPDATE_COMMAND_UI(ID_VIEW_SIMULATION_TOOLPATH, &CIM3DEditorView::OnUpdateViewSimulationToolpath)
END_MESSAGE_MAP()

// CIM3DEditorView construction/destruction

CIM3DEditorView::CIM3DEditorView():
m_cx(0)
, m_cy(0)
, m_fRenderingRate(5)
,m_pWnd(0)
,m_hRC(0)
,m_pDC(0)
,m_theta(0.0)
,m_phi(0.0)
,m_eTrackingMode(TM_NONE)
,m_uiDisplayAxis(0)
,m_viewType(1)
,m_simulationStatus(0)
,m_CamSim(NULL)
,m_clGenObj(NULL)
,m_stlObj(NULL)
,m_isViewMaterial(true)
,m_isViewTool(true)
,m_isViewToolPath(true)
{
	// TODO: add construction code here
	m_f3RenderingCenter[0]		= 0.0;
	m_f3RenderingCenter[1]		= 0.0;
	m_f3RenderingCenter[2]		= 0.0;
	for(int i=1;i<7;i++)
	{
		m_aLightSetting[i].m_bLightEnabled = false;
		//m_aLightSetting[i].m_f4LightPosition
		m_aLightSetting[i].m_f4LightDiffuse[0] = 1.0f;
		m_aLightSetting[i].m_f4LightDiffuse[1] = 1.0f;
		m_aLightSetting[i].m_f4LightDiffuse[2] = 1.0f;
		m_aLightSetting[i].m_f4LightSpecular[0] = 0.2f;
		m_aLightSetting[i].m_f4LightSpecular[1] = 0.2f;
		m_aLightSetting[i].m_f4LightSpecular[2] = 0.2f;
	}

	m_aLightSetting[0].m_bLightEnabled = true;

	m_aLightSetting[0].m_f4LightPosition[0]=0.0f;
	m_aLightSetting[0].m_f4LightPosition[1]=0.0f;
	m_aLightSetting[0].m_f4LightPosition[2]=1.0f;
	m_aLightSetting[0].m_f4LightPosition[3]=0.0f;

	m_aLightSetting[1].m_f4LightPosition[0]=0.0f;
	m_aLightSetting[1].m_f4LightPosition[1]=0.0f;
	m_aLightSetting[1].m_f4LightPosition[2]=-1.0f;
	m_aLightSetting[1].m_f4LightPosition[3]=0.0f;

	m_aLightSetting[2].m_f4LightPosition[0]=0.0f;
	m_aLightSetting[2].m_f4LightPosition[1]=-1.0f;
	m_aLightSetting[2].m_f4LightPosition[2]=0.0f;
	m_aLightSetting[2].m_f4LightPosition[3]=0.0f;

	m_aLightSetting[3].m_f4LightPosition[0]=0.0f;
	m_aLightSetting[3].m_f4LightPosition[1]=1.0f;
	m_aLightSetting[3].m_f4LightPosition[2]=0.0f;
	m_aLightSetting[3].m_f4LightPosition[3]=0.0f;

	m_aLightSetting[4].m_f4LightPosition[0]=1.0f;
	m_aLightSetting[4].m_f4LightPosition[1]=0.0f;
	m_aLightSetting[4].m_f4LightPosition[2]=0.0f;
	m_aLightSetting[4].m_f4LightPosition[3]=0.0f;

	m_objectXform[0][0] = 1.0f; m_objectXform[0][1] = 0.0f; m_objectXform[0][2] = 0.0f; m_objectXform[0][3] = 0.0f;
	m_objectXform[1][0] = 0.0f; m_objectXform[1][1] = 1.0f; m_objectXform[1][2] = 0.0f; m_objectXform[1][3] = 0.0f;
	m_objectXform[2][0] = 0.0f; m_objectXform[2][1] = 0.0f; m_objectXform[2][2] = 1.0f; m_objectXform[2][3] = 0.0f;
	m_objectXform[3][0] = 0.0f; m_objectXform[3][1] = 0.0f; m_objectXform[3][2] = 0.0f; m_objectXform[3][3] = 1.0f;
	
	m_objectColor[0] = 0.5;
	m_objectColor[1] = 0.5;
	m_objectColor[2] = 1.0;

	m_backgrColor[0] = 0.3;
	m_backgrColor[1] = 0.5;
	m_backgrColor[2] = 0.8;

	m_bkrTop[0] = 0.6;
	m_bkrTop[1] = 0.8;
	m_bkrTop[2] = 0.9;
	m_bkrBottom[0] = 0.4;
	m_bkrBottom[1] = 0.2;
	m_bkrBottom[2] = 0.6;

   m_ov.v[0] = 0.0;
   m_ov.v[1] = 0.0;
   m_ov.v[2] = 0.0;
   m_size[0] = 1.0;
   m_size[1] = 1.0;
   m_size[2] = 1.0;

}

CIM3DEditorView::~CIM3DEditorView()
{
	if(m_uiDisplayAxis){
		::glDeleteLists(m_uiDisplayAxis,1);
		m_uiDisplayAxis = 0;
	}
   if(m_pDC){
      delete m_pDC;
      m_pDC = NULL;
   }
   if(m_stlObj){
	   delete m_stlObj;
	   m_stlObj = 0;
   }
}

BOOL CIM3DEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CIM3DEditorView drawing

void CIM3DEditorView::OnDraw(CDC* /*pDC*/)
{
	CIM3DEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	if( !m_pDC )
	{
		return;
	}
	::wglMakeCurrent( m_pDC->GetSafeHdc(), m_hRC );

	::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  enableAntialias();
	::glPushMatrix();
	renderStockScene();// Draw the coordinate axis system		
	::glPopMatrix();
  disableAntialias();

  // Render Object
  renderObject();
  
	::SwapBuffers( m_pDC->GetSafeHdc() );
}


// CIM3DEditorView printing

BOOL CIM3DEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CIM3DEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CIM3DEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CIM3DEditorView diagnostics

#ifdef _DEBUG
void CIM3DEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CIM3DEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIM3DEditorDoc* CIM3DEditorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIM3DEditorDoc)));
	return (CIM3DEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CIM3DEditorView message handlers

void CIM3DEditorView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if( 0 >= cx || 0 >= cy )
	{
		return;
	}

	if( NULL == m_hRC )
	{
		InitializeOpenGL();	
	}

	if( NULL != m_hRC )
	{
		m_cx = cx;
		m_cy = cy;
		::glViewport(0,0,m_cx, m_cy );
//::glEnable(GL_DEPTH_TEST);
//::glEnable(GL_CULL_FACE);

		::glMatrixMode( GL_PROJECTION );
		::glLoadIdentity();
		setupViewingFrustum();
		::glMatrixMode( GL_MODELVIEW );
		::glLoadIdentity();
		setupViewingTransform();

	}
}
HWND CIM3DEditorView::getHWnd(){ 
   if( !m_pWnd){
      
      m_pWnd = this->GetSafeHwnd(); 
   } 
   return m_pWnd;
}

bool CIM3DEditorView::InitializeOpenGL(void)
{

	m_pDC = new CClientDC( this );

	if( NULL == m_pDC )
	{
		ASSERT( !"m_pDC is NULL" );
		return false;
	}

	if( !setupPixelFormat() )
	{
		ASSERT( !"SetupPixelFormat failed" );
		return false;
	}


	if( 0 == ( m_hRC = ::wglCreateContext( m_pDC->GetSafeHdc() ) ) )
	{
		ASSERT( !"wglCreateContext failed" );
		return false;
	}

	if( TRUE != ::wglMakeCurrent( m_pDC->GetSafeHdc(), m_hRC ) )
	{
		ASSERT( !"wglMakeCurrent failed" );
		return false;
	}

	::glClearColor( m_backgrColor[0], m_backgrColor[1], m_backgrColor[2], 0 );

	::glClearDepth( 1.0f );

	::glEnable( GL_DEPTH_TEST );	
	//glEnable(GL_POLYGON_SMOOTH);
	//::glDepthFunc( GL_LEQUAL );
	return true;

}

bool CIM3DEditorView::setupViewingFrustum(void)
{
	::glOrtho(	- m_cx * 0.5 / m_fRenderingRate,	// left
		m_cx * 0.5 / m_fRenderingRate,	// right
		- m_cy * 0.5 / m_fRenderingRate,	// buttom
		m_cy * 0.5 / m_fRenderingRate,	// top
		-10000,			// near
		10000 );	
	return true;
}

void CIM3DEditorView::enableAntialias() {
  ::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  ::glEnable(GL_BLEND);
  ::glEnable(GL_POINT_SMOOTH);
  ::glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
  ::glEnable(GL_LINE_SMOOTH);
  ::glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  ::glEnable(GL_POLYGON_SMOOTH);
  ::glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
}

void CIM3DEditorView::disableAntialias() {
  ::glDisable(GL_BLEND);
  ::glDisable(GL_POINT_SMOOTH);
  ::glDisable(GL_LINE_SMOOTH);
  ::glDisable(GL_POLYGON_SMOOTH);
}

bool CIM3DEditorView::setupViewingTransform(void)
{

	::gluLookAt (	m_f3RenderingCenter[0] + 1.0,  m_f3RenderingCenter[1] , m_f3RenderingCenter[2] ,
		m_f3RenderingCenter[0],  m_f3RenderingCenter[1], m_f3RenderingCenter[2],		
		0.0,  0.0, 1.0 );
	::glTranslatef( (GLfloat)(- m_cx * 0.5 / m_fRenderingRate), 0.0, 0.0 );
	setupLight();
	::glRotatef( m_theta, 0.0f, 0.0f, 1.0f);
	GLfloat modelView[4][4];
	glGetFloatv(GL_MODELVIEW_MATRIX, modelView[0]);	
	GLfloat fX = modelView[0][0];
	GLfloat fY = modelView[1][0];
	GLfloat fZ = 0;
	::glRotatef( m_phi, fX, fY, fZ);
   setupMaterial();
	return true;

}

bool CIM3DEditorView::setupPixelFormat(void)
{

	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	int iPixelFormat;
	if( 0 == ( iPixelFormat = ::ChoosePixelFormat( m_pDC->GetSafeHdc(), &pfd ) ) )
	{
		ASSERT( !"ChoosePixelFormat is failed" );
		return FALSE;
	}

	if( TRUE != ::SetPixelFormat( m_pDC->GetSafeHdc(), iPixelFormat, &pfd ) )
	{
		ASSERT( !"SetPixelFormat is failed" );
		return FALSE;
	}

	return true;

}

bool CIM3DEditorView::setupLight(void)
{
	for( int nIndexLight = 0; nIndexLight < 5; nIndexLight++ )
	{
		if( m_aLightSetting[nIndexLight].m_bLightEnabled )
		{
			::glEnable(  GL_LIGHT0 + nIndexLight );
			::glLightfv( GL_LIGHT0 + nIndexLight, GL_POSITION,				m_aLightSetting[nIndexLight].m_f4LightPosition );
			::glLightfv( GL_LIGHT0 + nIndexLight, GL_AMBIENT,				m_aLightSetting[nIndexLight].m_f4LightAmbient );
			::glLightfv( GL_LIGHT0 + nIndexLight, GL_DIFFUSE,				m_aLightSetting[nIndexLight].m_f4LightDiffuse );
			::glLightfv( GL_LIGHT0 + nIndexLight, GL_SPECULAR,				m_aLightSetting[nIndexLight].m_f4LightSpecular );
			::glLightfv( GL_LIGHT0 + nIndexLight, GL_SPOT_DIRECTION,		m_aLightSetting[nIndexLight].m_f3LightSpotDirection );
			::glLightf(  GL_LIGHT0 + nIndexLight, GL_SPOT_EXPONENT,			m_aLightSetting[nIndexLight].m_fLightSpotExponent );
			::glLightf(  GL_LIGHT0 + nIndexLight, GL_SPOT_CUTOFF,			m_aLightSetting[nIndexLight].m_fLightSpotCutoff );
			::glLightf(  GL_LIGHT0 + nIndexLight, GL_CONSTANT_ATTENUATION,	m_aLightSetting[nIndexLight].m_fLightConstantAttenuation );
			::glLightf(  GL_LIGHT0 + nIndexLight, GL_LINEAR_ATTENUATION,	m_aLightSetting[nIndexLight].m_fLightLinearAttenuation );
			::glLightf(  GL_LIGHT0 + nIndexLight, GL_QUADRATIC_ATTENUATION,	m_aLightSetting[nIndexLight].m_fLightQuadraticAttenuation );
		}
		else
		{
			::glDisable( GL_LIGHT0 + nIndexLight );
		}
	}
	return true;
}

void CIM3DEditorView::setupPosLighting(int pos)
{
	if (m_aLightSetting[pos].m_bLightEnabled)
		m_aLightSetting[pos].m_bLightEnabled=false;
	else
		m_aLightSetting[pos].m_bLightEnabled=true;

	::glMatrixMode( GL_MODELVIEW );
	::glLoadIdentity();
	setupViewingTransform();
	Invalidate( FALSE );
}
void CIM3DEditorView::BeginTracking(CPoint point, ETRACKINGMODE eTrackingMode )
{
	SetCapture();
	m_eTrackingMode = eTrackingMode;
	switch( m_eTrackingMode )
	{
	case TM_NONE:
		break;
	case TM_SPIN:
		GLfloat	p[2];
		p[0] = (GLfloat)point.x;
		p[1] = (GLfloat)point.y;
		//ptov( p, m_f3LastPos, (GLfloat)m_cx, (GLfloat)m_cy );
		m_ptLast = point;
		break;
	case TM_PAN:
		m_ptLast = point;
		break;
	case TM_ZOOM:
		m_ptLast = point;
		break;
	default:
		break;
	}
}

void CIM3DEditorView::ptov( GLfloat p[2], GLfloat v[3], GLfloat fWidth, GLfloat fHeight )
{
	GLfloat d, a;
	//	v[0] = ( 2.0f * p[0]   - fWidth ) / fWidth;
	//	v[1] = ( fHeight - 2.0f * p[1]  ) / fHeight;
	v[0] = ( 2.0f * p[0]   - fWidth ) / fWidth * 0.5f;
	v[1] = ( fHeight - 2.0f * p[1]  ) / fHeight * 0.5f;
	d = (GLfloat)sqrt( v[0]*v[0] + v[1]*v[1] );
	v[2] = (GLfloat)cos( (M_PI/2.0f) * ( ( d < 1.0f ) ? d : 1.0f ) );

	a = 1.0f / (GLfloat)sqrt( v[0]*v[0] + v[1]*v[1] + v[2]*v[2] );
	v[0] *= a;
	v[1] *= a;
	v[2] *= a;
}

void CIM3DEditorView::EndTracking()
{
	ReleaseCapture();
	m_eTrackingMode = TM_NONE;
	Invalidate();
}

void CIM3DEditorView::DoTracking( CPoint point )
{

	bool isUpdateView = FALSE;
	switch( m_eTrackingMode )
	{
	case TM_NONE:
		break;
	case TM_SPIN:
		RotateScene(point);
		m_ptLast = point;
		break;
	case TM_PAN:
		MovingScene(point);
		m_ptLast = point;
		break;
	case TM_ZOOM:
		ZoomScene(point);	
		m_ptLast = point;
		break;
	default:
		ASSERT( !"–¢‘Î‰ž" );
		break;
	}
	if(isUpdateView){
		Invalidate();
	}
}
void CIM3DEditorView::DoRotation( float fAngle, float fX, float fY, float fZ )
{
	::glPushMatrix();
	::glLoadIdentity();
	::glRotatef( fAngle, fX, fY, fZ);
	::glMultMatrixf( (GLfloat*) m_objectXform );
	::glGetFloatv( GL_MODELVIEW_MATRIX, (GLfloat*)m_objectXform );
	::glPopMatrix();

	::glMatrixMode( GL_MODELVIEW );
	::glLoadIdentity();
	setupViewingTransform();

}

/*
@Description
Rotate the scence due to the movement of the mouse
@input
point: the window coordinate of left mouse
@output
rotate angle: m_theta or m_phi
update the view
@used global variables:
Read/Write: m_theta, m_phi, m_ptLast

*/
void CIM3DEditorView::RotateScene( CPoint point)
{
	/*GLfloat	p[2];
	p[0] = (GLfloat)point.x;
	p[1] = (GLfloat)point.y;
	GLfloat f3CurPos[3];
	ptov( p, f3CurPos, (GLfloat)m_cx, (GLfloat)m_cy );
	GLfloat dx = f3CurPos[0] - m_f3LastPos[0];
	GLfloat dy = f3CurPos[1] - m_f3LastPos[1];
	GLfloat dz = f3CurPos[2] - m_f3LastPos[2];
	float fAngle = 180.0f * (GLfloat)sqrt(dx*dx + dy*dy + dz *dz );
	float fX = m_f3LastPos[1]*f3CurPos[2] - m_f3LastPos[2]*f3CurPos[1];
	float fY = m_f3LastPos[2]*f3CurPos[0] - m_f3LastPos[0]*f3CurPos[2];
	float fZ = m_f3LastPos[0]*f3CurPos[1] - m_f3LastPos[1]*f3CurPos[0];*/

   float fX,fY,fZ,fAngle;
	GLfloat modelView[4][4];

	glGetFloatv(GL_MODELVIEW_MATRIX, modelView[0]);

	int ix = point.x - m_ptLast.x;
	int iy = point.y - m_ptLast.y;

	if(abs(ix) > abs(iy)){
		if(ix < 0){
			fZ = 1;
		}
		else{
			fZ = 1;
		}
		fX = fY = 0;
		fAngle = ix * 180.0f / m_cx;
		m_theta += fAngle;
		for(;m_theta > 180; m_theta -= 360);
		for(;m_theta < -180; m_theta += 360);					
	}
	else{
		fAngle = iy * 180.0f / m_cy;
		if(iy > 0){
			fX = modelView[0][0];
			fY = modelView[1][0];
			fZ = 0;
		}
		else{
			fX = -modelView[0][0];
			fY = -modelView[1][0];
			fZ = 0;

		}
		m_phi += fAngle;
		if(m_phi > 360)  m_phi -= 360;
		if(m_phi < -360)  m_phi += 360;
	}
	::glMatrixMode( GL_MODELVIEW );
	::glLoadIdentity();
	setupViewingTransform();
	Invalidate( FALSE );
/*
	m_f3LastPos[0] = f3CurPos[0];
	m_f3LastPos[1] = f3CurPos[1];
	m_f3LastPos[2] = f3CurPos[2];	*/
}

/*
@Description
Move the scence due to mouse movement
@input
point: the window coordinate of the mouse
@output
Change the coordinates of rendering center: m_f3RenderingCenter
@used global variables:
Read/Write: m_f3RenderingCenter
*/
void CIM3DEditorView::MovingScene( CPoint point)
{
	::glBegin(GL_LINES);
	glColor3f(0.5,0.5,0);
	glVertex3f(0,0,0);
	glVertex3f(50,50,50);
	::glEnd();
	m_f3RenderingCenter[1] -= ( point.x - m_ptLast.x ) / m_fRenderingRate;
	m_f3RenderingCenter[2] += ( point.y - m_ptLast.y ) / m_fRenderingRate;

	::glMatrixMode( GL_MODELVIEW );
	::glLoadIdentity();
	setupViewingTransform();
	Invalidate( FALSE );
}


/*
@Description
zoom the scence due to mouse wheel
@input
point: show the movement of mouse wheel
@output
Change the rendering rate: m_fRenderingRate
@used global variables:
Read/Write: m_fRenderingRate
*/
void CIM3DEditorView::ZoomScene(CPoint point)
{
	m_fRenderingRate *= (float)pow( 2, ( m_ptLast.y - point.y ) * 0.002f );
	::glMatrixMode( GL_PROJECTION );
	::glLoadIdentity();
	setupViewingFrustum();
	::glMatrixMode( GL_MODELVIEW );
	Invalidate( FALSE );

}
void CIM3DEditorView::renderStockScene()
{
	if( 0 == m_uiDisplayAxis )
	{	
		/*m_uiDisplayAxis = ::glGenLists(1);
		if( 0 == m_uiDisplayAxis )
		{
			return;
		}

		::glNewList( m_uiDisplayAxis, GL_COMPILE );*/

		renderAxis();
		//::glEndList();
	}

	if( 0 != m_uiDisplayAxis )
	{
		renderBackground();
		::glCallList( m_uiDisplayAxis );
	}
}

void CIM3DEditorView::renderBackground()
{

	GLfloat rate = m_fRenderingRate;
	::glPushMatrix();
	::glLoadIdentity();
	::glDisable(GL_LIGHTING);
	::glDisable(GL_DEPTH_TEST);
	::glBegin(GL_QUADS);
	::glColor3fv(m_bkrTop);
	::glVertex3f( m_cx * 0.5 / rate,m_cy * 0.5 / rate,10.0f);
	::glVertex3f(- m_cx * 0.5 / rate,m_cy * 0.5 / rate,10.0f);
	::glColor3fv(m_bkrBottom);
	::glVertex3f( -m_cx * 0.5 / rate,-m_cy * 0.5 / rate,10.0f);
	::glVertex3f( m_cx * 0.5 / rate,-m_cy * 0.5 / rate,10.0f);
	::glEnd();
	::glPopMatrix();
	::glEnable(GL_DEPTH_TEST);
}


void CIM3DEditorView::renderAxis()
{
	//renderBackground();
	float	points[4][3];
	points[0][0] = 0.0;
	points[0][1] = 0.0;
	points[0][2] = 0.0;
	points[1][0] = 40/m_fRenderingRate;
	points[1][1] = 0.0;
	points[1][2] = 0.0;
	points[2][0] = 0.0;
	points[2][1] = 80/m_fRenderingRate;
	points[2][2] = 0.0;
	points[3][0] = 0.0;
	points[3][1] = 0.0;
	points[3][2] = 160/m_fRenderingRate;

	::glDisable(GL_LIGHTING);
	::glPushAttrib( GL_CURRENT_BIT | GL_LINE_BIT );	
	::glLineWidth( 2.0 );
	glBegin( GL_LINES );
	::glColor3ub( 255, 0, 0 );
	::glVertex3fv( points[0] );
	::glVertex3fv( points[1] );
	::glColor3ub( 0, 255, 0 );
	::glVertex3fv( points[0] );
	::glVertex3fv( points[2] );
	::glColor3ub( 0, 0, 255 );
	::glVertex3fv( points[0] );
	::glVertex3fv( points[3] );
	::glEnd();
	::glPopAttrib();
	::glEnable(GL_LIGHTING);

}
void CIM3DEditorView::renderObject()
{
   // render object
   if(m_isViewMaterial && m_CamSim){
     ::glPushMatrix();
     //enableAntialias();
     m_CamSim->drawWork(m_viewType);
    // disableAntialias();
     ::glPopMatrix();
   }

  // render tool
   if(m_isViewTool && m_CamSim){
     ::glPushMatrix();
     m_CamSim->drawTool();
     ::glPopMatrix();
   }
  //render cl tool path
   if(m_isViewToolPath && m_CamSim){
        ::glPushMatrix();
        enableAntialias();
        m_CamSim->drawToolPath();
        disableAntialias();
        ::glPopMatrix();
     }
   // render cl gen cl
   if(m_clGenObj){
	   ::glPushMatrix();
	   m_clGenObj->drawCL();
	   ::glPopMatrix();
   }
   // render clGen cad model
   if(m_clGenObj){
	   ::glPushMatrix();
	   m_clGenObj->drawCadModel();
	   ::glPopMatrix();
   }
   // render cutting segment
   if(m_clGenObj){
	   ::glPushMatrix();
	   m_clGenObj->drawCuttingSegment();
	   ::glPopMatrix();
   }

   // render cell model
    if(m_clGenObj){
	   ::glPushMatrix();
	  // m_clGenObj->drawModel();
	   ::glPopMatrix();
   }

	// render stl proj
	if(m_isViewMaterial && m_stlObj){
		::glPushMatrix();
		m_stlObj->draw(m_viewType);
	   ::glPopMatrix();
	}
}


void CIM3DEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	BeginTracking( point, TM_SPIN );

	CView::OnLButtonDown(nFlags, point);
}

void CIM3DEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	EndTracking();

	Invalidate();

	CView::OnLButtonUp(nFlags, point);
}

void CIM3DEditorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	DoTracking( point );

	Invalidate();

	CView::OnMouseMove(nFlags, point);
}

BOOL CIM3DEditorView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default

	BeginTracking( pt, TM_ZOOM );
	
	CPoint	pt_delta( pt.x - zDelta / 3, pt.y - zDelta / 3 );
	DoTracking( pt_delta );

	EndTracking();

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CIM3DEditorView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	BeginTracking( point, TM_PAN );

	CView::OnRButtonDown(nFlags, point);
}

void CIM3DEditorView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	EndTracking();

	CView::OnRButtonUp(nFlags, point);
}

BOOL CIM3DEditorView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
return true;

	//return CView::OnEraseBkgnd(pDC);
}

void CIM3DEditorView::OnLighting(UINT nID)
{
	setupPosLighting(nID-IDR_TOOLBAR_LIGHTING_TOP);
}
void CIM3DEditorView::OnUpdateLighting(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_aLightSetting[pCmdUI->m_nID-IDR_TOOLBAR_LIGHTING_TOP].m_bLightEnabled==true?1:0);
}

void CIM3DEditorView::OnDisplayStyleWire()
{
	m_viewType = 0;
	Invalidate( FALSE );
}
void CIM3DEditorView::OnDisplayStyleSolid()
{
	m_viewType = 1;
	Invalidate( FALSE );
}
void CIM3DEditorView::OnDisplayStyleSolidWire()
{
	m_viewType = 2;
	Invalidate( FALSE );
}

void CIM3DEditorView::OnViewTop()
{
	
	m_phi = 90.0;
	m_theta = 0.0;
	::glMatrixMode( GL_MODELVIEW );
	::glLoadIdentity();
	setupViewingTransform();
   fitToScreenSize(2);
	moveToCenterScreen();
	Invalidate( FALSE );
}

void CIM3DEditorView::OnViewBottom()
{
	
	m_phi = -90.0;
	m_theta = 0.0;
	::glMatrixMode( GL_MODELVIEW );
	::glLoadIdentity();
	setupViewingTransform();
   fitToScreenSize(2);
	moveToCenterScreen();
	Invalidate( FALSE );
}

void CIM3DEditorView::OnViewLeft()
{
	
	m_phi = 0.0;
	m_theta = 90.0;
	::glMatrixMode( GL_MODELVIEW );
	::glLoadIdentity();
	setupViewingTransform();
   fitToScreenSize(1);
	moveToCenterScreen();
	Invalidate( FALSE );
}
void CIM3DEditorView::OnViewRight()
{
	
	m_phi = 0.0;
	m_theta = -90.0;
	::glMatrixMode( GL_MODELVIEW );
	::glLoadIdentity();
	setupViewingTransform();
   fitToScreenSize(1);
	moveToCenterScreen();
	Invalidate( FALSE );
}
void CIM3DEditorView::OnViewFront()
{
	
	m_phi = 0.0;
	m_theta = 0.0;
	::glMatrixMode( GL_MODELVIEW );
	::glLoadIdentity();
	setupViewingTransform();
   fitToScreenSize(0);
	moveToCenterScreen();
	Invalidate( FALSE );
}
void CIM3DEditorView::OnViewBack()
{
	
	m_phi = 0.0;
	m_theta = -180.0;
	::glMatrixMode( GL_MODELVIEW );
	::glLoadIdentity();
	setupViewingTransform();
   fitToScreenSize(0);
	moveToCenterScreen();
	Invalidate( FALSE );
}
void CIM3DEditorView::OnViewIsometric()
{
	
	m_phi = 45.0;
	m_theta = -45.0;
	::glMatrixMode( GL_MODELVIEW );
	::glLoadIdentity();
	setupViewingTransform();
   fitToScreenSize(3);
	moveToCenterScreen();
	Invalidate( FALSE );
}
void CIM3DEditorView::moveToCenterScreen()
{
	m_ptLast.x = 0;
	m_ptLast.y = 0;
	m_f3RenderingCenter[0] = 0;
	m_f3RenderingCenter[1] = 0;
	m_f3RenderingCenter[2] = 0;
	CPoint point;
	double center[3];
	center[0] = m_ov.v[0] + m_size.v[0]/2;
	center[1] = m_ov.v[1] + m_size.v[1]/2;
	center[2] = m_ov.v[2] + m_size.v[2]/2;
	double cen[2];
#if 0
	double phi = m_phi*M_PI/180;
	double theta = m_theta*M_PI/180;
	cen[0] = center[0]*sin(theta)*cos(phi) + center[1]*cos(theta) + center[2]*sin(phi)*sin(theta);
	cen[1] = -center[0]*sin(phi) +  center[2]*cos(phi);
#else
	GLfloat modelView[4][4];
	glGetFloatv(GL_MODELVIEW_MATRIX, modelView[0]);
	cen[0] = center[0]*modelView[0][0] + center[1]*modelView[1][0] + center[2]*modelView[2][0];
	cen[1] = center[0]*modelView[0][1] + center[1]*modelView[1][1] + center[2]*modelView[2][1];
#endif
	point.x =  -cen[0]*m_fRenderingRate;
	point.y = cen[1]*m_fRenderingRate;
	MovingScene(point);
	Invalidate( FALSE );
}

void CIM3DEditorView::fitToScreenSize(int axis)
{
   CRect lpRect1;
	GetClientRect(&lpRect1);
	double maxleng;
   if(0 == axis){
      maxleng = sqrt(m_size.v[1]*m_size.v[1] + m_size.v[2]*m_size.v[2]);
   }
   else if(1 == axis){
      maxleng = sqrt(m_size.v[0]*m_size.v[0] + m_size.v[2]*m_size.v[2]);
   }
   else if(2 == axis){
      maxleng = sqrt(m_size.v[0]*m_size.v[0] + m_size.v[1]*m_size.v[1]);
   }
   else{
      maxleng = sqrt(m_size.v[0]*m_size.v[0] + m_size.v[1]*m_size.v[1] + m_size.v[2]*m_size.v[2]);
   }
	maxleng = max(maxleng,40);
	double scale1 = lpRect1.right/maxleng;
	double scale2 = lpRect1.bottom/maxleng;
	
	m_fRenderingRate = min(scale1,scale2);
	::glMatrixMode( GL_PROJECTION );
	::glLoadIdentity();
	setupViewingFrustum();
	::glMatrixMode( GL_MODELVIEW );

}
void CIM3DEditorView::updateBoundingBox(double *ov, double *lv)
{
   for(int i = 0; i < 3;++i){
      if(ov[i] < m_ov.v[i]){
         m_ov.v[i] = ov[i];
      }
      if(lv[i] > m_size.v[i]){
         m_size.v[i] = lv[i];
      }
   }
}

void CIM3DEditorView::setupMaterial()
{
   float	MatAmbient[]  = {0.25,0.20725,	0.20725,0.922};
	float	MatDiffuse[]  = {1.0,0.829,	0.829,	0.922};
	float	MatSpecular[]  = {0.296648,	0.296648,0.296648,0.922};
	float	MatShininess  =  11.264 ;
	float	MatEmission[]  = {0.0f, 0.0f, 0.0f, 0.0f};
	float MatAmbientBack[]  = {0.0f, 0.5f, 1.0f, 0.0f}; // green material behind
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,MatAmbient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,MatDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,MatSpecular);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,MatShininess);
}

void CIM3DEditorView::OnEditViewClear()
{
   g_Store.clearAllObject();
   Invalidate();
}

void CIM3DEditorView::OnStopSimulation()
{
   m_simulationStatus = 0;
   if(m_CamSim){
      m_CamSim->stopSimulation();
   }
}

void CIM3DEditorView::OnStartSimulation()
{
   if(0 == m_simulationStatus){
      m_simulationStatus = 1;
      if(m_CamSim){
         m_CamSim->startSimulation();
      }
   }
   else if(1 == m_simulationStatus){
      m_simulationStatus = 2;
      if(m_CamSim){
         m_CamSim->pauseSimulation();
      }

   }
   else{
      m_simulationStatus = 1;
      if(m_CamSim){
         m_CamSim->resumeSimulation();
      }
   }
}

void CIM3DEditorView::OnUpdateStopSimulation(CCmdUI* pCmdUI)
{
   if(1 == m_simulationStatus || 2 == m_simulationStatus){
      pCmdUI->SetCheck(0);
   }
   else{
      pCmdUI->SetCheck(1);
   }
}

void CIM3DEditorView::OnUpdateStartSimulation(CCmdUI* pCmdUI)
{
   if(0 == m_simulationStatus){
     // pCmdUI->SetCheck(0);
      // change icon to start
      CMainFrame *pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
      pFrame->updateSimulationBarIcon(1);
      pCmdUI->SetCheck(0);
   }
   else if(1 == m_simulationStatus){
      
      // change icon to start
      CMainFrame *pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
      pFrame->updateSimulationBarIcon(2);
      pCmdUI->SetCheck(1);
   }
   else{
    //  pCmdUI->SetCheck(1);
      //change icon to pause
      CMainFrame *pFrame = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
      pFrame->updateSimulationBarIcon(1);
      pCmdUI->SetCheck(1);
   }
}

void CIM3DEditorView::OnFemDelaunaymesh()
{
   // TODO: Add your command handler code here
   g_Store.splitMesh();
   Invalidate();
}

void CIM3DEditorView::OnViewSimulationMaterial()
{
   // TODO: Add your command handler code here
   m_isViewMaterial = !m_isViewMaterial;
}

void CIM3DEditorView::OnUpdateViewSimulationMaterial(CCmdUI *pCmdUI)
{
   // TODO: Add your command update UI handler code here
   pCmdUI->SetCheck(m_isViewMaterial);
}

void CIM3DEditorView::OnViewSimulationTool()
{
   // TODO: Add your command handler code here
   m_isViewTool = !m_isViewTool;
}

void CIM3DEditorView::OnUpdateViewSimulationTool(CCmdUI *pCmdUI)
{
   // TODO: Add your command update UI handler code here
   pCmdUI->SetCheck(m_isViewTool);
}

void CIM3DEditorView::OnViewSimulationToolpath()
{
   // TODO: Add your command handler code here
   m_isViewToolPath = !m_isViewToolPath;
}

void CIM3DEditorView::OnUpdateViewSimulationToolpath(CCmdUI *pCmdUI)
{
   // TODO: Add your command update UI handler code here
   pCmdUI->SetCheck(m_isViewToolPath);
}

LRESULT CIM3DEditorView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
   // TODO: Add your specialized code here and/or call the base class

   switch(message){
      case IM3DEDITOR_SIMULATION_UPDATEVIEW:
         {
            Invalidate();
            break;
         }
      default:
         {
            break;
         }
   }
   return CView::WindowProc(message, wParam, lParam);
}


