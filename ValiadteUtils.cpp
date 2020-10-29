// ValiadteUtils.cpp: implementation of the ValiadteUtils class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "wbc.h"
#include "ValiadteUtils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ValiadteUtils::ValiadteUtils()
{

}

ValiadteUtils::~ValiadteUtils()
{

}

bool ValiadteUtils::validateWafer(CString wafer){
	if (wafer.GetLength()<20)
	{
		return false;
	}
	//¼ÆÊý
	int count=0;
	for (int i=0;i<wafer.GetLength();i++)
	{
		if(wafer.GetAt(i)=='^'){
			count++;
		}
	}
	if(count!=3){
		return false;
	}
	return true;
}