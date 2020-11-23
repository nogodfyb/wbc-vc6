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
#include "MySqlUtil.h"
#include "AddRelationDialog.h"

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
	DDX_Control(pDX, IDC_LIST1, toolsRelationListCtr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ToolsRelation, CDialog)
	//{{AFX_MSG_MAP(ToolsRelation)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ToolsRelation message handlers

void ToolsRelation::OnOK() //重写 ok
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void ToolsRelation::OnCancel() //重写 cancel
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL ToolsRelation::OnInitDialog() //初始化
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	initToolsRelationListCtr();
	getAllToolsRelation();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ToolsRelation::initToolsRelationListCtr()//初始化列表
{

	CString str[6] = { TEXT("WaferSource"),TEXT("芯片尺寸"), TEXT("钢网sn"),TEXT("垫片sn"),TEXT("刮刀sn"),TEXT("银浆物料码")};
	for (int i = 0; i < 6; i++)
	{
		toolsRelationListCtr.InsertColumn(i, str[i], LVCFMT_LEFT, 100);
	}
	//设置风格  整行选中 加入网格线
	toolsRelationListCtr.SetExtendedStyle(toolsRelationListCtr.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	toolsRelationListCtr.AdjustColumnWidth();
}

void ToolsRelation::getAllToolsRelation()//获取所有工具关系
{
	try
	{
		CString msg;
		MySqlUtil mysql(msg);
		CString sql;
		sql.Format("SELECT wafer_source,wafer_size,steel_mesh_sn,shim_sn,scraper_sn,ep_pn from wbc20_tool_rule");
		mysql.SelectDataAndToList(sql,msg,&toolsRelationListCtr);
	}
	catch (const char * info)
	{
		MessageBox(info);
	}


}

void ToolsRelation::OnButton1() //添加关系
{
	// TODO: Add your control notification handler code here
	AddRelationDialog dlg;
	dlg.DoModal();
}
