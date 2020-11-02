#if !defined(AFX_CHECKTOOLSDLG_H__C5BBB811_F414_4A17_B170_717AEE98BF4E__INCLUDED_)
#define AFX_CHECKTOOLSDLG_H__C5BBB811_F414_4A17_B170_717AEE98BF4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CheckToolsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CheckToolsDlg dialog

class CheckToolsDlg : public CDialog
{
// Construction
public:
	CheckToolsDlg(CWnd* pParent = NULL);   // standard constructor
	CString waferSource;
	void selectToolsInfo();
	void onScanScraper();
	void onScanSteelMesh();
	void onScanShim();
	void initAppearanceCheckSelects();
	//������Ƭ��Ϣ
	CString expectedScraper;
	//��ƬУ����
	bool scraperCheck;
	//����������Ϣ
	CString expectedSteelMesh;
	//����У����
	bool steelMeshCheck;
	//������Ƭ��Ϣ
	CString expectedShim;
	//��ƬУ����
	bool shimCheck;
// Dialog Data
	//{{AFX_DATA(CheckToolsDlg)
	enum { IDD = CHECK_TOOLS_DIALOG };
	CEdit	vacuumEditCtr;
	CEdit	speedEditCtr;
	CEdit	powerEditCtr;
	CComboBox	machineCodeCbxCtr;
	CEdit	bnEditCtr;
	CComboBox	shimCbxCtr;
	CComboBox	steelMeshCbxCtr;
	CComboBox	scraperCbxCtr;
	CEdit	shimEditCtr;
	CEdit	steelMeshEditCtr;
	CEdit	scraperEditCtr;
	CStatic	steelMeshTextCtr;
	CStatic	shimTextCtr;
	CStatic	scraperTextCtr;
	CStatic	waferSourceCtr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CheckToolsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CheckToolsDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKTOOLSDLG_H__C5BBB811_F414_4A17_B170_717AEE98BF4E__INCLUDED_)
