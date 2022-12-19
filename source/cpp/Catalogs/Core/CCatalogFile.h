/*!
*  \file      CCatalogFile.h
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

#include "CCatalog.h"

/*!
* \brief Common routines for catalogs stored in a file system
*
* The CCatalogFile class provides implements some basic CCatalog's
* virtual methods and adds shared routines for catalogs that
* are stored as regular files. 
*/
class CCatalogFile : public CCatalog
{
public:
	explicit CCatalogFile(const QString& filePath) : m_filePath(filePath) {}

	const QString& filePath(void) const { return m_filePath; }

	QString getSignature() const noexcept override;

protected:
	QString m_filePath;
};
