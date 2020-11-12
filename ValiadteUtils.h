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
	//У�鹤�Ÿ�ʽ
	static bool validateBn(CString bn);
	//У������
	static bool validatePower(CString power);
	//У���ٶ�
	static bool validateSpeed(CString speed);
	//У�����
	static bool validateVacuum(CString vacuum);
	//У������
	static bool validateWeight(CString weight);
	//У��������ά��
	static bool validateEpo(CString ep);
};

#endif // !defined(AFX_VALIADTEUTILS_H__BF7A0A2E_F624_42B4_AB43_ECE7AB249EE1__INCLUDED_)
