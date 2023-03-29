#include "CEVEphemerisItemModel.h"

#include "CEphemerisBase.h"
#include "UtilsQt.h"
#include "CCatalogObject.h"
#include "CPlanets.h"

class CEphemerisNoData : public CEphemerisBase
{
public:
	explicit CEphemerisNoData(QObject* parent = nullptr) : CEphemerisBase(parent) {}

	// Update ephemeris
	void update(CJulianDate start, CJulianDate end, tCancelledFn cbCancelled, tSetCaption cbSetCaption,
		tSetProgressMaxFn cbSetProgressRange, tSetProgressValueFn cbSetProgressValue) {}
};


//
// Constructor
//
CEVEphemerisItemModel::CEVEphemerisItemModel(QObject* parent) : m_sharedData(false)
{
	m_data = new CEphemerisNoData(this);
}

//
// Destructor
//
CEVEphemerisItemModel::~CEVEphemerisItemModel(void)
{
	if (!m_sharedData)
		delete m_data;
}

//
// Set data
//
void CEVEphemerisItemModel::setDataModel(CEphemerisBase* data)
{
	if (data != m_data) {
		beginResetModel();
		if (!m_sharedData) 
			delete m_data;
		if (data) {
			m_sharedData = true;
			m_data = data;
		}
		else {
			m_sharedData = false;
			m_data = new CEphemerisNoData(this);
		}
		endResetModel();
	}
}

int CEVEphemerisItemModel::rowCount(const QModelIndex& parent) const
{
	if (!parent.isValid())
		return m_rawData.size();
	return 0;
}

QModelIndex CEVEphemerisItemModel::index(int row, int column, const QModelIndex& parent) const
{
	if (parent.isValid())
		return createIndex(row, column);
	return QModelIndex();
}

QModelIndex CEVEphemerisItemModel::parent(const QModelIndex& index) const
{
	return QModelIndex();
}

QVariant CEVEphemerisItemModel::data(const QModelIndex& index, int role) const
{
	switch (role)
	{
	case Qt::DisplayRole:
		return getDisplayString(*m_rawData[index.row()], m_cols[index.column()]);
	}
	return QVariant();
}

QVariant CEVEphemerisItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal) {
		switch (role)
		{
		case Qt::DisplayRole:
			return getColumnCaption(m_cols[section]);
		}
	}
	return QVariant();
}

Qt::ItemFlags CEVEphemerisItemModel::flags(const QModelIndex& index) const
{
	return QAbstractItemModel::flags(index);
}


QString CEVEphemerisItemModel::getColumnCaption(const tColumnId& col)
{
	switch (col)
	{
	case tColumnId::COL_NAME:
		return tr("Name");
	case tColumnId::COL_PS:
		return tr("PS");
	case tColumnId::COL_DATE_UTC:
	case tColumnId::COL_DATE_LOCAL:
		return tr("Date");
	case tColumnId::COL_TIME_UTC:
		return tr("UT");
	case tColumnId::COL_TIME_LOCAL:
		return tr("Local");
	case tColumnId::COL_AZ:
		return tr("Az.");
	case tColumnId::COL_ALT:
		return tr("Alt.");
	case tColumnId::COL_RA:
		return tr("R.A.");
	case tColumnId::COL_DEC:
		return tr("Dec.");
	case tColumnId::COL_TYPE:
		return tr("Type");
	case tColumnId::COL_MAG:
		return tr("Mag");
	case tColumnId::COL_CATALOG:
		return tr("Catalog");
	case tColumnId::COL_RANK:
		return tr("Pts");
	case tColumnId::COL_OBJMOON:
		return tr("Obj-Moon");
	case tColumnId::COL_REMARKS:
		return tr("Remarks");
	case tColumnId::COL_DAYOFWEEK:
		return tr("DoW");
	case tColumnId::COL_JULIANDATE:
		return tr("JD");
	case tColumnId::COL_EPOCH:
		return tr("Epoch");
	case tColumnId::COL_MOONPHASE:
		return tr("Moon phase");
	}
	return QString();
}

QString CEVEphemerisItemModel::getDisplayString(tRow& row, const tColumnId& col) const
{
	if (!row.status)
		updateRowCache(row);
	return row.cache.value(col);
}

void CEVEphemerisItemModel::updateRowCache(tRow& row) const
{
	if (m_data) {
		auto eph = m_data->at(row.index_to_data);
		const CVariableStar* vs = dynamic_cast<const CVariableStar*>(eph.object);
		if (vs) {
			// Var name
			row.cache.insert(tColumnId::COL_NAME, vs->variableName());
			// Event type
			row.cache.insert(tColumnId::COL_PS, UtilsQt::eventTypeShortCaption(eph.evtype));
			// Date & UT
			CDateTime utc = eph.jd.toDateTime();
			row.cache.insert(tColumnId::COL_DATE_UTC, QDate(utc.year(), utc.month(), utc.day()).toString(Qt::ISODate));
			double time1 = 0.5 * (int)((utc.hour() + (double)utc.minute() / 60) * 2 + 0.5);
			row.cache.insert(tColumnId::COL_TIME_UTC, QString::number(time1, 'f', 2));
			// Local time
			QDateTime local = UtilsQt::fromUTC(utc);
			row.cache.insert(tColumnId::COL_DATE_LOCAL, local.date().toString(Qt::ISODate));
			double time2 = (double)local.time().msecsSinceStartOfDay() / 3600000;
			row.cache.insert(tColumnId::COL_TIME_LOCAL, QString::number(time2, 'f', 2));
			// Day of week
			if (local.time().msecsSinceStartOfDay() >= 12 * 3600000) {
				row.cache.insert(tColumnId::COL_DAYOFWEEK, local.date().toString(QStringLiteral("ddd")) + QStringLiteral("/") +
					local.date().addDays(1).toString(QStringLiteral("ddd")));
			}
			else {
				row.cache.insert(tColumnId::COL_DAYOFWEEK, local.date().addDays(-1).toString(QStringLiteral("ddd")) + QStringLiteral("/") +
					local.date().toString(QStringLiteral("ddd")));
			}
			// Julian date
			row.cache.insert(tColumnId::COL_JULIANDATE, QString::number(eph.jd, 'f', 3));
			// Az & Alt
			CAzAltCoordinates azAlt = eph.jd.RaDeToAzAlt(vs->coords(), m_geoCoords);
			if (azAlt.isValid()) {
				row.cache.insert(tColumnId::COL_AZ, UtilsQt::compassPointName(azAlt.azimuth().toCompassPoint()));
				row.cache.insert(tColumnId::COL_ALT, QString::number(azAlt.elevation().degrees(), 'f', 0));
			}
			else {
				row.cache.insert(tColumnId::COL_AZ, tr("N/A"));
				row.cache.insert(tColumnId::COL_ALT, tr("N/A"));
			}
			// R.A. & Dec.
			if (vs->coords().isValid()) {
				QTime ra = QTime::fromMSecsSinceStartOfDay((int)(vs->coords().rightAscension().hours() * 3600000));
				row.cache.insert(tColumnId::COL_RA, ra.toString(QStringLiteral("h:mm")));
				double dec = vs->coords().declination().degrees();
				row.cache.insert(tColumnId::COL_DEC, QString::number(dec, 'f', 1));
			}
			else {
				row.cache.insert(tColumnId::COL_RA, tr("N/A"));
				row.cache.insert(tColumnId::COL_DEC, tr("N/A"));
			}
			// Type
			row.cache.insert(tColumnId::COL_TYPE, vs->varTypeString());
			// Mag range
			double mag_min = vs->minimumMag(), mag_max = vs->maximumMag();
			if (mag_min == INVALID_MAG && mag_max == INVALID_MAG)
				row.cache.insert(tColumnId::COL_MAG, tr("N/A"));
			else if (mag_min != INVALID_MAG)
				row.cache.insert(tColumnId::COL_MAG, QStringLiteral(":%1").arg(mag_min, 0, 'f', 1));
			else if (mag_max != INVALID_MAG)
				row.cache.insert(tColumnId::COL_MAG, QStringLiteral("%1:").arg(mag_max, 0, 'f', 1));
			else
				row.cache.insert(tColumnId::COL_MAG, QStringLiteral("%1:%2").arg(mag_max, 0, 'f', 1).arg(mag_min, 0, 'f', 1));
			// Moon phase
			static constexpr double period = 29.53059, epoch = 1721088.5;
			double phase_age = fmod(eph.jd - epoch + 0.25 * period, period);
			double illum_pct = 0.5 * (1.0 - cos(phase_age / period * 2 * M_PI)) * 100.0;
			if (phase_age < 0.5 * period)
				row.cache.insert(tColumnId::COL_MOONPHASE, QStringLiteral("%1%+").arg(illum_pct, 0, 'f', 0));
			else
				row.cache.insert(tColumnId::COL_MOONPHASE, QStringLiteral("%1%-").arg(illum_pct, 0, 'f', 0));
			// Object moon distance
			CEquCoordinates moon = Utils::vsop87ToFK5(CPlanets(eph.jd).Moon()), obj = vs->coords();
			if (moon.isValid() && obj.isValid()) {
				double d = RAD_TO_DEG(moon.distanceTo(obj));
				row.cache.insert(tColumnId::COL_OBJMOON, QString::number(d, 'f', 0));
			}
			else
				row.cache.insert(tColumnId::COL_OBJMOON, tr("N/A"));
			// Remarks
			row.cache.insert(tColumnId::COL_REMARKS, vs->remarks());
		}
	}
}
