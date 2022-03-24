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

#include <QtWidgets>

class CMainWindow;

/*!
* \brief The base class for main tabs
*
* The CMainTabWidget class implements functionality that is shared 
* between other main window tabs.
*/
class CMainTabWidget : public QWidget
{
	Q_OBJECT

public:
	/*!
	* \brief Constructor
	* \param mainWnd main window
	* \param parent parent widget
	*/
	CMainTabWidget(CMainWindow* mainWnd, QWidget* parent);

	/*!
	* \brief Tab caption
	*/
	QString text(void) const { return m_text; }

	/*!
	 * \brief Entring this tab
	 * 
	 * The function is called when the tab is going to
	 * be shown.
	 */
	virtual void onTabEnter(CMainTabWidget* previousTab) {}

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
	enum tDockWidgetId
	{
		SUN_DOCK_WIDGET,
		MOON_DOCK_WIDGET,
		SKY_CHART_DOCK_WIDGET,
		JD_CONVERTER_DOCK_WIDGET,
		HELIOC_CORRECTION_DOCK_WIDGET,
		AIR_MASS_DOCK_WIDGET
	};

	QString m_text;

	/// Main window
	CMainWindow* m_mainWnd;

	// Get pointer to a dock widget
	QDockWidget* dockWidget(tDockWidgetId id) const;
};
