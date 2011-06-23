// SetupToolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IM3DEditor.h"
#include "SetupToolDlg.h"


// SetupToolDlg dialog

IMPLEMENT_DYNAMIC(SetupToolDlg, CDialog)

SetupToolDlg::SetupToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SetupToolDlg::IDD, pParent)
   , m_diameter(10)
   , m_height(80)
   , m_cuttingH(50)
   , m_filletR(0)
   , m_toolType(0)
{
   m_cuttingColor = RGB(210,168,23);
}

SetupToolDlg::~SetupToolDlg()
{
}

void SetupToolDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Text(pDX, IDC_SETUPTOOL_EDIT_DIAMETER, m_diameter);
   DDX_Text(pDX, IDC_SETUPTOOL_EDIT_HEIGHT, m_height);
   DDX_Text(pDX, IDC_SETUPTOOL_EDIT_CUTTING_H, m_cuttingH);
   DDX_Text(pDX, IDC_SETUPTOOL_EDIT_FILLET_R, m_filletR);
   DDX_Control(pDX, IDC_SETUPTOOL_EDIT_FILLET_R, m_filletR_Ctrl);
   DDX_Radio(pDX, IDC_SETUPTOOL_RADIO_BALL, m_toolType);
   //DDX_Text(pDX, IDC_SETUP_TOOL_STATIC_CUTTINGCOLOR, m_cuttingColor);
   DDX_Control(pDX, IDC_SETUP_TOOL_STATIC_CUTTINGCOLOR, m_cuttingColorCtrl);
}


BEGIN_MESSAGE_MAP(SetupToolDlg, CDialog)
   ON_STN_CLICKED(IDC_SETUP_TOOL_STATIC_CUTTINGCOLOR, &SetupToolDlg::OnStnClickedSetupToolStaticCuttingcolor)
   ON_BN_CLICKED(IDC_SETUPTOOL_RADIO_BALL, &SetupToolDlg::OnBnClickedSetuptoolRadioBall)
   ON_BN_CLICKED(IDC_SETUPTOOL_RADIO_FLAT, &SetupToolDlg::OnBnClickedSetuptoolRadioFlat)
   ON_BN_CLICKED(IDC_SETUPTOOL_RADIO_FILLET, &SetupToolDlg::OnBnClickedSetuptoolRadioFillet)
END_MESSAGE_MAP()


// SetupToolDlg message handlers

void SetupToolDlg::OnStnClickedSetupToolStaticCuttingcolor()
{
   // TODO: Add your control notification handler code here
   CColorDialog colorDlg;
   if(IDOK == colorDlg.DoModal()){
      m_cuttingColor = colorDlg.GetColor();
      m_cuttingColorCtrl.SetBackColor(m_cuttingColor);
      //SetBkColor( GetDlgItem(IDC_SETUP_TOOL_STATIC_CUTTINGCOLOR)->GetDC()->GetSafeHdc(),m_cuttingColor);
      BYTE red =  GetRValue(m_cuttingColor);
	   BYTE green =  GetGValue(m_cuttingColor);
	   BYTE blue =  GetBValue(m_cuttingColor);
	   m_colorf[0] = red/255.0;
	   m_colorf[1] = green/255.0;
	   m_colorf[2] = blue/255.0;
   }
}

BOOL SetupToolDlg::OnInitDialog()
{
   CDialog::OnInitDialog();

   // TODO:  Add extra initialization here
   m_cuttingColorCtrl.SetBackColor(m_cuttingColor);
   GetDlgItem(IDC_SETUPTOOL_EDIT_FILLET_R)->EnableWindow(FALSE);
   return TRUE;  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

void SetupToolDlg::OnBnClickedSetuptoolRadioBall()
{
   // TODO: Add your control notification handler code here
   GetDlgItem(IDC_SETUPTOOL_EDIT_FILLET_R)->EnableWindow(FALSE);
}

void SetupToolDlg::OnBnClickedSetuptoolRadioFlat()
{
   // TODO: Add your control notification handler code here
   GetDlgItem(IDC_SETUPTOOL_EDIT_FILLET_R)->EnableWindow(FALSE);
}

void SetupToolDlg::OnBnClickedSetuptoolRadioFillet()
{
   // TODO: Add your control notification handler code here
   GetDlgItem(IDC_SETUPTOOL_EDIT_FILLET_R)->EnableWindow(TRUE);
}
