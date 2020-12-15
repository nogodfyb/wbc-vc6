// MySqlUtil.h: interface for the MySqlUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSQLUTIL_H__1C70EF04_E87C_43F7_A890_8157928FB403__INCLUDED_)
#define AFX_MYSQLUTIL_H__1C70EF04_E87C_43F7_A890_8157928FB403__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define HOST  "localhost"
#define USER  "tester"
#define PASSWORD "tester"
#define DATABASE "diesaw"
#define PORT  3307

class MySqlUtil  
{
public:
MySqlUtil();

	virtual ~MySqlUtil();
	
	void beginTransaction();
	
	void commitTransaction();
	
	void rollbackTransaction();
	
	int ConnMySQL();

	void SelectData(CString SQL, CStringArray& array, int* rowNums,int * colNums);
	
	void SelectData(CString SQL,CStringArray &array);
	
	void SelectDataAndToList(CString SQL,CListCtrl *list);
	
	int InsertData(CString SQL);
	
	int UpdateData(CString SQL);
	
	int DeleteData(CString SQL);
	
	int excute(CString sql);
	
private:
	MYSQL mysql;
	
};

#endif // !defined(AFX_MYSQLUTIL_H__1C70EF04_E87C_43F7_A890_8157928FB403__INCLUDED_)
