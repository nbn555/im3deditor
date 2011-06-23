// IM3DEditorDoc.cpp : implementation of the CIM3DEditorDoc class
//

#include "stdafx.h"
#include "IM3DEditor.h"

#include "IM3DEditorDoc.h"
#include "objStore.h"
#include <string>
#include "IM3DEditorView.h"
#include "CAMSim.h"
#include "SetupMaterialDlg.h"
#include "SetupToolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIM3DEditorDoc

IMPLEMENT_DYNCREATE(CIM3DEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CIM3DEditorDoc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, &CIM3DEditorDoc::OnFileOpen)

   //Setup Simulation
   ON_COMMAND(ID_SETUP_SIMULATION_MATERIAL, &CIM3DEditorDoc::OnSetupMaterial)
   ON_COMMAND(ID_SETUP_SIMULATION_TOOL, &CIM3DEditorDoc::OnSetupTool)

END_MESSAGE_MAP()


// CIM3DEditorDoc construction/destruction

CIM3DEditorDoc::CIM3DEditorDoc():
m_CamSim(NULL)
,m_pView(NULL)
{
	// TODO: add one-time construction code here

}

CIM3DEditorDoc::~CIM3DEditorDoc()
{
   if(m_CamSim){
      delete m_CamSim;
      m_CamSim = NULL;
   }
}

BOOL CIM3DEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CIM3DEditorDoc serialization

void CIM3DEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CIM3DEditorDoc diagnostics

#ifdef _DEBUG
void CIM3DEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CIM3DEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CIM3DEditorDoc commands

void CIM3DEditorDoc::OnFileOpen()
{
	// TODO: Add your command handler code here
	CFileDialog filedlg(TRUE,NULL,NULL,OFN_OVERWRITEPROMPT,
		_T("CL Data(*.cl|*.cl|STL Data(*.stl)|*.stl|"));
	INT_PTR iret = filedlg.DoModal();
	if (IDOK==iret)
	{
      if(NULL == m_pView){
         CFrameWnd *pFrame = static_cast<CFrameWnd *> (AfxGetMainWnd());
         m_pView = static_cast<CIM3DEditorView *> (pFrame->GetActiveView());
         ASSERT(m_pView != NULL); // SDI should have one
      }

		CString fileName = filedlg.GetFileName();
		std::string ss = std::string(CT2CA(fileName));
		const char *cc = ss.c_str();      
      CString fileExt = filedlg.GetFileExt();
      if(0 == fileExt.CompareNoCase(_T("stl"))){
		   int ind = g_Store.createAnObjectFromStl(cc);
         if(ind >= 0){
            double ov[3],lv[3];
            g_Store.getBoundingBoxOfObject(ind,ov,lv);
            m_pView->updateBoundingBox(ov,lv);
            m_pView-> fitToScreenSize(3);
	         m_pView->moveToCenterScreen();
         }
      }
      else if(0 == fileExt.CompareNoCase(_T("cl"))){
         if(NULL == m_CamSim){
            m_CamSim = new ImCAMSim();
            m_CamSim->setViewhandle(m_pView->getHWnd());
            if(NULL == m_pView->getCAMSim()){
               m_pView->setCAMSim(m_CamSim);
            }
         }
         m_CamSim->readClData(cc);
         double maxc[3],minc[3],lv[3];
         
         m_CamSim->getBoundingBox(minc,maxc);
         lv[0] = maxc[0] - minc[0];
         lv[1] = maxc[1] - minc[1];
         lv[2] = maxc[2] - minc[2];
         m_pView->updateBoundingBox(minc,lv);
      }
      m_pView->fitToScreenSize();
      m_pView->Invalidate( );
	}
}



void CIM3DEditorDoc::OnSetupMaterial()
{
   if(NULL == m_pView){
      CFrameWnd *pFrame = static_cast<CFrameWnd *> (AfxGetMainWnd());
      m_pView = static_cast<CIM3DEditorView *> (pFrame->GetActiveView());
      ASSERT(m_pView != NULL); // SDI should have one
   }
   SetupMaterialDlg wDlg;
   if(m_CamSim){
      double maxc[3],minc[3];
      m_CamSim->getBoundingBox(minc,maxc);
      wDlg.m_ox = minc[0];
      wDlg.m_oy = minc[1];
      wDlg.m_oz = minc[2];
      wDlg.m_sx = maxc[0] - minc[0];
      wDlg.m_sy = maxc[1] - minc[1];
      wDlg.m_sz = maxc[2] - minc[2];
   }
   if(IDOK == wDlg.DoModal()){
      double ov[3],lv[3];
      ov[0] = wDlg.m_ox;
      ov[1] = wDlg.m_oy;
      ov[2] = wDlg.m_oz;
      lv[0] = wDlg.m_sx;
      lv[1] = wDlg.m_sy;
      lv[2] = wDlg.m_sz;
      int id = g_Store.createSimWorkWithMakeWall(ov,lv);
      if(m_CamSim){
         m_CamSim->setCurrentID(id);
      }
      m_pView->updateBoundingBox(ov,lv);
      m_pView->Invalidate();
   }
}

void CIM3DEditorDoc::OnSetupTool()
{
   SetupToolDlg toolDlg;
   if(IDOK == toolDlg.DoModal()){
      int type = toolDlg.m_toolType;
      float cuttingcolor[3];
      cuttingcolor[0] = toolDlg.m_colorf[0];
      g_Store.createBallTool(0,1,toolDlg.m_diameter/2.0,toolDlg.m_height,toolDlg.m_cuttingH);
   }
}