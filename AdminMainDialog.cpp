// AdminMainDialog.cpp : implementation file
//

#include "stdafx.h"
#include "wbc.h"
#include "AdminMainDialog.h"
#include "MySqlUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AdminMainDialog dialog


AdminMainDialog::AdminMainDialog(CWnd* pParent /*=NULL*/)
	: CDialog(AdminMainDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(AdminMainDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void AdminMainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AdminMainDialog)
	DDX_Control(pDX, IDC_EDIT2, passwordEditCtr);
	DDX_Control(pDX, IDC_EDIT1, usernameEditCtr);
	DDX_Control(pDX, IDC_TAB1, tabCtr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AdminMainDialog, CDialog)
	//{{AFX_MSG_MAP(AdminMainDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AdminMainDialog message handlers

void AdminMainDialog::OnOK() //��дok
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void AdminMainDialog::OnCancel() //��дcancel
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL AdminMainDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here


	CSize size(50, 50), sizeReturn;
	sizeReturn = tabCtr.SetItemSize(size);

	//����4��ҳ��
	tabCtr.InsertItem(0,"�����б�");
	tabCtr.InsertItem(1,"������wafersource");
	tabCtr.InsertItem(2,"����¼");
	tabCtr.InsertItem(3,"ˢ����¼");

	page1.Create(TOOLS_LIST_DIALOG,&tabCtr);
	page2.Create(TOOLS_RELATION,&tabCtr);
	page3.Create(CHECK_RECORD_LIST,&tabCtr);
	page4.Create(WEIGH_RECORD_LIST,&tabCtr);

	//�趨��Tab����ʾ�ķ�Χ
	CRect rc;
	tabCtr.GetClientRect(rc);
	rc.top += 50;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;
	page1.MoveWindow(&rc);
	page2.MoveWindow(&rc);
	page3.MoveWindow(&rc);
	page4.MoveWindow(&rc);

	//�ѶԻ������ָ�뱣������
	pDialog[0] = &page1;
	pDialog[1] = &page2;
	pDialog[2] = &page3;
	pDialog[3] = &page4;
	//��ʾ��ʼҳ��
	pDialog[0]->ShowWindow(SW_SHOW);
	pDialog[1]->ShowWindow(SW_HIDE);
	pDialog[2]->ShowWindow(SW_HIDE);
	pDialog[3]->ShowWindow(SW_HIDE);
	//���浱ǰѡ��
	m_CurSelTab = 0;
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//�л�tabҳ��
void AdminMainDialog::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	//�ѵ�ǰ��ҳ����������
	pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
	//�õ��µ�ҳ������
	m_CurSelTab = tabCtr.GetCurSel();
	//���µ�ҳ����ʾ����
	pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);	
	
	*pResult = 0;
}

void AdminMainDialog::OnButton1() //��¼��̨����
{
	// TODO: Add your control notification handler code here
	CString username;
	CString password;
	usernameEditCtr.GetWindowText(username);
	passwordEditCtr.GetWindowText(password);

	CString msg;
	try
	{
		MySqlUtil mysql(msg);
		CString sql;
		CStringArray array;
		sql.Format("SELECT bn from diesaw_user WHERE bn='%s' AND pw=MD5('%s')",username,password);
		mysql.SelectData(sql,msg,array);
		if(array.GetSize()!=1){
			MessageBox("���ź����벻��ȷ");
			return;
		}else{
			adminLogin=1;
			MessageBox("��¼�ɹ�!");
		}
	}
	catch (const char * info)
	{
		MessageBox(info);
		MessageBox(msg);
	}
	
}
