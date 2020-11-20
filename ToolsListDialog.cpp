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

void ToolsListDialog::OnOK() //��дok
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void ToolsListDialog::OnCancel() //��дcancel
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}

BOOL ToolsListDialog::OnInitDialog() //��ʼ��
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	initToolsListCtr();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ToolsListDialog::initToolsListCtr()//��ʼ��list
{

	//��ʼ�����
	//�����ͷ
	CString str[7] = { TEXT("���к�"),TEXT("��������"), TEXT("����"),TEXT("����"),
		TEXT("����ʱ��"),TEXT("����ʱ��")};
	for (int i = 0; i < 6; i++)
	{
		toolsListCtr.InsertColumn(i, str[i], LVCFMT_LEFT, 100);
	}
	//���÷��  ����ѡ�� ����������
	toolsListCtr.SetExtendedStyle(toolsListCtr.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	toolsListCtr.AdjustColumnWidth();
}

void ToolsListDialog::OnButton1() //��ӹ���
{
	// TODO: Add your control notification handler code here
	AddToolDialog dlg;
	dlg.DoModal();
	
}
