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

void WeighRecordListDialog::OnOK() //��дok
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void WeighRecordListDialog::OnCancel() //��дcancel
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL WeighRecordListDialog::OnInitDialog() //��ʼ��
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	initWeighRecordListCtr();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void WeighRecordListDialog::initWeighRecordListCtr() //��ʼ��listCtr
{

	CString str[27]={"���","����","������","оƬ�ͺ�","оƬ��Դ","оƬ����","ˢ��ǰ����","ˢ��ǰ����ʱ��","�������к�","�����ⶳ���ʱ��","��������ʱ��",
	"ˢ�����������","ˢ�������ʱ��","����","оƬ�ߴ�","�Ƿ񳬱�","�ε����к�","�������к�","��Ƭ���к�","�ε�����","��������","��Ƭ����","�쳣ԭ��","������","��ע","������","������"};
	for (int i = 0; i < 27; i++)
	{
		weighRecordListCtr.InsertColumn(i, str[i], LVCFMT_LEFT, 100);
	}
	//���÷��  ����ѡ�� ����������
	weighRecordListCtr.SetExtendedStyle(weighRecordListCtr.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	weighRecordListCtr.AdjustColumnWidth();
}

void WeighRecordListDialog::OnButton1() //��ѯ
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
		MessageBox("ʱ�䷶Χ���Ϸ�!");
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

bool WeighRecordListDialog::isAdmin()//����Ա�Ƿ��¼
{
	CWnd * parent=GetParent()->GetParent();
	AdminMainDialog * adminDlg=(AdminMainDialog *)parent;
	if (adminDlg->adminLogin==1)
	{
		return true;
	}
	return false;
}

