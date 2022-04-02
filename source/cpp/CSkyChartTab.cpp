#include "CSkyChartTab.h"

#include "CSkyChartView.h"

CSkyChartTab::CSkyChartTab(CMainWindow* mainWnd, QWidget* parent) : CMainTabWidget(mainWnd, parent),
m_toolBar(NULL), m_toolsBtn(NULL), m_toolsMenu(NULL), m_toolsActionMapper(NULL)
{
	setupUi(this);
	setText(tr("Sky chart"));
	layout()->setContentsMargins(0, 0, 0, 0);
	toolBox->layout()->setContentsMargins(9, 9, 9, 9);

	m_toolsActionMapper = new QSignalMapper(this);
	connect(m_toolsActionMapper, &QSignalMapper::mappedInt, this, &CSkyChartTab::onToolsAction);

	createToolBar();

	on_view_viewChanged();
}


//
// Create toolbar and actions
//
void CSkyChartTab::createToolBar()
{
	m_toolBar = new QToolBar(this);
	static_cast<QVBoxLayout*>(mainFrame->layout())->insertWidget(0, m_toolBar);
	m_toolBar->setFloatable(false);
	m_toolBar->setMovable(false);

	m_toolsMenu = new QMenu(this);

	m_toolsBtn = new QToolButton(this);
	m_toolsBtn->setText(tr("Tools"));
	m_toolsBtn->setPopupMode(QToolButton::InstantPopup);
	m_toolsBtn->setMenu(m_toolsMenu);
	m_toolsAction = m_toolBar->addWidget(m_toolsBtn);

	m_helpAction = m_toolsMenu->addAction(tr("Help"));
}


//
// Handle toolbar actions
//
void CSkyChartTab::onToolsAction(int dockWidgetId)
{

}


void CSkyChartTab::on_view_viewChanged(void)
{
	QQuaternion q = view->viewQuat();

	qSSpinBox->blockSignals(true);
	qSSpinBox->setValue(q.scalar());
	qSSpinBox->blockSignals(false);

	qXSpinBox->blockSignals(true);
	qXSpinBox->setValue(q.x());
	qXSpinBox->blockSignals(false);

	qYSpinBox->blockSignals(true);
	qYSpinBox->setValue(q.y());
	qYSpinBox->blockSignals(false);

	qZSpinBox->blockSignals(true);
	qZSpinBox->setValue(q.z());
	qZSpinBox->blockSignals(false);
}

void CSkyChartTab::on_qSSpinBox_valueChanged(double value)
{
	QQuaternion q = view->viewQuat();
	q.setScalar(value);
	view->setViewQuat(q);
}

void CSkyChartTab::on_qXSpinBox_valueChanged(double value)
{
	QQuaternion q = view->viewQuat();
	q.setX(value);
	view->setViewQuat(q);
}

void CSkyChartTab::on_qYSpinBox_valueChanged(double value)
{
	QQuaternion q = view->viewQuat();
	q.setY(value);
	view->setViewQuat(q);
}

void CSkyChartTab::on_qZSpinBox_valueChanged(double value)
{
	QQuaternion q = view->viewQuat();
	q.setZ(value);
	view->setViewQuat(q);
}
