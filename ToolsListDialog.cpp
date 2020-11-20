// ToolsListDialog.cpp : implementation file
//

#include "stdafx.h"
#include "wbc.h"
#include "ToolsListDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ToolsListDialog dialog


ToolsListDialog::ToolsListDialog(CWnd* pParent /*=NULL*/)
	: CDialog(ToolsListDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(ToolsListDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ToolsListDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ToolsListDialog)
	DDX_Control(pDX, IDC_LIST1, toolsListCtr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ToolsListDialog, CDialog)
	//{{AFX_MSG_MAP(ToolsListDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ToolsListDialog message handlers

void ToolsListDialog::OnOK() //重写ok
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void ToolsListDialog::OnCancel() //重写cancel
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}

BOOL ToolsListDialog::OnInitDialog() //初始化
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	initToolsListCtr();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ToolsListDialog::initToolsListCtr()//初始化list
{

	//初始化表格
	//插入表头
	CString str[7] = { TEXT("序列号"),TEXT("工具类型"), TEXT("寿命"),TEXT("描述"),
		TEXT("创建时间"),TEXT("更新时间")};
	for (int i = 0; i < 6; i++)
	{
		toolsListCtr.InsertColumn(i, str[i], LVCFMT_LEFT, 100);
	}
	//设置风格  整行选中 加入网格线
	toolsListCtr.SetExtendedStyle(toolsListCtr.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	toolsListCtr.AdjustColumnWidth();
}

void ToolsListDialog::OnButton1() //添加工具
{
	// TODO: Add your control notification handler code here
	AddToolDialog dlg;
	dlg.DoModal();
	
}
