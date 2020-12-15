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

void CheckRecordListDialog::OnOK() //��дok
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CheckRecordListDialog::OnCancel() //��дcancel
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CheckRecordListDialog::OnInitDialog() //��ʼ��
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	initCheckRecordListCtr();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CheckRecordListDialog::initCheckRecordListCtr()//��ʼ������¼�б�
{

	//��ʼ�����
	//�����ͷ
	CString str[10] = { TEXT("���"),TEXT("������"), TEXT("���ʱ��"),TEXT("����"),
		TEXT("����"),TEXT("�ٶ�"),TEXT("���������"),TEXT("��Ƭ"),TEXT("�ε�"),TEXT("����")};
	for (int i = 0; i < 10; i++)
	{
		checkRecordListCtr.InsertColumn(i, str[i], LVCFMT_LEFT, 100);
	}
	//���÷��  ����ѡ�� ����������
	checkRecordListCtr.SetExtendedStyle(checkRecordListCtr.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	checkRecordListCtr.AdjustColumnWidth();
}

void CheckRecordListDialog::OnButton1() //��ѯ
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
		MessageBox("ʱ�䷶Χ���Ϸ�!");
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
