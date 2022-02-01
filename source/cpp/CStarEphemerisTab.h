#pragma once

#include <QtWidgets>

#include "ui_CStarEphemerisTab.h"

class CMainWindow;

class CStarEphemerisTab : public QWidget, private Ui::CStarEphemerisTab
{
	Q_OBJECT

public:
	// Constructor
	CStarEphemerisTab(CMainWindow* mainWnd, QWidget* parent);

	// Tab caption
	static QString caption(void) { return tr("Star ephemeris"); }

private:
	QToolBar* m_toolBar;

	QAction* m_updateAction, * m_sortAction, * m_deleteAction, * m_findAction;
	QAction* m_printAction, * m_exportAction, * m_copyAction;
	QAction* m_sunAction, * m_moonAction, * m_chartAction;
	QAction* m_setupAction, * m_helpAction;

	void createToolBar();
};
