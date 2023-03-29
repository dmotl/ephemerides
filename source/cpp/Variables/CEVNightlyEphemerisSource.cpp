#include "CEVNightlyEphemerisSource.h"

#include "Utils.h"
#include "CCatalog.h"

CEVNightlyEphemerisSource::CEVNightlyEphemerisSource() : m_flags(All), m_magMin(INVALID_MAG), m_magMax(INVALID_MAG), m_rankMin(0),
m_rankMax(0), m_raMin(0), m_raMax(0), m_decMin(0), m_decMax(0), m_needUpdate(false)
{
	m_it = m_end = m_data.constEnd();
}

void CEVNightlyEphemerisSource::setFlag(tFilter f, bool state)
{
	if (m_flags.testFlag(f) != state) {
		m_flags.setFlag(f, state);
		m_needUpdate = true;
	}
}

void CEVNightlyEphemerisSource::setFlags(const Filter& flags)
{
	if (flags != m_flags) {
		m_flags = flags;
		m_needUpdate = true;
	}
}

void CEVNightlyEphemerisSource::setMagRange(double mag_min, double mag_max)
{
	if (mag_min != m_magMin || mag_max != m_magMax) {
		m_magMin = mag_min;
		m_magMax = mag_max;
		m_needUpdate = m_needUpdate || m_flags.testFlag(F_MAG);
	}
}

void CEVNightlyEphemerisSource::setRankRange(int rank_min, int rank_max)
{
	if (rank_min != m_rankMin || rank_max != m_rankMax) {
		m_rankMin = rank_min;
		m_rankMax = rank_max;
		m_needUpdate = m_needUpdate || m_flags.testFlag(F_RANK);
	}
}

void CEVNightlyEphemerisSource::setRARange(double ra_min, double ra_max)
{
	if (ra_min != m_raMin || ra_max != m_raMax) {
		m_raMin = ra_min;
		m_raMax = ra_max;
		m_needUpdate = m_needUpdate || m_flags.testFlag(F_RA);
	}
}

void CEVNightlyEphemerisSource::setDecRange(double dec_min, double dec_max)
{
	if (dec_min != m_decMin || dec_max != m_decMax) {
		m_decMin = dec_min;
		m_decMax = dec_max;
		m_needUpdate = m_needUpdate || m_flags.testFlag(F_DEC);
	}
}

void CEVNightlyEphemerisSource::setConstList(const QList<CConstellation>& const_list)
{
	QSet<CConstellation> new_list(const_list.begin(), const_list.end());
	if (new_list != m_constList) {
		m_constList = new_list;
		m_needUpdate = m_needUpdate || m_flags.testFlag(F_CONS);
	}
}

void CEVNightlyEphemerisSource::setVarTypeList(const QStringList& vartype_list)
{
	QSet<QString> new_list(vartype_list.begin(), vartype_list.end());
	if (new_list != m_varTypeList) {
		m_varTypeList = new_list;
		m_needUpdate = m_needUpdate || m_flags.testFlag(F_VARTYPE);
	}
}

void CEVNightlyEphemerisSource::addCatalog(CCatalog* catalog)
{
	if (!m_catalogs.contains(catalog)) {
		m_catalogs.append(catalog);
		m_needUpdate = true;
	}
}

const CCatalogObject* CEVNightlyEphemerisSource::first() 
{
	if (m_needUpdate) {
		update();
		m_needUpdate = false;
	}
	m_it = m_data.constBegin();
	m_end = m_data.constEnd();
	return find();
}

const CCatalogObject* CEVNightlyEphemerisSource::next()
{
	assert(m_it != m_end);

	++m_it;
	return find();
}

const CCatalogObject* CEVNightlyEphemerisSource::find(void)
{
	if (m_it != m_end)
		return *m_it;
	return nullptr;
}

void CEVNightlyEphemerisSource::update(void)
{
	m_data.clear();
	m_it = m_end = m_data.constEnd();

	for (int i = 0; i < m_catalogs.count(); i++) {
		CCatalog* c = m_catalogs[i];
		m_data.reserve(m_data.size() + c->count());
		const CCatalogObject* obj = c->first();
		while (obj) {
			m_data.append(obj);
			obj = c->next();
		}
	}
}
