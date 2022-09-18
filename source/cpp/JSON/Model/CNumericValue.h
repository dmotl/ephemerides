/*!
*  \file      CNumericValue.h
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
    /// Numeric value
    ///
    /// The CNumericValue class holds a value of a numeric literal. It can
    /// represent either an integral or a decimal number. The value is stored as a string,
    /// so the original precision is preserved.
    ///
    class CNumericValue : public CPrimitiveValue
    {
    public:
        /// Default constructor
        CNumericValue() {}

        /// Constructor
        /// \param token position in the script
        /// \param str value
        CNumericValue(const tToken& token, const QString& str) : CPrimitiveValue(token), m_str(str) {}

        /// Stored value
        const QString& value(void) const { return m_str; }

        // Overridables:
        // -------------

        // Node type
        tValueType valueType(void) const override { return tValueType::Numeric; }

        // Returns true if this is a "null" value
        bool isNull(void) const override { return false; }

        // Get logic value, returns specified defaultValue, if the node is not of a Logic type.
        bool toBool(bool* ok = NULL) const override;

        // Get integer value, ok=true on success, false on failure. In case of failure, the function returns zero.
        int toInt(bool* ok = NULL) const override;

        // Get numeric value, ok=true on success, false on failure. In case of failure, the function returns zero.
        double toDouble(bool* ok = NULL) const override;

        // Get value as a string
        QString toString(bool* ok = NULL) const override { if (ok) *ok = true; return m_str; }

    private:
        /// Value as a string
        QString m_str;
    };
}
