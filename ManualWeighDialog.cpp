// ManualWeighDialog.cpp : implementation file
//

#include "stdafx.h"
#include "wbc.h"
#include "ManualWeighDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ManualWeighDialog dialog


ManualWeighDialog::ManualWeighDialog(CWnd* pParent /*=NULL*/)
	: CDialog(ManualWeighDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(ManualWeighDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ManualWeighDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ManualWeighDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ManualWeighDialog, CDialog)
	//{{AFX_MSG_MAP(ManualWeighDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ManualWeighDialog message handlers

//确定
void ManualWeighDialog::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

//取消
void ManualWeighDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
