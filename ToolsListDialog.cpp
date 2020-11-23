// ToolsListDialog.cpp : implementation file
//

#include "stdafx.h"
#include "wbc.h"
#include "ToolsListDialog.h"
#include "MySqlUtil.h"

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
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_MENUITEM32774, OnMenuitem32774)
	ON_COMMAND(ID_MENUITEM32775, OnMenuitem32775)
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
	getAllTools();
	
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
	toolsListCtr.DeleteAllItems();
	getAllTools();
	
}
void ToolsListDialog::getAllTools()//��ȡ���й���
{

	try
	{
		CString msg;
		MySqlUtil mysql(msg);
		CString sql;
		sql.Format("SELECT sn,type,life,description,create_time,update_time FROM wbc20_tool");
		mysql.SelectDataAndToList(sql,msg,&toolsListCtr);
		//�����б���������ת��Ϊ
		for (int i=0;i<toolsListCtr.GetItemCount();i++)
		{
			CString type=toolsListCtr.GetItemText(i,1);
			if (type=="1")
			{
				toolsListCtr.SetItemText(i,1,"�ε�");
			}else if (type=="2")
			{
				toolsListCtr.SetItemText(i,1,"����");
			}else{
				toolsListCtr.SetItemText(i,1,"��Ƭ");
			}
		}
	}
	catch (const char * info)
	{
		MessageBox(info);
	}

}

void ToolsListDialog::OnContextMenu(CWnd* pWnd, CPoint point) //�˵�����
{
	// TODO: Add your message handler code here
	//����ˢ�������б�
	CRect  rect; //�����������
	GetDlgItem(IDC_LIST1) -> GetWindowRect(&rect);  //��ÿؼ��������Ļ��λ������
	if(rect.PtInRect(point))  //�һ�����ָ���ؼ���
	{
		CMenu popMenu;//�����˵�
		popMenu.LoadMenu(IDR_MENU4);//������ԴID�����˵���Դ
		CMenu * subMenu = popMenu.GetSubMenu(0);//��õ�0���Ӳ˵���ָ��
		subMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, point.x, point.y, this);  //��ָ��λ����ʾ���������˵�����׷�ٵ����˵��б�ѡ�����
	}
	
}

void ToolsListDialog::OnMenuitem32774() //�༭
{
	// TODO: Add your command handler code here
	int currentRow=toolsListCtr.GetSelectionMark();
	//���к�
	CString sn=toolsListCtr.GetItemText(currentRow,0);
	//��������
	CString type=toolsListCtr.GetItemText(currentRow,1);
	//����
	CString life=toolsListCtr.GetItemText(currentRow,2);
	//����
	CString description=toolsListCtr.GetItemText(currentRow,3);
	AddToolDialog dlg;
	//�����������ݸ���������
	dlg.sn=sn;
	dlg.type=type;
	dlg.life=life;
	dlg.description=description;
	//�򿪱༭ģʽ
	dlg.mode=1;
	dlg.DoModal();
	toolsListCtr.DeleteAllItems();
	getAllTools();

}

void ToolsListDialog::OnMenuitem32775() //ɾ��
{
	// TODO: Add your command handler code here
	if(MessageBox(TEXT("�Ƿ�ȷ��ɾ��?"),TEXT("ɾ������"),MB_OKCANCEL)!=IDOK)
	{
		return;
	}
	int currentRow=toolsListCtr.GetSelectionMark();
	//���к�
	CString sn=toolsListCtr.GetItemText(currentRow,0);

	try
	{
		CString msg;
		MySqlUtil mysql(msg);
		CString sql;
		sql.Format("DELETE from wbc20_tool WHERE sn='%s'",sn);
		mysql.DeleteData(sql,msg);
		MessageBox("ɾ���ɹ�!");
		toolsListCtr.DeleteAllItems();
		getAllTools();
	}
	catch (const char * info)
	{
		MessageBox(info);
	}

}
