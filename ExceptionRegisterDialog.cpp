// ExceptionRegisterDialog.cpp : implementation file
//

#include "stdafx.h"
#include "wbc.h"
#include "ExceptionRegisterDialog.h"

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

void ExceptionRegisterDialog::OnOK() //��дok
{
	// TODO: Add extra validation here
	
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
