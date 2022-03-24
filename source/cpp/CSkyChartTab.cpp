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
