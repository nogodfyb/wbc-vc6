// WeighRecordListDialog.cpp : implementation file
//

#include "stdafx.h"
#include "wbc.h"
#include "WeighRecordListDialog.h"
#include "ValiadteUtils.h"
#include "MySqlUtil.h"
#include "AdminMainDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// WeighRecordListDialog dialog


WeighRecordListDialog::WeighRecordListDialog(CWnd* pParent /*=NULL*/)
	: CDialog(WeighRecordListDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(WeighRecordListDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void WeighRecordListDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(WeighRecordListDialog)
	DDX_Control(pDX, IDC_DATETIMEPICKER2, endTimeCtr);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, beginTimeCtr);
	DDX_Control(pDX, IDC_LIST1, weighRecordListCtr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(WeighRecordListDialog, CDialog)
	//{{AFX_MSG_MAP(WeighRecordListDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// WeighRecordListDialog message handlers

void WeighRecordListDialog::OnOK() //重写ok
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void WeighRecordListDialog::OnCancel() //重写cancel
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL WeighRecordListDialog::OnInitDialog() //初始化
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	initWeighRecordListCtr();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void WeighRecordListDialog::initWeighRecordListCtr() //初始化listCtr
{

	CString str[27]={"班次","工号","机器号","芯片型号","芯片来源","芯片批次","刷胶前重量","刷胶前称重时间","银浆序列号","银浆解冻完成时间","银浆过期时间",
	"刷胶后称重重量","刷胶后称重时间","胶重","芯片尺寸","是否超标","刮刀序列号","钢网序列号","垫片序列号","刮刀寿命","钢网寿命","垫片寿命","异常原因","处理方案","备注","处理结果","处理人"};
	for (int i = 0; i < 27; i++)
	{
		weighRecordListCtr.InsertColumn(i, str[i], LVCFMT_LEFT, 100);
	}
	//设置风格  整行选中 加入网格线
	weighRecordListCtr.SetExtendedStyle(weighRecordListCtr.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	weighRecordListCtr.AdjustColumnWidth();
}

void WeighRecordListDialog::OnButton1() //查询
{

	// TODO: Add your control notification handler code here
	weighRecordListCtr.DeleteAllItems();
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
		sql.Format("SELECT shift,bn,machine_code,wafer_device,wafer_source,wafer_lot,first_weight,first_weigh_time,ep_sn,ep_start_time,ep_exceed_time,second_weight,\
					create_time,second_weight-first_weight,wafer_size,is_over_weight,scraper_sn,steel_mesh_sn,shim_sn,scraper_life,steel_mesh_life,shim_life,expection_reason,handle_plan,handle_remark,handle_result,deal_person from wbc20_second_weigh_record WHERE create_time BETWEEN '%s' AND '%s'",beginTime,endTime);
		mysql.SelectDataAndToList(sql,&weighRecordListCtr);
	}
	catch (CString info)
	{
		MessageBox(info);
	}
	
}

bool WeighRecordListDialog::isAdmin()//管理员是否登录
{
	CWnd * parent=GetParent()->GetParent();
	AdminMainDialog * adminDlg=(AdminMainDialog *)parent;
	if (adminDlg->adminLogin==1)
	{
		return true;
	}
	return false;
}

