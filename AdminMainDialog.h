#if !defined(AFX_ADMINMAINDIALOG_H__C8339A7D_5D22_4891_A16B_D92D68B6E1A9__INCLUDED_)
#define AFX_ADMINMAINDIALOG_H__C8339A7D_5D22_4891_A16B_D92D68B6E1A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdminMainDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AdminMainDialog dialog
#include "ToolsListDialog.h"
#include "ToolsRelation.h"
#include "CheckRecordListDialog.h"
#include "WeighRecordListDialog.h"

class AdminMainDialog : public CDialog
{
// Construction
public:
	AdminMainDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(AdminMainDialog)
	enum { IDD = ADMIN_MAIN_DIALOG };
	CTabCtrl	tabCtr;
	//}}AFX_DATA
	
	int m_CurSelTab;
	ToolsListDialog page1;
	ToolsRelation page2;
	CheckRecordListDialog page3;
	WeighRecordListDialog page4;
	CDialog* pDialog[4];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AdminMainDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AdminMainDialog)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADMINMAINDIALOG_H__C8339A7D_5D22_4891_A16B_D92D68B6E1A9__INCLUDED_)
