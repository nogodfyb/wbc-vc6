// MySqlUtil.cpp: implementation of the MySqlUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "wbc.h"
#include "MySqlUtil.h"

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
}

MySqlUtil::~MySqlUtil()
{
	mysql_close(&mysql);
}

//��������
void MySqlUtil::beginTransaction() {
    mysql_query(&mysql, "start transaction");
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
		throw "���ݿ��ʼ��ʧ��!";
    }

    if (mysql_real_connect(&mysql, HOST, USER, PASSWORD, DATABASE, PORT, NULL, 0) == NULL)
    {
        Msg = mysql_error(&mysql);
		throw "���ݿ�����ʧ��:�˿ںŻ��˺��������!";
    }

    if (mysql_set_character_set(&mysql, "GBK") != 0)
    {
        Msg = mysql_error(&mysql);
		throw "���ݿ�����ʧ��2!";
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
		throw "��ѯ����ʧ��1";
    }
    m_res = mysql_store_result(&mysql);

    if (m_res == NULL)
    {
        Msg = mysql_error(&mysql);
		throw "��ѯ����ʧ��2";
    }
    while (m_row = mysql_fetch_row(m_res))
    {
        for (int i = 0; i < mysql_num_fields(m_res); i++)
        {
            array.Add(m_row[i]);
        }
    }
	if (rowNums!=NULL)
	{
		*rowNums=mysql_num_rows(m_res);
		*colNums = mysql_num_fields(m_res);
	}
    mysql_free_result(m_res);
    return ;
}
//��ѯ����
void MySqlUtil::SelectData(CString SQL, CString & Msg,CStringArray &array)
{
	SelectData(SQL,Msg,array,NULL,NULL);
}

//��ѯ���ݲ���Ⱦ���
void MySqlUtil::SelectDataAndToList(CString SQL, CString & Msg,CMyListCtrl *list){
	MYSQL_ROW m_row;
    MYSQL_RES* m_res;
	CStringArray array;
    if (mysql_query(&mysql, SQL) != 0)
    {
        Msg = mysql_error(&mysql);
		throw "��ѯ����ʧ��!";
    }
    m_res = mysql_store_result(&mysql);
	
    if (m_res == NULL)
    {
        Msg = mysql_error(&mysql);
		throw "��ѯ����ʧ��!";
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

	return excute(SQL,Msg);
}

//��������
int MySqlUtil::UpdateData(CString SQL, CString& Msg)
{
	return excute(SQL,Msg);
}

//ɾ������
int MySqlUtil::DeleteData(CString SQL, CString& Msg)
{
	return excute(SQL,Msg);
}

int MySqlUtil::excute(CString sql,CString& msg){
    if (mysql_query(&mysql, sql) != 0)
    {
        msg = mysql_error(&mysql);
		throw "��������ʧ��!";
    }
	return mysql_affected_rows(&mysql);
}

//�ر����ݿ�����
void MySqlUtil::CloseMySQLConn()
{
    mysql_close(&mysql);
}

