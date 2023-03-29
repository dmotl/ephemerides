#pragma once

#include <QtGui>

#include "CGeoCoordinates.h"

class CEphemerisBase;

class CEVEphemerisItemModel : public QAbstractItemModel
{
public:
	explicit CEVEphemerisItemModel(QObject* parent = nullptr);

	~CEVEphemerisItemModel() override;

	void setDataModel(CEphemerisBase* data);

	CEphemerisBase* model(void) { return m_data; }

	void setObserverCoordinates(const CGeoCoordinates& loc);

	const CGeoCoordinates& observerCoordinates(void) const { return m_geoCoords; }

	int columnCount(const QModelIndex& parent = QModelIndex()) const override { return m_cols.size(); }

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;

	QModelIndex parent(const QModelIndex& index) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	Qt::ItemFlags flags(const QModelIndex& index) const override;

protected:
	enum class tColumnId
	{
		COL_NAME,
		COL_PS,
		COL_DATE_UTC,
		COL_TIME_UTC,
		COL_DATE_LOCAL,
		COL_TIME_LOCAL,
		COL_DAYOFWEEK,
		COL_JULIANDATE,
		COL_EPOCH,
		COL_AZ,
		COL_ALT,
		COL_RA,
		COL_DEC,
		COL_TYPE,
		COL_MAG,
		COL_CATALOG,
		COL_RANK,
		COL_OBJMOON,
		COL_MOONPHASE,
		COL_REMARKS
	};

	struct tRow
	{
		int index_to_data;
		bool status;
		QMap<tColumnId, QString> cache;
		tRow() : index_to_data(0), status(false) {}
	};

	CEphemerisBase* m_data;
	bool m_sharedData;
	CGeoCoordinates m_geoCoords;

	QList<tColumnId> m_cols;

	QList<tRow*> m_rawData;

	QList<int> m_rowIndices;

	static QString getColumnCaption(const tColumnId& col);

	QString getDisplayString(tRow& row, const tColumnId& col) const;

	void updateRowCache(tRow& row) const;
};
