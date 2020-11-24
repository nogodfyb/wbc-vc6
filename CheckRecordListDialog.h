#if !defined(AFX_CHECKRECORDLISTDIALOG_H__B6A3B979_9025_42D1_BCEF_817629C83303__INCLUDED_)
#define AFX_CHECKRECORDLISTDIALOG_H__B6A3B979_9025_42D1_BCEF_817629C83303__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CheckRecordListDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CheckRecordListDialog dialog
#include "CMyListCtrl.h"

class CheckRecordListDialog : public CDialog
{
// Construction
public:
	CheckRecordListDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CheckRecordListDialog)
	enum { IDD = CHECK_RECORD_LIST };
	CDateTimeCtrl	endTimeCtr;
	CDateTimeCtrl	beginTimeCtr;
	CMyListCtrl	checkRecordListCtr;
	//}}AFX_DATA

	void initCheckRecordListCtr();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CheckRecordListDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CheckRecordListDialog)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKRECORDLISTDIALOG_H__B6A3B979_9025_42D1_BCEF_817629C83303__INCLUDED_)
