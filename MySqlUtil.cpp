// MySqlUtil.cpp: implementation of the MySqlUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "wbc.h"
#include "MySqlUtil.h"
#include "properties.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MySqlUtil::MySqlUtil()
{

}

MySqlUtil::MySqlUtil(CString &msg){
	ConnMySQL(msg);
	if (!msg.IsEmpty())
	{
		throw "���ݿ�����ʧ��!";
	}
}

MySqlUtil::~MySqlUtil()
{
	mysql_close(&mysql);
}

//��������
void MySqlUtil::beginTransaction() {
    //�ر��Զ��ύ
    mysql_autocommit(&mysql, 0);
}

//�ύ����
void MySqlUtil::commitTransaction() {
    mysql_commit(&mysql);
}
//�ع�����
void MySqlUtil::rollbackTransaction() {
    mysql_rollback(&mysql);
}
//��ʼ�����������ݿ�
int MySqlUtil::ConnMySQL(CString &Msg)
{
    if (mysql_init(&mysql) == NULL)
    {
        Msg=mysql_error(&mysql);
        return 0;
    }

    if (mysql_real_connect(&mysql, HOST, USER, PASSWORD, DATABASE, PORT, NULL, 0) == NULL)
    {
        Msg = mysql_error(&mysql);
        return 0;
    }

    if (mysql_set_character_set(&mysql, "GBK") != 0)
    {
        Msg = mysql_error(&mysql);
        return 0;
    }
    return 1;
}

//��ѯ����
void MySqlUtil::SelectData(CString SQL, CString & Msg,CStringArray &array,int * rowNums,int * colNums)
{
    MYSQL_ROW m_row;
    MYSQL_RES* m_res;
    if (mysql_query(&mysql, SQL) != 0)
    {
        Msg = mysql_error(&mysql);
        return ;
    }
    m_res = mysql_store_result(&mysql);

    if (m_res == NULL)
    {
        Msg = mysql_error(&mysql);
        return ;
    }
    while (m_row = mysql_fetch_row(m_res))
    {
        for (int i = 0; i < mysql_num_fields(m_res); i++)
        {
            array.Add(m_row[i]);
        }
    }
    *rowNums=mysql_num_rows(m_res);
    *colNums = mysql_num_fields(m_res);
    mysql_free_result(m_res);
	if (!Msg.IsEmpty())
	{
		throw "��ѯ����ʧ��!";
		return;
	}
    return ;
}
//��ѯ����
void MySqlUtil::SelectData(CString SQL, CString & Msg,CStringArray &array)
{

    MYSQL_ROW m_row;
    MYSQL_RES* m_res;
    if (mysql_query(&mysql, SQL) != 0)
    {
        Msg = mysql_error(&mysql);
        return ;
    }
    m_res = mysql_store_result(&mysql);
	
    if (m_res == NULL)
    {
        Msg = mysql_error(&mysql);
        return ;
    }
    while (m_row = mysql_fetch_row(m_res))
    {
        for (int i = 0; i < mysql_num_fields(m_res); i++)
        {
            array.Add(m_row[i]);
        }
    }
    mysql_free_result(m_res);
	if (!Msg.IsEmpty())
	{
		throw "��ѯ����ʧ��!";
		return;
	}
    return ;
}

//��ѯ���ݲ���Ⱦ���
void MySqlUtil::SelectDataAndToList(CString SQL, CString & Msg,CMyListCtrl *list){
	MYSQL_ROW m_row;
    MYSQL_RES* m_res;
	CStringArray array;
    if (mysql_query(&mysql, SQL) != 0)
    {
        Msg = mysql_error(&mysql);
        return ;
    }
    m_res = mysql_store_result(&mysql);
	
    if (m_res == NULL)
    {
        Msg = mysql_error(&mysql);
        return ;
    }
    while (m_row = mysql_fetch_row(m_res))
    {
        for (int i = 0; i < mysql_num_fields(m_res); i++)
        {
            array.Add(m_row[i]);
        }
    }
    int rowNums=mysql_num_rows(m_res);
    int colNums = mysql_num_fields(m_res);
    mysql_free_result(m_res);
	//���ñ������
	for ( int i = 0; i < rowNums; i++)
	{
		list->InsertItem(i, array.GetAt(i * colNums));
		for ( int j = 1; j < colNums; j++)
		{
			list->SetItemText(i, j, array.GetAt(i * colNums + j));
		}
	}
	//�ػ�
	list->AdjustColumnWidth();
	if (!Msg.IsEmpty())
	{
		throw "��ѯ����ʧ��!";
		return;
	}
    return ;

}
//�ж��Ƿ����
bool MySqlUtil::isExist(CString SQL) {
    mysql_query(&mysql, SQL);
    MYSQL_RES* m_res;
    m_res = mysql_store_result(&mysql);
    int rows=mysql_num_rows(m_res);
    if (rows>0) {
		mysql_free_result(m_res);
        return true;
    }
    else
    {
		mysql_free_result(m_res);
        return false;
    }
}

//��������
int MySqlUtil::InsertData(CString SQL, CString &Msg)
{
    if (mysql_query(&mysql, SQL) != 0)
    {
        Msg = mysql_error(&mysql);
		if (!Msg.IsEmpty())
		{
			throw "��������ʧ��!";
			return 0;
		}
        return 0;
    }
    return 1;
}

//��������
int MySqlUtil::UpdateData(CString SQL, CString& Msg)
{
    if (mysql_query(&mysql, SQL) != 0)
    {
        Msg = mysql_error(&mysql);
        return 0;
    }
	if (!Msg.IsEmpty())
	{
		throw "��������ʧ��!";
		return 0;
	}
    return 1;
}

//ɾ������
int MySqlUtil::DeleteData(CString SQL, CString& Msg)
{
    if (mysql_query(&mysql, SQL) != 0)
    {
        Msg = mysql_error(&mysql);
        return 0;
    }
	if (!Msg.IsEmpty())
	{
		throw "ɾ������ʧ��!";
		return 0;
	}
    return 1;
}

//�ر����ݿ�����
void MySqlUtil::CloseMySQLConn()
{
    mysql_close(&mysql);
}