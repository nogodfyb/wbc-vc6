// AddRelationDialog.cpp : implementation file
//

#include "stdafx.h"
#include "wbc.h"
#include "AddRelationDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AddRelationDialog dialog
#include "MySqlUtil.h"


AddRelationDialog::AddRelationDialog(CWnd* pParent /*=NULL*/)
	: CDialog(AddRelationDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(AddRelationDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void AddRelationDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AddRelationDialog)
	DDX_Control(pDX, IDC_COMBO4, scraperCbxCtr);
	DDX_Control(pDX, IDC_COMBO3, shimCbxCtr);
	DDX_Control(pDX, IDC_COMBO2, steelMeshCbxCtr);
	DDX_Control(pDX, IDC_COMBO1, waferSizeCbxCtr);
	DDX_Control(pDX, IDC_EDIT2, epPnEditCtr);
	DDX_Control(pDX, IDC_EDIT1, waferSourceEditCtr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AddRelationDialog, CDialog)
	//{{AFX_MSG_MAP(AddRelationDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AddRelationDialog message handlers

void AddRelationDialog::OnOK() //重写ok
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void AddRelationDialog::OnCancel() //重写cancel
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL AddRelationDialog::OnInitDialog() //初始化
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	initWaferSizeCbxCtr();
	initSteelMeshCbxCtr();
	initShimCbxCtr();
	initScraperCbxCtr();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void AddRelationDialog::initWaferSizeCbxCtr()//初始化芯片尺寸下拉框
{
	waferSizeCbxCtr.AddString("5");
	waferSizeCbxCtr.AddString("6");
}

void AddRelationDialog::initSteelMeshCbxCtr()//初始化钢网下拉框
{
	try
	{
		CString msg;
		MySqlUtil mysql(msg);
		CString sql;
		sql.Format("SELECT sn from wbc20_tool WHERE type=2");
		CStringArray array;
		mysql.SelectData(sql,msg,array);
		for (int i=0;i<array.GetSize();i++)
		{
			steelMeshCbxCtr.AddString(array.GetAt(i));
		}
	}
	catch (const char * info)
	{
		MessageBox(info);
		return;
	}
}

void AddRelationDialog::initShimCbxCtr()//初始化垫片下拉框
{
	try
	{
		CString msg;
		MySqlUtil mysql(msg);
		CString sql;
		sql.Format("SELECT sn from wbc20_tool WHERE type=3");
		CStringArray array;
		mysql.SelectData(sql,msg,array);
		for (int i=0;i<array.GetSize();i++)
		{
			shimCbxCtr.AddString(array.GetAt(i));
		}
	}
	catch (const char * info)
	{
		MessageBox(info);
		return;
	}
}

void AddRelationDialog::initScraperCbxCtr()//初始化刀片下拉框
{

	try
	{
		CString msg;
		MySqlUtil mysql(msg);
		CString sql;
		sql.Format("SELECT sn from wbc20_tool WHERE type=1");
		CStringArray array;
		mysql.SelectData(sql,msg,array);
		for (int i=0;i<array.GetSize();i++)
		{
			scraperCbxCtr.AddString(array.GetAt(i));
		}
	}
	catch (const char * info)
	{
		MessageBox(info);
		return;
	}
}
