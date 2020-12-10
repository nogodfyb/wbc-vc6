// wbcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "wbc.h"
#include "wbcDlg.h"
#include "CheckToolsDlg.h"
#include "ValiadteUtils.h"
#include "MyUtils.h"
#include "SettingDialog.h"
#include "ManualWeighDialog.h"
#include "Epo.h"
#include "MyRepository.h"
#include "ShiftUtils.h"
#include "ExceptionRegisterDialog.h"
#include "AdminMainDialog.h"

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
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST3, OnCustomdrawMyList2)
	ON_COMMAND(ID_MENUITEM32772, OnMenuitem32772)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_COMMAND(ID_MENUITEM32773, OnMenuitem32773)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnDblclkList2)
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
	//初始化一些简单变量
	needRestoreTimer=false;

	CString msg;
	MySqlUtil mysql;
	try
	{
		mysql.ConnMySQL(msg);
	}
	catch (const char * info)
	{
		MessageBox(info);
		MessageBox(msg);
	}


	initSelectWaferListCtr(); //初始化查询wafer信息列表的结果控件
	initPlanIdCbxCtr(); //初始化计划下拉框控件
	initFirstWeighWaferListCtr(mysql,msg); //初始化第一次称重的listCtr
	initSecondWeighWaferListCtr(); //初始化第二次称重的listCtr
	matchTools(mysql,msg); //匹配刷胶工具和银浆
	getSetting(); //读取配置信息
	//创建定时器
	SetTimer(IDTIMER1,5000,0); //定时刷新plasma剩余时间
	SetTimer(IDTIMER2,5000,0); //定时刷新银浆上机剩余时间
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

void CWbcDlg::OnScanWafer()//点检扫描wafer
{
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
		//设置上次点检工具信息
		lastCheckScraperSn=dlg.expectedScraper;
		lastCheckSteelMeshSn=dlg.expectedSteelMesh;
		lastCheckShimSn=dlg.expectedShim;
	}else{
		MessageBox("芯片二维码格式不正确!");
	}
	waferCtr.SetWindowText("");
}
void CWbcDlg::OnScanWaferFistWeigh()//第一次称重前扫描wafer
{
	CString wafer;
	firstWeighWaferEditCtr.GetWindowText(wafer);
	firstWeighWaferEditCtr.SetWindowText("");
	if (ValiadteUtils::validateWafer(wafer))
	{
		CStringArray array;
		MyUtils::splitStr(wafer,'^',array);
		CString waferLot=array.GetAt(3);
		CString waferSource=array.GetAt(1);
		CString waferDevice=array.GetAt(0);
		manualFirstWeigh(waferLot,waferSource,waferDevice);
	} 
	else
	{
		MessageBox("芯片二维码格式不正确");
	}
}

void CWbcDlg::OnScanEp()//扫银浆
{
	CString qrCode;
	epEditCtr.GetWindowText(qrCode);
	epEditCtr.SetWindowText("");
	if (!ValiadteUtils::validateEpo(qrCode))
	{
		MessageBox("扫描银浆不合法!");
		return;
	}
	Epo epo(qrCode);
	CTime now=CTime::GetCurrentTime();
	CString nowStr=now.Format(_T("%Y%m%d%H%M"));
	if (!epo.isLegal(now))
	{
		MessageBox("银浆已过期!");
		return;
	}
	MessageBox("银浆已上机!");
	//恢复刷新银浆上机时间的定时器
	if (needRestoreTimer)
	{
		SetTimer(IDTIMER2,5000,0);
		needRestoreTimer=false;
	}
	FILE *pFile=fopen("epo.dll","w");
	fwrite(qrCode+";"+nowStr,1,strlen(qrCode+";"+nowStr),pFile);
	fclose(pFile);
	refreshEpoRemainTime();
}
//初始化芯片查询的listCtr
void CWbcDlg::initSelectWaferListCtr(){
	CString str[4] = { TEXT("WaferSource"),TEXT("WaferLot"), TEXT("WaferDevice"),TEXT("刷胶前重量")};
	for (size_t i = 0; i < 4; i++)
	{
		waferSelectListCtr.InsertColumn(i, str[i], LVCFMT_LEFT, 100);
	}
	//设置风格  整行选中 加入网格线
	waferSelectListCtr.SetExtendedStyle(waferSelectListCtr.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	waferSelectListCtr.AdjustColumnWidth();
}

//初始化第一次称重的listCtr
void CWbcDlg::initFirstWeighWaferListCtr(MySqlUtil &mysql,CString &msg){
	CString str[6] = { TEXT("WaferSource"),TEXT("WaferLot"), TEXT("刷胶前重量"),TEXT("Plasma(剩余分钟)"),TEXT("刷胶工具"),TEXT("银浆")};
	for (size_t i = 0; i < 6; i++)
	{
		firstWeighWaferListCtr.InsertColumn(i, str[i], LVCFMT_LEFT, 100);
	}
	//设置风格  整行选中 加入网格线
	firstWeighWaferListCtr.SetExtendedStyle(firstWeighWaferListCtr.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	firstWeighWaferListCtr.AdjustColumnWidth();
	completeFirstWeighWaferListCtr(mysql,msg);
}
//初始化第二次称重的listCtr
void CWbcDlg::initSecondWeighWaferListCtr(){
	CString str[7] = { TEXT("WaferSource"),TEXT("WaferLot"),TEXT("刷胶前重量"), TEXT("刷胶后重量"),TEXT("胶重"),TEXT("异常登记"),TEXT("标准")};
	for (int i=0;i<7;i++)
	{
		secondWeighWaferListCtr.InsertColumn(i,str[i],LVCFMT_LEFT,100);
	}
	secondWeighWaferListCtr.SetExtendedStyle(secondWeighWaferListCtr.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);
	secondWeighWaferListCtr.AdjustColumnWidth();
}
//填充第一次称重的listCtr
void CWbcDlg::completeFirstWeighWaferListCtr(MySqlUtil &mysql,CString &msg){
	//将第一次称重还未进行第二次称重的数据填充到表格
	try
	{
		CString sql="SELECT wafer_source,wafer_lot,weight from wbc20_first_weigh_record";
		mysql.SelectDataAndToList(sql,msg,&firstWeighWaferListCtr);
	}
	catch (const char *info)
	{
		MessageBox(info);
		return;
	}
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
void CWbcDlg::OnButton1() //芯片查询
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
		sql.Format("SELECT ws,wl,tt from wafer_list_mes_org WHERE schid='%s'",planDate+"-"+planId);
		mysql.SelectDataAndToList(sql,msg,&waferSelectListCtr);
		if (waferSelectListCtr.GetItemCount()==0)
		{
			MessageBox("未查询到芯片信息!");
			return;
		}
	}
	catch (const char * info)
	{
		MessageBox(info);
		return;
	}
	completeWaferSelectListCtr();
}

void CWbcDlg::completeWaferSelectListCtr()//填充查询listCtr
{

	//如果列表不为空;遍历每一行从第一次称重记录里查询第一次称重数据;并在该行填充
	for (int i=0;i<waferSelectListCtr.GetItemCount();i++)
	{
		CString waferLot=waferSelectListCtr.GetItemText(i,1);
		//遍历第一次称重记录
		for (int j=0;j<firstWeighWaferListCtr.GetItemCount();j++)
		{
			CString expectWaferLot=firstWeighWaferListCtr.GetItemText(j,1);
			if (waferLot==expectWaferLot)
			{
				waferSelectListCtr.SetItemText(i,3,firstWeighWaferListCtr.GetItemText(j,2));
				break;
			}else{
				waferSelectListCtr.SetItemText(i,3,"");
			}
		}

	}
}

//弹出设置窗口
void CWbcDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	SettingDialog dlg;
	dlg.DoModal();
	
}
void CWbcDlg::OnButton3() //提交称重记录
{
	// TODO: Add your control notification handler code here
	//遍历所有行，查看是否有被选中的
	bool flag=false;
	for (int i=0;i<secondWeighWaferListCtr.GetItemCount();i++)
	{
		flag=secondWeighWaferListCtr.GetCheck(i);
		if (flag)
		{
			break;
		}
	}
	if (!flag)
	{
		MessageBox("未选中任何需要提交的记录!");
		return;
	}
	//得到当前班次
	ShiftUtils shiftUtils;
	CString shift=shiftUtils.getShiftByNow();
	//查询当次点检人工号
	CString msg;
	MySqlUtil mysql;
	CStringArray array;
	//第一次称重列表的行数
	int length;
	//工号
	CString bn;
	//机器号
	CString machineCode;
	try
	{
		mysql.ConnMySQL(msg);
		CString sql;
		CString id;
		idTextCtr.GetWindowText(id);
		sql.Format("SELECT bn from wbc20_check_record WHERE id='%s'",id);
		mysql.SelectData(sql,msg,array);
		bn=array.GetAt(0);
		machineCode="2FC01";
		length=secondWeighWaferListCtr.GetItemCount();

	}
	catch (const char * info)
	{
		MessageBox(info);
		return;
	}
	//开启事务
	mysql.beginTransaction();
	try
	{
		for (int k=length-1;k>=0;k--)
		{
			bool check=secondWeighWaferListCtr.GetCheck(k);
			if (!check)
			{
				continue;	
			}
			CString waferLot=secondWeighWaferListCtr.GetItemText(k,1);
			CString firstWeight=secondWeighWaferListCtr.GetItemText(k,2);
			CString secondWeight=secondWeighWaferListCtr.GetItemText(k,3);
			CString waferSource=secondWeighWaferListCtr.GetItemText(k,0);
			//根据waferLot查询第一次称重的时间
			CString sql2;
			CStringArray array2;
			sql2.Format("SELECT update_time,wafer_device from wbc20_first_weigh_record WHERE wafer_lot='%s'",waferLot);
			mysql.SelectData(sql2,msg,array2);
			CString firstWeighTime=array2.GetAt(0);
			CString waferDevice=array2.GetAt(1);
			//根据waferSource查询waferSize
			CString sql3;
			CStringArray array3;
			sql3.Format("SELECT wafer_size from wbc20_tool_rule WHERE wafer_source='%s'",waferSource);
			mysql.SelectData(sql3,msg,array3);
			//如果数据库中存在对应关系
			CString waferSize;
			if (array3.GetSize()==1)
			{
				waferSize=array3.GetAt(0);
			}
			//根据waferLot查询存储到map中的异常登记记录
			CString exceptionReason;
			CString handlePlan;
			CString remark;
			CString handleResult;
			CString exceptionRecord;
			CString dealPerson;
			bool state=exceptionMap.Lookup(waferLot,exceptionRecord);
			if (state)
			{
				CStringArray result;
				MyUtils::splitStr(exceptionRecord,';',result);
				exceptionReason=result.GetAt(0);
				handlePlan=result.GetAt(1);
				remark=result.GetAt(2);
				handleResult=result.GetAt(3);
				dealPerson=result.GetAt(4);
			}
			//根据waferSource查询刮刀寿命
			CString sql4;
			CStringArray array4;
			sql4.Format("SELECT scraper_sn,life-1 from wbc20_tool_rule,wbc20_tool WHERE wafer_source='%s' AND scraper_sn=sn",waferSource);
			mysql.SelectData(sql4,msg,array4);
			CString scraperLife;
			if (array4.GetSize()==2)
			{
				scraperLife=array4.GetAt(1);
			}
			//根据waferSource查询钢网寿命
			CString sql5;
			CStringArray array5;
			sql5.Format("SELECT steel_mesh_sn,life-1 from wbc20_tool_rule,wbc20_tool WHERE wafer_source='%s' AND steel_mesh_sn=sn",waferSource);
			mysql.SelectData(sql5,msg,array5);
			CString steelMeshLife;
			if (array5.GetSize()==2)
			{
				steelMeshLife=array5.GetAt(1);
			}
			//根据waferSource查询垫片寿命
			CString sql6;
			CStringArray array6;
			sql6.Format("SELECT shim_sn,life-1 from wbc20_tool_rule,wbc20_tool WHERE wafer_source='%s' AND shim_sn=sn",waferSource);
			mysql.SelectData(sql6,msg,array6);
			CString shimLife;
			if (array6.GetSize()==2)
			{
				shimLife=array6.GetAt(1);
			}
			//胶重是否超过标准
			CString overWeight=secondWeighWaferListCtr.GetItemText(k,6);
			
			
			
			CStringArray params;
			params.Add(shift);//参数1 班次
			params.Add(bn);//参数2 工号
			params.Add(machineCode);//参数3 机器号
			params.Add(currentEpo.serialNumber);//参数4 银浆序列号
			params.Add(currentEpo.beginTimeStr);//参数5 银浆解冻完成时间
			params.Add(currentEpo.exceedTimeStr);//参数6 银浆过期时间
			params.Add(firstWeight);//参数7 第一次称重的重量
			params.Add(firstWeighTime); //参数8 第一次称重时间
			params.Add(secondWeight);//参数9 第二次称重重量
			params.Add(waferDevice);//参数10 芯片型号
			params.Add(waferSource);//参数11 waferSource
			params.Add(waferLot);//参数12 waferLot 
			params.Add(waferSize);//参数13 waferSize
			params.Add(overWeight);//参数14 是否超重
			params.Add(lastCheckScraperSn);//参数15 刮刀sn
			params.Add(lastCheckSteelMeshSn);//参数16 钢网sn
			params.Add(lastCheckShimSn);//参数17 垫片sn
			params.Add(exceptionReason);//参数18 异常原因
			params.Add(handlePlan); //参数19 处理方案
			params.Add(remark);//参数20 备注
			params.Add(handleResult);//参数21 处理结果
			params.Add(scraperLife);//参数22 刮刀寿命
			params.Add(steelMeshLife);//参数23 钢网寿命
			params.Add(shimLife);//参数24 垫片寿命
			params.Add(dealPerson);//参数25 处理人
			CString insertSql=MyRepository::insertSecondWeighRecord(params);
			mysql.InsertData(insertSql,msg);
			//更新各个工具的寿命
			CString sql7;
			sql7.Format("UPDATE wbc20_tool SET life=life-1 WHERE sn in ('%s','%s','%s')",array4.GetAt(0),array5.GetAt(0),array6.GetAt(0));
			mysql.UpdateData(sql7,msg);
			//提交称重记录之后 删除该wafer第一次称重记录
			CString sql8;
			sql8.Format("DELETE from wbc20_first_weigh_record WHERE wafer_lot='%s'",waferLot);
			mysql.DeleteData(sql8,msg);

			secondWeighWaferListCtr.DeleteItem(k);
			//删除查询列表的该waferLot行
			for (int m=0;m<waferSelectListCtr.GetItemCount();m++)
			{
				CString expectWaferLot=waferSelectListCtr.GetItemText(m,1);
				if (waferLot==expectWaferLot)
				{
					waferSelectListCtr.DeleteItem(m);
					break;
				}
			}
		}
	}
	catch (const char * info)
	{
		MessageBox(info);
		MessageBox(msg);
		//回滚,不提交
		mysql.rollbackTransaction();
		return;
	}
	mysql.commitTransaction();
	//更新第一次称重记录表
	firstWeighWaferListCtr.DeleteAllItems();
	//completeFirstWeighWaferListCtr();
	
}

//读取配置信息
void CWbcDlg::getSetting(){
	// TODO: Add your control notification handler code here
	CFile file;
	bool state=file.Open("setting.ini",CFile::modeRead,NULL); 
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
	//关联异常登记菜单
	CRect  rect3; //定义矩形区域
	GetDlgItem(IDC_LIST3) -> GetWindowRect(&rect3);  //获得控件相对于屏幕的位置坐标
	if(rect3.PtInRect(point))  //右击点在指定控件上
	{
		CMenu popMenu;//弹出菜单
		popMenu.LoadMenu(IDR_MENU3);//根据资源ID关联菜单资源
		CMenu * subMenu = popMenu.GetSubMenu(0);//获得第0列子菜单的指针
		subMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, point.x, point.y, this);  //在指定位置显示浮动弹出菜单，并追踪弹出菜单中被选择的项
	}
}

//点击刷胶前称重菜单
void CWbcDlg::OnMenuitem32771() //刷胶前称重
{
	// TODO: Add your command handler code here
	CString waferLot;
	CString waferSource;
	int row = waferSelectListCtr.GetSelectionMark();
	waferLot=waferSelectListCtr.GetItemText(row, 1);
	waferSource=waferSelectListCtr.GetItemText(row,0);
	CString waferDevice=waferSelectListCtr.GetItemText(row,2);
	if (waferLot.IsEmpty())
	{
		MessageBox("当前未选中任何wafer!");
		return;
	}
	//手动模式
	if (weigthMode=="1")
	{
		manualFirstWeigh(waferLot,waferSource,waferDevice,row);
	}
}
void CWbcDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) //刷胶前称重
{
	// TODO: Add your control notification handler code here
	CString waferLot;
	CString waferSource;
	int row = waferSelectListCtr.GetSelectionMark();
	waferLot=waferSelectListCtr.GetItemText(row, 1);
	waferSource=waferSelectListCtr.GetItemText(row,0);
	CString waferDevice=waferSelectListCtr.GetItemText(row,2);
	if (waferLot.IsEmpty())
	{
		MessageBox("当前未选中任何wafer!");
		return;
	}
	//手动模式
	if (weigthMode=="1")
	{
		manualFirstWeigh(waferLot,waferSource,waferDevice,row);
	}
	*pResult = 0;
}
void CWbcDlg::OnMenuitem32772() //删除第一次称重记录
{
	// TODO: Add your command handler code here
	if(MessageBox(TEXT("是否确认删除?"),TEXT("删除第一次称重记录"),MB_OKCANCEL)!=IDOK)
	{
		return;
	}
	int currentRow =firstWeighWaferListCtr.GetSelectionMark();
	CString waferLot=firstWeighWaferListCtr.GetItemText(currentRow,1);
	if (waferLot.IsEmpty())
	{
		MessageBox("当前未选中任何wafer!");
		return;
	}
	try
	{
		CString msg;
		MySqlUtil mysql(msg);
		CString sql;
		sql.Format("DELETE FROM wbc20_first_weigh_record WHERE wafer_lot='%s'",waferLot);
		mysql.DeleteData(sql,msg);
		MessageBox("删除成功!");
		firstWeighWaferListCtr.DeleteItem(currentRow);
	}
	catch (const char * info)
	{
		MessageBox(info);
		return;
	}
	completeWaferSelectListCtr();
}
void CWbcDlg::OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult) //刷胶后称重
{
	// TODO: Add your control notification handler code here
	CString plasmaRemain;
	int currentRow =firstWeighWaferListCtr.GetSelectionMark();
	plasmaRemain=firstWeighWaferListCtr.GetItemText(currentRow,3);
	//剩余分钟数
	int minutes=atoi(plasmaRemain);
	//刷胶工具匹配情况
	CString toolsMatch=firstWeighWaferListCtr.GetItemText(currentRow,4);
	//银浆匹配情况
	CString epoMatch=firstWeighWaferListCtr.GetItemText(currentRow,5);
	CString waferLot=firstWeighWaferListCtr.GetItemText(currentRow,1);
	CString waferSource=firstWeighWaferListCtr.GetItemText(currentRow,0);
	CString firstWeight=firstWeighWaferListCtr.GetItemText(currentRow,2);
	if (waferLot.IsEmpty())
	{
		MessageBox("当前未选中任何wafer!");
		return;
	}

	if (currentEpoRunTime>120)
	{
		MessageBox("银浆上机时间已超过2小时!");
		return;
	}
	if (minutes<=0||toolsMatch!="匹配"||epoMatch!="匹配")
	{
		MessageBox("不满足第二次称重的条件!");
		return;
	} 

	//手动模式
	if (weigthMode=="1")
	{
		manualSecondWeigh(waferLot,waferSource,firstWeight);
	}
	
	*pResult = 0;
}
void CWbcDlg::OnMenuitem32773() //异常登记
{
	// TODO: Add your command handler code here
	int currentRow =secondWeighWaferListCtr.GetSelectionMark();
	CString waferLot=secondWeighWaferListCtr.GetItemText(currentRow,1);
	if (waferLot.IsEmpty())
	{
		MessageBox("当前未选中任何wafer!");
		return;
	}
	ExceptionRegisterDialog dlg;
	dlg.waferLot=waferLot;
	//模态窗口关闭前查询当前waferLot有无存储异常登记信息
	CString exceptionRecordBefore;
	bool beforeState=exceptionMap.Lookup(waferLot,exceptionRecordBefore);
	if (beforeState)
	{
		dlg.exceptionRecordBefore=exceptionRecordBefore;
	}
	dlg.DoModal();
	//模态窗口关闭后查询当前waferLot有无存储异常登记信息
	CString exceptionRecordAfter;
	bool afterState=exceptionMap.Lookup(waferLot,exceptionRecordAfter);
	//已登记
	if (afterState)
	{
		//查询waferLot所在行
		for (int i=0;i<secondWeighWaferListCtr.GetItemCount();i++)
		{
			CString currentWaferLot=secondWeighWaferListCtr.GetItemText(i,1);
			if (waferLot==currentWaferLot)
			{
				secondWeighWaferListCtr.SetItemText(i,5,"已登记");
			}
		}
	}

}

void CWbcDlg::matchTools(MySqlUtil &mysql,CString &msg)//匹配刷胶工具和银浆
{

	CString lastCheckId;
	idTextCtr.GetWindowText(lastCheckId);
	try
	{
		mysql.ConnMySQL(msg);
	}
	catch (const char * info)
	{
		MessageBox(info);
		return;
	}
	for (int i=0;i<firstWeighWaferListCtr.GetItemCount();i++)
	{

		CString waferSource=firstWeighWaferListCtr.GetItemText(i,0);
		if (lastCheckId=="******"||lastCheckId.IsEmpty())
		{
			//设置刷胶工具那一列
			firstWeighWaferListCtr.SetItemText(i,4,"未点检");
			continue;
		}

		CStringArray array;
		try
		{
			CString sql;
			sql.Format("SELECT steel_mesh_sn,shim_sn,scraper_sn,ep_pn from wbc20_tool_rule WHERE wafer_source='%s'",waferSource);
			mysql.SelectData(sql,msg,array);
		}
		catch (const char * info)
		{
			MessageBox(info);
			return;
		}
		if (array.GetSize()!=4)
		{
			firstWeighWaferListCtr.SetItemText(i,4,"异常");
			continue;
		}
		if (currentEpo.partNumber!=array.GetAt(3))
		{
			//设置银浆工具那一列
			firstWeighWaferListCtr.SetItemText(i,5,"不匹配");
		}else{
			firstWeighWaferListCtr.SetItemText(i,5,"匹配");
		}
		if(lastCheckSteelMeshSn!=array.GetAt(0)||lastCheckShimSn!=array.GetAt(1)||lastCheckScraperSn!=array.GetAt(2)){
			firstWeighWaferListCtr.SetItemText(i,4,"不匹配");
			continue;
		}
		firstWeighWaferListCtr.SetItemText(i,4,"匹配");
	}
}
//手动第一次称重从wafer查询类别中选中
void CWbcDlg::manualFirstWeigh(CString waferLot,CString waferSource,CString waferDevice, int currentRow){
	bool cover=false;
	int needCoveredRow=0;
	for (int i=0;i<firstWeighWaferListCtr.GetItemCount();i++)
	{
		CString currentWaferLot=firstWeighWaferListCtr.GetItemText(i,1);
		if (currentWaferLot==waferLot)
		{
			if(MessageBox(TEXT("已有称重数据,是否再次称重?"),TEXT("再次确认"),MB_OKCANCEL)!=IDOK)
			{
				return;
			}
			cover=true;
			needCoveredRow=i;
			break;
		}
	}
	ManualWeighDialog dlg;
	dlg.waferLot=waferLot;
	dlg.DoModal();
	//传来的重量数据非空
	if (!dlg.manualWeighValue.IsEmpty())
	{
		if (currentRow!=NULL)
		{
			waferSelectListCtr.SetItemText(currentRow,3,dlg.manualWeighValue);
		}
		//保存或更新该wafer的第一次称重记录
		try
		{
			CString msg;
			MySqlUtil mysql(msg);
			CString sql;
			sql.Format("INSERT INTO wbc20_first_weigh_record (wafer_lot, wafer_source,wafer_device, weight) VALUES ('%s','%s','%s','%s') ON DUPLICATE KEY UPDATE weight='%s'",waferLot,waferSource,waferDevice,dlg.manualWeighValue,dlg.manualWeighValue);
			mysql.InsertData(sql,msg);
			//如果是覆盖
			if (cover)
			{
				firstWeighWaferListCtr.SetItemText(needCoveredRow,2,dlg.manualWeighValue);
			}else{
				//向第一次称重列表尾部添加一行
				int endRow=firstWeighWaferListCtr.GetItemCount();
				firstWeighWaferListCtr.InsertItem(endRow,waferSource);
				firstWeighWaferListCtr.SetItemText(endRow,1,waferLot);
				firstWeighWaferListCtr.SetItemText(endRow,2,dlg.manualWeighValue);
			}
			refreshPlasmaRemainTime();
			//matchTools();
		}
		catch (const char * info)
		{
			MessageBox(info);
			return;
		}
	}
}
//手动第一次称重
void CWbcDlg::manualFirstWeigh(CString waferLot,CString waferSource,CString waferDevice){
	manualFirstWeigh(waferLot,waferSource,waferDevice,NULL);
}
//手动第二次称重
void CWbcDlg::manualSecondWeigh(CString waferLot,CString waferSource,CString firstWeight){
	//根据waferSource查询waferSize


	CString waferSize;
	try
	{
		CString msg;
		MySqlUtil mysql(msg);
		CString sql3;
		CStringArray array3;
		sql3.Format("SELECT wafer_size from wbc20_tool_rule WHERE wafer_source='%s'",waferSource);
		mysql.SelectData(sql3,msg,array3);
		if (array3.GetSize()==1)
		{
			waferSize=array3.GetAt(0);
		}else{
			MessageBox("未查询到waferSize!请联系管理员!");
			return;
		}
	}
	catch (const char * info)
	{
		MessageBox(info);
		return;
	}
	for (int i=0;i<secondWeighWaferListCtr.GetItemCount();i++)
	{
		CString currentWaferLot=secondWeighWaferListCtr.GetItemText(i,1);
		if (currentWaferLot==waferLot)
		{
			if(MessageBox(TEXT("已有称重数据,是否再次称重?"),TEXT("再次确认"),MB_OKCANCEL)!=IDOK)
			{
				return;
			}
			//重新称重
			ManualWeighDialog dlg;
			dlg.waferLot=waferLot;
			dlg.DoModal();
			if (!dlg.manualWeighValue.IsEmpty())
			{
				secondWeighWaferListCtr.SetItemText(i,3,dlg.manualWeighValue);
				double epWeight=atof(dlg.manualWeighValue)-atof(firstWeight);
				CString epWeightStr;
				epWeightStr.Format("%g", epWeight);
				secondWeighWaferListCtr.SetItemText(i,4,epWeightStr);
				bool over=ValiadteUtils::validateEpoWeight(waferSize,epWeightStr);
				CString overWeight;
				over?overWeight="OK":overWeight="NG";
				secondWeighWaferListCtr.SetItemText(i,6,overWeight);
			}
			return;
		}
	}
	ManualWeighDialog dlg;
	dlg.waferLot=waferLot;
	dlg.DoModal();
	//传来的重量数据非空
	if (!dlg.manualWeighValue.IsEmpty())
	{
		int endRow=secondWeighWaferListCtr.GetItemCount();
		secondWeighWaferListCtr.InsertItem(endRow,waferSource);
		secondWeighWaferListCtr.SetItemText(endRow,1,waferLot);
		secondWeighWaferListCtr.SetItemText(endRow,2,firstWeight);
		secondWeighWaferListCtr.SetItemText(endRow,3,dlg.manualWeighValue);
		secondWeighWaferListCtr.SetItemText(endRow,5,"未登记");
		double epWeight=atof(dlg.manualWeighValue)-atof(firstWeight);
		CString epWeightStr;
		epWeightStr.Format("%g", epWeight);
		secondWeighWaferListCtr.SetItemText(endRow,4,epWeightStr);
		bool over=ValiadteUtils::validateEpoWeight(waferSize,epWeightStr);
		CString overWeight;
		over?overWeight="OK":overWeight="NG";
		secondWeighWaferListCtr.SetItemText(endRow,6,overWeight);
		secondWeighWaferListCtr.AdjustColumnWidth();
	}
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
void CWbcDlg::refreshPlasmaRemainTime()//刷新plasma时间
{
	CString msg;
	MySqlUtil mysql;
	try
	{
		mysql.ConnMySQL(msg);
	}
	catch (const char * info)
	{
		MessageBox(info);
		return;
	}
	//遍历表格;取每一行的waferLot;查询该wafer的Plasma剩余时间
	for (int i=0;i<firstWeighWaferListCtr.GetItemCount();i++)
	{
		
		CStringArray array;
		try
		{
			CString waferLot=firstWeighWaferListCtr.GetItemText(i,1);
			CString sql;
			sql.Format("SELECT 30-TIMESTAMPDIFF(MINUTE, in_time, NOW()),is_over_count from plasma_rec WHERE wl='%s' ORDER BY r_id DESC LIMIT 1",waferLot);
			mysql.SelectData(sql,msg,array);
		}
		catch (const char * info)
		{
			MessageBox(info);
			return;
		}
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
	firstWeighWaferListCtr.AdjustColumnWidth();
}
//刷新银浆上机时间
void CWbcDlg::refreshEpoRemainTime()
{
	//读取上次上胶时间
	CFile file;
	bool state=file.Open("epo.dll",CFile::modeRead,NULL); 
	if (!state)
	{
		//MessageBox("打开银浆本地存储文件失败!");
		epPromptTextCtr.SetWindowText("没有银浆扫描记录!记录文件不存在!");
		return;
	}
	DWORD len=file.GetLength( );
	char * arr=new char[len+1];
	arr[len]=0;  //0终止字符串，用于输出。
	file.Read(arr,len);   //Read( void* lpBuf, UINT nCount ) lpBuf是用于接收读取到的数据的Buf指针nCount是从文件读取的字节数
	file.Close();
	CString epoStr(arr);
	if (epoStr.IsEmpty())
	{
		epPromptTextCtr.SetWindowText("不存在银浆上机记录!");
		return;
	}
	//存储当前银浆信息
	currentEpo=Epo(epoStr);
	CStringArray array;
	MyUtils::splitStr(epoStr,';',array);
	//上一次扫描时间
	CTime lastDate=MyUtils::strToCTime(array.GetAt(5));
	CTime now=CTime::GetCurrentTime();
	CTimeSpan span=now-lastDate;
	currentEpoRunTime=span.GetTotalMinutes();
	CString lastScanTime;
	lastScanTime.Format("%d",120-span.GetTotalMinutes());
	epPromptTextCtr.SetWindowText("银浆上机有效时间还剩:"+lastScanTime+"分钟!银浆序列号:"+currentEpo.serialNumber+" 物料编码:"+currentEpo.partNumber);
	if (span.GetTotalMinutes()>=120)
	{
		//已超时
		epPromptTextCtr.SetWindowText("银浆上机已超过2小时!请重新点检!重新上银浆!");
		AfxMessageBox("银浆上机已超过2小时!请重新点检!重新上银浆!");
		//销毁定时器
		KillTimer(IDTIMER2);
		needRestoreTimer=true;
		//将点检id置为******
		idTextCtr.SetWindowText("******");
		GetDlgItem(IDC_BUTTON3)->EnableWindow(false);
	}else{
		GetDlgItem(IDC_BUTTON3)->EnableWindow(true);
	}
	delete arr;
	
}
//自定义绘制list2
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
		//刷胶工具匹配情况
		CString toolsMatch=firstWeighWaferListCtr.GetItemText(nItem,4);
		//银浆匹配情况
		CString epoMatch=firstWeighWaferListCtr.GetItemText(nItem,5);
		if (state>0&&toolsMatch=="匹配"&&epoMatch=="匹配")
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


//自定义绘制list3
void CWbcDlg::OnCustomdrawMyList2( NMHDR* pNMHDR, LRESULT* pResult){
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
		CString strTemp = secondWeighWaferListCtr.GetItemText(nItem,6);
		if (strTemp=="OK")
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







void CWbcDlg::OnButton4() //后台管理
{
	// TODO: Add your control notification handler code here
	AdminMainDialog dlg;
	dlg.DoModal();
}




