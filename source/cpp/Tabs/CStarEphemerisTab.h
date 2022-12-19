/*!
*  \file      CStarEphemerisTab.h
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
#pragma once

#include "CMainTabWidget.h"

#include "ui_CStarEphemerisTab.h"

/*!
* \brief The "Star ephemeris" tab
*
* The CStarEphemerisTab class implements one of the main sections of the
* application. The widgets is used to show ephemeris of a selected
* variable star for a range between two dates.
*/
class CStarEphemerisTab : public CMainTabWidget, private Ui::CStarEphemerisTab
{
	Q_OBJECT

public:
	/*!
	* \brief Constructor
	* \param mainWnd main window
	* \param parent parent widget
	*/
	CStarEphemerisTab(CSharedData* sharedData, CMainWindow* mainWnd, QWidget* parent);

	static constexpr const char* type_id = "vstar";

	static constexpr const char* caption = QT_TR_NOOP("Variable star ephemerides");

	void loadState(const QJsonObject& obj) override;

	void saveState(QJsonObject& obj) override;

private:
	QString m_catalogName, m_constellationName, m_variableName;

	QAction* m_updateAction, * m_sortAction, * m_deleteAction, * m_findAction;
	QAction* m_printAction, * m_exportAction, * m_copyAction;

	void addCustomToolBarActions();

	void updateCaption();
};
