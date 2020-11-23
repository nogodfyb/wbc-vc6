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

void ToolsListDialog::OnOK() //重写ok
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void ToolsListDialog::OnCancel() //重写cancel
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}

BOOL ToolsListDialog::OnInitDialog() //初始化
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	initToolsListCtr();
	getAllTools();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ToolsListDialog::initToolsListCtr()//初始化list
{

	//初始化表格
	//插入表头
	CString str[7] = { TEXT("序列号"),TEXT("工具类型"), TEXT("寿命"),TEXT("描述"),
		TEXT("创建时间"),TEXT("更新时间")};
	for (int i = 0; i < 6; i++)
	{
		toolsListCtr.InsertColumn(i, str[i], LVCFMT_LEFT, 100);
	}
	//设置风格  整行选中 加入网格线
	toolsListCtr.SetExtendedStyle(toolsListCtr.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	toolsListCtr.AdjustColumnWidth();
}

void ToolsListDialog::OnButton1() //添加工具
{
	// TODO: Add your control notification handler code here
	AddToolDialog dlg;
	dlg.DoModal();
	toolsListCtr.DeleteAllItems();
	getAllTools();
	
}
void ToolsListDialog::getAllTools()//获取所有工具
{

	try
	{
		CString msg;
		MySqlUtil mysql(msg);
		CString sql;
		sql.Format("SELECT sn,type,life,description,create_time,update_time FROM wbc20_tool");
		mysql.SelectDataAndToList(sql,msg,&toolsListCtr);
		//遍历列表将数字类型转换为
		for (int i=0;i<toolsListCtr.GetItemCount();i++)
		{
			CString type=toolsListCtr.GetItemText(i,1);
			if (type=="1")
			{
				toolsListCtr.SetItemText(i,1,"刮刀");
			}else if (type=="2")
			{
				toolsListCtr.SetItemText(i,1,"钢网");
			}else{
				toolsListCtr.SetItemText(i,1,"垫片");
			}
		}
	}
	catch (const char * info)
	{
		MessageBox(info);
	}

}

void ToolsListDialog::OnContextMenu(CWnd* pWnd, CPoint point) //菜单关联
{
	// TODO: Add your message handler code here
	//关联刷胶工具列表
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

void ToolsListDialog::OnMenuitem32774() //编辑
{
	// TODO: Add your command handler code here
	int currentRow=toolsListCtr.GetSelectionMark();
	//序列号
	CString sn=toolsListCtr.GetItemText(currentRow,0);
	//工具类型
	CString type=toolsListCtr.GetItemText(currentRow,1);
	//寿命
	CString life=toolsListCtr.GetItemText(currentRow,2);
	//描述
	CString description=toolsListCtr.GetItemText(currentRow,3);
	AddToolDialog dlg;
	//将表单参数传递给弹出窗口
	dlg.sn=sn;
	dlg.type=type;
	dlg.life=life;
	dlg.description=description;
	//打开编辑模式
	dlg.mode=1;
	dlg.DoModal();
	toolsListCtr.DeleteAllItems();
	getAllTools();

}

void ToolsListDialog::OnMenuitem32775() //删除
{
	// TODO: Add your command handler code here
	if(MessageBox(TEXT("是否确认删除?"),TEXT("删除工具"),MB_OKCANCEL)!=IDOK)
	{
		return;
	}
	int currentRow=toolsListCtr.GetSelectionMark();
	//序列号
	CString sn=toolsListCtr.GetItemText(currentRow,0);

	try
	{
		CString msg;
		MySqlUtil mysql(msg);
		CString sql;
		sql.Format("DELETE from wbc20_tool WHERE sn='%s'",sn);
		mysql.DeleteData(sql,msg);
		MessageBox("删除成功!");
		toolsListCtr.DeleteAllItems();
		getAllTools();
	}
	catch (const char * info)
	{
		MessageBox(info);
	}

}
