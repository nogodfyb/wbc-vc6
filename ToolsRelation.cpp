// ToolsRelation.cpp : implementation file
//

#include "stdafx.h"
#include "wbc.h"
#include "ToolsRelation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ToolsRelation dialog
#include "MySqlUtil.h"
#include "AddRelationDialog.h"
#include "AdminMainDialog.h"

ToolsRelation::ToolsRelation(CWnd* pParent /*=NULL*/)
	: CDialog(ToolsRelation::IDD, pParent)
{
	//{{AFX_DATA_INIT(ToolsRelation)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ToolsRelation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ToolsRelation)
	DDX_Control(pDX, IDC_LIST1, toolsRelationListCtr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ToolsRelation, CDialog)
	//{{AFX_MSG_MAP(ToolsRelation)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_MENUITEM32774, OnMenuitem32774)
	ON_COMMAND(ID_MENUITEM32775, OnMenuitem32775)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ToolsRelation message handlers

void ToolsRelation::OnOK() //��д ok
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void ToolsRelation::OnCancel() //��д cancel
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL ToolsRelation::OnInitDialog() //��ʼ��
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	initToolsRelationListCtr();
	getAllToolsRelation();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ToolsRelation::initToolsRelationListCtr()//��ʼ���б�
{

	CString str[6] = { TEXT("WaferSource"),TEXT("оƬ�ߴ�"), TEXT("����sn"),TEXT("��Ƭsn"),TEXT("�ε�sn"),TEXT("����������")};
	for (int i = 0; i < 6; i++)
	{
		toolsRelationListCtr.InsertColumn(i, str[i], LVCFMT_LEFT, 100);
	}
	//���÷��  ����ѡ�� ����������
	toolsRelationListCtr.SetExtendedStyle(toolsRelationListCtr.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	toolsRelationListCtr.AdjustColumnWidth();
}

void ToolsRelation::getAllToolsRelation()//��ȡ���й��߹�ϵ
{
	try
	{
		MySqlUtil mysql;
		CString sql;
		sql.Format("SELECT wafer_source,wafer_size,steel_mesh_sn,shim_sn,scraper_sn,ep_pn from wbc20_tool_rule");
		mysql.SelectDataAndToList(sql,&toolsRelationListCtr);
	}
	catch (CString info)
	{
		MessageBox(info);
	}


}

void ToolsRelation::OnButton1() //��ӹ�ϵ
{
	if (!isAdmin())
	{
		MessageBox("����Աδ��¼!");
		return;
	}
	// TODO: Add your control notification handler code here
	AddRelationDialog dlg;
	dlg.DoModal();
	toolsRelationListCtr.DeleteAllItems();
	getAllToolsRelation();
}

bool ToolsRelation::isAdmin()
{
	CWnd * parent=GetParent()->GetParent();
	AdminMainDialog * adminDlg=(AdminMainDialog *)parent;
	if (adminDlg->adminLogin==1)
	{
		return true;
	}
	return false;
}

void ToolsRelation::OnContextMenu(CWnd* pWnd, CPoint point) //�����˵�
{
	// TODO: Add your message handler code here
	//�������߹�ϵ�б�
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

void ToolsRelation::OnMenuitem32774() //�޸�
{
	if (!isAdmin())
	{
		MessageBox("����Աδ��¼!");
		return;
	}
	// TODO: Add your command handler code here
	int currentRow=toolsRelationListCtr.GetSelectionMark();
	
	CString waferSource=toolsRelationListCtr.GetItemText(currentRow,0);
	CString waferSize=toolsRelationListCtr.GetItemText(currentRow,1);
	CString steelMeshSn=toolsRelationListCtr.GetItemText(currentRow,2);
	CString shimSn=toolsRelationListCtr.GetItemText(currentRow,3);
	CString scraperSn=toolsRelationListCtr.GetItemText(currentRow,4);
	CString epSn=toolsRelationListCtr.GetItemText(currentRow,5);

	AddRelationDialog dlg;
	//�����������ݸ���������
	dlg.mode=1;
	dlg.waferSource=waferSource;
	dlg.waferSize=waferSize;
	dlg.steelMeshSn=steelMeshSn;
	dlg.shimSn=shimSn;
	dlg.scraperSn=scraperSn;
	dlg.epPn=epSn;
	dlg.DoModal();
	toolsRelationListCtr.DeleteAllItems();
	getAllToolsRelation();
}

void ToolsRelation::OnMenuitem32775() //ɾ��
{
	if (!isAdmin())
	{
		MessageBox("����Աδ��¼!");
		return;
	}
	// TODO: Add your command handler code here
	if(MessageBox(TEXT("�Ƿ�ȷ��ɾ��?"),TEXT("ɾ�����߹�ϵ"),MB_OKCANCEL)!=IDOK)
	{
		return;
	}
	int currentRow=toolsRelationListCtr.GetSelectionMark();
	//���к�
	CString waferSource=toolsRelationListCtr.GetItemText(currentRow,0);
	try
	{
		MySqlUtil mysql;
		CString sql;
		sql.Format("DELETE from wbc20_tool_rule WHERE wafer_source='%s'",waferSource);
		mysql.DeleteData(sql);
		MessageBox("ɾ���ɹ�!");
		toolsRelationListCtr.DeleteAllItems();
		getAllToolsRelation();
	}
	catch (CString info)
	{
		MessageBox(info);
	}

}
