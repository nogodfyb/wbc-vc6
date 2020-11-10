// MyUtils.h: interface for the MyUtils class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYUTILS_H__8995524F_144E_4165_B1EC_C7735D0D87FF__INCLUDED_)
#define AFX_MYUTILS_H__8995524F_144E_4165_B1EC_C7735D0D87FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MyUtils  
{
public:
	MyUtils();
	virtual ~MyUtils();
	static void splitStr(CString input,char separtor,CStringArray &array);
	static void completeZero(CString &input);
	static CTime strToCTime(CString input);
};

#endif // !defined(AFX_MYUTILS_H__8995524F_144E_4165_B1EC_C7735D0D87FF__INCLUDED_)
