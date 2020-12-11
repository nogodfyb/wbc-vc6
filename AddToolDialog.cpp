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
	if (sn.IsEmpty())
	{
		MessageBox("���кŲ���Ϊ��");
		return;
	}
	//��������
	CString type;
	if (typeCbxCtr.GetCurSel()==-1)
	{
		MessageBox("�������ͱ�ѡ!");
		return;
	}
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
	if (life.IsEmpty())
	{
		MessageBox("��������Ϊ��!");
		return;
	}
	//��������
	CString description;
	descriptionEditCtr.GetWindowText(description);
	if (description.IsEmpty())
	{
		MessageBox("������������Ϊ��!");
		return;
	}

	CString msg;
	try
	{
		MySqlUtil mysql(msg);
		CString sql;

		//�༭ģʽ
		if (mode==1)
		{
			sql.Format("UPDATE wbc20_tool SET type='%s',life='%s',description='%s' WHERE sn='%s'",type,life,description,sn);
			mysql.UpdateData(sql,msg);
			MessageBox("�޸ĳɹ�!");
		}else{
			sql.Format("INSERT INTO wbc20_tool(sn, type, life, description) VALUES ('%s','%s','%s','%s')",sn,type,life,description);
			mysql.InsertData(sql,msg);
			MessageBox("��ӳɹ�!");
		}

	}
	catch (const char * info)
	{
		MessageBox(info);
		MessageBox(msg);
		return;
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

	//�����ǰ���޸�ģʽ
	if (mode==1)
	{
		initEditForm();
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void AddToolDialog::initEditForm()//��ʼ���༭��
{

	snEditCtr.SetWindowText(sn);
	snEditCtr.EnableWindow(false);
	descriptionEditCtr.SetWindowText(description);
	lifeEditCtr.SetWindowText(life);
	int count=typeCbxCtr.GetCount();
	for (int i=0;i<count;i++)
	{
		CString msg;
		typeCbxCtr.GetLBText(i,msg);
		if (msg==type)
		{
			typeCbxCtr.SetCurSel(i);
			break;
		}
	}
	
}

