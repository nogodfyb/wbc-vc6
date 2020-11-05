#if !defined(AFX_SETTINGDIALOG_H__B836EB3C_41D7_40AA_8917_B11FD44C2F0F__INCLUDED_)
#define AFX_SETTINGDIALOG_H__B836EB3C_41D7_40AA_8917_B11FD44C2F0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SettingDialog dialog

class SettingDialog : public CDialog
{
// Construction
public:
	SettingDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SettingDialog)
	enum { IDD = SETTING_DIALOG };
	CEdit	serialPortEditCtr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SettingDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SettingDialog)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGDIALOG_H__B836EB3C_41D7_40AA_8917_B11FD44C2F0F__INCLUDED_)
