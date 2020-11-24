// ValiadteUtils.cpp: implementation of the ValiadteUtils class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "wbc.h"
#include "ValiadteUtils.h"
#include "MyUtils.h"

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
	//计数
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

bool ValiadteUtils::validateBn(CString bn){

	if(bn.IsEmpty()){
		return false;
	}
	//校验第一位字符必须是大写英文字母
	if(bn.GetAt(0)<'A'||bn.GetAt(0)>'Z'){
		return false;
	}
	if(bn.GetLength()!=5){
		return false;
	}
	for (int i=1;i<bn.GetLength();i++)
	{
		if(bn.GetAt(i)<'0'||bn.GetAt(i)>'9'){
			return false;
		}
	}
	return true;
}

bool ValiadteUtils::validatePower(CString power){
	float num=atof(power);
	if (num < 2.2f || num > 2.8f)
	{
		return false;
	}
	int count=0;
	//遍历每一个字符
	for (int i=0;i<power.GetLength();i++)
	{
		char ch=power.GetAt(i);
		int num=ch-'0';
		if(ch=='.'){
			count++;
		}else if(num<0||num>9){
			return false;
		}
	}
	//超过两个小数点非法
	if(count>1){
		return false;
	}
	return true;
}

bool ValiadteUtils::validateSpeed(CString speed){
	float num=atof(speed);
	if (num < 4.0f || num > 7.0f)
	{
		return false;
	}
	int count=0;
	//遍历每一个字符
	for (int i=0;i<speed.GetLength();i++)
	{
		char ch=speed.GetAt(i);
		int num=ch-'0';
		if(ch=='.'){
			count++;
		}else if(num<0||num>9){
			return false;
		}
	}
	//超过两个小数点非法
	if(count>1){
		return false;
	}
	return true;
	
}

bool ValiadteUtils::validateVacuum(CString vacuum){
	float num=atof(vacuum);
	if (num>-40.0f)
	{
		return false;
	}
	int count=0;
	//遍历每一个字符
	for (int i=0;i<vacuum.GetLength();i++)
	{
		char ch=vacuum.GetAt(i);
		int num=ch-'0';
		if (i==0)
		{
			if (ch!='-')
			{
				return false;
			}
		} else if(ch=='.'){
			count++;
		}else if(num<0||num>9){
			return false;
		}
	}
	//超过两个小数点非法
	if(count>1){
		return false;
	}
	return true;
	
}

bool ValiadteUtils::validateWeight(CString weight){
	float num=atof(weight);
	if (num <=0.0f || num > 100.0f)
	{
		return false;
	}
	int count=0;
	//遍历每一个字符
	for (int i=0;i<weight.GetLength();i++)
	{
		char ch=weight.GetAt(i);
		int num=ch-'0';
		if(ch=='.'){
			count++;
		}else if(num<0||num>9){
			return false;
		}
	}
	//超过两个小数点非法
	if(count>1){
		return false;
	}
	return true;
}

bool ValiadteUtils::validateEpo(CString ep){
	if (ep.GetLength()<20)
	{
		return false;
	}
	//计数
	int count=0;
	for (int i=0;i<ep.GetLength();i++)
	{
		if(ep.GetAt(i)==';'){
			count++;
		}
	}
	if(count!=4){
		return false;
	}
	return true;
}

bool ValiadteUtils::validateEpoWeight(CString waferSize,CString weight){

	if (waferSize.IsEmpty())
	{
		return false;
	}
	
	if (waferSize=="5")
	{
		float weightF=atof(weight);
		if (weightF<0.5f||weightF>1.0f)
		{
			return false;
		}
	}

	if (waferSize=="6")
	{
		float weightF=atof(weight);
		if (weightF<0.7f||weightF>1.4f)
		{
			return false;
		}
	}
	return true;
}

bool ValiadteUtils::validDateInterval(CString beginTime,CString endTime){
	
	CStringArray array1;
	CStringArray array2;
	MyUtils::splitStr(beginTime,'/',array1);
	MyUtils::splitStr(endTime,'/',array2);
	CTime begin(atoi(array1.GetAt(0)),atoi(array1.GetAt(1)),atoi(array1.GetAt(2)),0,0,0);
	CTime end(atoi(array2.GetAt(0)),atoi(array2.GetAt(1)),atoi(array2.GetAt(2)),0,0,0);
	CTimeSpan span=end-begin;
	int days=span.GetDays();
	if (days<0||days>40)
	{
		return false;
	}
	return true;
}