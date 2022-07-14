#pragma once

#include <QtGui>

#include "CProjection.h"
#include "CQuaternion.h"
#include "CTransform.h"

using CPointd = QPointF;
using CVector3d = QVector3D;
using CTransformd = QTransform;
using CQuaterniond = QQuaternion;

class CSkyChartDataset
{
public:
	CSkyChartDataset() {}

	virtual ~CSkyChartDataset() {}

	virtual void paint(QPainter& painter, const CQuaterniond& q,
		const CProjection& p, const CTransformd& m, const QRectF& paint_rect) = 0;
};