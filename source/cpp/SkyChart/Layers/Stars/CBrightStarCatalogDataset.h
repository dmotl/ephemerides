#pragma once

#include "CSkyChartDataset.h"
#include "CBSC1991.h"

class CBrightStarCatalogDataset : public CSkyChartDataset
{
public:
	explicit CBrightStarCatalogDataset(const CBSC1991* data, QObject* parent = nullptr);

	void paint(QPainter& painter, const CMatrix3d& q, const CProjection& p, const CTransformd& m, const QRectF& paint_rect) override;

private:
	struct tObject
	{
		CVector3d pos;
		double rsize;
	};

	std::vector<tObject> m_data;
};
