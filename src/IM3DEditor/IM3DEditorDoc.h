// IM3DEditorDoc.h : interface of the CIM3DEditorDoc class
//


#pragma once

class ImCAMSim;
class CIM3DEditorView;
class ClGenObject;
class CIM3DEditorDoc : public CDocument
{
protected: // create from serialization only
	CIM3DEditorDoc();
	DECLARE_DYNCREATE(CIM3DEditorDoc)

// Attributes
   ImCAMSim* m_CamSim;
   CIM3DEditorView* m_pView;
   ClGenObject *m_clGenObj;
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CIM3DEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();

   // Setup Simulation
   afx_msg void OnSetupMaterial();
   afx_msg void OnSetupTool();
   afx_msg void OnClgenLoadsolidmodel();
   afx_msg void OnClgenGeneratecl();
};


