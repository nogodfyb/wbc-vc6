// Epo.cpp: implementation of the Epo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "wbc.h"
#include "Epo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Epo::Epo(CString qrcodeString)
{
	CString sToken=_T("");
	CStringArray array;
	int i = 0; 
	while (AfxExtractSubString(sToken, qrcodeString, i,';'))
	{   
		array.Add(sToken);
		i++;
	}
	partNumber=array.GetAt(0);
	CString exceedTimeString=array.GetAt(2);
	//year
	CString year="20"+exceedTimeString.Mid(0,2);
	//month
	CString month=exceedTimeString.Mid(2,2);
	//day
	CString day=exceedTimeString.Mid(4,2);
	//hour
	CString hour=exceedTimeString.Mid(6,2);
	//minute
	CString minute=exceedTimeString.Mid(8,2);
	exceedTime=CTime(atoi(year),atoi(month),atoi(day),atoi(hour),atoi(minute),0);
	
	CString beginTimeString=array.GetAt(1);
	//year
	CString year2="20"+beginTimeString.Mid(0,2);
	//month
	CString month2=beginTimeString.Mid(2,2);
	//day
	CString day2=beginTimeString.Mid(4,2);
	//hour
	CString hour2=beginTimeString.Mid(6,2);
	//minute
	CString minute2=beginTimeString.Mid(8,2);
    beginTime=CTime(atoi(year2),atoi(month2),atoi(day2),atoi(hour2),atoi(minute2),0);
	
	serialNumber=array.GetAt(3);
	gongyi=array.GetAt(4);
	
}

Epo::Epo(CString partNumber,CTime beginTime,CTime exceedTime,CString serialNumber,CString gongyi){
	this->partNumber=partNumber;
	this->beginTime=beginTime;
	this->exceedTime=exceedTime;
	this->serialNumber=serialNumber;
	this->gongyi=gongyi;
}

Epo::~Epo()
{
	
}

bool Epo::isLegal(CTime compareDate){
	CTimeSpan diff=compareDate-exceedTime;
	return diff.GetSeconds()<0&&gongyi=="C";
}

CString Epo::generateQRcode(){
	CString beginTimeString=beginTime.Format(_T("%Y%m%d%H%M"));
	beginTimeString=beginTimeString.Mid(2);
	CString exceedTimeString=exceedTime.Format(_T("%Y%m%d%H%M"));
	exceedTimeString=exceedTimeString.Mid(2);
	return partNumber+";"+beginTimeString+";"+exceedTimeString+";"+serialNumber+";"+gongyi;
}
