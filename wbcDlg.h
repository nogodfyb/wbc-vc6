// wbcDlg.h : header file
//

#if !defined(AFX_WBCDLG_H__35D06783_C954_430C_9D77_0591978721BC__INCLUDED_)
#define AFX_WBCDLG_H__35D06783_C954_430C_9D77_0591978721BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "CMyListCtrl.h"

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

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWbcDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	void OnScanWafer();
	void OnScanWaferFistWeigh();
	void initSelectWaferListCtr();
	void initFirstWeighWaferListCtr();
	void completeFirstWeighWaferListCtr();
	void initPlanIdCbxCtr();
	void getSetting();
	void refreshPlasmaRemainTime();
	void manualFirstWeigh(CString waferLot,CString waferSource, int currentRow);
	void manualFirstWeigh(CString waferLot,CString waferSource);
	CString serialPort;
	CString weigthMode;
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WBCDLG_H__35D06783_C954_430C_9D77_0591978721BC__INCLUDED_)
