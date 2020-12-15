// CheckRecordListDialog.cpp : implementation file
//

#include "stdafx.h"
#include "wbc.h"
#include "CheckRecordListDialog.h"
#include "ValiadteUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CheckRecordListDialog dialog
#include "MySqlUtil.h"

CheckRecordListDialog::CheckRecordListDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CheckRecordListDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CheckRecordListDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CheckRecordListDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CheckRecordListDialog)
	DDX_Control(pDX, IDC_DATETIMEPICKER2, endTimeCtr);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, beginTimeCtr);
	DDX_Control(pDX, IDC_LIST1, checkRecordListCtr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CheckRecordListDialog, CDialog)
	//{{AFX_MSG_MAP(CheckRecordListDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CheckRecordListDialog message handlers

void CheckRecordListDialog::OnOK() //重写ok
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CheckRecordListDialog::OnCancel() //重写cancel
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CheckRecordListDialog::OnInitDialog() //初始化
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	initCheckRecordListCtr();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CheckRecordListDialog::initCheckRecordListCtr()//初始化点检记录列表
{

	//初始化表格
	//插入表头
	CString str[10] = { TEXT("班次"),TEXT("机器号"), TEXT("点检时间"),TEXT("工号"),
		TEXT("力量"),TEXT("速度"),TEXT("工作盘真空"),TEXT("垫片"),TEXT("刮刀"),TEXT("钢网")};
	for (int i = 0; i < 10; i++)
	{
		checkRecordListCtr.InsertColumn(i, str[i], LVCFMT_LEFT, 100);
	}
	//设置风格  整行选中 加入网格线
	checkRecordListCtr.SetExtendedStyle(checkRecordListCtr.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	checkRecordListCtr.AdjustColumnWidth();
}

void CheckRecordListDialog::OnButton1() //查询
{
	// TODO: Add your control notification handler code here
	checkRecordListCtr.DeleteAllItems();
	CString beginTime;
	beginTimeCtr.GetWindowText(beginTime);
	CString endTime;
	endTimeCtr.GetWindowText(endTime);
	bool valid=ValiadteUtils::validDateInterval(beginTime,endTime);
	if (!valid)
	{
		MessageBox("时间范围不合法!");
		return;
	}
	beginTime=beginTime+" 00:00:00";
	endTime=endTime+" 23:59:59";
	try
	{
		MySqlUtil mysql;
		CString sql;
		sql.Format("SELECT shift,machine_code,create_time,bn,power,speed,vacuum,shim_check,scraper_check,steelmesh_check from wbc20_check_record WHERE create_time BETWEEN '%s' AND '%s'",beginTime,endTime);
		mysql.SelectDataAndToList(sql,&checkRecordListCtr);
	}
	catch (CString info)
	{
		MessageBox(info);
	}
	
}
