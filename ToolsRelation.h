#if !defined(AFX_TOOLSRELATION_H__1D6D53DF_42D5_4F61_9CDB_163B56AF16EF__INCLUDED_)
#define AFX_TOOLSRELATION_H__1D6D53DF_42D5_4F61_9CDB_163B56AF16EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToolsRelation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ToolsRelation dialog
#include "CMyListCtrl.h"
class ToolsRelation : public CDialog
{
// Construction
public:
	ToolsRelation(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ToolsRelation)
	enum { IDD = TOOLS_RELATION };
	CMyListCtrl	toolsRelationListCtr;
	//}}AFX_DATA
	void initToolsRelationListCtr();
	void getAllToolsRelation();
	bool isAdmin();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ToolsRelation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ToolsRelation)
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

#endif // !defined(AFX_TOOLSRELATION_H__1D6D53DF_42D5_4F61_9CDB_163B56AF16EF__INCLUDED_)
