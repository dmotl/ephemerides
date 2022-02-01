#include "CStarEphemerisTab.h"

// Constructor
CStarEphemerisTab::CStarEphemerisTab(CMainWindow* mainWnd, QWidget* parent) : QWidget(parent), m_toolBar(NULL)
{
	setupUi(this);

	createToolBar();
}

void CStarEphemerisTab::createToolBar()
{
	m_toolBar = new QToolBar(this);
	static_cast<QVBoxLayout*>(mainFrame->layout())->insertWidget(0, m_toolBar);
	m_toolBar->setFloatable(false);
	m_toolBar->setMovable(false);

	m_updateAction = m_toolBar->addAction(tr("Update"));
	m_toolBar->addSeparator();
	m_sortAction = m_toolBar->addAction(tr("Sort"));
	m_deleteAction = m_toolBar->addAction(tr("Delete"));
	m_findAction = m_toolBar->addAction(tr("Find"));
	m_toolBar->addSeparator();
	m_printAction = m_toolBar->addAction(tr("Print"));
	m_exportAction = m_toolBar->addAction(tr("Export"));
	m_copyAction = m_toolBar->addAction(tr("Copy"));
	m_toolBar->addSeparator();
	m_sunAction = m_toolBar->addAction(tr("Sun"));
	m_moonAction = m_toolBar->addAction(tr("Moon"));
	m_chartAction = m_toolBar->addAction(tr("Chart"));
	m_toolBar->addSeparator();
	m_setupAction = m_toolBar->addAction(tr("Setup"));
	m_toolBar->addSeparator();
	m_helpAction = m_toolBar->addAction(tr("Help"));
}
