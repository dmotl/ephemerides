#pragma once

#include <QtGui>

#include "CProjection.h"
#include "CQuaternion.h"
#include "CTransform.h"
#include "CMatrix3d.h"

class CSkyChartDataset : public QObject
{
public:
	CSkyChartDataset(QObject* parent = nullptr) : QObject(parent) {}

	virtual void paint(QPainter& painter, const CMatrix3d& q,
		const CProjection& p, const CTransformd& m, const QRectF& paint_rect) = 0;
};