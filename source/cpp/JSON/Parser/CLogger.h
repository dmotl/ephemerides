/*!
*  \file      CLogger.h
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
    /// Error handling
    ///
    /// The CLogger class is a base class that receives errors
    /// generated during parsing the JSON input.
    /// 
    /// The log method is virtual and the default implementation
    /// does nothing. You should override the method and provide
    /// an instance of your class to the parsing routines.
    ///
    class CLogger
    {
    public:
        /// Default constructor
        CLogger() {}

        /// Error handling
        ///
        /// The function handles the error. This is a virtual function.
        /// The default implementation does nothing.
        ///
        /// 
        /// \param e error
        virtual void log(const JSON::Utils::CError& e) { (void)e; }
    };
}
