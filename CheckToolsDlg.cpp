// CheckToolsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "wbc.h"
#include "CheckToolsDlg.h"
#include "MySqlUtil.h"
#include "ShiftUtils.h"
#include "ValiadteUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CheckToolsDlg dialog


CheckToolsDlg::CheckToolsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CheckToolsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CheckToolsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CheckToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CheckToolsDlg)
	DDX_Control(pDX, IDC_EDIT7, vacuumEditCtr);
	DDX_Control(pDX, IDC_EDIT6, speedEditCtr);
	DDX_Control(pDX, IDC_EDIT5, powerEditCtr);
	DDX_Control(pDX, IDC_COMBO4, machineCodeCbxCtr);
	DDX_Control(pDX, IDC_EDIT4, bnEditCtr);
	DDX_Control(pDX, IDC_COMBO3, shimCbxCtr);
	DDX_Control(pDX, IDC_COMBO2, steelMeshCbxCtr);
	DDX_Control(pDX, IDC_COMBO1, scraperCbxCtr);
	DDX_Control(pDX, IDC_EDIT3, shimEditCtr);
	DDX_Control(pDX, IDC_EDIT2, steelMeshEditCtr);
	DDX_Control(pDX, IDC_EDIT1, scraperEditCtr);
	DDX_Control(pDX, STEELMESH_TEXT, steelMeshTextCtr);
	DDX_Control(pDX, SHIM_TEXT, shimTextCtr);
	DDX_Control(pDX, SCRAPER_TEXT, scraperTextCtr);
	DDX_Control(pDX, CHECK_TOOLS_DLG_WS, waferSourceCtr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CheckToolsDlg, CDialog)
	//{{AFX_MSG_MAP(CheckToolsDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CheckToolsDlg message handlers

//初始化窗口
BOOL CheckToolsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	//初始化当前waferSource
	waferSourceCtr.SetWindowText(waferSource);
	selectToolsInfo();
	initAppearanceCheckSelects();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//重写onOk
void CheckToolsDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//响应刮刀扫描二维码事件
	if(GetDlgItem(IDC_EDIT1)==GetFocus())
	{
		onScanScraper();
		return;
	}

	//响应钢网扫描二维码事件
	if(GetDlgItem(IDC_EDIT2)==GetFocus())
	{
		onScanSteelMesh();
		return;
	}

	//响应垫片扫描二维码事件
	if(GetDlgItem(IDC_EDIT3)==GetFocus())
	{
		onScanShim();
		return;
	}
}
//重写onCancel
void CheckToolsDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

//查询所有工具信息并填充到3个静态文本控件
void CheckToolsDlg::selectToolsInfo(){

	try
	{
		CString msg;
		MySqlUtil mysqlUtil(msg);
		CString sql;
		sql.Format("SELECT description,sn from wbc20_wafer_tool_relation,wbc20_tool WHERE tool_id=wbc20_tool.id AND wafer_source='%s' ORDER BY type",waferSource);
		CStringArray array;
		mysqlUtil.SelectData(sql,msg,array);
		if(array.GetSize()!=6){
			MessageBox("刷胶工具未知!请联系管理员!");
			CDialog::OnOK();
			return;
		}
		//设置刮刀信息
		scraperTextCtr.SetWindowText(array.GetAt(0));
		expectedScraper=array.GetAt(1);
		//设置钢网信息
		steelMeshTextCtr.SetWindowText(array.GetAt(2));
		expectedSteelMesh=array.GetAt(3);
		//设置垫片信息
		shimTextCtr.SetWindowText(array.GetAt(4));
		expectedShim=array.GetAt(5);
	}
	catch (const char * info)
	{
		MessageBox(info);
	}

}

//响应刮刀扫描二维码
void CheckToolsDlg::onScanScraper(){
	CString currentScraper;
	scraperEditCtr.GetWindowText(currentScraper);
	if (currentScraper!=expectedScraper)
	{
		MessageBox("匹配刮刀失败!");
	}else{
		scraperCheck=true;
		scraperCbxCtr.EnableWindow(true);
	}
	scraperEditCtr.SetWindowText("");
}

//响应钢网扫描二维码
void CheckToolsDlg::onScanSteelMesh(){
	CString currentSteelMesh;
	steelMeshEditCtr.GetWindowText(currentSteelMesh);
	if (currentSteelMesh!=expectedSteelMesh)
	{
		MessageBox("匹配钢网失败!");
	}else{
		steelMeshCheck=true;
		steelMeshCbxCtr.EnableWindow(true);
	}
	steelMeshEditCtr.SetWindowText("");
}


//响应垫片扫描二维码
void CheckToolsDlg::onScanShim(){
	CString currentShim;
	shimEditCtr.GetWindowText(currentShim);
	if (currentShim!=expectedShim)
	{
		MessageBox("匹配垫片失败!");
	}else{
		shimCheck=true;
		shimCbxCtr.EnableWindow(true);
	}
	shimEditCtr.SetWindowText("");
}

//初始化三个外观状态下拉框及机器号下拉框
void CheckToolsDlg::initAppearanceCheckSelects(){
	scraperCbxCtr.AddString(TEXT("OK"));
	scraperCbxCtr.AddString(TEXT("NG"));
	steelMeshCbxCtr.AddString(TEXT("OK"));
	steelMeshCbxCtr.AddString(TEXT("NG"));
	shimCbxCtr.AddString(TEXT("OK"));
	shimCbxCtr.AddString(TEXT("NG"));
	scraperCbxCtr.EnableWindow(false);
	steelMeshCbxCtr.EnableWindow(false);
	shimCbxCtr.EnableWindow(false);
	machineCodeCbxCtr.AddString(TEXT("2FC01"));
	machineCodeCbxCtr.SetCurSel(0);
}


//保存点检记录
void CheckToolsDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	try
	{
		CString msg;
		MySqlUtil mysql(msg);
		CString sql;
		ShiftUtils shiftUtil;
		CString shift=shiftUtil.getShiftByNow();
		//机器号
		CString machineCode;
		//工号
		CString bn;
		//力量
		CString power;
		//速度
		CString speed;
		//真空
		CString vacuum;
		//刮刀外观检查
		CString scraperCheckStr;
		//钢网垫片外观检查
		CString steelMeshCheckStr;
		//垫片外观检查
		CString shimCheckStr;
		powerEditCtr.GetWindowText(power);
		bnEditCtr.GetWindowText(bn);
		speedEditCtr.GetWindowText(speed);
		vacuumEditCtr.GetWindowText(vacuum);
		machineCodeCbxCtr.GetLBText(machineCodeCbxCtr.GetCurSel(),machineCode);
		if (scraperCbxCtr.GetCurSel()==-1)
		{
			MessageBox("刀片外观检查未填写!");
			return;
		}else{
			scraperCbxCtr.GetLBText(scraperCbxCtr.GetCurSel(),scraperCheckStr);
		}

		if (steelMeshCbxCtr.GetCurSel()==-1)
		{
			MessageBox("钢网外观检查未填写!");
			return;
		} 
		else
		{
			steelMeshCbxCtr.GetLBText(steelMeshCbxCtr.GetCurSel(),steelMeshCheckStr);
		}

		if (shimCbxCtr.GetCurSel()==-1)
		{
			MessageBox("垫片外观检查未填写!");
			return;
		} 
		else
		{
			shimCbxCtr.GetLBText(shimCbxCtr.GetCurSel(),shimCheckStr);
		}
		//校验工号
		if(!ValiadteUtils::validateBn(bn)){
			MessageBox("工号不合法!");
			return;
		}
		//校验力量
		if(!ValiadteUtils::validatePower(power)){
			MessageBox("印刷压力不合法!");
			return;
		}
		//校验速度
		if(!ValiadteUtils::validateSpeed(speed)){
			MessageBox("印刷速度不合法!");
			return;
		}
		//校验真空
		if (!ValiadteUtils::validateVacuum(vacuum))
		{
			MessageBox("工作盘真空不合法!");
			return;
		}
		sql.Format("INSERT INTO wbc20_check_record (shift, machine_code,bn,power,speed,vacuum,shim_check,scraper_check,steelmesh_check) \
			VALUES ('%s','%s','%s','%s','%s','%s','%s','%s','%s')",shift,machineCode,bn,power,speed,vacuum,shimCheckStr,scraperCheckStr,steelMeshCheckStr);
		mysql.InsertData(sql,msg);
		MessageBox("保存点检记录成功!");
		CStringArray array;
		CString sql2;
		sql2.Format("SELECT id,create_time from wbc20_check_record WHERE id=LAST_INSERT_ID()");
		mysql.SelectData(sql2,msg,array);
		lastCheckId=array.GetAt(0);
		lastCheckTime=array.GetAt(1);
		//关闭弹窗
		CDialog::OnOK();
	}
	catch (const char * info)
	{
		MessageBox(info);
	}
	
}
