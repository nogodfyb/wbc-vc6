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

void ToolsRelation::OnOK() //重写 ok
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void ToolsRelation::OnCancel() //重写 cancel
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL ToolsRelation::OnInitDialog() //初始化
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	initToolsRelationListCtr();
	getAllToolsRelation();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ToolsRelation::initToolsRelationListCtr()//初始化列表
{

	CString str[6] = { TEXT("WaferSource"),TEXT("芯片尺寸"), TEXT("钢网sn"),TEXT("垫片sn"),TEXT("刮刀sn"),TEXT("银浆物料码")};
	for (int i = 0; i < 6; i++)
	{
		toolsRelationListCtr.InsertColumn(i, str[i], LVCFMT_LEFT, 100);
	}
	//设置风格  整行选中 加入网格线
	toolsRelationListCtr.SetExtendedStyle(toolsRelationListCtr.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	toolsRelationListCtr.AdjustColumnWidth();
}

void ToolsRelation::getAllToolsRelation()//获取所有工具关系
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

void ToolsRelation::OnButton1() //添加关系
{
	if (!isAdmin())
	{
		MessageBox("管理员未登录!");
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

void ToolsRelation::OnContextMenu(CWnd* pWnd, CPoint point) //关联菜单
{
	// TODO: Add your message handler code here
	//关联工具关系列表
	CRect  rect; //定义矩形区域
	GetDlgItem(IDC_LIST1) -> GetWindowRect(&rect);  //获得控件相对于屏幕的位置坐标
	if(rect.PtInRect(point))  //右击点在指定控件上
	{
		CMenu popMenu;//弹出菜单
		popMenu.LoadMenu(IDR_MENU4);//根据资源ID关联菜单资源
		CMenu * subMenu = popMenu.GetSubMenu(0);//获得第0列子菜单的指针
		subMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, point.x, point.y, this);  //在指定位置显示浮动弹出菜单，并追踪弹出菜单中被选择的项
	}
	
}

void ToolsRelation::OnMenuitem32774() //修改
{
	if (!isAdmin())
	{
		MessageBox("管理员未登录!");
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
	//将表单参数传递给弹出窗口
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

void ToolsRelation::OnMenuitem32775() //删除
{
	if (!isAdmin())
	{
		MessageBox("管理员未登录!");
		return;
	}
	// TODO: Add your command handler code here
	if(MessageBox(TEXT("是否确认删除?"),TEXT("删除工具关系"),MB_OKCANCEL)!=IDOK)
	{
		return;
	}
	int currentRow=toolsRelationListCtr.GetSelectionMark();
	//序列号
	CString waferSource=toolsRelationListCtr.GetItemText(currentRow,0);
	try
	{
		MySqlUtil mysql;
		CString sql;
		sql.Format("DELETE from wbc20_tool_rule WHERE wafer_source='%s'",waferSource);
		mysql.DeleteData(sql);
		MessageBox("删除成功!");
		toolsRelationListCtr.DeleteAllItems();
		getAllToolsRelation();
	}
	catch (CString info)
	{
		MessageBox(info);
	}

}
