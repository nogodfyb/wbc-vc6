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

void AddToolDialog::OnOK() //��дok
{
	// TODO: Add extra validation here
	//���к�
	CString sn;
	snEditCtr.GetWindowText(sn);
	//��������
	CString type;
	typeCbxCtr.GetLBText(typeCbxCtr.GetCurSel(),type);
	if (type=="�ε�")
	{
		type="1";
	}else if (type=="����")
	{
		type="2";
	}else{
		type="3";
	}
	//����
	CString life;
	lifeEditCtr.GetWindowText(life);
	//��������
	CString description;
	descriptionEditCtr.GetWindowText(description);

	try
	{
		CString msg;
		MySqlUtil mysql(msg);
		CString sql;
		sql.Format("INSERT INTO wbc20_tool(sn, type, life, description) VALUES ('%s','%s','%s','%s')",sn,type,life,description);
		mysql.InsertData(sql,msg);
		MessageBox("��ӳɹ�");
	}
	catch (const char * info)
	{
		MessageBox(info);
	}
	
	
	CDialog::OnOK();
}

void AddToolDialog::OnCancel() //��дcancel
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL AddToolDialog::OnInitDialog() //��ʼ��
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	//��ʼ��������
	typeCbxCtr.AddString("�ε�");
	typeCbxCtr.AddString("����");
	typeCbxCtr.AddString("��Ƭ");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
