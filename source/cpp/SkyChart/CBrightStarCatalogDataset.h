#pragma once

#include "CSkyChartDataset.h"

class CBSC1991;

class CBrightStarCatalogDataset : public CSkyChartDataset
{
public:
	CBrightStarCatalogDataset();

	~CBrightStarCatalogDataset() override;

	void paint(QPainter& painter, const CQuaterniond& q, const CProjection& p, const CTransformd& m, const QRectF& paint_rect) override;

private:
	struct tObject
	{
		CVector3d pos;
		double rsize;
	};

	CBSC1991 *m_bsc;
	std::vector<tObject> m_data;
};
