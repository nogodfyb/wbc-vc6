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

void ExceptionRegisterDialog::OnOK() //��д�쳣��¼
{
	// TODO: Add extra validation here
	if (!setException(waferLot))
	{
		return;
	}
	
	CDialog::OnOK();
}

void ExceptionRegisterDialog::OnCancel() //��дcancel
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

void ExceptionRegisterDialog::initExceptionReasonCbxCtr() //��ʼ���쳣ԭ��������
{
	exceptionReasonCbxCtr.AddString("ˢ��������");
	exceptionReasonCbxCtr.AddString("������");
	exceptionReasonCbxCtr.AddString("���滮��");
	exceptionReasonCbxCtr.AddString("��������");
	exceptionReasonCbxCtr.AddString("ˢ������");
	exceptionReasonCbxCtr.AddString("ˢ��ƫ��");
	exceptionReasonCbxCtr.AddString("����Сȱ��");
	exceptionReasonCbxCtr.AddString("�����ѷ�");
	exceptionReasonCbxCtr.AddString("����͹��");
	exceptionReasonCbxCtr.AddString("��Ƭ");
	exceptionReasonCbxCtr.AddString("������");
	exceptionReasonCbxCtr.AddString("���ϼ������");

}
bool ExceptionRegisterDialog::setException(CString waferLot) //�洢�쳣��¼��map
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
		MessageBox("���ź����벻��ȷ");
		return false;
	}
	
	CWnd * parent=GetParent();
	CWbcDlg * wbcDlg=(CWbcDlg *)parent;
	//�쳣ԭ��
	CString exceptionReason;
	exceptionReasonCbxCtr.GetWindowText(exceptionReason);

	//������
	CString handlePlan;
	handlePlanEditCtr.GetWindowText(handlePlan);

	//��ע
	CString remark;
	remarkEditCtr.GetWindowText(remark);

	//������
	CString handleResult;
	handleResultCbxCtr.GetWindowText(handleResult);

	//�洢��map
	CString value=exceptionReason+";"+handlePlan+";"+remark+";"+handleResult+";"+username;
	wbcDlg->exceptionMap.SetAt(waferLot,value);
	MessageBox("�Ǽǳɹ�!");
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