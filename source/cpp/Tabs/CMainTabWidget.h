/*!
*  \file      CMainTabWidget.h
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

#include "CConfigSupport.h"

#include <QtWidgets>

class CSharedData;
class CMainWindow;
class CMainDockWidget;

/*!
* \brief The base class for main tabs
*
* The CMainTabWidget class implements functionality that is shared 
* between other main window tabs.
*/
class CMainTabWidget : public QWidget, public CConfigSupport
{
	Q_OBJECT

public:
	/*!
	* \brief Constructor
	* \param mainWnd main window
	* \param parent parent widget
	*/
	CMainTabWidget(CSharedData* data, CMainWindow* mainWnd, QWidget* parent);

	/*!
	* \brief Unique window identifier 
	*/
	QString uniqueId(void) const { return m_uniqueId; }

	/*!
	 * \brief Entring this tab
	 * 
	 * The function is called when the tab is going to
	 * be shown.
	 */
	virtual void onTabEnter(CMainTabWidget* previousTab);

	/*!
	* \brief Restore last state
	* 
	* The function loads the state of a tab from the XML tree
	*/
	virtual void loadState(const QJsonObject& obj) {}

	/*!
	* \brief Save last state
	* 
	* The function updates content of the given XML element
	* with the current state of the tab.
	*/
	virtual void saveState(QJsonObject& obj) {}

public slots:
	/*!
	* \brief Set tab caption
	* \param caption
	*/
	void setText(const QString& text);

signals:
	/*!
	 * \brief The signal gets emitted when the caption has been changed
	 */
	void captionChanged();

protected:
	// Unique identifier
	QString m_uniqueId;

	/// Tab caption
	QString m_text;

	/// Main window
	CMainWindow* m_mainWnd;

	/// Shared data
	CSharedData* m_sharedData;

	// Signal mapper for toolbox actions
	QSignalMapper* m_toolsActionMapper;

	// Maps dock type id to toolbox actions
	QMap<QString, QAction*> m_toolsActionList;

	QAction* m_toolsAction, * m_setupAction, * m_helpAction;

	QToolBar* m_toolBar;

	QMenu* m_toolsMenu;

	QToolButton* m_toolsBtn;

	// Get pointer to a dock widget
	CMainDockWidget* dockWidget(const char *typeId) const;
	CMainDockWidget* dockWidget(const QString& typeId) const;

	// Register a tab widget
	void registerTabWidget(const char* typeId);

	// Create popup menu for the "Tools" button
	void createToolsMenu(void);

	// Create a toolbar
	void createToolBar(QWidget* mainFrame);

protected slots:
	// Toolbox actions
	void onToolsAction(const QString& dockTypeId);
};
