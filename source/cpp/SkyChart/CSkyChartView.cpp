#include "CSkyChartView.h"

#include "CEquCoordinates.h"

CSkyChartView::CSkyChartView(QWidget* parent) : QWidget(parent), m_viewNorm(1, QVector3D(0, 0, 1)), m_scale(1.0), m_viewSize(0)
{ 
	setMouseTracking(true); 
}

void CSkyChartView::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setPen(QPen(Qt::white));
	painter.fillRect(event->rect(), Qt::black);

	// Equatorial grid
	for (int i = -8; i <= 8; i++) {
		double dec = CDeclination::fromDegrees(i * 10).radians();
		for (int j = 0; j < 24; j++) {
			double ra = CRightAscension::fromHours(j).radians();
			QVector3D equ3d(cos(ra) * cos(dec), sin(ra) * cos(dec), sin(dec));
			QVector3D r3d = m_viewNorm.rotatedVector(equ3d);
			QVector2D r2d = r3d.normalized().toVector2D();
			painter.drawPoint(r2d.toPointF() * 0.5 * m_scale * m_viewSize + m_offset);
		}
	}
}

void CSkyChartView::resizeEvent(QResizeEvent* event)
{
	QSize sz = size();
	int size = qMin(sz.width(), sz.height());
	if (size != m_viewSize) {
		m_viewSize = size;
		m_offset = 0.5 * QPointF(sz.width(), sz.height());
		update();
	}
	QWidget::resizeEvent(event);
}

void CSkyChartView::mouseMoveEvent(QMouseEvent* event)
{
	QWidget::mouseMoveEvent(event);
}

void CSkyChartView::leaveEvent(QEvent* event)
{
	QWidget::leaveEvent(event);
}

void CSkyChartView::mousePressEvent(QMouseEvent* event)
{
	QWidget::mousePressEvent(event);
}

void CSkyChartView::wheelEvent(QWheelEvent* event)
{
	QWidget::wheelEvent(event);
}
