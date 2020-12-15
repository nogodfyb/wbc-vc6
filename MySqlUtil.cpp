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
	ConnMySQL();
}


MySqlUtil::~MySqlUtil()
{
	mysql_close(&mysql);
}

//开启事务
void MySqlUtil::beginTransaction() {
    mysql_query(&mysql, "start transaction");
}

//提交事务
void MySqlUtil::commitTransaction() {
    mysql_commit(&mysql);
}
//回滚事务
void MySqlUtil::rollbackTransaction() {
    mysql_rollback(&mysql);
}
//初始化并连接数据库
int MySqlUtil::ConnMySQL()
{

	CString msg;
    if (mysql_init(&mysql) == NULL)
    {
        msg=mysql_error(&mysql);
		msg="数据库初始化失败:\n"+msg;
		throw msg;
    }

    if (mysql_real_connect(&mysql, HOST, USER, PASSWORD, DATABASE, PORT, NULL, 0) == NULL)
    {
		msg=mysql_error(&mysql);
		msg="数据库连接失败:\n"+msg;
		throw msg;
    }

    if (mysql_set_character_set(&mysql, "GBK") != 0)
    {
		msg=mysql_error(&mysql);
		msg="数据库连接失败:\n"+msg;
		throw msg;
    }
    return 1;
}

//查询数据
void MySqlUtil::SelectData(CString SQL,CStringArray &array,int * rowNums,int * colNums)
{
	CString msg;
    MYSQL_ROW m_row;
    MYSQL_RES* m_res;
    if (mysql_query(&mysql, SQL) != 0)
    {
        msg = mysql_error(&mysql);
		msg = "查询数据失败\n"+msg;
		throw msg;
    }
    m_res = mysql_store_result(&mysql);

    if (m_res == NULL)
    {
        msg = mysql_error(&mysql);
		msg = "查询数据失败\n"+msg;
		throw msg;
    }
    while (m_row = mysql_fetch_row(m_res))
    {
        for (int i = 0; i < mysql_num_fields(m_res); i++)
        {
            array.Add(m_row[i]);
        }
    }
	if (rowNums!=NULL)//重载函数复用
	{
		*rowNums=mysql_num_rows(m_res);
		*colNums = mysql_num_fields(m_res);
	}
    mysql_free_result(m_res);
    return ;
}
//查询数据
void MySqlUtil::SelectData(CString SQL, CStringArray &array)
{
	SelectData(SQL,array,NULL,NULL);
}

//查询数据并渲染表格
void MySqlUtil::SelectDataAndToList(CString SQL,CListCtrl *list){
	CString msg;

	MYSQL_ROW m_row;
    MYSQL_RES* m_res;
	CStringArray array;
    if (mysql_query(&mysql, SQL) != 0)
    {
        msg = mysql_error(&mysql);
		msg = "查询数据失败\n"+msg;
		throw msg;
    }
    m_res = mysql_store_result(&mysql);
	
    if (m_res == NULL)
    {
        msg = mysql_error(&mysql);
		msg = "查询数据失败\n"+msg;
		throw msg;
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

	//设置表格正文
	for ( int i = 0; i < rowNums; i++)
	{
		list->InsertItem(i, array.GetAt(i * colNums));
		for ( int j = 1; j < colNums; j++)
		{
			list->SetItemText(i, j, array.GetAt(i * colNums + j));
		}
	}
	//重绘

	CHeaderCtrl* pHeaderCtrl = list->GetHeaderCtrl();
	list->SetRedraw(FALSE);
	for (int index=0;index<pHeaderCtrl->GetItemCount();index++)
	{
		list->SetColumnWidth(index, LVSCW_AUTOSIZE);
        int nColumnWidth = list->GetColumnWidth(index);
        list->SetColumnWidth(index, LVSCW_AUTOSIZE_USEHEADER);
        int nHeaderWidth = list->GetColumnWidth(index);
        list->SetColumnWidth(index, max(nColumnWidth, nHeaderWidth));
	}
	list->SetRedraw(TRUE);
    return ;

}
//插入数据
int MySqlUtil::InsertData(CString SQL)
{

	return excute(SQL);
}

//更新数据
int MySqlUtil::UpdateData(CString SQL)
{
	return excute(SQL);
}

//删除数据
int MySqlUtil::DeleteData(CString SQL)
{
	return excute(SQL);
}

int MySqlUtil::excute(CString sql){
	CString msg;
    if (mysql_query(&mysql, sql) != 0)
    {
        msg = mysql_error(&mysql);
		msg = "操作数据失败\n"+msg;
		throw msg;
    }
	return mysql_affected_rows(&mysql);
}