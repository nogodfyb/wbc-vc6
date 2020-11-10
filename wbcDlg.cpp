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
#include "Epo.h"

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
	DDX_Control(pDX, EP_PROMPT_TEXT, epPromptTextCtr);
	DDX_Control(pDX, IDC_LIST3, secondWeighWaferListCtr);
	DDX_Control(pDX, IDC_EDIT3, epEditCtr);
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
	ON_WM_TIMER()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST2, OnCustomdrawMyList)
	ON_COMMAND(ID_MENUITEM32772, OnMenuitem32772)
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
	initSecondWeighWaferListCtr();
	getSetting();
	//创建定时器
	SetTimer(IDTIMER1,5000,0);
	//SetTimer(IDTIMER2,5000,0);
	refreshEpoRemainTime();
	
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
	//扫银浆
	if(GetDlgItem(IDC_EDIT3)==GetFocus())
	{
		OnScanEp();
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
		CString waferLot=array.GetAt(3);
		CString waferSource=array.GetAt(1);
		manualFirstWeigh(waferLot,waferSource);
	} 
	else
	{
		MessageBox("芯片二维码格式不正确");
	}
}
//扫银浆
void CWbcDlg::OnScanEp(){
	CString qrCode;
	epEditCtr.GetWindowText(qrCode);
	Epo epo(qrCode);
	CTime now=CTime::GetCurrentTime();
	CString nowStr=now.Format(_T("%Y%m%d%H%M"));
	epEditCtr.SetWindowText("");
	if (epo.isLegal(now))
	{
	}else{
		MessageBox("扫描银浆不合法!");
		return;
	}
	FILE *pFile=fopen("epo.dll","w");
	fwrite(qrCode+";"+nowStr,1,strlen(qrCode+";"+nowStr),pFile);
	fclose(pFile);

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
	CString str[4] = { TEXT("WaferSource"),TEXT("WaferLot"), TEXT("刷胶前重量"),TEXT("Plasma剩余时间(分钟)")};
	for (size_t i = 0; i < 4; i++)
	{
		firstWeighWaferListCtr.InsertColumn(i, str[i], LVCFMT_LEFT, 100);
	}
	//设置风格  整行选中 加入网格线
	firstWeighWaferListCtr.SetExtendedStyle(firstWeighWaferListCtr.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	firstWeighWaferListCtr.AdjustColumnWidth();
	completeFirstWeighWaferListCtr();
}
//初始化第二次称重的listCtr
void CWbcDlg::initSecondWeighWaferListCtr(){
	CString str[4] = { TEXT("WaferLot"),TEXT("刷胶前重量"), TEXT("刷胶后重量"),TEXT("胶重")};
	for (int i=0;i<4;i++)
	{
		secondWeighWaferListCtr.InsertColumn(i,str[i],LVCFMT_LEFT,100);
	}
	secondWeighWaferListCtr.SetExtendedStyle(secondWeighWaferListCtr.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	secondWeighWaferListCtr.AdjustColumnWidth();
}
//填充第一次称重的listCtr
void CWbcDlg::completeFirstWeighWaferListCtr(){
	//将第一次称重还未进行第二次称重的数据填充到表格
	CString msg;
	MySqlUtil mysql(msg);
	CString sql="SELECT wafer_source,wafer_lot,weight from wbc20_first_weigh_record";
	mysql.SelectDataAndToList(sql,msg,&firstWeighWaferListCtr);
	refreshPlasmaRemainTime();
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
		if (waferSelectListCtr.GetItemCount()==0)
		{
			MessageBox("未查询到芯片信息!");
			return;
		}
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
	//关联芯片查询listCtr
	CRect  rect; //定义矩形区域
	GetDlgItem(IDC_LIST1) -> GetWindowRect(&rect);  //获得控件相对于屏幕的位置坐标
	if(rect.PtInRect(point))  //右击点在指定控件上
	{
		CMenu popMenu;//弹出菜单
		popMenu.LoadMenu(IDR_MENU1);//根据资源ID关联菜单资源
		CMenu * subMenu = popMenu.GetSubMenu(0);//获得第0列子菜单的指针
		subMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, point.x, point.y, this);  //在指定位置显示浮动弹出菜单，并追踪弹出菜单中被选择的项
	}
	//关联刷胶前称重listCtr
	CRect  rect2; //定义矩形区域
	GetDlgItem(IDC_LIST2) -> GetWindowRect(&rect2);  //获得控件相对于屏幕的位置坐标
	if(rect2.PtInRect(point))  //右击点在指定控件上
	{
		CMenu popMenu;//弹出菜单
		popMenu.LoadMenu(IDR_MENU2);//根据资源ID关联菜单资源
		CMenu * subMenu = popMenu.GetSubMenu(0);//获得第0列子菜单的指针
		subMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, point.x, point.y, this);  //在指定位置显示浮动弹出菜单，并追踪弹出菜单中被选择的项
	}
	
}

//点击刷胶前称重菜单
void CWbcDlg::OnMenuitem32771() 
{
	// TODO: Add your command handler code here
	CString waferLot;
	CString waferSource;
	int row = waferSelectListCtr.GetSelectionMark();
	waferLot=waferSelectListCtr.GetItemText(row, 1);
	waferSource=waferSelectListCtr.GetItemText(row,0);
	if (waferLot.IsEmpty())
	{
		MessageBox("当前未选中任何wafer!");
		return;
	}
	//手动模式
	if (weigthMode=="1")
	{
		manualFirstWeigh(waferLot,waferSource,row);
	}
}
//刷胶后称重
void CWbcDlg::OnMenuitem32772() 
{
	// TODO: Add your command handler code here
	CString plasmaRemain;
	int currentRow =firstWeighWaferListCtr.GetSelectionMark();
	plasmaRemain=firstWeighWaferListCtr.GetItemText(currentRow,3);
	int minutes=atoi(plasmaRemain);
	CString waferLot=firstWeighWaferListCtr.GetItemText(currentRow,1);
	if (waferLot.IsEmpty())
	{
		MessageBox("当前未选中任何wafer!");
		return;
	}
	if (minutes<=0)
	{
		MessageBox("Plasma不满足第二次称重的条件!");
		return;
	} 
	//手动模式
	if (weigthMode=="1")
	{

	}
}



//手动第一次称重从wafer查询类别中选中
void CWbcDlg::manualFirstWeigh(CString waferLot,CString waferSource, int currentRow){
	for (int i=0;i<firstWeighWaferListCtr.GetItemCount();i++)
	{
		CString currentWaferLot=firstWeighWaferListCtr.GetItemText(i,1);
		if (currentWaferLot==waferLot)
		{
			if(MessageBox(TEXT("已有称重数据,是否再次称重?"),TEXT("再次确认"),MB_OKCANCEL)!=IDOK)
			{
				return;
			}
			break;
		}
	}
	ManualWeighDialog dlg;
	dlg.waferLot=waferLot;
	dlg.DoModal();
	waferSelectListCtr.SetItemText(currentRow,2,dlg.manualWeighValue);
	//传来的重量数据非空
	if (!dlg.manualWeighValue.IsEmpty())
	{
		//保存或更新该wafer的第一次称重记录
		try
		{
			CString msg;
			MySqlUtil mysql(msg);
			CString sql;
			sql.Format("INSERT INTO wbc20_first_weigh_record (wafer_lot, wafer_source, weight) VALUES ('%s','%s','%s') ON DUPLICATE KEY UPDATE weight='%s'",waferLot,waferSource,dlg.manualWeighValue,dlg.manualWeighValue);
			mysql.InsertData(sql,msg);
			firstWeighWaferListCtr.DeleteAllItems();
			//重新初始化
			completeFirstWeighWaferListCtr();
		}
		catch (const char * info)
		{
			MessageBox(info);
		}
	}
}
//手动第一次称重
void CWbcDlg::manualFirstWeigh(CString waferLot,CString waferSource){
	for (int i=0;i<firstWeighWaferListCtr.GetItemCount();i++)
	{
		CString currentWaferLot=firstWeighWaferListCtr.GetItemText(i,1);
		if (currentWaferLot==waferLot)
		{
			if(MessageBox(TEXT("已有称重数据,是否再次称重?"),TEXT("再次确认"),MB_OKCANCEL)!=IDOK)
			{
				return;
			}
			break;
		}
	}
	ManualWeighDialog dlg;
	dlg.waferLot=waferLot;
	dlg.DoModal();
	//传来的重量数据非空
	if (!dlg.manualWeighValue.IsEmpty())
	{
		//保存或更新该wafer的第一次称重记录
		try
		{
			CString msg;
			MySqlUtil mysql(msg);
			CString sql;
			sql.Format("INSERT INTO wbc20_first_weigh_record (wafer_lot, wafer_source, weight) VALUES ('%s','%s','%s') ON DUPLICATE KEY UPDATE weight='%s'",waferLot,waferSource,dlg.manualWeighValue,dlg.manualWeighValue);
			mysql.InsertData(sql,msg);
			firstWeighWaferListCtr.DeleteAllItems();
			//重新初始化
			completeFirstWeighWaferListCtr();
		}
		catch (const char * info)
		{
			MessageBox(info);
		}
	}
}
//手动第二次称重
void CWbcDlg::manualSecondWeigh(CString waferLot){

}

//定时器处理
void CWbcDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent==IDTIMER1)
	{
		refreshPlasmaRemainTime();
	}
	if (nIDEvent==IDTIMER2)
	{
		refreshEpoRemainTime();
	}
	
	CDialog::OnTimer(nIDEvent);
}

//刷新Plasma剩余时间
void CWbcDlg::refreshPlasmaRemainTime(){
	CString msg;
	MySqlUtil mysql(msg);
	//遍历表格;取每一行的waferLot;查询该wafer的Plasma剩余时间
	for (int i=0;i<firstWeighWaferListCtr.GetItemCount();i++)
	{
		CString waferLot=firstWeighWaferListCtr.GetItemText(i,1);
		CString sql;
		sql.Format("SELECT 30-TIMESTAMPDIFF(MINUTE, in_time, NOW()),is_over_count from plasma_rec WHERE wl='%s' ORDER BY r_id DESC LIMIT 1",waferLot);
		CStringArray array;
		mysql.SelectData(sql,msg,array);
		if (array.GetSize()==2)
		{
			if (array.GetAt(1)=="1")
			{
				firstWeighWaferListCtr.SetItemText(i,3,array.GetAt(0)+"***清洗超次");
			}else firstWeighWaferListCtr.SetItemText(i,3,array.GetAt(0));
		}else{
			firstWeighWaferListCtr.SetItemText(i,3,"无记录");
		}
	}
}
//刷新银浆上机时间
void CWbcDlg::refreshEpoRemainTime()
{
	//读取上次上胶时间
	CFile file;
	bool state=file.Open("epo.dll",CFile::modeRead,NULL); 
	if (!state)
	{
		MessageBox("打开银浆本地存储文件失败!");
		return;
	}
	int i=0;
	DWORD len=file.GetLength( );
	char * arr=new char[len+1];
	arr[len]=0;  //0终止字符串，用于输出。
	file.Read(arr,len);   //Read( void* lpBuf, UINT nCount ) lpBuf是用于接收读取到的数据的Buf指针nCount是从文件读取的字节数
	file.Close();
	CString epoStr(arr);
	CStringArray array;
	MyUtils::splitStr(epoStr,';',array);
	CTime lastDate=MyUtils::strToCTime(array.GetAt(5));
	CString str=lastDate.Format(_T("%Y%m%d%H%M"));
	MessageBox(str);
	CTime now=CTime::GetCurrentTime();
	CTimeSpan span=now-lastDate;
	CString msg;
	msg.Format("%d",span.GetMinutes());
	delete arr;
	
}
//自定义绘制
void CWbcDlg::OnCustomdrawMyList( NMHDR* pNMHDR, LRESULT* pResult){
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );
	
    // Take the default processing unless we set this to something else below.
    *pResult = 0;
	
    // First thing - check the draw stage. If it's the control's prepaint
    // stage, then tell Windows we want messages for every item.
    if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	{
        *pResult = CDRF_NOTIFYITEMDRAW;
	}
	
	// This is the notification message for an item. We'll request
	// notifications before each subitem's prepaint stage.
	else if ( pLVCD->nmcd.dwDrawStage==CDDS_ITEMPREPAINT )
	{
		COLORREF m_crTextBk , m_clrText;
		int nItem = static_cast<int> (pLVCD->nmcd.dwItemSpec);
		
		// 判断使ListCtrl不同颜色现实的条件
		CString strTemp = firstWeighWaferListCtr.GetItemText(nItem,3);
		int state=atoi(strTemp);
		if (state>0)
		{
			m_clrText = RGB(0,0,0);
		}
		else
		{
			m_clrText = RGB(255,0,0);
		}
		pLVCD->clrText = m_clrText;
		*pResult = CDRF_DODEFAULT;
	}
}


