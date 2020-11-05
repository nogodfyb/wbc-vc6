// MyUtils.cpp: implementation of the MyUtils class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "wbc.h"
#include "MyUtils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MyUtils::MyUtils()
{

}

MyUtils::~MyUtils()
{

}


void MyUtils::splitStr(CString input,char separtor,CStringArray &array){
	CString sToken=_T("");
	int i = 0;
	while (AfxExtractSubString(sToken, input, i,separtor))
	{   
		array.Add(sToken);
		i++;
	}
}

void MyUtils::completeZero(CString &input){
	int length=input.GetLength();
	if (input.GetLength()<3)
	{
		for (int i=0;i<3-length;i++)
		{
			input="0"+input;
		}
	}
}