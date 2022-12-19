/*!
*  \file      CCatalogFile.cpp
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
#include "CCatalogFile.h"

#include <filesystem>
#include <sstream>

QString CCatalogFile::getSignature() const noexcept
{
	if (!m_filePath.isEmpty()) {
		try {
			std::filesystem::path path(m_filePath.toStdWString());
			std::ostringstream oss;
			oss << std::filesystem::file_size(path)
				<< "," 
				<< std::filesystem::last_write_time(path).time_since_epoch().count();
			return QString::fromStdString(oss.str());
		}
		catch (std::filesystem::filesystem_error&) {
			return QString();
		}
	}
	return QString();
}
