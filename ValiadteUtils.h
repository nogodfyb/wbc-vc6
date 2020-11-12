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

	//校验wafer芯片二维码的格式是否正确
	static bool validateWafer(CString wafer);
	//校验工号格式
	static bool validateBn(CString bn);
	//校验力量
	static bool validatePower(CString power);
	//校验速度
	static bool validateSpeed(CString speed);
	//校验真空
	static bool validateVacuum(CString vacuum);
	//校验重量
	static bool validateWeight(CString weight);
	//校验银浆二维码
	static bool validateEpo(CString ep);
};

#endif // !defined(AFX_VALIADTEUTILS_H__BF7A0A2E_F624_42B4_AB43_ECE7AB249EE1__INCLUDED_)
