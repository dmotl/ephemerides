#include "CEVStarEphemerisModel.h"

CEVStarEphemerisModel::CEVStarEphemerisModel(QObject* parent) : CEVEphemerisItemModel(parent)
{
	m_cols.append(tColumnId::COL_DATE_UTC);
	m_cols.append(tColumnId::COL_TIME_UTC);
	m_cols.append(tColumnId::COL_DAYOFWEEK);
	m_cols.append(tColumnId::COL_JULIANDATE);
	m_cols.append(tColumnId::COL_EPOCH);
	m_cols.append(tColumnId::COL_PS);
	m_cols.append(tColumnId::COL_AZ);
	m_cols.append(tColumnId::COL_ALT);
	m_cols.append(tColumnId::COL_MOONPHASE);
	m_cols.append(tColumnId::COL_OBJMOON);
}
