/*!
*  \file      CError.cpp
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

namespace JSON::Utils
{
    /// \brief Error event descriptor
    ///
    /// This is a base class for event descriptors. Each error type is implemented
    /// as a descendant class.
    /// 
    class CError
    {
    public:
        /// Constructor
        CError(void) {}

        /// Destructor
        virtual ~CError() {}

        /// Get error message as a string. The string shall comprise of a position
        /// and error message. This is presented to the user, so it must be meaningful.
        virtual QString toString() const = 0;
    };
}
