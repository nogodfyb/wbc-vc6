#if !defined(AFX_CMYLISTCTRL_H__B6048C43_259A_4BC2_A29B_B3EB28F64843__INCLUDED_)
#define AFX_CMYLISTCTRL_H__B6048C43_259A_4BC2_A29B_B3EB28F64843__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CMyListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl window

class CMyListCtrl : public CListCtrl
{
// Construction
public:
	CMyListCtrl();

// Attributes
public:

// Operations
public:

	int GetColumnCount();
    void AdjustColumnWidth();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMYLISTCTRL_H__B6048C43_259A_4BC2_A29B_B3EB28F64843__INCLUDED_)
