// ShiftUtils.cpp: implementation of the ShiftUtils class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "wbc.h"
#include "ShiftUtils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ShiftUtils::ShiftUtils()
{
	DAY1 = CTime(2020,6,13,0,0,0);
	DAY2 = CTime(2020,6,14,0,0,0);
	DAY3 = CTime(2020,6,15,0,0,0);
	DAY4 = CTime(2020,6,16,0,0,0);
	DAY5 = CTime(2020,6,17,0,0,0);
	DAY6 = CTime(2020,6,18,0,0,0);
	DAY7 = CTime(2020,6,19,0,0,0);
	DAY8 = CTime(2020,6,20,0,0,0);
	DAY9 = CTime(2020,6,21,0,0,0);
	DAY10 = CTime(2020,6,22,0,0,0);
	DAY11 = CTime(2020,6,23,0,0,0);
	DAY12 = CTime(2020,6,24,0,0,0);
}

ShiftUtils::~ShiftUtils()
{

}


//获取当前时间是夜班还是白班
CString ShiftUtils::getShift(CTime now) {
	int year = now.GetYear();
	int month = now.GetMonth();
	int day = now.GetDay();
	CTime a(year, month, day, 8, 15, 0);
	CTime b(year, month, day, 20, 15, 0);
	if (now > a && now <= b) {
		return "白";
	}
	else
	{
		return "夜";
	}
}

CTime ShiftUtils::getLocalDateYe(CTime now) {
	int year = now.GetYear();
	int month = now.GetMonth();
	int day = now.GetDay();
	CTime a(year, month, day, 20, 15, 0);
	CTime b(year, month, day, 23, 59, 59);
	if (now > a && now <= b) {
		CTimeSpan span(1, 0, 0, 0);
		now = now + span;
		return now;
	}
	else
	{
		return now;
	}
}

CString ShiftUtils::getGroupBai(CTime now) {
	int span1=(now - DAY1).GetDays();
	int span2=(now - DAY2).GetDays();
	int span3=(now - DAY3).GetDays();
	int span4=(now - DAY4).GetDays();
	int span5=(now - DAY5).GetDays();
	int span6=(now - DAY6).GetDays();
	int span7=(now - DAY7).GetDays();
	int span8=(now - DAY8).GetDays();
	int span9=(now - DAY9).GetDays();
	int span10=(now - DAY10).GetDays();
	int span11=(now - DAY11).GetDays();
	int span12=(now - DAY12).GetDays();
	if (span1 % 12==0 ||span2 % 12==0 || span3 % 12 == 0 || span4 % 12 == 0) {
		return "A";
	}
	if (span5 % 12 == 0 || span6 % 12 == 0 || span7 % 12 == 0 || span8 % 12 == 0) {
		return "C";
	}
	if (span9 % 12 == 0 || span10 % 12 == 0 || span11 % 12 == 0 || span12 % 12 == 0) {
		return "B";
	}
}

CString ShiftUtils::getGroupYe(CTime now) {
	int span1 = (now - DAY1).GetDays();
	int span2 = (now - DAY2).GetDays();
	int span3 = (now - DAY3).GetDays();
	int span4 = (now - DAY4).GetDays();
	int span5 = (now - DAY5).GetDays();
	int span6 = (now - DAY6).GetDays();
	int span7 = (now - DAY7).GetDays();
	int span8 = (now - DAY8).GetDays();
	int span9 = (now - DAY9).GetDays();
	int span10 = (now - DAY10).GetDays();
	int span11 = (now - DAY11).GetDays();
	int span12 = (now - DAY12).GetDays();
	if (span1 % 12 == 0 || span2 % 12 == 0 || span11 % 12 == 0 || span12 % 12 == 0) {
		return "C";
	}
	if (span3 % 12 == 0 || span4 % 12 == 0 || span5 % 12 == 0 || span6 % 12 == 0) {
		return "B";
	}
	if (span7 % 12 == 0 || span8 % 12 == 0 || span9 % 12 == 0 || span10 % 12 == 0) {
		return "A";
	}
}

CString ShiftUtils::getShiftByNow(){
	CTime now = CTime::GetCurrentTime();
	CString shift=getShift(now);
	CString group;
	if (shift=="白") {
		group=getGroupBai(now);
		return group+"1";
	}
	else
	{
		CTime specificDate=getLocalDateYe(now);
		group=getGroupYe(specificDate);
		return group+"0";
	}
}
