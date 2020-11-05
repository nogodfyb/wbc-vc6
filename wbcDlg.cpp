// wbcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "wbc.h"
#include "wbcDlg.h"
#include "MySqlUtil.h"
#include "CheckToolsDlg.h"
#include "ValiadteUtils.h"
#include "MyUtils.h"
#include "SettingDialog.h"
#include "ManualWeighDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWbcDlg dialog

CWbcDlg::CWbcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWbcDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWbcDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWbcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWbcDlg)
	DDX_Control(pDX, IDC_LIST2, firstWeighWaferListCtr);
	DDX_Control(pDX, IDC_COMBO1, planIdCbxCtr);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, planDateCtr);
	DDX_Control(pDX, IDC_LIST1, waferSelectListCtr);
	DDX_Control(pDX, IDC_EDIT2, firstWeighWaferEditCtr);
	DDX_Control(pDX, ID_TEXT, idTextCtr);
	DDX_Control(pDX, LAST_CHECK_TEXT, lastCheckCtr);
	DDX_Control(pDX, IDC_EDIT1, waferCtr);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWbcDlg, CDialog)
	//{{AFX_MSG_MAP(CWbcDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_MENUITEM32771, OnMenuitem32771)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWbcDlg message handlers

BOOL CWbcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	initSelectWaferListCtr();
	initPlanIdCbxCtr();
	initFirstWeighWaferListCtr();
	getSetting();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWbcDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWbcDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWbcDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// 重写onOk
void CWbcDlg::OnOK() 
{

	//点检前匹配刷胶工具
	if(GetDlgItem(IDC_EDIT1)==GetFocus())
	{
		OnScanWafer();
		return;
	}
	//第一次称重前扫描wafer
	if(GetDlgItem(IDC_EDIT2)==GetFocus())
	{
		OnScanWaferFistWeigh();
		return;
	}

}

// 重写onCancel
void CWbcDlg::OnCancel() 
{
	if(MessageBox(TEXT("是否确认退出?"),TEXT("退出程序"),MB_OKCANCEL)!=IDOK)
	{
		return;
	}
	CDialog::OnCancel();
}

//扫描枪扫描wafer
void CWbcDlg::OnScanWafer(){
	CString wafer;
	waferCtr.GetWindowText(wafer);
	if (ValiadteUtils::validateWafer(wafer))
	{
		CheckToolsDlg dlg;
		CStringArray array;
		MyUtils::splitStr(wafer,'^',array);
		//将芯片二维码中的waferSource分割提取出来，传递给弹出的校验工具窗口
		dlg.waferSource=array.GetAt(1);
		dlg.DoModal();
		//设置上次点检时间
		lastCheckCtr.SetWindowText(dlg.lastCheckTime);
		//设置上次点检id
		idTextCtr.SetWindowText(dlg.lastCheckId);
	}else{
		MessageBox("芯片二维码格式不正确!");
	}
	waferCtr.SetWindowText("");
}
//第一次称重前扫描wafer
void CWbcDlg::OnScanWaferFistWeigh(){
	CString wafer;
	firstWeighWaferEditCtr.GetWindowText(wafer);
	firstWeighWaferEditCtr.SetWindowText("");
	if (ValiadteUtils::validateWafer(wafer))
	{
		CStringArray array;
		MyUtils::splitStr(wafer,'^',array);
		for (int i=0;i<waferSelectListCtr.GetItemCount();i++)
		{
			CString waferLot=waferSelectListCtr.GetItemText(i,1);
			if (waferLot==array.GetAt(3))
			{
				MessageBox("已存在!");
				return;
			}
		}
		//将waferSource和waferLot填充到第一行
		waferSelectListCtr.InsertItem(0,array.GetAt(1));
		waferSelectListCtr.SetItemText(0,1,array.GetAt(3));
		waferSelectListCtr.AdjustColumnWidth();
	} 
	else
	{
		MessageBox("芯片二维码格式不正确");
	}
}
//初始化芯片查询的listCtr
void CWbcDlg::initSelectWaferListCtr(){
	CString str[3] = { TEXT("WaferSource"),TEXT("WaferLot"), TEXT("刷胶前重量")};
	for (size_t i = 0; i < 3; i++)
	{
		waferSelectListCtr.InsertColumn(i, str[i], LVCFMT_LEFT, 100);
	}
	//设置风格  整行选中 加入网格线
	waferSelectListCtr.SetExtendedStyle(waferSelectListCtr.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	waferSelectListCtr.AdjustColumnWidth();
}

//初始化第一次称重的listCtr
void CWbcDlg::initFirstWeighWaferListCtr(){
	CString str[4] = { TEXT("WaferSource"),TEXT("WaferLot"), TEXT("刷胶前重量"),TEXT("Plasma")};
	for (size_t i = 0; i < 4; i++)
	{
		firstWeighWaferListCtr.InsertColumn(i, str[i], LVCFMT_LEFT, 100);
	}
	//设置风格  整行选中 加入网格线
	firstWeighWaferListCtr.SetExtendedStyle(firstWeighWaferListCtr.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	firstWeighWaferListCtr.AdjustColumnWidth();
}
//初始化计划号下拉框
void CWbcDlg::initPlanIdCbxCtr(){
	for (int i=1;i<=200;i++)
	{
		CString str;
		str.Format("%d",i);
		MyUtils::completeZero(str);
		planIdCbxCtr.AddString(str);
	}
	planIdCbxCtr.SetCurSel(0);
}

//芯片查询
void CWbcDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	try
	{
		waferSelectListCtr.DeleteAllItems();
		CTime date;
		planDateCtr.GetTime(date);
		CString planDate=date.Format(_T("%y%m%d"));
		CString planId;
		planIdCbxCtr.GetWindowText(planId);
		CString msg;
		MySqlUtil mysql(msg);
		//查询数据并渲染
		CString sql;
		sql.Format("SELECT ws,wl from wafer_list_mes_org WHERE schid='%s'",planDate+"-"+planId);
		mysql.SelectDataAndToList(sql,msg,&waferSelectListCtr);
		//如果列表不为空;遍历每一行从第一次称重记录里查询第一次称重数据;并在该行填充
		for (int i=0;i<waferSelectListCtr.GetItemCount();i++)
		{
			CString waferLot=waferSelectListCtr.GetItemText(i,1);
			CString sql;
			sql.Format("SELECT weight from wbc20_first_weigh_record WHERE wafer_lot='%s'",waferLot);
			CStringArray array;
			mysql.SelectData(sql,msg,array);
			//设置重量
			if (array.GetSize()==1)
			{
				waferSelectListCtr.SetItemText(i,2,array.GetAt(0));
			}
		}
	}
	catch (const char * info)
	{
		MessageBox(info);
	}
}

//弹出设置窗口
void CWbcDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	SettingDialog dlg;
	dlg.DoModal();
	
}

//读取配置信息
void CWbcDlg::getSetting(){
	// TODO: Add your control notification handler code here
	CFile file;
	bool state=file.Open("setting.ini",CFile::modeRead,NULL); 
	int i=0;
	DWORD len=file.GetLength( );
	char * arr=new char[len+1];
	arr[len]=0;  //0终止字符串，用于输出。
	file.Read(arr,len);   //Read( void* lpBuf, UINT nCount ) lpBuf是用于接收读取到的数据的Buf指针nCount是从文件读取的字节数
	CString setting(arr);
	CStringArray array;
	MyUtils::splitStr(setting,'\r\n',array);
	weigthMode=array.GetAt(0).Mid(11);
	serialPort=array.GetAt(1).Mid(12);
	delete arr;
}

//菜单关联映射
void CWbcDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	CRect  rect; //定义矩形区域
	GetDlgItem(IDC_LIST1) -> GetWindowRect(&rect);  //获得控件相对于屏幕的位置坐标
	if(rect.PtInRect(point))  //右击点在指定控件上
	{
		CMenu popMenu;//弹出菜单
		popMenu.LoadMenu(IDR_MENU1);//根据资源ID关联菜单资源
		CMenu * subMenu = popMenu.GetSubMenu(0);//获得第0列子菜单的指针
		subMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, point.x, point.y, this);  //在指定位置显示浮动弹出菜单，并追踪弹出菜单中被选择的项
	}
	
}

//点击称重菜单
void CWbcDlg::OnMenuitem32771() 
{
	// TODO: Add your command handler code here
	CString wafeLot;
	CString waferSource;
	int row = waferSelectListCtr.GetSelectionMark();
	wafeLot=waferSelectListCtr.GetItemText(row, 1);
	waferSource=waferSelectListCtr.GetItemText(row,0);
	if (wafeLot.IsEmpty())
	{
		MessageBox("当前未选中任何wafer!");
		return;
	}
	//手动模式
	if (weigthMode=="1")
	{
		ManualWeighDialog dlg;
		dlg.waferLot=wafeLot;
		dlg.DoModal();
		waferSelectListCtr.SetItemText(row,2,dlg.manualWeighValue);
		//传来的重量数据非空
		if (!dlg.manualWeighValue.IsEmpty())
		{
			//保存或更新该wafer的第一次称重记录
			try
			{
				CString msg;
				MySqlUtil mysql(msg);
				CString sql;
				sql.Format("INSERT INTO wbc20_first_weigh_record (wafer_lot, wafer_source, weight) VALUES ('%s','%s','%s') ON DUPLICATE KEY UPDATE weight='%s'",wafeLot,waferSource,dlg.manualWeighValue,dlg.manualWeighValue);
				mysql.InsertData(sql,msg);
			}
			catch (const char * info)
			{
				MessageBox(info);
			}
		}
	}
}
