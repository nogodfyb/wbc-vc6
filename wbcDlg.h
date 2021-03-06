// wbcDlg.h : header file
//

#if !defined(AFX_WBCDLG_H__35D06783_C954_430C_9D77_0591978721BC__INCLUDED_)
#define AFX_WBCDLG_H__35D06783_C954_430C_9D77_0591978721BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "CMyListCtrl.h"
#include "Epo.h"
#include "MySqlUtil.h"

/////////////////////////////////////////////////////////////////////////////
// CWbcDlg dialog

class CWbcDlg : public CDialog
{
// Construction
public:
	CWbcDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWbcDlg)
	enum { IDD = MAIN_DIALOG };
	CStatic	epPromptTextCtr;
	CMyListCtrl	secondWeighWaferListCtr;
	CEdit	epEditCtr;
	CMyListCtrl	firstWeighWaferListCtr;
	CComboBox	planIdCbxCtr;
	CDateTimeCtrl	planDateCtr;
	CMyListCtrl	waferSelectListCtr;
	CEdit	firstWeighWaferEditCtr;
	CStatic	idTextCtr;
	CStatic	lastCheckCtr;
	CEdit	waferCtr;
	//}}AFX_DATA

	//存储异常记录map
	CMapStringToString exceptionMap;
	//缓存各个waferLot对应的最近的plasma时间
	CMapStringToString plasmaMap;
	//当前银浆上机时间
	int currentEpoRunTime;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWbcDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	void OnScanWafer();
	void OnScanWaferFistWeigh();
	void OnScanEp();
	void initSelectWaferListCtr();
	void initFirstWeighWaferListCtr(MySqlUtil &mysql);
	void initSecondWeighWaferListCtr();
	void completeFirstWeighWaferListCtr(MySqlUtil &mysql);
	void initPlanIdCbxCtr();
	void getSetting();
	void refreshPlasmaRemainTime(MySqlUtil &mysql);
	void refreshPlasmaRemainTime();
	void refreshEpoRemainTime();
	void manualFirstWeigh(CString waferLot,CString waferSource,CString waferDevice, int currentRow);
	void manualFirstWeigh(CString waferLot,CString waferSource,CString waferDevice);
	void manualSecondWeigh(CString waferLot,CString waferSource,CString firstWeight);
	void matchTools(MySqlUtil &mysql);
	void completeWaferSelectListCtr();
	CString serialPort;
	CString weigthMode;
	//上次点检信息
	CString lastCheckScraperSn;
	CString lastCheckSteelMeshSn;
	CString lastCheckShimSn;
	//当前上机银浆
	Epo currentEpo;

	//是否需要重新恢复定时器
	bool needRestoreTimer;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWbcDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnMenuitem32771();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCustomdrawMyList ( NMHDR* pNMHDR, LRESULT* pResult );
	afx_msg void OnCustomdrawMyList2 ( NMHDR* pNMHDR, LRESULT* pResult );
	afx_msg void OnMenuitem32772();
	afx_msg void OnButton3();
	afx_msg void OnMenuitem32773();
	afx_msg void OnButton4();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButton5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WBCDLG_H__35D06783_C954_430C_9D77_0591978721BC__INCLUDED_)
