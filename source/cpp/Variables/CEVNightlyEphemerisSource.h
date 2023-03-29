#pragma once

#include "CSource.h"
#include "CConstellation.h"

class CCatalog;

class CEVNightlyEphemerisSource : public CSource
{
public:
	enum tFilter { All = 0, F_MAG = (1 << 0), F_RANK = (1 << 1), F_RA = (1 << 2), F_DEC = (1 << 3), F_CONS = (1 << 4), F_VARTYPE = (1 << 5) };
	Q_DECLARE_FLAGS(Filter, tFilter);

	CEVNightlyEphemerisSource();

	void setFlag(tFilter f, bool state = true);
	bool testFlag(tFilter f) { return m_flags.testFlag(f); }
	const Filter& flags() const { return m_flags; }
	void setFlags(const Filter& flags);

	void setMagRange(double mag_min, double mag_max);
	void setRankRange(int rank_min, int rank_max);
	void setRARange(double ra_min, double ra_max);
	void setDecRange(double dec_min, double dec_max);
	void setConstList(const QList<CConstellation>& const_list);
	void setVarTypeList(const QStringList& vartype_list);

	void addCatalog(CCatalog* catalog);

	const CCatalogObject* first() override;
	const CCatalogObject* next() override;

protected:
	Filter m_flags;
	double m_magMin, m_magMax;
	int m_rankMin, m_rankMax;
	double m_raMin, m_raMax;
	double m_decMin, m_decMax;
	QSet<CConstellation> m_constList;
	QSet<QString> m_varTypeList;
	QList<CCatalog*> m_catalogs;

	QList<const CCatalogObject*> m_data;
	QList<const CCatalogObject*>::const_iterator m_it, m_end;

	bool m_needUpdate;

	virtual void update(void);

	const CCatalogObject* find(void);
};

Q_DECLARE_OPERATORS_FOR_FLAGS(CEVNightlyEphemerisSource::Filter);
