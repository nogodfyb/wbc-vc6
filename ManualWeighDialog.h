#if !defined(AFX_MANUALWEIGHDIALOG_H__9B3A8D2C_7216_44A2_A79C_8A856D10D80F__INCLUDED_)
#define AFX_MANUALWEIGHDIALOG_H__9B3A8D2C_7216_44A2_A79C_8A856D10D80F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManualWeighDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ManualWeighDialog dialog

class ManualWeighDialog : public CDialog
{
// Construction
public:
	ManualWeighDialog(CWnd* pParent = NULL);   // standard constructor
	CString waferLot;
	CString manualWeighValue;

// Dialog Data
	//{{AFX_DATA(ManualWeighDialog)
	enum { IDD = MANUAL_WEIGH_DIALOG };
	CEdit	manualWeighEditCtr;
	CStatic	waferLotTextCtr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ManualWeighDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ManualWeighDialog)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANUALWEIGHDIALOG_H__9B3A8D2C_7216_44A2_A79C_8A856D10D80F__INCLUDED_)
