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
#include "CQuaternion.h"

class CProjection;
class CSkyChartDataset;

class CSkyChartView : public QWidget
{
	Q_OBJECT

public:
	CSkyChartView(QWidget* parent);

	~CSkyChartView() override;

	CEquCoordinates centerCoords(void) const { return fromRotationMatrix(m_rotMatrix); }

	void setCoords(const CEquCoordinates& coords);

	double scale(void) const { return m_scale; }

	void setScale(double scale);

	CEquCoordinates mapToCoords(const CPointd& pos) const;

	void addDataset(CSkyChartDataset* dataset);

	void setProjector(CProjection* projector);

	CProjection* projector(void) const { return m_projector; }

	/* Equatorial coordinates to rotation matrix */
	static CMatrix3d toRotationMatrix(const CEquCoordinates& coords);

	/* Rotation matrix to equatorial coordinates */
	static CEquCoordinates fromRotationMatrix(const CMatrix3d& rotMatrix);

private:
	// Viewport normal vector (look direction)
	// Z = +/-1 (celestial north/south pole)
	// X = +/-1 (spring/autumnal equinox)
	// Y = +/-1 (???)
	CQuaterniond m_lastQ;
	bool m_rotating;
	QPoint m_startPos;
	double m_scale;
	int m_viewSize, m_width, m_height;
	CPointd m_offset;
	CEquCoordinates m_centerCoords;
	CMatrix3d m_rotMatrix;

	CProjection* m_projector;

	CVector3d toXYZ(const QPoint& xy) const;

	CVector3d toXYZ(const CPointd& xy) const;

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