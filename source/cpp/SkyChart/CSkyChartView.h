#pragma once

#include <QtWidgets>

class CSkyChartView : public QWidget
{
public:
	CSkyChartView(QWidget* parent);

private:
	// Viewport normal vector (look direction)
	// Z = +/-1 (celestial north/south pole)
	// X = +/-1 (spring/autumnal equinox)
	// Y = +/-1 (???)
	QQuaternion m_viewNorm;
	double m_scale;
	int m_viewSize;
	QPointF m_offset;

protected:
	void paintEvent(QPaintEvent* event) override;

	void resizeEvent(QResizeEvent* event) override;

	void mouseMoveEvent(QMouseEvent* event) override;

	void leaveEvent(QEvent* event) override;

	void mousePressEvent(QMouseEvent* event) override;

	void wheelEvent(QWheelEvent* event) override;
};