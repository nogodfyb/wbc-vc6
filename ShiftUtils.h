// ShiftUtils.h: interface for the ShiftUtils class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHIFTUTILS_H__417A8773_E2B3_491B_8EF4_51CBD91BD6C0__INCLUDED_)
#define AFX_SHIFTUTILS_H__417A8773_E2B3_491B_8EF4_51CBD91BD6C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ShiftUtils  
{
public:
	ShiftUtils();
	virtual ~ShiftUtils();

	CString getShift(CTime now);
	CTime getLocalDateYe(CTime now);
	CString getGroupBai(CTime now);
	CString getGroupYe(CTime now);
	CString getShiftByNow();
	CTime DAY1;
	CTime DAY2;
	CTime DAY3;
	CTime DAY4;
	CTime DAY5;
	CTime DAY6;
	CTime DAY7;
	CTime DAY8;
	CTime DAY9;
	CTime DAY10;
	CTime DAY11;
	CTime DAY12;


};

#endif // !defined(AFX_SHIFTUTILS_H__417A8773_E2B3_491B_8EF4_51CBD91BD6C0__INCLUDED_)
