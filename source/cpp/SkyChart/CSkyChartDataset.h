#pragma once

#include <QtGui>

class CSkyChartDataset : public QObject
{
public:
	explicit CSkyChartDataset(QObject* parent = nullptr) : QObject(parent) {}

	virtual ~CSkyChartDataset() {}

	virtual void paint(QPainter& painter, const QQuaternion& q, const QTransform& m) = 0;
};