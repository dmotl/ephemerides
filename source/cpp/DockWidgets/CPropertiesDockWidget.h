/*!
*  \file      CPropertiesDockWidget.h
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

#include "CMainDockWidget.h"

/*!
* \brief The "Properties" tool
*
* The CPropertiesDockWidget class implements a dock widget that shows 
* details for a selected row it the table of ephemeris.
* 
* The ephemeris is specified in the shared data.
*/
class CPropertiesDockWidget : public CMainDockWidget
{
	Q_OBJECT

public:
	/*!
	* \brief Constructor
	* 
	* \param data shared data container
	* \param parent parent widget
	*/
	CPropertiesDockWidget(CSharedData* data, CMainWindow* mainWnd, QWidget* parent);

	static constexpr const char* type_id = "properties";

	static constexpr const char* caption = QT_TR_NOOP("Properties");

private:
	// Shared data
	CSharedData* m_sharedData;

	// Tree view
	QWidget* m_treeView;
};
