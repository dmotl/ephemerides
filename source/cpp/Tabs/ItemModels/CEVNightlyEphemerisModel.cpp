#include "CEVNightlyEphemerisModel.h"

//
// Constructor
//
CEVNightlyEphemerisModel::CEVNightlyEphemerisModel(QObject* parent) : CEVEphemerisItemModel(parent)
{
	m_cols.append(tColumnId::COL_NAME);
	m_cols.append(tColumnId::COL_PS);
	m_cols.append(tColumnId::COL_DATE_UTC);
	m_cols.append(tColumnId::COL_TIME_UTC);
	m_cols.append(tColumnId::COL_AZ);
	m_cols.append(tColumnId::COL_ALT);
	m_cols.append(tColumnId::COL_RA);
	m_cols.append(tColumnId::COL_DEC);
	m_cols.append(tColumnId::COL_TYPE);
	m_cols.append(tColumnId::COL_MAG);
	m_cols.append(tColumnId::COL_CATALOG);
	m_cols.append(tColumnId::COL_RANK);
	m_cols.append(tColumnId::COL_OBJMOON);
	m_cols.append(tColumnId::COL_REMARKS);
}

