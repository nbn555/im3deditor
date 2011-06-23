#pragma once


// SetupMaterialDlg dialog

class SetupMaterialDlg : public CDialog
{
	DECLARE_DYNAMIC(SetupMaterialDlg)

public:
	SetupMaterialDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~SetupMaterialDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_SETUP_MATERIAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
   double m_oy;
   double m_oz;
   double m_sx;
   double m_sy;
   double m_sz;
   double m_ox;
};
