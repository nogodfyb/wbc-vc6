// wbc.h : main header file for the WBC application
//

#if !defined(AFX_WBC_H__CCEF1D74_AD83_437A_8ECA_6BB2DB89698B__INCLUDED_)
#define AFX_WBC_H__CCEF1D74_AD83_437A_8ECA_6BB2DB89698B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWbcApp:
// See wbc.cpp for the implementation of this class
//

class CWbcApp : public CWinApp
{
public:
	CWbcApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWbcApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWbcApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WBC_H__CCEF1D74_AD83_437A_8ECA_6BB2DB89698B__INCLUDED_)
