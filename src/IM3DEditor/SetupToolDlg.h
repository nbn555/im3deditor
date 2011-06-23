#pragma once
#include "afxwin.h"
#include "ColorBox.h"

// SetupToolDlg dialog

class SetupToolDlg : public CDialog
{
	DECLARE_DYNAMIC(SetupToolDlg)

public:
	SetupToolDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~SetupToolDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_SETUP_TOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
   double m_diameter;
public:
   double m_height;
public:
   double m_cuttingH;
public:
   double m_filletR;
public:
   CEdit m_filletR_Ctrl;
public:
   int m_toolType;
public:
   COLORREF m_cuttingColor;
   float m_colorf[3];
public:
   afx_msg void OnStnClickedSetupToolStaticCuttingcolor();
public:
   CColorBox m_cuttingColorCtrl;
public:
   virtual BOOL OnInitDialog();
public:
   afx_msg void OnBnClickedSetuptoolRadioBall();
public:
   afx_msg void OnBnClickedSetuptoolRadioFlat();
public:
   afx_msg void OnBnClickedSetuptoolRadioFillet();
};
