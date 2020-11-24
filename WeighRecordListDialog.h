#if !defined(AFX_WEIGHRECORDLISTDIALOG_H__6F134555_8C6E_4BD4_9158_1C82B25628DF__INCLUDED_)
#define AFX_WEIGHRECORDLISTDIALOG_H__6F134555_8C6E_4BD4_9158_1C82B25628DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WeighRecordListDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// WeighRecordListDialog dialog
#include "CMyListCtrl.h"
class WeighRecordListDialog : public CDialog
{
// Construction
public:
	WeighRecordListDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(WeighRecordListDialog)
	enum { IDD = WEIGH_RECORD_LIST };
	CDateTimeCtrl	endTimeCtr;
	CDateTimeCtrl	beginTimeCtr;
	CMyListCtrl	weighRecordListCtr;
	//}}AFX_DATA
	void initWeighRecordListCtr();
	bool isAdmin();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(WeighRecordListDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(WeighRecordListDialog)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEIGHRECORDLISTDIALOG_H__6F134555_8C6E_4BD4_9158_1C82B25628DF__INCLUDED_)
