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
	//������ʱ��
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

//ɨ��ǹɨ��wafer
void CWbcDlg::OnScanWafer(){
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
	}else{
		MessageBox("оƬ��ά���ʽ����ȷ!");
	}
	waferCtr.SetWindowText("");
}
//��һ�γ���ǰɨ��wafer
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
		MessageBox("оƬ��ά���ʽ����ȷ");
	}
}
//ɨ����
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
		MessageBox("ɨ���������Ϸ�!");
		return;
	}
	FILE *pFile=fopen("epo.dll","w");
	fwrite(qrCode+";"+nowStr,1,strlen(qrCode+";"+nowStr),pFile);
	fclose(pFile);

}
//��ʼ��оƬ��ѯ��listCtr
void CWbcDlg::initSelectWaferListCtr(){
	CString str[3] = { TEXT("WaferSource"),TEXT("WaferLot"), TEXT("ˢ��ǰ����")};
	for (size_t i = 0; i < 3; i++)
	{
		waferSelectListCtr.InsertColumn(i, str[i], LVCFMT_LEFT, 100);
	}
	//���÷��  ����ѡ�� ����������
	waferSelectListCtr.SetExtendedStyle(waferSelectListCtr.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	waferSelectListCtr.AdjustColumnWidth();
}

//��ʼ����һ�γ��ص�listCtr
void CWbcDlg::initFirstWeighWaferListCtr(){
	CString str[4] = { TEXT("WaferSource"),TEXT("WaferLot"), TEXT("ˢ��ǰ����"),TEXT("Plasmaʣ��ʱ��(����)")};
	for (size_t i = 0; i < 4; i++)
	{
		firstWeighWaferListCtr.InsertColumn(i, str[i], LVCFMT_LEFT, 100);
	}
	//���÷��  ����ѡ�� ����������
	firstWeighWaferListCtr.SetExtendedStyle(firstWeighWaferListCtr.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	firstWeighWaferListCtr.AdjustColumnWidth();
	completeFirstWeighWaferListCtr();
}
//��ʼ���ڶ��γ��ص�listCtr
void CWbcDlg::initSecondWeighWaferListCtr(){
	CString str[4] = { TEXT("WaferLot"),TEXT("ˢ��ǰ����"), TEXT("ˢ��������"),TEXT("����")};
	for (int i=0;i<4;i++)
	{
		secondWeighWaferListCtr.InsertColumn(i,str[i],LVCFMT_LEFT,100);
	}
	secondWeighWaferListCtr.SetExtendedStyle(secondWeighWaferListCtr.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	secondWeighWaferListCtr.AdjustColumnWidth();
}
//����һ�γ��ص�listCtr
void CWbcDlg::completeFirstWeighWaferListCtr(){
	//����һ�γ��ػ�δ���еڶ��γ��ص�������䵽���
	CString msg;
	MySqlUtil mysql(msg);
	CString sql="SELECT wafer_source,wafer_lot,weight from wbc20_first_weigh_record";
	mysql.SelectDataAndToList(sql,msg,&firstWeighWaferListCtr);
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
		//��ѯ���ݲ���Ⱦ
		CString sql;
		sql.Format("SELECT ws,wl from wafer_list_mes_org WHERE schid='%s'",planDate+"-"+planId);
		mysql.SelectDataAndToList(sql,msg,&waferSelectListCtr);
		if (waferSelectListCtr.GetItemCount()==0)
		{
			MessageBox("δ��ѯ��оƬ��Ϣ!");
			return;
		}
		//����б�Ϊ��;����ÿһ�дӵ�һ�γ��ؼ�¼���ѯ��һ�γ�������;���ڸ������
		for (int i=0;i<waferSelectListCtr.GetItemCount();i++)
		{
			CString waferLot=waferSelectListCtr.GetItemText(i,1);
			CString sql;
			sql.Format("SELECT weight from wbc20_first_weigh_record WHERE wafer_lot='%s'",waferLot);
			CStringArray array;
			mysql.SelectData(sql,msg,array);
			//��������
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

//�������ô���
void CWbcDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	SettingDialog dlg;
	dlg.DoModal();
	
}

//��ȡ������Ϣ
void CWbcDlg::getSetting(){
	// TODO: Add your control notification handler code here
	CFile file;
	bool state=file.Open("setting.ini",CFile::modeRead,NULL); 
	int i=0;
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
	
}

//���ˢ��ǰ���ز˵�
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
		MessageBox("��ǰδѡ���κ�wafer!");
		return;
	}
	//�ֶ�ģʽ
	if (weigthMode=="1")
	{
		manualFirstWeigh(waferLot,waferSource,row);
	}
}
//ˢ�������
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
		MessageBox("��ǰδѡ���κ�wafer!");
		return;
	}
	if (minutes<=0)
	{
		MessageBox("Plasma������ڶ��γ��ص�����!");
		return;
	} 
	//�ֶ�ģʽ
	if (weigthMode=="1")
	{

	}
}



//�ֶ���һ�γ��ش�wafer��ѯ�����ѡ��
void CWbcDlg::manualFirstWeigh(CString waferLot,CString waferSource, int currentRow){
	for (int i=0;i<firstWeighWaferListCtr.GetItemCount();i++)
	{
		CString currentWaferLot=firstWeighWaferListCtr.GetItemText(i,1);
		if (currentWaferLot==waferLot)
		{
			if(MessageBox(TEXT("���г�������,�Ƿ��ٴγ���?"),TEXT("�ٴ�ȷ��"),MB_OKCANCEL)!=IDOK)
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
	//�������������ݷǿ�
	if (!dlg.manualWeighValue.IsEmpty())
	{
		//�������¸�wafer�ĵ�һ�γ��ؼ�¼
		try
		{
			CString msg;
			MySqlUtil mysql(msg);
			CString sql;
			sql.Format("INSERT INTO wbc20_first_weigh_record (wafer_lot, wafer_source, weight) VALUES ('%s','%s','%s') ON DUPLICATE KEY UPDATE weight='%s'",waferLot,waferSource,dlg.manualWeighValue,dlg.manualWeighValue);
			mysql.InsertData(sql,msg);
			firstWeighWaferListCtr.DeleteAllItems();
			//���³�ʼ��
			completeFirstWeighWaferListCtr();
		}
		catch (const char * info)
		{
			MessageBox(info);
		}
	}
}
//�ֶ���һ�γ���
void CWbcDlg::manualFirstWeigh(CString waferLot,CString waferSource){
	for (int i=0;i<firstWeighWaferListCtr.GetItemCount();i++)
	{
		CString currentWaferLot=firstWeighWaferListCtr.GetItemText(i,1);
		if (currentWaferLot==waferLot)
		{
			if(MessageBox(TEXT("���г�������,�Ƿ��ٴγ���?"),TEXT("�ٴ�ȷ��"),MB_OKCANCEL)!=IDOK)
			{
				return;
			}
			break;
		}
	}
	ManualWeighDialog dlg;
	dlg.waferLot=waferLot;
	dlg.DoModal();
	//�������������ݷǿ�
	if (!dlg.manualWeighValue.IsEmpty())
	{
		//�������¸�wafer�ĵ�һ�γ��ؼ�¼
		try
		{
			CString msg;
			MySqlUtil mysql(msg);
			CString sql;
			sql.Format("INSERT INTO wbc20_first_weigh_record (wafer_lot, wafer_source, weight) VALUES ('%s','%s','%s') ON DUPLICATE KEY UPDATE weight='%s'",waferLot,waferSource,dlg.manualWeighValue,dlg.manualWeighValue);
			mysql.InsertData(sql,msg);
			firstWeighWaferListCtr.DeleteAllItems();
			//���³�ʼ��
			completeFirstWeighWaferListCtr();
		}
		catch (const char * info)
		{
			MessageBox(info);
		}
	}
}
//�ֶ��ڶ��γ���
void CWbcDlg::manualSecondWeigh(CString waferLot){

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
void CWbcDlg::refreshPlasmaRemainTime(){
	CString msg;
	MySqlUtil mysql(msg);
	//�������;ȡÿһ�е�waferLot;��ѯ��wafer��Plasmaʣ��ʱ��
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
				firstWeighWaferListCtr.SetItemText(i,3,array.GetAt(0)+"***��ϴ����");
			}else firstWeighWaferListCtr.SetItemText(i,3,array.GetAt(0));
		}else{
			firstWeighWaferListCtr.SetItemText(i,3,"�޼�¼");
		}
	}
}
//ˢ�������ϻ�ʱ��
void CWbcDlg::refreshEpoRemainTime()
{
	//��ȡ�ϴ��Ͻ�ʱ��
	CFile file;
	bool state=file.Open("epo.dll",CFile::modeRead,NULL); 
	if (!state)
	{
		MessageBox("���������ش洢�ļ�ʧ��!");
		return;
	}
	int i=0;
	DWORD len=file.GetLength( );
	char * arr=new char[len+1];
	arr[len]=0;  //0��ֹ�ַ��������������
	file.Read(arr,len);   //Read( void* lpBuf, UINT nCount ) lpBuf�����ڽ��ն�ȡ�������ݵ�Bufָ��nCount�Ǵ��ļ���ȡ���ֽ���
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
//�Զ������
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


