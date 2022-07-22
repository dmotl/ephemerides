/*!
*  \file      CSkyChartView.cpp
*  \author    David Motl
*  \date      2022-05-11
*
*  \copyright
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted
*  provided that the following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions
*      and the following disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list
*      of conditions and the following disclaimer in the documentation and/or other materials provided
*      with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of its contributors may be used
*      to endorse or promote products derived from this software without specific prior written
*      permission.
*/
#include "CSkyChartView.h"

#include "CSkyChartDataset.h"
#include "CStereographicProjection.h"
#include "COrthographicProjection.h"

CVector3d CSkyChartView::toXYZ(const QPoint& xy) const
{
	double res = m_viewSize - 1;

	// map to -1 to 1
	double x = (2 * xy.x() - m_width - 1) / res;
	double y = (2 * xy.y() - m_height - 1) / res;

	double h = x * x + y * y;
	if (h <= 0.5)
		return CVector3d(x, y, sqrt(1 - h));
	else
		return CVector3d(x, y, 0.5 / sqrt(h));
}

CVector3d CSkyChartView::toXYZ(const CPointd& xy) const
{
	double res = m_viewSize - 1;

	// map to -1 to 1
	double x = (2 * xy.x() - m_width - 1) / res;
	double y = (2 * xy.y() - m_height - 1) / res;

	double h = x * x + y * y;
	if (h <= 0.5)
		return CVector3d(x, y, sqrt(1 - h)).normalized();
	else
		return CVector3d(x, y, 0.5 / sqrt(h)).normalized();
}

CSkyChartView::CSkyChartView(QWidget* parent) : QWidget(parent), m_centerCoords({ 0.0, 0.0, 1.0 }),
m_scale(1.0), m_viewSize(0), m_rotating(false), m_width(0), m_height(0)
{
	m_projector = new COrthographicProjection(this);
	m_rotMatrix = toRotationMatrix(m_centerCoords);
	setMouseTracking(true); 
}

CSkyChartView::~CSkyChartView()
{
}

void CSkyChartView::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.fillRect(event->rect(), Qt::black);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setRenderHint(QPainter::TextAntialiasing);

	if (m_projector) {
		double scale = 0.5 * m_scale * m_viewSize, dx = m_offset.x(), dy = m_offset.y();
		CTransformd scaleShift = CTransformd::fromScale(scale, scale) * CTransformd::fromTranslate(dx, dy);
		for (int i = 0; i < m_datasets.count(); i++)
			m_datasets[i]->paint(painter, m_rotMatrix, *m_projector, scaleShift, event->rect());
	}
}

void CSkyChartView::resizeEvent(QResizeEvent* event)
{
	QSize sz = size();
	m_width = sz.width();
	m_height = sz.height();
	int size = qMin(m_width, m_height);
	if (size != m_viewSize) {
		m_viewSize = size;
		m_offset = 0.5 * CPointd(m_width, m_height);
		update();
	}
	QWidget::resizeEvent(event);
}

void CSkyChartView::mouseMoveEvent(QMouseEvent* event)
{
	if (m_rotating) {
		CQuaterniond rotQ = CQuaterniond::rotationTo(toXYZ(event->pos()), toXYZ(m_startPos));
		m_centerCoords = fromRotationMatrix((rotQ * m_lastQ).toRotationMatrix());
		m_rotMatrix = toRotationMatrix(m_centerCoords);
		event->accept();
		emit viewChanged();
		update();
		return;
	}
	QWidget::mouseMoveEvent(event);
}

void CSkyChartView::leaveEvent(QEvent* event)
{
	QWidget::leaveEvent(event);
}

void CSkyChartView::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) 
	{
		if (!m_rotating) {
			m_rotating = true;
			m_lastQ = CQuaterniond::fromRotationMatrix(m_rotMatrix);
			m_startPos = event->pos();
			event->accept();
			return;
		}
	}
	QWidget::mousePressEvent(event);
}

void CSkyChartView::mouseReleaseEvent(QMouseEvent* event)
{
	if (m_rotating) {
		m_rotating = false;
		emit viewChanged();
		update();
		event->accept();
		return;
	}
	QWidget::mouseReleaseEvent(event);
}

void CSkyChartView::wheelEvent(QWheelEvent* event)
{
	//event->



	QWidget::wheelEvent(event);
}

void CSkyChartView::setScale(double scale)
{
	if (scale != m_scale) {
		m_scale = scale;
		update();
	}
}

void CSkyChartView::addDataset(CSkyChartDataset* dataset)
{
	if (dataset != nullptr and !m_datasets.contains(dataset)) 
		m_datasets.append(dataset);
}

void CSkyChartView::setProjector(CProjection* projector)
{
	if (projector != m_projector) {
		m_projector = projector;
		update();
	}
}

CMatrix3d CSkyChartView::toRotationMatrix(const CEquCoordinates& coords)
{
	const double ra = coords.rightAscension().radians(), de = coords.declination().radians();
	const double sin_ra = std::sin(ra), cos_ra = std::cos(ra), sin_de = std::sin(de), cos_de = std::cos(de);

	CMatrix3<double> rot3x3;
	rot3x3.at(0, 0) = -sin_ra;
	rot3x3.at(0, 1) = cos_ra;
	rot3x3.at(0, 2) = 0.0;
	rot3x3.at(1, 0) = cos_ra * sin_de;
	rot3x3.at(1, 1) = sin_ra * sin_de;
	rot3x3.at(1, 2) = -cos_de;
	rot3x3.at(2, 0) = -cos_ra * cos_de;
	rot3x3.at(2, 1) = -sin_ra * cos_de;
	rot3x3.at(2, 2) = -sin_de;
	return rot3x3;
}

CEquCoordinates CSkyChartView::fromRotationMatrix(const CMatrix3d& rotMatrix)
{
	double det = rotMatrix.determinant();
	if (det != 0) {
		const double x = (rotMatrix(0, 2) * rotMatrix(1, 1) - rotMatrix(0, 1) * rotMatrix(1, 2)) / det;
		const double y = (rotMatrix(0, 0) * rotMatrix(1, 2) - rotMatrix(0, 2) * rotMatrix(1, 0)) / det;
		const double z = (rotMatrix(0, 1) * rotMatrix(1, 0) - rotMatrix(0, 0) * rotMatrix(1, 1)) / det;
		return CEquCoordinates(CVector3d(x, y, z));
	}
	return CEquCoordinates();
}

void CSkyChartView::setCoords(const CEquCoordinates& coords)
{
	if (m_projector && !m_rotating && coords.isValid()) {
		CMatrix3d rotMatrix = toRotationMatrix(coords);
		if (rotMatrix != m_rotMatrix) {
			m_rotMatrix = rotMatrix;
			m_centerCoords = coords;
			update();
		}
	}
}

CEquCoordinates CSkyChartView::mapToCoords(const CPointd& pos) const
{
	if (m_projector) {
		double scale = 0.5 * m_scale * m_viewSize, dx = m_offset.x(), dy = m_offset.y();
		CTransformd invScaleShift = (CTransformd::fromScale(scale, scale) * CTransformd::fromTranslate(dx, dy)).inverted();
		CVector3d r3d(invScaleShift.map(pos));
		m_projector->unproject(r3d);
		return CEquCoordinates(m_rotMatrix.inverted() * r3d);
	}
	return CEquCoordinates();
}
