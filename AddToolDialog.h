#if !defined(AFX_ADDTOOLDIALOG_H__0FC30E0B_43BA_4AC2_9EAC_E6BB5CD1B9EE__INCLUDED_)
#define AFX_ADDTOOLDIALOG_H__0FC30E0B_43BA_4AC2_9EAC_E6BB5CD1B9EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddToolDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AddToolDialog dialog

class AddToolDialog : public CDialog
{
// Construction
public:
	AddToolDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(AddToolDialog)
	enum { IDD = ADD_TOOL_DIALOG };
	CEdit	descriptionEditCtr;
	CEdit	lifeEditCtr;
	CComboBox	typeCbxCtr;
	CEdit	snEditCtr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AddToolDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AddToolDialog)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDTOOLDIALOG_H__0FC30E0B_43BA_4AC2_9EAC_E6BB5CD1B9EE__INCLUDED_)
