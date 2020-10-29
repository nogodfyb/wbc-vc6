// CheckToolsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "wbc.h"
#include "CheckToolsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CheckToolsDlg dialog


CheckToolsDlg::CheckToolsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CheckToolsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CheckToolsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CheckToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CheckToolsDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CheckToolsDlg, CDialog)
	//{{AFX_MSG_MAP(CheckToolsDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CheckToolsDlg message handlers
