#if !defined(AFX_ADDRELATIONDIALOG_H__4E72983A_53DD_43B5_9A60_D5391152A42C__INCLUDED_)
#define AFX_ADDRELATIONDIALOG_H__4E72983A_53DD_43B5_9A60_D5391152A42C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddRelationDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AddRelationDialog dialog

class AddRelationDialog : public CDialog
{
// Construction
public:
	AddRelationDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(AddRelationDialog)
	enum { IDD = ADD_RELATION_DIALOG };
	CComboBox	scraperCbxCtr;
	CComboBox	shimCbxCtr;
	CComboBox	steelMeshCbxCtr;
	CComboBox	waferSizeCbxCtr;
	CEdit	epPnEditCtr;
	CEdit	waferSourceEditCtr;
	//}}AFX_DATA
	void initWaferSizeCbxCtr();
	void initSteelMeshCbxCtr();
	void initShimCbxCtr();
	void initScraperCbxCtr();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AddRelationDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AddRelationDialog)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDRELATIONDIALOG_H__4E72983A_53DD_43B5_9A60_D5391152A42C__INCLUDED_)
