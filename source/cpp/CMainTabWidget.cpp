#include "CMainTabWidget.h"

#include "CMainWindow.h"

//
// Constructor
//
CMainTabWidget::CMainTabWidget(CMainWindow* mainWnd, QWidget* parent) : QWidget(parent), m_mainWnd(mainWnd)
{

}


//
// Set tab caption
//
void CMainTabWidget::setText(const QString& text) 
{ 
	if (m_text != text) {
		m_text = text;
		emit captionChanged();
	}
}


//
// Get pointer to a dock widget
//
QDockWidget* CMainTabWidget::dockWidget(tDockWidgetId id) const
{
	assert(m_mainWnd != NULL);

	switch (id)
	{
	case SUN_DOCK_WIDGET:
		return m_mainWnd->m_sunDockWidget;
	case MOON_DOCK_WIDGET:
		return m_mainWnd->m_moonDockWidget;
	case SKY_CHART_DOCK_WIDGET:
		return m_mainWnd->m_chartDockWidget;
	case JD_CONVERTER_DOCK_WIDGET:
		return m_mainWnd->m_julianDateDockWidget;
	case HELIOC_CORRECTION_DOCK_WIDGET:
		return m_mainWnd->m_heliocentricCorrectionDockWidget;
	case AIR_MASS_DOCK_WIDGET:
		return m_mainWnd->m_airMassDockWidget;
	default:
		return NULL;
	}
}
