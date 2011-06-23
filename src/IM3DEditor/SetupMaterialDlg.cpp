// SetupMaterialDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IM3DEditor.h"
#include "SetupMaterialDlg.h"


// SetupMaterialDlg dialog

IMPLEMENT_DYNAMIC(SetupMaterialDlg, CDialog)

SetupMaterialDlg::SetupMaterialDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SetupMaterialDlg::IDD, pParent)
   , m_oy(0)
   , m_oz(0)
   , m_sx(0)
   , m_sy(0)
   , m_sz(0)
   , m_ox(0)
{

}

SetupMaterialDlg::~SetupMaterialDlg()
{
}

void SetupMaterialDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Text(pDX, IDC_EDIT_SETUP_MATERIAL_OY, m_oy);
   DDX_Text(pDX, IDC_EDIT_SETUP_MATERIAL_OZ, m_oz);
   DDX_Text(pDX, IDC_EDIT_SETUP_MATERIAL_SX, m_sx);
   DDX_Text(pDX, IDC_EDIT_SETUP_MATERIAL_SY, m_sy);
   DDX_Text(pDX, IDC_EDIT_SETUP_MATERIAL_SZ, m_sz);
   DDX_Text(pDX, IDC_EDIT_SETUP_MATERIAL_OX, m_ox);
}


BEGIN_MESSAGE_MAP(SetupMaterialDlg, CDialog)
END_MESSAGE_MAP()


// SetupMaterialDlg message handlers
