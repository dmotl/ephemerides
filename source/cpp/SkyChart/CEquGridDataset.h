#pragma once

#include <QtWidgets>

#include "CSkyChartDataset.h"

class CEquGridDataset : public CSkyChartDataset
{
public:
	explicit CEquGridDataset(QObject* parent = nullptr) :CSkyChartDataset(parent), m_longitudeStep(10), m_latitudeStep(10) {}
	CEquGridDataset(double longitudeStep, double latitudeStep, QObject* parent = nullptr) :CSkyChartDataset(parent), m_longitudeStep(longitudeStep), m_latitudeStep(latitudeStep) {}

	void paint(QPainter& painter, const QQuaternion& q, const CProjection& p, const QTransform& m);

private:
	double m_longitudeStep;
	double m_latitudeStep;
};