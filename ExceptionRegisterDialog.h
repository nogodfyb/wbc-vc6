#if !defined(AFX_EXCEPTIONREGISTERDIALOG_H__A58F57EE_FA64_4F57_9465_6D4A52738A96__INCLUDED_)
#define AFX_EXCEPTIONREGISTERDIALOG_H__A58F57EE_FA64_4F57_9465_6D4A52738A96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExceptionRegisterDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ExceptionRegisterDialog dialog

class ExceptionRegisterDialog : public CDialog
{
// Construction
public:
	ExceptionRegisterDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ExceptionRegisterDialog)
	enum { IDD = EXCEPTION_REGISTER };
	CComboBox	handleResultCbxCtr;
	CEdit	remarkEditCtr;
	CComboBox	exceptionReasonCbxCtr;
	CStatic	waferLotTextCtr;
	//}}AFX_DATA

	CString waferLot;
	void initExceptionReasonCbxCtr() ;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ExceptionRegisterDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ExceptionRegisterDialog)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXCEPTIONREGISTERDIALOG_H__A58F57EE_FA64_4F57_9465_6D4A52738A96__INCLUDED_)
