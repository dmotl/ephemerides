#include "CPropertiesDockWidget.h"

CPropertiesDockWidget::CPropertiesDockWidget(CMainWindow* mainWnd, QWidget* parent)
{
	m_treeView = new QTreeView(this);
	setWidget(m_treeView);
}
