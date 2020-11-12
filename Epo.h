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
	//���� ����
	CString partNumber;
	//��ʼʱ��
	CTime beginTime;
	CString beginTimeStr;
	//����ʱ��
	CTime exceedTime;
	CString exceedTimeStr;
	//���к�
	CString serialNumber;
	//����
	CString gongyi;
	//�ж��Ƿ�Ϸ�
	bool isLegal(CTime compareDate);
	//���ɶ�ά���ַ���
	CString generateQRcode();

};

#endif // !defined(AFX_EPO_H__E057D427_993C_4860_A935_4D73F5F8D3B6__INCLUDED_)
