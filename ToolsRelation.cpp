// ToolsRelation.cpp : implementation file
//

#include "stdafx.h"
#include "wbc.h"
#include "ToolsRelation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ToolsRelation dialog


ToolsRelation::ToolsRelation(CWnd* pParent /*=NULL*/)
	: CDialog(ToolsRelation::IDD, pParent)
{
	//{{AFX_DATA_INIT(ToolsRelation)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ToolsRelation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ToolsRelation)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ToolsRelation, CDialog)
	//{{AFX_MSG_MAP(ToolsRelation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ToolsRelation message handlers

void ToolsRelation::OnOK() //ÖØÐ´ ok
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void ToolsRelation::OnCancel() //ÖØÐ´ cancel
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
