/*!
*  \file      CMainTabWidget.cpp
*  \author    David Motl
*  \date      2022-05-11
*
*  \copyright
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted
*  provided that the following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions
*      and the following disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list
*      of conditions and the following disclaimer in the documentation and/or other materials provided
*      with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of its contributors may be used
*      to endorse or promote products derived from this software without specific prior written
*      permission.
*/
#include "CMainTabWidget.h"

#include "CMainWindow.h"

//
// Constructor
//
CMainTabWidget::CMainTabWidget(CSharedData* sharedData, CMainWindow* mainWnd, QWidget* parent) : QWidget(parent), m_mainWnd(mainWnd), m_sharedData(sharedData)
{
	setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
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
