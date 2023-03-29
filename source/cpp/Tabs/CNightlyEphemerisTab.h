/*!
*  \file      CNightlyEphemeris.h
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

#include <QtWidgets>

#include "ui_CNightlyEphemerisTab.h"

#include "CMainTabWidget.h"
#include "CConstellation.h"

class CMainApp;
class CMainWindow;
class CVarEphemeris;
class CEVNightlyEphemerisModel;
class CCatalogSelectionModel;
class CCatalogList;


/*!
* \brief The "Nightly ephemeris" tab
* 
* The CNightlyEphemerisTab class implements one of the main sections of the 
* application. The widgets is used to show ephemeris of variable stars
* for a selected night.
*/
class CNightlyEphemerisTab : public CMainTabWidget, private Ui::CNightlyEphemerisTab
{
	Q_OBJECT

public:
	/*!
	* \brief Constructor
	* \param mainWnd main window
	* \param parent parent widget
	*/
	CNightlyEphemerisTab(CMainApp* app, CSharedData* sharedData, CMainWindow* mainWnd, QWidget* parent);

	~CNightlyEphemerisTab() override;

	static constexpr const char* type_id = "nightly";

	static constexpr const char* caption = QT_TR_NOOP("Nightly ephemerides");

	void loadState(const QJsonObject& obj) override;

	void saveState(QJsonObject& obj) override;

private:
	bool m_initialized;
	QList<CConstellation> m_constellationList;
	QStringList m_varTypesList;
	QMap<QString, bool> m_checkedCatalogs;

	CVarEphemeris *m_data;
	CEVNightlyEphemerisModel* m_model;
	CCatalogSelectionModel* m_catalogSelectionModel;

	QAction* m_updateAction, * m_sortAction, * m_deleteAction, * m_findAction;
	QAction* m_printAction, * m_exportAction, * m_copyAction;

	void addCustomToolBarActions();

	void updateCaption();

	void updateCatalogsList();

protected slots:
	void onUpdateAction();

	void onCatalogSelectionDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight, const QList<int>& roles = QList<int>());
};
