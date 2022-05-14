#pragma once

#include "CSkyChartDataset.h"

class CBSC1991;

class CBrightStarCatalogDataset : public CSkyChartDataset
{
public:
	explicit CBrightStarCatalogDataset(QObject* parent = nullptr);

	~CBrightStarCatalogDataset() override;

	void paint(QPainter& painter, const QQuaternion& q, const QTransform& m) override;

private:
	struct tObject
	{
		QVector3D pos;
		double rsize;
	};

	CBSC1991 *m_bsc;
	std::list<tObject> m_data;
};
