/*!
*  \file      CNightlyEphemeris.cpp
*  \author    David Motl
*  \date      2022-01-31
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
#include "CNightlyEphemerisTab.h"

//
// Constructor
//
CNightlyEphemerisTab::CNightlyEphemerisTab(CMainWindow* mainWnd, QWidget* parent) : QWidget(parent), m_toolBar(NULL)
{
	setupUi(this);

	createToolBar();
}


//
// Create toolbar and actions
//
void CNightlyEphemerisTab::createToolBar()
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
