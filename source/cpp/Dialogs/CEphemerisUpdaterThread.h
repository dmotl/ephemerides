/*!
*  \file      CEphemerisUpdaterThread.h
*  \author    David Motl
*  \date      2022-12-19
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

#include <QtCore>

class CEphemerisUpdater;

/*!
* \brief Catalog loader (work thread)
*
* The CEphemerisUpdaterThread implements a work thread
* that is reposponsible for loading known catalogs
* at application start.
*
*/
class CEphemerisUpdaterThread :public QThread
{
public:
	CEphemerisUpdaterThread(CEphemerisUpdater* process, QObject* parent) : QThread(parent), m_process(process) {}

protected:
	friend class CCatalogLoaderDialog;

	CEphemerisUpdater* m_process;

	virtual void run();
};
