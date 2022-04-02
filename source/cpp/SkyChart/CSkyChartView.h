#pragma once

#include <QtWidgets>

#include "CEquCoordinates.h"

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