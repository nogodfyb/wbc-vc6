// SettingDialog.cpp : implementation file
//

#include "stdafx.h"
#include "wbc.h"
#include "SettingDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingDialog dialog


SettingDialog::SettingDialog(CWnd* pParent /*=NULL*/)
	: CDialog(SettingDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SettingDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingDialog)
	DDX_Control(pDX, IDC_EDIT1, serialPortEditCtr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SettingDialog, CDialog)
	//{{AFX_MSG_MAP(SettingDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SettingDialog message handlers

//确定
void SettingDialog::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

//取消
void SettingDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
