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
	CString waferSource;
	waferSourceEditCtr.GetWindowText(waferSource);
	if (waferSource.IsEmpty())
	{
		MessageBox("waferSource不能为空!");
		return;
	}
	CString waferSize;
	if (waferSizeCbxCtr.GetCurSel()==-1)
	{
		MessageBox("未选芯片尺寸!");
		return;
	}
	waferSizeCbxCtr.GetWindowText(waferSize);
	CString steelMeshSn;
	if (steelMeshCbxCtr.GetCurSel()==-1)
	{
		MessageBox("未选钢网sn");
		return;
	}
	steelMeshCbxCtr.GetLBText(steelMeshCbxCtr.GetCurSel(),steelMeshSn);
	CString shimSn;
	if (shimCbxCtr.GetCurSel()==-1)
	{
		MessageBox("未选垫片sn");
		return;
	}
	shimCbxCtr.GetLBText(shimCbxCtr.GetCurSel(),shimSn);
	CString scraperSn;
	if (scraperCbxCtr.GetCurSel()==-1)
	{
		MessageBox("未选刮刀sn");
		return;
	}
	scraperCbxCtr.GetLBText(scraperCbxCtr.GetCurSel(),scraperSn);
	CString epSn;
	epPnEditCtr.GetWindowText(epSn);
	if (epSn.IsEmpty())
	{
		MessageBox("银浆sn为空!");
		return;
	}
	CString msg;
	try
	{
		MySqlUtil mysql(msg);
		CString sql;
		if (mode==1)
		{
			sql.Format("UPDATE wbc20_tool_rule SET wafer_size='%s', steel_mesh_sn='%s', shim_sn='%s', scraper_sn='%s', ep_pn='%s' WHERE (wafer_source='%s')",waferSize,steelMeshSn,shimSn,scraperSn,epSn,waferSource);
			mysql.UpdateData(sql,msg);
			MessageBox("修改成功!");
		}else{
			sql.Format("INSERT INTO wbc20_tool_rule (wafer_source, wafer_size, steel_mesh_sn, shim_sn, scraper_sn, ep_pn)\
				VALUES ('%s','%s','%s','%s','%s','%s')",waferSource,waferSize,steelMeshSn,shimSn,scraperSn,epSn);
			mysql.InsertData(sql,msg);
			MessageBox("添加成功!");
		}

	}
	catch (const char * info)
	{
		MessageBox(info);
		MessageBox(msg);
	}
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
	
	if (mode==1)
	{
		initEditForm();
	}
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
	CString msg;
	try
	{
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
		MessageBox(msg);
		return;
	}
}

void AddRelationDialog::initShimCbxCtr()//初始化垫片下拉框
{
	CString msg;
	try
	{
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
		MessageBox(msg);
		return;
	}
}

void AddRelationDialog::initScraperCbxCtr()//初始化刀片下拉框
{

	CString msg;
	try
	{
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
		MessageBox(msg);
		return;
	}
}

void AddRelationDialog::initEditForm()//初始化编辑表单
{

	waferSourceEditCtr.SetWindowText(waferSource);
	waferSourceEditCtr.EnableWindow(false);
	epPnEditCtr.SetWindowText(epPn);
	//芯片尺寸
	int waferSizeCount=waferSizeCbxCtr.GetCount();
	for (int i=0;i<waferSizeCount;i++)
	{
		CString msg;
		waferSizeCbxCtr.GetLBText(i,msg);
		if (msg==waferSize)
		{
			waferSizeCbxCtr.SetCurSel(i);
			break;
		}
	}
	//钢网sn
	int steelMeshSnCount=steelMeshCbxCtr.GetCount();
	for (int j=0;j<steelMeshSnCount;j++)
	{
		CString msg;
		steelMeshCbxCtr.GetLBText(j,msg);
		if (msg==steelMeshSn)
		{
			steelMeshCbxCtr.SetCurSel(j);
			break;
		}
	}
	//垫片sn
	int shimSnCount=shimCbxCtr.GetCount();
	for (int k=0;k<shimSnCount;k++)
	{
		CString msg;
		shimCbxCtr.GetLBText(k,msg);
		if (msg==shimSn)
		{
			shimCbxCtr.SetCurSel(k);
			break;
		}
	}
	//刮刀sn
	int scraperSnCount=scraperCbxCtr.GetCount();
	for (int m=0;m<scraperSn;m++)
	{
		CString msg;
		scraperCbxCtr.GetLBText(m,msg);
		if (msg==scraperSn)
		{
			scraperCbxCtr.SetCurSel(m);
			break;
		}
	}
}
