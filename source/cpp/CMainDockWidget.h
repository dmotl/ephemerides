/*!
*  \file      CMainDockWidget.h
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

class CMainDockWidget : public QDockWidget, public CConfigSupport
{
	Q_OBJECT

public:
	/*!
	* \brief Constructor
	* \param mainWnd main window
	* \param parent parent widget
	*/
	CMainDockWidget(CSharedData* data, CMainWindow* mainWnd, QWidget* parent);

	/*!
	* \brief Unique window identifier
	*/
	QString uniqueId(void) const { return m_uniqueId; }

	/*!
	* \brief Restore last state
	*
	* The function loads the state of a tab from the XML tree
	*/
	virtual void loadState(const QDomElement& xml) {}

	/*!
	* \brief Save last state
	*
	* The function updates content of the given XML element
	* with the current state of the tab.
	*/
	virtual void saveState(QDomElement& xml) {}

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
	/// Window caption
	QString m_text;

	// Unique identifier
	QString m_uniqueId;

	/// Main window
	CMainWindow* m_mainWnd;

	/// Shared data
	CSharedData* m_sharedData;

	// Get pointer to a dock widget
	void registerDockWidget(const char* typeId);
};