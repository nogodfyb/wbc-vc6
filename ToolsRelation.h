#if !defined(AFX_TOOLSRELATION_H__1D6D53DF_42D5_4F61_9CDB_163B56AF16EF__INCLUDED_)
#define AFX_TOOLSRELATION_H__1D6D53DF_42D5_4F61_9CDB_163B56AF16EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToolsRelation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ToolsRelation dialog

class ToolsRelation : public CDialog
{
// Construction
public:
	ToolsRelation(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ToolsRelation)
	enum { IDD = TOOLS_RELATION };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLSRELATION_H__1D6D53DF_42D5_4F61_9CDB_163B56AF16EF__INCLUDED_)
