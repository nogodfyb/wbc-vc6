// MyRepository.cpp: implementation of the MyRepository class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "wbc.h"
#include "MyRepository.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MyRepository::MyRepository()
{

}

MyRepository::~MyRepository()
{

}

CString MyRepository::insertSecondWeighRecord(CStringArray &params){
	CString sql;
	sql.Format("INSERT INTO wbc20_second_weigh_record\
		(shift, bn, machine_code, ep_sn, ep_start_time, ep_exceed_time, first_weight, first_weigh_time, second_weight, wafer_device, wafer_source, \
		wafer_lot, wafer_size, is_over_weight, scraper_sn, steel_mesh_sn, shim_sn,expection_reason,handle_plan,handle_remark,handle_result) VALUES ('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s',\
		'%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')",params.GetAt(0),params.GetAt(1),params.GetAt(2),params.GetAt(3),params.GetAt(4),params.GetAt(5),params.GetAt(6),params.GetAt(7),
		params.GetAt(8),params.GetAt(9),params.GetAt(10),params.GetAt(11),params.GetAt(12),params.GetAt(13),params.GetAt(14),params.GetAt(15),params.GetAt(16),params.GetAt(17),params.GetAt(18),params.GetAt(19),params.GetAt(20));
	return sql;
}

