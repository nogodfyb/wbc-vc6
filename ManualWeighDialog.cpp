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
#include "ValiadteUtils.h"

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
	DDX_Control(pDX, IDC_EDIT1, manualWeighEditCtr);
	DDX_Control(pDX, WAFER_LOT_TEXT, waferLotTextCtr);
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
	CString input;
	manualWeighEditCtr.GetWindowText(input);
	if (ValiadteUtils::validateWeight(input))
	{
		manualWeighValue=input;
	}else{
		MessageBox("填入重量数据不合法!");
		manualWeighEditCtr.SetWindowText("");
		return;
	}
	CDialog::OnOK();
}

//取消
void ManualWeighDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL ManualWeighDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	waferLotTextCtr.SetWindowText(waferLot);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
