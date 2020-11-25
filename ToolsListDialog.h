#if !defined(AFX_TOOLSLISTDIALOG_H__0CD5CBAA_7EAE_4217_91D8_B36FF2907DDB__INCLUDED_)
#define AFX_TOOLSLISTDIALOG_H__0CD5CBAA_7EAE_4217_91D8_B36FF2907DDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToolsListDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ToolsListDialog dialog
#include "CMyListCtrl.h"
#include "AddToolDialog.h"
class ToolsListDialog : public CDialog
{
// Construction
public:
	ToolsListDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ToolsListDialog)
	enum { IDD = TOOLS_LIST_DIALOG };
	CMyListCtrl	toolsListCtr;
	//}}AFX_DATA
	void initToolsListCtr();
	void getAllTools();
	bool isAdmin();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ToolsListDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ToolsListDialog)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnMenuitem32774();
	afx_msg void OnMenuitem32775();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLSLISTDIALOG_H__0CD5CBAA_7EAE_4217_91D8_B36FF2907DDB__INCLUDED_)
