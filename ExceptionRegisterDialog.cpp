// ExceptionRegisterDialog.cpp : implementation file
//

#include "stdafx.h"
#include "wbc.h"
#include "ExceptionRegisterDialog.h"
#include "wbcDlg.h"
#include "MySqlUtil.h"
#include "MyUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ExceptionRegisterDialog dialog


ExceptionRegisterDialog::ExceptionRegisterDialog(CWnd* pParent /*=NULL*/)
	: CDialog(ExceptionRegisterDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(ExceptionRegisterDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ExceptionRegisterDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ExceptionRegisterDialog)
	DDX_Control(pDX, IDC_EDIT4, handlePlanEditCtr);
	DDX_Control(pDX, IDC_EDIT3, passwordEditCtr);
	DDX_Control(pDX, IDC_EDIT2, usernameEditCtr);
	DDX_Control(pDX, IDC_COMBO2, handleResultCbxCtr);
	DDX_Control(pDX, IDC_EDIT1, remarkEditCtr);
	DDX_Control(pDX, IDC_COMBO1, exceptionReasonCbxCtr);
	DDX_Control(pDX, WAFER_LOT_TEXT, waferLotTextCtr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ExceptionRegisterDialog, CDialog)
	//{{AFX_MSG_MAP(ExceptionRegisterDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ExceptionRegisterDialog message handlers

void ExceptionRegisterDialog::OnOK() //填写异常记录
{
	// TODO: Add extra validation here
	if (!setException(waferLot))
	{
		return;
	}
	
	CDialog::OnOK();
}

void ExceptionRegisterDialog::OnCancel() //重写cancel
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL ExceptionRegisterDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	waferLotTextCtr.SetWindowText(waferLot);
	initExceptionReasonCbxCtr();
	handleResultCbxCtr.AddString("OK");
	handleResultCbxCtr.AddString("NG");
	reloadRecord();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ExceptionRegisterDialog::initExceptionReasonCbxCtr() //初始化异常原因下拉框
{
	exceptionReasonCbxCtr.AddString("刷胶不均匀");
	exceptionReasonCbxCtr.AddString("背面光点");
	exceptionReasonCbxCtr.AddString("背面划痕");
	exceptionReasonCbxCtr.AddString("背面异物");
	exceptionReasonCbxCtr.AddString("刷胶超重");
	exceptionReasonCbxCtr.AddString("刷胶偏轻");
	exceptionReasonCbxCtr.AddString("来料小缺口");
	exceptionReasonCbxCtr.AddString("来料裂缝");
	exceptionReasonCbxCtr.AddString("背面凸痕");
	exceptionReasonCbxCtr.AddString("破片");
	exceptionReasonCbxCtr.AddString("胶不够");
	exceptionReasonCbxCtr.AddString("来料检查异物");

}
bool ExceptionRegisterDialog::setException(CString waferLot) //存储异常记录到map
{
	CString username;
	usernameEditCtr.GetWindowText(username);
	CString password;
	passwordEditCtr.GetWindowText(password);
	CString sql;
	CString msg;
	CStringArray array;
	MySqlUtil mysql(msg);
	sql.Format("SELECT bn from diesaw_user WHERE bn='%s' AND pw=MD5('%s')",username,password);
	mysql.SelectData(sql,msg,array);
	if(array.GetSize()!=1){
		MessageBox("工号和密码不正确");
		return false;
	}
	
	CWnd * parent=GetParent();
	CWbcDlg * wbcDlg=(CWbcDlg *)parent;
	//异常原因
	CString exceptionReason;
	exceptionReasonCbxCtr.GetWindowText(exceptionReason);

	//处理方案
	CString handlePlan;
	handlePlanEditCtr.GetWindowText(handlePlan);

	//备注
	CString remark;
	remarkEditCtr.GetWindowText(remark);

	//处理结果
	CString handleResult;
	handleResultCbxCtr.GetWindowText(handleResult);

	//存储到map
	CString value=exceptionReason+";"+handlePlan+";"+remark+";"+handleResult+";"+username;
	wbcDlg->exceptionMap.SetAt(waferLot,value);
	MessageBox("登记成功!");
	return true;
}

void ExceptionRegisterDialog::reloadRecord(){

	if (!exceptionRecordBefore.IsEmpty())
	{
		CStringArray array;
		MyUtils::splitStr(exceptionRecordBefore,';',array);
		exceptionReasonCbxCtr.SetWindowText(array.GetAt(0));
		handlePlanEditCtr.SetWindowText(array.GetAt(1));
		remarkEditCtr.SetWindowText(array.GetAt(2));
		handleResultCbxCtr.SetWindowText(array.GetAt(3));
	}
}