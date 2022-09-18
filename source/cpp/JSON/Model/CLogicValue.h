/*!
*  \file      CLogicValue.h
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
    /// Logic value
    ///
    /// The CLogicValue class holds a value for a logic literal. It can be either "true" or "false".
    ///
    class CLogicValue : public CPrimitiveValue
    {
    public:
        /// Default constructor
        CLogicValue() : m_value(false) {}
            
        /// Constructor
        /// 
        /// \param token position in the script
        /// \param value truth value
        CLogicValue(const tToken& token, bool value) : CPrimitiveValue(token), m_value(value) {}

        /// To boolean value
        bool value(void) const { return m_value; }

        // Overridables:
        // -------------

        // Node type
        tValueType valueType(void) const override { return tValueType::Logic; }

        // Returns true if this is a "null" value
        bool isNull(void) const override { return false; }

        // Get logic value, returns specified defaultValue, if the node is not of a Logic type.
        bool toBool(bool* ok = NULL) const override { if (ok) *ok = true; return m_value; }

        // Get integer value, ok=true on success, false on failure. In case of failure, the function returns zero.
        int toInt(bool* ok = NULL) const override { if (ok) *ok = true; return m_value; }

        // Get numeric value, ok=true on success, false on failure. In case of failure, the function returns zero.
        double toDouble(bool* ok = NULL) const override { if (ok) *ok = true; return m_value; }

        // Get value as a string
        QString toString(bool* ok = NULL) const override { if (ok) *ok = true; return (m_value ? QStringLiteral("true") : QStringLiteral("false")); }

    private:
        /// Stored value
        bool m_value;
    };
}
