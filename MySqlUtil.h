// MySqlUtil.h: interface for the MySqlUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSQLUTIL_H__1C70EF04_E87C_43F7_A890_8157928FB403__INCLUDED_)
#define AFX_MYSQLUTIL_H__1C70EF04_E87C_43F7_A890_8157928FB403__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "CMyListCtrl.h"

class MySqlUtil  
{
public:
	MySqlUtil();

	MySqlUtil(CString &msg);
	virtual ~MySqlUtil();

	//����
    MYSQL mysql;

	void beginTransaction();
	
    void commitTransaction();
	
    void rollbackTransaction();
	
    int ConnMySQL( CString &Msg);
	
    void SelectData(CString SQL,  CString &Msg, CStringArray& array, int* rowNums,int * colNums);
	
	void SelectDataAndToList(CString SQL, CString & Msg,CMyListCtrl *list);
    bool isExist(CString SQL);
	
    int InsertData(CString SQL, CString &Msg);
	
    int UpdateData(CString SQL, CString& Msg);
	
    int DeleteData(CString SQL, CString& Msg);
	
    void CloseMySQLConn();

};

#endif // !defined(AFX_MYSQLUTIL_H__1C70EF04_E87C_43F7_A890_8157928FB403__INCLUDED_)