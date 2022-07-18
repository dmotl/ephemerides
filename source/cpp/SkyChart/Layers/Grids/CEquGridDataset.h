#pragma once

#include "CSkyChartDataset.h"

class CEquGridDataset : public CSkyChartDataset
{
public:
	enum class tStyle
	{
		DOTS, 
		LINES
	};

	CEquGridDataset(QObject* parent = nullptr) : CSkyChartDataset(parent), m_longitudeStep(15), m_latitudeStep(15), m_style(tStyle::LINES), m_dirty(true) {}
	CEquGridDataset(tStyle style, double longitudeStep, double latitudeStep) : m_style(style), m_longitudeStep(longitudeStep), m_latitudeStep(latitudeStep), m_dirty(true) {}

	void paint(QPainter& painter, const CMatrix3d& q,
		const CProjection& p, const CTransformd& m, const QRectF& paint_rect) override;

private:
	class CCurve
	{
	public:
		CCurve() {}
		CCurve(const std::vector<CVector3d>& pts) : m_pts(pts) {}
		std::optional<QPainterPath> toPath(const CMatrix3d& q, const CProjection& p, const CTransformd& m,
			const QRectF& paint_rect) const;

	private:
		std::vector<CVector3d> m_pts;
	};

	tStyle m_style;
	double m_longitudeStep;
	double m_latitudeStep;
	bool m_dirty;
	std::vector<CCurve> m_lines;
	std::vector<CVector3d> m_dots;

	void updatePoints();

	std::optional<QPainterPath> toPath(const std::vector<CVector3d>& pts, const CMatrix3d& q, const CProjection& p, const CTransformd& m,
		const QRectF& paint_rect) const;
};