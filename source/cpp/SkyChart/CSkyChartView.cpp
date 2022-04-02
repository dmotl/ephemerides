#include "CSkyChartView.h"

#include "CEquCoordinates.h"

QVector3D CSkyChartView::project(const QPoint& xy) const
{
	double res = m_viewSize - 1;

	// map to -1 to 1
	double x = (2 * xy.x() - m_width - 1) / res;
	double y = (2 * xy.y() - m_height - 1) / res;

	double z;
	if (x * x + y * y <= 0.5)
		z = sqrt(1 - (x * x + y * y));
	else
		z = 0.5 / sqrt(x * x + y * y);

	return QVector3D(x, y, z);
}

CSkyChartView::CSkyChartView(QWidget* parent) : QWidget(parent), m_lastQ(1, QVector3D(0, 0, 1)), 
m_currQ(QQuaternion()), m_scale(1.0), m_viewSize(0), m_rotating(false), m_width(0), m_height(0)
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
			QVector3D r3d = (m_currQ * m_lastQ).rotatedVector(equ3d).normalized();
			if (r3d.z() >= 0)
				painter.drawPoint(r3d.toPointF() * 0.5 * m_scale * m_viewSize + m_offset);
		}
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
		m_offset = 0.5 * QPointF(m_width, m_height);
		update();
	}
	QWidget::resizeEvent(event);
}

void CSkyChartView::mouseMoveEvent(QMouseEvent* event)
{
	if (m_rotating) {
		QVector3D a = project(m_startPos);
		QVector3D b = project(event->pos());
		m_currQ = QQuaternion::rotationTo(a, b);
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
		m_lastQ = m_currQ * m_lastQ;
		m_currQ = QQuaternion();
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
	event->



	QWidget::wheelEvent(event);
}

void CSkyChartView::setViewQuat(const QQuaternion& quat)
{
	if (quat != m_currQ && !m_rotating) {
		m_currQ = quat;
		update();
	}
}

void CSkyChartView::setScale(double scale)
{
	if (scale != m_scale) {
		m_scale = scale;
		update();
	}
}
