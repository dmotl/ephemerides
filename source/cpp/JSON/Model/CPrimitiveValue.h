/*!
*  \file      CPrimitiveValue.h
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

#include "CNode.h"

namespace JSON
{
    /// Primitive value (object)
    ///
    /// The CPrimitiveValue is a base class for objects that holds a primitive values:
    ///  - string literals (character strings)
    ///  - numerical literals (numbers)
    ///  - boolean literals (true or false)
    ///  - null value (a special 'null' value)
    ///
    class CPrimitiveValue : public CNode
    {
    public:
        /// Default constructor
        CPrimitiveValue() {}

        /// Constructor
        /// \param token position in the script
        explicit CPrimitiveValue(const tToken& token) : CNode(token) {}
    };
}
