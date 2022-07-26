#include "CBrightStarCatalogDataset.h"

#include "CBSC1991.h"

static const int MIN_MAG = -2000;
static const int MAG_RANGE = 12800;
static const int MAG_STEPS = 256;
static const int RCMAG_TABLE_SIZE = 4095;

static const double starRelativeScale = 1.0;
static const double starAbsoluteScaleF = 1.0;

// The 0.025 corresponds to the maximum eye resolution in degrees
static const double EYE_RESOLUTION = 0.25;

// Maximum radius
static const double MAX_LINEAR_RADIUS = 8.0;

CBrightStarCatalogDataset::CBrightStarCatalogDataset(const CBSC1991* file, QObject* parent) : CSkyChartDataset(parent),
m_rcmag(RCMAG_TABLE_SIZE), m_fov(-DBL_MAX)
{
	if (file) {
		auto begin = file->data().begin(), end = file->data().end();
		while (begin != end) {
			CEquCoordinates equ = (*begin)->equatorialJ2000();
			double ra = equ.rightAscension().radians(), dec = equ.declination().radians();
			tObject obj;
			obj.pos = CVector3d(cos(ra) * cos(dec), sin(ra) * cos(dec), sin(dec));
			int mag_index = qRound(static_cast<double>(1000.0 * (*begin)->magnitude() - MIN_MAG) / MAG_RANGE * MAG_STEPS);
			if (mag_index < 0)
				mag_index = 0;
			if (mag_index > MAG_STEPS)
				mag_index = MAG_STEPS;
			obj.mag_index = mag_index;
			m_data.push_back(obj);
			++begin;
		}
	}
}

void CBrightStarCatalogDataset::setFOV(double fov)
{
	if (fov != m_fov) {
		m_fov = qBound(1e-4, fov, M_PI);
		double inScale = 2.45;

		// This factor is fully arbitrary. It corresponds to the collecting area x exposure time of the instrument
		// It is based on a power law, so that it varies progressively with the FOV to smoothly switch from human
		// vision to binocculares/telescope. Use a max of 0.7 because after that the atmosphere starts to glow too much!
		float powFactor = std::pow(60.0 / qMax(0.7, fov / M_PI * 180.0), 0.8);
		inScale *= powFactor;

		m_inputScale = inScale;

		// Set the fov factor for point source luminance computation
		// the division by powFactor should in principle not be here, but it doesn't look nice if removed
		m_lnfovFactor = std::log(1.0 / 50.0 * 2025000.0 * 60.0 * 60.0 / (m_fov * m_fov * 180 * 180 / M_PI / M_PI) / (EYE_RESOLUTION * EYE_RESOLUTION) / powFactor / 1.4);

		// Precompute
		m_starLinearScale = static_cast<float>(std::pow(35.0 * 2.0 * starAbsoluteScaleF, 1.40 * 0.5 * starRelativeScale));

		updateRCMagTable();
	}
}

void CBrightStarCatalogDataset::updateRCMagTable()
{
	const double mag_min = 0.001 * MIN_MAG;
	const double k = (0.001 * MAG_RANGE) / MAG_STEPS; // MagStepIncrement

	m_limitMagIndex = RCMAG_TABLE_SIZE;
	for (int i = 0; i < RCMAG_TABLE_SIZE; i++) {
		const float mag = mag_min + k * i;
		double radius = 0, luminance = 0;
		if (!computeRCMag(mag, m_rcmag[i].first, m_rcmag[i].second)) {
			m_limitMagIndex = i - 1;
			break;
		}
	}
	for (int i = m_limitMagIndex + 1; i < RCMAG_TABLE_SIZE; i++) 
		m_rcmag[i].first = m_rcmag[i].second = 0;
}

void CBrightStarCatalogDataset::paint(QPainter& painter, const CMatrix3d& q, const CProjection& p, const CTransformd& m, const QRectF& paint_rect)
{
	Qt::GlobalColor color = Qt::transparent;

	painter.setBrush(Qt::white);

	// Equatorial grid
	auto begin = m_data.begin(), end = m_data.end();
	while (begin != end) {
		CVector3d r3d = (q * begin->pos);
		p.project(r3d);
		if (r3d.z() >= 0 && begin->mag_index >= 0 && begin->mag_index < RCMAG_TABLE_SIZE) {
			auto rc = m_rcmag[begin->mag_index];
			if (rc.first > 0 && rc.second > 0) {
				double radius = qMax(0.5 * rc.first, 0.6), luminance = rc.second;
				CPointd xy = m.map(r3d.toPointF());
				int grayLevel = (int)qBound(0.0, 255 * luminance + 0.5, 255.0);
				painter.setPen(qRgb(grayLevel, grayLevel, grayLevel));
				painter.drawEllipse(QPointF(xy.x(), xy.y()), radius, radius);
			}
		}
		++begin;
	}
}

double CBrightStarCatalogDataset::pointSourceMagToLnLuminance(double mag) const
{
	return -0.92103 * (mag + 12.12331) + m_lnfovFactor;
}

//! Return adapted ln(luminance) from world to display with 1 corresponding to full display white
//! @param lnWorldLuminance the world luminance to convert in ln(cd/m^2)
//! @param pFact the power at which the result should be set. The default is 0.5 and therefore return the square root of the adapted luminance
//! @return the converted display set at the pFact power. Luminance with 1 corresponding to full display white. The value can be more than 1 when saturated.
double CBrightStarCatalogDataset::adaptLuminanceScaledLn(double lnWorldLuminance, double pFact) const
{
	double lnInputScale = std::log(m_inputScale);

	static const double Lda = 50.0, Lwa = 3.753, maxDisplayLuminance = 100.0, Gamma = 2.2222;

	// Update alphaDa and betaDa values
	float log10Lwa = std::log10(Lwa);
	double alphaWa = 0.4 * log10Lwa + 1.619;
	double betaWa = -0.4 * log10Lwa * log10Lwa + 0.218 * log10Lwa + 6.1642;

	// Update alphaDa and betaDa values
	double log10Lda = std::log10(Lda);
	double alphaDa = 0.4f * log10Lda + 1.619f;
	double betaDa = -0.4f * log10Lda * log10Lda + 0.218f * log10Lda + 6.1642f;

	double oneOverMaxdL = 1.0 / maxDisplayLuminance;
	double oneOverGamma = 1.0 / Gamma;
	double lnOneOverMaxdL = std::log(oneOverMaxdL);

	// Update terms
	double alphaWaOverAlphaDa = alphaWa / alphaDa;
	double term2 = (std::exp((betaWa - betaDa) / alphaDa * 2.3025850930) / (M_PI * 0.0001));
	double lnTerm2 = std::log(term2);
	double term2TimesOneOverMaxdL = term2 * oneOverMaxdL;
	double term2TimesOneOverMaxdLpOneOverGamma = std::pow(term2TimesOneOverMaxdL, oneOverGamma);

	const float lnPix0p0001 = static_cast<float>(log(M_PI * 1e-4)); //  -8.0656104861f; // conversion factor, log(lambert to cd/m^2). See Devlin et al. 4.2
	return std::exp(((lnInputScale + lnWorldLuminance + lnPix0p0001) * alphaWaOverAlphaDa + lnTerm2 + lnOneOverMaxdL) * pFact);
}



bool CBrightStarCatalogDataset::computeRCMag(double mag, double& radius, double& luminance) const
{
	radius = adaptLuminanceScaledLn(pointSourceMagToLnLuminance(mag), static_cast<float>(starRelativeScale) * 1.4 * 0.5);
	radius *= m_starLinearScale;
	// Use now statically min_rmag = 0.5, because higher and too small values look bad
	if (radius < 0.3f) {
		radius = luminance = 0;
		return false;
	}

	// if size of star is too small (blink) we put its size to 1.2 --> no more blink
	// And we compensate the difference of brighteness with cmag
	if (radius < 1.2) {
		luminance = radius * radius * radius / 1.728;
		if (luminance < 0.05) {
			radius = luminance = 0;
			return false;
		}
		radius = 1.2;
	} 
	else {
		// cmag:
		luminance = 1.0;
		if (radius > MAX_LINEAR_RADIUS)
			radius = MAX_LINEAR_RADIUS + std::sqrt(1.0 + radius - MAX_LINEAR_RADIUS) - 1.0;
	}
	return true;
}