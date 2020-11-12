// Epo.h: interface for the Epo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EPO_H__E057D427_993C_4860_A935_4D73F5F8D3B6__INCLUDED_)
#define AFX_EPO_H__E057D427_993C_4860_A935_4D73F5F8D3B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Epo  
{
public:
	Epo();
	Epo(CString qrcodeString);
	Epo(CString partNumber,CTime beginTime,CTime exceedTime,CString serialNumber,CString gongyi);
	virtual ~Epo();
	//物料 编码
	CString partNumber;
	//开始时间
	CTime beginTime;
	CString beginTimeStr;
	//过期时间
	CTime exceedTime;
	CString exceedTimeStr;
	//序列号
	CString serialNumber;
	//工艺
	CString gongyi;
	//判断是否合法
	bool isLegal(CTime compareDate);
	//生成二维码字符串
	CString generateQRcode();

};

#endif // !defined(AFX_EPO_H__E057D427_993C_4860_A935_4D73F5F8D3B6__INCLUDED_)
