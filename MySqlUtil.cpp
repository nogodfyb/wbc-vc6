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
		throw "数据库连接失败!";
	}
}

MySqlUtil::~MySqlUtil()
{
	mysql_close(&mysql);
}

//开启事务
void MySqlUtil::beginTransaction() {
    //关闭自动提交
    mysql_autocommit(&mysql, 0);
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

//查询数据
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
		throw "查询数据失败!";
		return;
	}
    return ;
}
//查询数据
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
		throw "查询数据失败!";
		return;
	}
    return ;
}

//查询数据并渲染表格
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
	list->AdjustColumnWidth();
	if (!Msg.IsEmpty())
	{
		throw "查询数据失败!";
		return;
	}
    return ;

}
//判断是否存在
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

//插入数据
int MySqlUtil::InsertData(CString SQL, CString &Msg)
{
    if (mysql_query(&mysql, SQL) != 0)
    {
        Msg = mysql_error(&mysql);
		if (!Msg.IsEmpty())
		{
			throw "插入数据失败!";
			return 0;
		}
        return 0;
    }
    return 1;
}

//更新数据
int MySqlUtil::UpdateData(CString SQL, CString& Msg)
{
    if (mysql_query(&mysql, SQL) != 0)
    {
        Msg = mysql_error(&mysql);
        return 0;
    }
	if (!Msg.IsEmpty())
	{
		throw "更新数据失败!";
		return 0;
	}
    return 1;
}

//删除数据
int MySqlUtil::DeleteData(CString SQL, CString& Msg)
{
    if (mysql_query(&mysql, SQL) != 0)
    {
        Msg = mysql_error(&mysql);
        return 0;
    }
	if (!Msg.IsEmpty())
	{
		throw "删除数据失败!";
		return 0;
	}
    return 1;
}

//关闭数据库连接
void MySqlUtil::CloseMySQLConn()
{
    mysql_close(&mysql);
}