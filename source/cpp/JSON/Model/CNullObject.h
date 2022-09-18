/*!
*  \file      CNullObject.h
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

#include "CPrimitiveValue.h"

namespace JSON
{
    /// The 'null' object
    ///
    /// The CNullObject class represents the special 'null' object. This is used as a placeholder
    /// for default values.
    ///
    class CNullObject : public CPrimitiveValue
    {
    public:
        /// Default constructor
        CNullObject() {}

        /// Constructor
        /// \param token position in the script
        explicit CNullObject(const tToken& token) : CPrimitiveValue(token) {}

        // Overridables:
        // -------------

        // Node type
        tValueType valueType(void) const override { return tValueType::Null; }

        // Returns true if this is a "null" value
        bool isNull(void) const override { return true; }

        // Get logic value, returns specified defaultValue, if the node is not of a Logic type.
        bool toBool(bool* ok = NULL) const override { if (ok) *ok = true; return false; }

        // Get integer value, ok=true on success, false on failure. In case of failure, the function returns zero.
        int toInt(bool* ok = NULL) const override { if (ok) *ok = true; return 0; }

        // Get numeric value, ok=true on success, false on failure. In case of failure, the function returns zero.
        double toDouble(bool* ok = NULL) const override { if (ok) *ok = true; return 0; }

        // Get value as a string
        QString toString(bool* ok = NULL) const override { if (ok) *ok = true; return QString(); }
    };
}
