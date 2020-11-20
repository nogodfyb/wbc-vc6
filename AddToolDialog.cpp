// AddToolDialog.cpp : implementation file
//

#include "stdafx.h"
#include "wbc.h"
#include "AddToolDialog.h"
#include "MySqlUtil.h"

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
	DDX_Control(pDX, IDC_EDIT3, descriptionEditCtr);
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

void AddToolDialog::OnOK() //重写ok
{
	// TODO: Add extra validation here
	//序列号
	CString sn;
	snEditCtr.GetWindowText(sn);
	//工具类型
	CString type;
	typeCbxCtr.GetLBText(typeCbxCtr.GetCurSel(),type);
	if (type=="刮刀")
	{
		type="1";
	}else if (type=="钢网")
	{
		type="2";
	}else{
		type="3";
	}
	//寿命
	CString life;
	lifeEditCtr.GetWindowText(life);
	//中文描述
	CString description;
	descriptionEditCtr.GetWindowText(description);

	try
	{
		CString msg;
		MySqlUtil mysql(msg);
		CString sql;
		sql.Format("INSERT INTO wbc20_tool(sn, type, life, description) VALUES ('%s','%s','%s','%s')",sn,type,life,description);
		mysql.InsertData(sql,msg);
		MessageBox("添加成功");
	}
	catch (const char * info)
	{
		MessageBox(info);
	}
	
	
	CDialog::OnOK();
}

void AddToolDialog::OnCancel() //重写cancel
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL AddToolDialog::OnInitDialog() //初始化
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	//初始化下拉框
	typeCbxCtr.AddString("刮刀");
	typeCbxCtr.AddString("钢网");
	typeCbxCtr.AddString("垫片");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
