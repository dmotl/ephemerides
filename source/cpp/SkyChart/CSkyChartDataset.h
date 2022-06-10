#pragma once

#include <QtGui>

#include "CProjection.h"

class CSkyChartDataset : public QObject
{
public:
	explicit CSkyChartDataset(QObject* parent = nullptr) : QObject(parent) {}

	virtual ~CSkyChartDataset() {}

	virtual void paint(QPainter& painter, const QQuaternion& q, 
		const CProjection& p, const QTransform& m) = 0;
};