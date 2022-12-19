/*!
*  \file      CMainDockWidget.cpp
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
#include "CMainDockWidget.h"

#include "CMainWindow.h"

//
// Constructor
//
CMainDockWidget::CMainDockWidget(CSharedData* sharedData, CMainWindow* mainWnd, QWidget* parent) : QDockWidget(parent), m_mainWnd(mainWnd), m_sharedData(sharedData)
{
	setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
}


//
// Register a tab widget
//
void CMainDockWidget::registerDockWidget(const char* typeId)
{
	assert(typeId != nullptr && m_mainWnd != nullptr);
	m_uniqueId = m_mainWnd->registerDockWidget(typeId, this);
}


//
// Set tab caption
//
void CMainDockWidget::setText(const QString& text)
{
	if (m_text != text) {
		m_text = text;
		emit captionChanged();
	}
}
