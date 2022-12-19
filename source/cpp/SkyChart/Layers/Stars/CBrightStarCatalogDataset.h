#pragma once

#define USE_EMBEDED_BSC1991 1

#include "CSkyChartDataset.h"

#if USE_EMBEDED_BSC1991
class CBSC1991_Embedded;
using CBSC1991 = CBSC1991_Embedded;
#endif

#include "CBSC1991.h"

class CBrightStarCatalogDataset : public CSkyChartDataset
{
public:
	explicit CBrightStarCatalogDataset(const CBSC1991* data, QObject* parent = nullptr);

	void setFOV(double fov) override;

	void paint(QPainter& painter, const CMatrix3d& q, const CProjection& p, const CTransformd& m, const QRectF& paint_rect) override;

private:
	struct tObject
	{
		CVector3d pos;
		int mag_index;
		tObject() : mag_index(0) {}
	};

	double m_fov;

	std::vector<tObject> m_data;
	std::vector<std::pair<double, double>> m_rcmag;
	int m_limitMagIndex;
	double m_lnfovFactor, m_starLinearScale, m_inputScale;

	bool computeRCMag(double mag, double& radius, double& luminance) const;

	double pointSourceMagToLnLuminance(double mag) const;

	double adaptLuminanceScaledLn(double lnWorldLuminance, double pFact = 0.5) const;

	void updateRCMagTable();
};
