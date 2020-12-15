// CMyListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "wbc.h"
#include "CMyListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl

CMyListCtrl::CMyListCtrl()
{
}

CMyListCtrl::~CMyListCtrl()
{
}

void CMyListCtrl::AdjustColumnWidth()
{
    SetRedraw(FALSE);
    int nColumnCount = GetColumnCount();
	
    for (int i = 0; i < nColumnCount; i++)
    {
        SetColumnWidth(i, LVSCW_AUTOSIZE);
        int nColumnWidth = GetColumnWidth(i);
        SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
        int nHeaderWidth = GetColumnWidth(i);
        SetColumnWidth(i, max(nColumnWidth, nHeaderWidth));
    }
    SetRedraw(TRUE);
}

int CMyListCtrl::GetColumnCount()
{
    CHeaderCtrl* pHeaderCtrl = GetHeaderCtrl();
    return(pHeaderCtrl->GetItemCount());
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CMyListCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl message handlers
