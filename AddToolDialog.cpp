// AddToolDialog.cpp : implementation file
//

#include "stdafx.h"
#include "wbc.h"
#include "AddToolDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AddToolDialog dialog


AddToolDialog::AddToolDialog(CWnd* pParent /*=NULL*/)
	: CDialog(AddToolDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(AddToolDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void AddToolDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AddToolDialog)
	DDX_Control(pDX, IDC_EDIT2, lifeEditCtr);
	DDX_Control(pDX, IDC_COMBO1, typeCbxCtr);
	DDX_Control(pDX, IDC_EDIT1, snEditCtr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AddToolDialog, CDialog)
	//{{AFX_MSG_MAP(AddToolDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AddToolDialog message handlers

void AddToolDialog::OnOK() //÷ÿ–¥ok
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void AddToolDialog::OnCancel() //÷ÿ–¥cancel
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
