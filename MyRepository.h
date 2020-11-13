// MyRepository.h: interface for the MyRepository class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYREPOSITORY_H__21E65083_8243_4216_8769_4A5DF5E4E986__INCLUDED_)
#define AFX_MYREPOSITORY_H__21E65083_8243_4216_8769_4A5DF5E4E986__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MyRepository  
{
public:
	MyRepository();
	virtual ~MyRepository();
	static CString insertSecondWeighRecord(CStringArray &params);

};

#endif // !defined(AFX_MYREPOSITORY_H__21E65083_8243_4216_8769_4A5DF5E4E986__INCLUDED_)
