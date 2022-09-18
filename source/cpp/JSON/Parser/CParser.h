/*!
*  \file      CParser.h
*  \author    David Motl
*  \date      2022-09-18
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

namespace JSON
{
    class CObject;
}

namespace JSON::Parser
{
    class CLogger;

    /// JSON parser (public interface)
    ///
    /// The CParser parser provides a public interface for parsing the JSON objects.
    /// The input can be a string or a file.
    ///
    class CParser
    {
        /// Default constructor
        CParser() {}

        /// Parse a string
        ///
        /// The function creates a JSON object from a given string.
        /// 
        /// The function returns a pointer to a new object. The caller has
        /// to delete the object when it is no longer needed.
        /// 
        /// \param string input string
        /// \param logger error handling object
        /// \return pointer to a new object or nullptr on failure.
        CObject* parseFromString(const QString& string, CLogger* logger = nullptr);

        /// Parse content of a file
        ///
        /// The function creates a JSON object from content of a file
        /// specified by its path.
        /// 
        /// The function returns a pointer to a new object. The caller has
        /// to delete the object when it is no longer needed.
        /// 
        /// \param filePath path to the source file
        /// \param logger error handling object
        /// \return pointer to a new object or nullptr on failure.
        CObject* parseFromFile(const QString& filePath, CLogger* logger = nullptr);
    };
}
