// ValiadteUtils.h: interface for the ValiadteUtils class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VALIADTEUTILS_H__BF7A0A2E_F624_42B4_AB43_ECE7AB249EE1__INCLUDED_)
#define AFX_VALIADTEUTILS_H__BF7A0A2E_F624_42B4_AB43_ECE7AB249EE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class ValiadteUtils  
{
public:
	ValiadteUtils();
	virtual ~ValiadteUtils();

	//У��waferоƬ��ά��ĸ�ʽ�Ƿ���ȷ
	static bool validateWafer(CString wafer);

};

#endif // !defined(AFX_VALIADTEUTILS_H__BF7A0A2E_F624_42B4_AB43_ECE7AB249EE1__INCLUDED_)
