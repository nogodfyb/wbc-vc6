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
	DDX_Control(pDX, CHECK_TOOLS_DLG_WS, waferSourceCtr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CheckToolsDlg, CDialog)
	//{{AFX_MSG_MAP(CheckToolsDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CheckToolsDlg message handlers

//初始化窗口
BOOL CheckToolsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	//初始化当前waferSource
	waferSourceCtr.SetWindowText(waferSource);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
