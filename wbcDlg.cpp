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
	//��ʼ��һЩ�򵥱���
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


	initSelectWaferListCtr(); //��ʼ����ѯwafer��Ϣ�б�Ľ���ؼ�
	initPlanIdCbxCtr(); //��ʼ���ƻ�������ؼ�
	initFirstWeighWaferListCtr(mysql,msg); //��ʼ����һ�γ��ص�listCtr
	initSecondWeighWaferListCtr(); //��ʼ���ڶ��γ��ص�listCtr
	matchTools(mysql,msg); //ƥ��ˢ�����ߺ�����
	getSetting(); //��ȡ������Ϣ
	//������ʱ��
	SetTimer(IDTIMER1,5000,0); //��ʱˢ��plasmaʣ��ʱ��
	SetTimer(IDTIMER2,5000,0); //��ʱˢ�������ϻ�ʣ��ʱ��
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

// ��дonOk
void CWbcDlg::OnOK() 
{

	//���ǰƥ��ˢ������
	if(GetDlgItem(IDC_EDIT1)==GetFocus())
	{
		OnScanWafer();
		return;
	}
	//��һ�γ���ǰɨ��wafer
	if(GetDlgItem(IDC_EDIT2)==GetFocus())
	{
		OnScanWaferFistWeigh();
		return;
	}
	//ɨ����
	if(GetDlgItem(IDC_EDIT3)==GetFocus())
	{
		OnScanEp();
		return;
	}

}

// ��дonCancel
void CWbcDlg::OnCancel() 
{
	if(MessageBox(TEXT("�Ƿ�ȷ���˳�?"),TEXT("�˳�����"),MB_OKCANCEL)!=IDOK)
	{
		return;
	}
	CDialog::OnCancel();
}

void CWbcDlg::OnScanWafer()//���ɨ��wafer
{
	CString wafer;
	waferCtr.GetWindowText(wafer);
	if (ValiadteUtils::validateWafer(wafer))
	{
		CheckToolsDlg dlg;
		CStringArray array;
		MyUtils::splitStr(wafer,'^',array);
		//��оƬ��ά���е�waferSource�ָ���ȡ���������ݸ�������У�鹤�ߴ���
		dlg.waferSource=array.GetAt(1);
		dlg.DoModal();
		//�����ϴε��ʱ��
		lastCheckCtr.SetWindowText(dlg.lastCheckTime);
		//�����ϴε��id
		idTextCtr.SetWindowText(dlg.lastCheckId);
		//�����ϴε�칤����Ϣ
		lastCheckScraperSn=dlg.expectedScraper;
		lastCheckSteelMeshSn=dlg.expectedSteelMesh;
		lastCheckShimSn=dlg.expectedShim;
	}else{
		MessageBox("оƬ��ά���ʽ����ȷ!");
	}
	waferCtr.SetWindowText("");
}
void CWbcDlg::OnScanWaferFistWeigh()//��һ�γ���ǰɨ��wafer
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
		MessageBox("оƬ��ά���ʽ����ȷ");
	}
}

void CWbcDlg::OnScanEp()//ɨ����
{
	CString qrCode;
	epEditCtr.GetWindowText(qrCode);
	epEditCtr.SetWindowText("");
	if (!ValiadteUtils::validateEpo(qrCode))
	{
		MessageBox("ɨ���������Ϸ�!");
		return;
	}
	Epo epo(qrCode);
	CTime now=CTime::GetCurrentTime();
	CString nowStr=now.Format(_T("%Y%m%d%H%M"));
	if (!epo.isLegal(now))
	{
		MessageBox("�����ѹ���!");
		return;
	}
	MessageBox("�������ϻ�!");
	//�ָ�ˢ�������ϻ�ʱ��Ķ�ʱ��
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
//��ʼ��оƬ��ѯ��listCtr
void CWbcDlg::initSelectWaferListCtr(){
	CString str[4] = { TEXT("WaferSource"),TEXT("WaferLot"), TEXT("WaferDevice"),TEXT("ˢ��ǰ����")};
	for (size_t i = 0; i < 4; i++)
	{
		waferSelectListCtr.InsertColumn(i, str[i], LVCFMT_LEFT, 100);
	}
	//���÷��  ����ѡ�� ����������
	waferSelectListCtr.SetExtendedStyle(waferSelectListCtr.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	waferSelectListCtr.AdjustColumnWidth();
}

//��ʼ����һ�γ��ص�listCtr
void CWbcDlg::initFirstWeighWaferListCtr(MySqlUtil &mysql,CString &msg){
	CString str[6] = { TEXT("WaferSource"),TEXT("WaferLot"), TEXT("ˢ��ǰ����"),TEXT("Plasma(ʣ�����)"),TEXT("ˢ������"),TEXT("����")};
	for (size_t i = 0; i < 6; i++)
	{
		firstWeighWaferListCtr.InsertColumn(i, str[i], LVCFMT_LEFT, 100);
	}
	//���÷��  ����ѡ�� ����������
	firstWeighWaferListCtr.SetExtendedStyle(firstWeighWaferListCtr.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	firstWeighWaferListCtr.AdjustColumnWidth();
	completeFirstWeighWaferListCtr(mysql,msg);
}
//��ʼ���ڶ��γ��ص�listCtr
void CWbcDlg::initSecondWeighWaferListCtr(){
	CString str[7] = { TEXT("WaferSource"),TEXT("WaferLot"),TEXT("ˢ��ǰ����"), TEXT("ˢ��������"),TEXT("����"),TEXT("�쳣�Ǽ�"),TEXT("��׼")};
	for (int i=0;i<7;i++)
	{
		secondWeighWaferListCtr.InsertColumn(i,str[i],LVCFMT_LEFT,100);
	}
	secondWeighWaferListCtr.SetExtendedStyle(secondWeighWaferListCtr.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);
	secondWeighWaferListCtr.AdjustColumnWidth();
}
//����һ�γ��ص�listCtr
void CWbcDlg::completeFirstWeighWaferListCtr(MySqlUtil &mysql,CString &msg){
	//����һ�γ��ػ�δ���еڶ��γ��ص�������䵽���
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
//��ʼ���ƻ���������
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

//оƬ��ѯ
void CWbcDlg::OnButton1() //оƬ��ѯ
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
		//��ѯ���ݲ���Ⱦ
		CString sql;
		sql.Format("SELECT ws,wl,tt from wafer_list_mes_org WHERE schid='%s'",planDate+"-"+planId);
		mysql.SelectDataAndToList(sql,msg,&waferSelectListCtr);
		if (waferSelectListCtr.GetItemCount()==0)
		{
			MessageBox("δ��ѯ��оƬ��Ϣ!");
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

void CWbcDlg::completeWaferSelectListCtr()//����ѯlistCtr
{

	//����б�Ϊ��;����ÿһ�дӵ�һ�γ��ؼ�¼���ѯ��һ�γ�������;���ڸ������
	for (int i=0;i<waferSelectListCtr.GetItemCount();i++)
	{
		CString waferLot=waferSelectListCtr.GetItemText(i,1);
		//������һ�γ��ؼ�¼
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

//�������ô���
void CWbcDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	SettingDialog dlg;
	dlg.DoModal();
	
}
void CWbcDlg::OnButton3() //�ύ���ؼ�¼
{
	// TODO: Add your control notification handler code here
	//���������У��鿴�Ƿ��б�ѡ�е�
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
		MessageBox("δѡ���κ���Ҫ�ύ�ļ�¼!");
		return;
	}
	//�õ���ǰ���
	ShiftUtils shiftUtils;
	CString shift=shiftUtils.getShiftByNow();
	//��ѯ���ε���˹���
	CString msg;
	MySqlUtil mysql;
	CStringArray array;
	//��һ�γ����б������
	int length;
	//����
	CString bn;
	//������
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
	//��������
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
			//����waferLot��ѯ��һ�γ��ص�ʱ��
			CString sql2;
			CStringArray array2;
			sql2.Format("SELECT update_time,wafer_device from wbc20_first_weigh_record WHERE wafer_lot='%s'",waferLot);
			mysql.SelectData(sql2,msg,array2);
			CString firstWeighTime=array2.GetAt(0);
			CString waferDevice=array2.GetAt(1);
			//����waferSource��ѯwaferSize
			CString sql3;
			CStringArray array3;
			sql3.Format("SELECT wafer_size from wbc20_tool_rule WHERE wafer_source='%s'",waferSource);
			mysql.SelectData(sql3,msg,array3);
			//������ݿ��д��ڶ�Ӧ��ϵ
			CString waferSize;
			if (array3.GetSize()==1)
			{
				waferSize=array3.GetAt(0);
			}
			//����waferLot��ѯ�洢��map�е��쳣�ǼǼ�¼
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
			//����waferSource��ѯ�ε�����
			CString sql4;
			CStringArray array4;
			sql4.Format("SELECT scraper_sn,life-1 from wbc20_tool_rule,wbc20_tool WHERE wafer_source='%s' AND scraper_sn=sn",waferSource);
			mysql.SelectData(sql4,msg,array4);
			CString scraperLife;
			if (array4.GetSize()==2)
			{
				scraperLife=array4.GetAt(1);
			}
			//����waferSource��ѯ��������
			CString sql5;
			CStringArray array5;
			sql5.Format("SELECT steel_mesh_sn,life-1 from wbc20_tool_rule,wbc20_tool WHERE wafer_source='%s' AND steel_mesh_sn=sn",waferSource);
			mysql.SelectData(sql5,msg,array5);
			CString steelMeshLife;
			if (array5.GetSize()==2)
			{
				steelMeshLife=array5.GetAt(1);
			}
			//����waferSource��ѯ��Ƭ����
			CString sql6;
			CStringArray array6;
			sql6.Format("SELECT shim_sn,life-1 from wbc20_tool_rule,wbc20_tool WHERE wafer_source='%s' AND shim_sn=sn",waferSource);
			mysql.SelectData(sql6,msg,array6);
			CString shimLife;
			if (array6.GetSize()==2)
			{
				shimLife=array6.GetAt(1);
			}
			//�����Ƿ񳬹���׼
			CString overWeight=secondWeighWaferListCtr.GetItemText(k,6);
			
			
			
			CStringArray params;
			params.Add(shift);//����1 ���
			params.Add(bn);//����2 ����
			params.Add(machineCode);//����3 ������
			params.Add(currentEpo.serialNumber);//����4 �������к�
			params.Add(currentEpo.beginTimeStr);//����5 �����ⶳ���ʱ��
			params.Add(currentEpo.exceedTimeStr);//����6 ��������ʱ��
			params.Add(firstWeight);//����7 ��һ�γ��ص�����
			params.Add(firstWeighTime); //����8 ��һ�γ���ʱ��
			params.Add(secondWeight);//����9 �ڶ��γ�������
			params.Add(waferDevice);//����10 оƬ�ͺ�
			params.Add(waferSource);//����11 waferSource
			params.Add(waferLot);//����12 waferLot 
			params.Add(waferSize);//����13 waferSize
			params.Add(overWeight);//����14 �Ƿ���
			params.Add(lastCheckScraperSn);//����15 �ε�sn
			params.Add(lastCheckSteelMeshSn);//����16 ����sn
			params.Add(lastCheckShimSn);//����17 ��Ƭsn
			params.Add(exceptionReason);//����18 �쳣ԭ��
			params.Add(handlePlan); //����19 ������
			params.Add(remark);//����20 ��ע
			params.Add(handleResult);//����21 ������
			params.Add(scraperLife);//����22 �ε�����
			params.Add(steelMeshLife);//����23 ��������
			params.Add(shimLife);//����24 ��Ƭ����
			params.Add(dealPerson);//����25 ������
			CString insertSql=MyRepository::insertSecondWeighRecord(params);
			mysql.InsertData(insertSql,msg);
			//���¸������ߵ�����
			CString sql7;
			sql7.Format("UPDATE wbc20_tool SET life=life-1 WHERE sn in ('%s','%s','%s')",array4.GetAt(0),array5.GetAt(0),array6.GetAt(0));
			mysql.UpdateData(sql7,msg);
			//�ύ���ؼ�¼֮�� ɾ����wafer��һ�γ��ؼ�¼
			CString sql8;
			sql8.Format("DELETE from wbc20_first_weigh_record WHERE wafer_lot='%s'",waferLot);
			mysql.DeleteData(sql8,msg);

			secondWeighWaferListCtr.DeleteItem(k);
			//ɾ����ѯ�б�ĸ�waferLot��
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
		//�ع�,���ύ
		mysql.rollbackTransaction();
		return;
	}
	mysql.commitTransaction();
	//���µ�һ�γ��ؼ�¼��
	firstWeighWaferListCtr.DeleteAllItems();
	//completeFirstWeighWaferListCtr();
	
}

//��ȡ������Ϣ
void CWbcDlg::getSetting(){
	// TODO: Add your control notification handler code here
	CFile file;
	bool state=file.Open("setting.ini",CFile::modeRead,NULL); 
	DWORD len=file.GetLength( );
	char * arr=new char[len+1];
	arr[len]=0;  //0��ֹ�ַ��������������
	file.Read(arr,len);   //Read( void* lpBuf, UINT nCount ) lpBuf�����ڽ��ն�ȡ�������ݵ�Bufָ��nCount�Ǵ��ļ���ȡ���ֽ���
	CString setting(arr);
	CStringArray array;
	MyUtils::splitStr(setting,'\r\n',array);
	weigthMode=array.GetAt(0).Mid(11);
	serialPort=array.GetAt(1).Mid(12);
	delete arr;
}

//�˵�����ӳ��
void CWbcDlg::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	//����оƬ��ѯlistCtr
	CRect  rect; //�����������
	GetDlgItem(IDC_LIST1) -> GetWindowRect(&rect);  //��ÿؼ��������Ļ��λ������
	if(rect.PtInRect(point))  //�һ�����ָ���ؼ���
	{
		CMenu popMenu;//�����˵�
		popMenu.LoadMenu(IDR_MENU1);//������ԴID�����˵���Դ
		CMenu * subMenu = popMenu.GetSubMenu(0);//��õ�0���Ӳ˵���ָ��
		subMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, point.x, point.y, this);  //��ָ��λ����ʾ���������˵�����׷�ٵ����˵��б�ѡ�����
	}
	//����ˢ��ǰ����listCtr
	CRect  rect2; //�����������
	GetDlgItem(IDC_LIST2) -> GetWindowRect(&rect2);  //��ÿؼ��������Ļ��λ������
	if(rect2.PtInRect(point))  //�һ�����ָ���ؼ���
	{
		CMenu popMenu;//�����˵�
		popMenu.LoadMenu(IDR_MENU2);//������ԴID�����˵���Դ
		CMenu * subMenu = popMenu.GetSubMenu(0);//��õ�0���Ӳ˵���ָ��
		subMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, point.x, point.y, this);  //��ָ��λ����ʾ���������˵�����׷�ٵ����˵��б�ѡ�����
	}
	//�����쳣�Ǽǲ˵�
	CRect  rect3; //�����������
	GetDlgItem(IDC_LIST3) -> GetWindowRect(&rect3);  //��ÿؼ��������Ļ��λ������
	if(rect3.PtInRect(point))  //�һ�����ָ���ؼ���
	{
		CMenu popMenu;//�����˵�
		popMenu.LoadMenu(IDR_MENU3);//������ԴID�����˵���Դ
		CMenu * subMenu = popMenu.GetSubMenu(0);//��õ�0���Ӳ˵���ָ��
		subMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, point.x, point.y, this);  //��ָ��λ����ʾ���������˵�����׷�ٵ����˵��б�ѡ�����
	}
}

//���ˢ��ǰ���ز˵�
void CWbcDlg::OnMenuitem32771() //ˢ��ǰ����
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
		MessageBox("��ǰδѡ���κ�wafer!");
		return;
	}
	//�ֶ�ģʽ
	if (weigthMode=="1")
	{
		manualFirstWeigh(waferLot,waferSource,waferDevice,row);
	}
}
void CWbcDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) //ˢ��ǰ����
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
		MessageBox("��ǰδѡ���κ�wafer!");
		return;
	}
	//�ֶ�ģʽ
	if (weigthMode=="1")
	{
		manualFirstWeigh(waferLot,waferSource,waferDevice,row);
	}
	*pResult = 0;
}
void CWbcDlg::OnMenuitem32772() //ɾ����һ�γ��ؼ�¼
{
	// TODO: Add your command handler code here
	if(MessageBox(TEXT("�Ƿ�ȷ��ɾ��?"),TEXT("ɾ����һ�γ��ؼ�¼"),MB_OKCANCEL)!=IDOK)
	{
		return;
	}
	int currentRow =firstWeighWaferListCtr.GetSelectionMark();
	CString waferLot=firstWeighWaferListCtr.GetItemText(currentRow,1);
	if (waferLot.IsEmpty())
	{
		MessageBox("��ǰδѡ���κ�wafer!");
		return;
	}
	try
	{
		CString msg;
		MySqlUtil mysql(msg);
		CString sql;
		sql.Format("DELETE FROM wbc20_first_weigh_record WHERE wafer_lot='%s'",waferLot);
		mysql.DeleteData(sql,msg);
		MessageBox("ɾ���ɹ�!");
		firstWeighWaferListCtr.DeleteItem(currentRow);
	}
	catch (const char * info)
	{
		MessageBox(info);
		return;
	}
	completeWaferSelectListCtr();
}
void CWbcDlg::OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult) //ˢ�������
{
	// TODO: Add your control notification handler code here
	CString plasmaRemain;
	int currentRow =firstWeighWaferListCtr.GetSelectionMark();
	plasmaRemain=firstWeighWaferListCtr.GetItemText(currentRow,3);
	//ʣ�������
	int minutes=atoi(plasmaRemain);
	//ˢ������ƥ�����
	CString toolsMatch=firstWeighWaferListCtr.GetItemText(currentRow,4);
	//����ƥ�����
	CString epoMatch=firstWeighWaferListCtr.GetItemText(currentRow,5);
	CString waferLot=firstWeighWaferListCtr.GetItemText(currentRow,1);
	CString waferSource=firstWeighWaferListCtr.GetItemText(currentRow,0);
	CString firstWeight=firstWeighWaferListCtr.GetItemText(currentRow,2);
	if (waferLot.IsEmpty())
	{
		MessageBox("��ǰδѡ���κ�wafer!");
		return;
	}

	if (currentEpoRunTime>120)
	{
		MessageBox("�����ϻ�ʱ���ѳ���2Сʱ!");
		return;
	}
	if (minutes<=0||toolsMatch!="ƥ��"||epoMatch!="ƥ��")
	{
		MessageBox("������ڶ��γ��ص�����!");
		return;
	} 

	//�ֶ�ģʽ
	if (weigthMode=="1")
	{
		manualSecondWeigh(waferLot,waferSource,firstWeight);
	}
	
	*pResult = 0;
}
void CWbcDlg::OnMenuitem32773() //�쳣�Ǽ�
{
	// TODO: Add your command handler code here
	int currentRow =secondWeighWaferListCtr.GetSelectionMark();
	CString waferLot=secondWeighWaferListCtr.GetItemText(currentRow,1);
	if (waferLot.IsEmpty())
	{
		MessageBox("��ǰδѡ���κ�wafer!");
		return;
	}
	ExceptionRegisterDialog dlg;
	dlg.waferLot=waferLot;
	//ģ̬���ڹر�ǰ��ѯ��ǰwaferLot���޴洢�쳣�Ǽ���Ϣ
	CString exceptionRecordBefore;
	bool beforeState=exceptionMap.Lookup(waferLot,exceptionRecordBefore);
	if (beforeState)
	{
		dlg.exceptionRecordBefore=exceptionRecordBefore;
	}
	dlg.DoModal();
	//ģ̬���ڹرպ��ѯ��ǰwaferLot���޴洢�쳣�Ǽ���Ϣ
	CString exceptionRecordAfter;
	bool afterState=exceptionMap.Lookup(waferLot,exceptionRecordAfter);
	//�ѵǼ�
	if (afterState)
	{
		//��ѯwaferLot������
		for (int i=0;i<secondWeighWaferListCtr.GetItemCount();i++)
		{
			CString currentWaferLot=secondWeighWaferListCtr.GetItemText(i,1);
			if (waferLot==currentWaferLot)
			{
				secondWeighWaferListCtr.SetItemText(i,5,"�ѵǼ�");
			}
		}
	}

}

void CWbcDlg::matchTools(MySqlUtil &mysql,CString &msg)//ƥ��ˢ�����ߺ�����
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
			//����ˢ��������һ��
			firstWeighWaferListCtr.SetItemText(i,4,"δ���");
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
			firstWeighWaferListCtr.SetItemText(i,4,"�쳣");
			continue;
		}
		if (currentEpo.partNumber!=array.GetAt(3))
		{
			//��������������һ��
			firstWeighWaferListCtr.SetItemText(i,5,"��ƥ��");
		}else{
			firstWeighWaferListCtr.SetItemText(i,5,"ƥ��");
		}
		if(lastCheckSteelMeshSn!=array.GetAt(0)||lastCheckShimSn!=array.GetAt(1)||lastCheckScraperSn!=array.GetAt(2)){
			firstWeighWaferListCtr.SetItemText(i,4,"��ƥ��");
			continue;
		}
		firstWeighWaferListCtr.SetItemText(i,4,"ƥ��");
	}
}
//�ֶ���һ�γ��ش�wafer��ѯ�����ѡ��
void CWbcDlg::manualFirstWeigh(CString waferLot,CString waferSource,CString waferDevice, int currentRow){
	bool cover=false;
	int needCoveredRow=0;
	for (int i=0;i<firstWeighWaferListCtr.GetItemCount();i++)
	{
		CString currentWaferLot=firstWeighWaferListCtr.GetItemText(i,1);
		if (currentWaferLot==waferLot)
		{
			if(MessageBox(TEXT("���г�������,�Ƿ��ٴγ���?"),TEXT("�ٴ�ȷ��"),MB_OKCANCEL)!=IDOK)
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
	//�������������ݷǿ�
	if (!dlg.manualWeighValue.IsEmpty())
	{
		if (currentRow!=NULL)
		{
			waferSelectListCtr.SetItemText(currentRow,3,dlg.manualWeighValue);
		}
		//�������¸�wafer�ĵ�һ�γ��ؼ�¼
		try
		{
			CString msg;
			MySqlUtil mysql(msg);
			CString sql;
			sql.Format("INSERT INTO wbc20_first_weigh_record (wafer_lot, wafer_source,wafer_device, weight) VALUES ('%s','%s','%s','%s') ON DUPLICATE KEY UPDATE weight='%s'",waferLot,waferSource,waferDevice,dlg.manualWeighValue,dlg.manualWeighValue);
			mysql.InsertData(sql,msg);
			//����Ǹ���
			if (cover)
			{
				firstWeighWaferListCtr.SetItemText(needCoveredRow,2,dlg.manualWeighValue);
			}else{
				//���һ�γ����б�β�����һ��
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
//�ֶ���һ�γ���
void CWbcDlg::manualFirstWeigh(CString waferLot,CString waferSource,CString waferDevice){
	manualFirstWeigh(waferLot,waferSource,waferDevice,NULL);
}
//�ֶ��ڶ��γ���
void CWbcDlg::manualSecondWeigh(CString waferLot,CString waferSource,CString firstWeight){
	//����waferSource��ѯwaferSize


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
			MessageBox("δ��ѯ��waferSize!����ϵ����Ա!");
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
			if(MessageBox(TEXT("���г�������,�Ƿ��ٴγ���?"),TEXT("�ٴ�ȷ��"),MB_OKCANCEL)!=IDOK)
			{
				return;
			}
			//���³���
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
	//�������������ݷǿ�
	if (!dlg.manualWeighValue.IsEmpty())
	{
		int endRow=secondWeighWaferListCtr.GetItemCount();
		secondWeighWaferListCtr.InsertItem(endRow,waferSource);
		secondWeighWaferListCtr.SetItemText(endRow,1,waferLot);
		secondWeighWaferListCtr.SetItemText(endRow,2,firstWeight);
		secondWeighWaferListCtr.SetItemText(endRow,3,dlg.manualWeighValue);
		secondWeighWaferListCtr.SetItemText(endRow,5,"δ�Ǽ�");
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

//��ʱ������
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

//ˢ��Plasmaʣ��ʱ��
void CWbcDlg::refreshPlasmaRemainTime()//ˢ��plasmaʱ��
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
	//�������;ȡÿһ�е�waferLot;��ѯ��wafer��Plasmaʣ��ʱ��
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
				firstWeighWaferListCtr.SetItemText(i,3,array.GetAt(0)+"***��ϴ����");
			}else firstWeighWaferListCtr.SetItemText(i,3,array.GetAt(0));
		}else{
			firstWeighWaferListCtr.SetItemText(i,3,"�޼�¼");
		}
	}
	firstWeighWaferListCtr.AdjustColumnWidth();
}
//ˢ�������ϻ�ʱ��
void CWbcDlg::refreshEpoRemainTime()
{
	//��ȡ�ϴ��Ͻ�ʱ��
	CFile file;
	bool state=file.Open("epo.dll",CFile::modeRead,NULL); 
	if (!state)
	{
		//MessageBox("���������ش洢�ļ�ʧ��!");
		epPromptTextCtr.SetWindowText("û������ɨ���¼!��¼�ļ�������!");
		return;
	}
	DWORD len=file.GetLength( );
	char * arr=new char[len+1];
	arr[len]=0;  //0��ֹ�ַ��������������
	file.Read(arr,len);   //Read( void* lpBuf, UINT nCount ) lpBuf�����ڽ��ն�ȡ�������ݵ�Bufָ��nCount�Ǵ��ļ���ȡ���ֽ���
	file.Close();
	CString epoStr(arr);
	if (epoStr.IsEmpty())
	{
		epPromptTextCtr.SetWindowText("�����������ϻ���¼!");
		return;
	}
	//�洢��ǰ������Ϣ
	currentEpo=Epo(epoStr);
	CStringArray array;
	MyUtils::splitStr(epoStr,';',array);
	//��һ��ɨ��ʱ��
	CTime lastDate=MyUtils::strToCTime(array.GetAt(5));
	CTime now=CTime::GetCurrentTime();
	CTimeSpan span=now-lastDate;
	currentEpoRunTime=span.GetTotalMinutes();
	CString lastScanTime;
	lastScanTime.Format("%d",120-span.GetTotalMinutes());
	epPromptTextCtr.SetWindowText("�����ϻ���Чʱ�仹ʣ:"+lastScanTime+"����!�������к�:"+currentEpo.serialNumber+" ���ϱ���:"+currentEpo.partNumber);
	if (span.GetTotalMinutes()>=120)
	{
		//�ѳ�ʱ
		epPromptTextCtr.SetWindowText("�����ϻ��ѳ���2Сʱ!�����µ��!����������!");
		AfxMessageBox("�����ϻ��ѳ���2Сʱ!�����µ��!����������!");
		//���ٶ�ʱ��
		KillTimer(IDTIMER2);
		needRestoreTimer=true;
		//�����id��Ϊ******
		idTextCtr.SetWindowText("******");
		GetDlgItem(IDC_BUTTON3)->EnableWindow(false);
	}else{
		GetDlgItem(IDC_BUTTON3)->EnableWindow(true);
	}
	delete arr;
	
}
//�Զ������list2
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
		
		// �ж�ʹListCtrl��ͬ��ɫ��ʵ������
		CString strTemp = firstWeighWaferListCtr.GetItemText(nItem,3);
		int state=atoi(strTemp);
		//ˢ������ƥ�����
		CString toolsMatch=firstWeighWaferListCtr.GetItemText(nItem,4);
		//����ƥ�����
		CString epoMatch=firstWeighWaferListCtr.GetItemText(nItem,5);
		if (state>0&&toolsMatch=="ƥ��"&&epoMatch=="ƥ��")
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


//�Զ������list3
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
		
		// �ж�ʹListCtrl��ͬ��ɫ��ʵ������
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







void CWbcDlg::OnButton4() //��̨����
{
	// TODO: Add your control notification handler code here
	AdminMainDialog dlg;
	dlg.DoModal();
}




