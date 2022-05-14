/*!
*  \file      CSkyChartView.h
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
#pragma once

#include <QtWidgets>

#include "CEquCoordinates.h"

class CSkyChartDataset;

class CSkyChartView : public QWidget
{
	Q_OBJECT

public:
	CSkyChartView(QWidget* parent);

	QQuaternion viewQuat(void) const { return m_currQ * m_lastQ; }
	
	void setViewQuat(const QQuaternion& quat);

	CEquCoordinates centerCoords(void) const;

	void setCoords(const CEquCoordinates& coords);

	double scale(void) const { return m_scale; }

	void setScale(double scale);

	CEquCoordinates mapToCoords(const QPointF& pos) const;

	void addDataset(CSkyChartDataset* dataset);

private:
	// Viewport normal vector (look direction)
	// Z = +/-1 (celestial north/south pole)
	// X = +/-1 (spring/autumnal equinox)
	// Y = +/-1 (???)
	QQuaternion m_lastQ, m_currQ;
	bool m_rotating;
	QPoint m_startPos;
	double m_scale;
	int m_viewSize, m_width, m_height;
	QPointF m_offset;

	QVector3D project(const QPoint& xy) const;

	QList<CSkyChartDataset*> m_datasets;

signals:
	void viewChanged(void);

protected:
	void paintEvent(QPaintEvent* event) override;

	void resizeEvent(QResizeEvent* event) override;

	void mouseMoveEvent(QMouseEvent* event) override;

	void leaveEvent(QEvent* event) override;

	void mousePressEvent(QMouseEvent* event) override;

	void mouseReleaseEvent(QMouseEvent* event) override;

	void wheelEvent(QWheelEvent* event) override;
};