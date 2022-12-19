/*!
*  \file      CChartDockWidget.h
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
* \brief The "Sky chart" tool
* 
* The CChartDockWidget class implements a dock widget that shows a sky chart 
* with bright stars, constellation lines and planets. The widget is used
* to give an overview where a variable star is found in the context of
* bright stars and constellations.
* 
* The time and celestial coordinates are specified in the shared data. The chart
* has constant view field. 
*/
class CChartDockWidget : public CMainDockWidget
{
	Q_OBJECT

public:
	/*!
	* \brief Constructor
	* \param data shared data container
	* \param parent parent widget
	*/
	CChartDockWidget(CSharedData* data, CMainWindow* mainWnd, QWidget* parent);

	static constexpr const char* type_id = "skychart";

	static constexpr const char* caption = QT_TR_NOOP("Sky chart");


private:
	// Shared data
	CSharedData* m_sharedData;

	// Chart widget
	QWidget* m_chartView;
};
