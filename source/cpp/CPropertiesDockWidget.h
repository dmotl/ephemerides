#pragma once

#include <QtWidgets>

class CMainWindow;

class CPropertiesDockWidget : public QDockWidget
{
	Q_OBJECT

public:
	CPropertiesDockWidget(CMainWindow* mainWnd, QWidget* parent);

private:
	QWidget* m_treeView;
};
