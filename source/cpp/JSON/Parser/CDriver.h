/*!
*  \file      CDriver.h
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

#include "CScanner.h"
#include "CObject.h"
#include "CLogicValue.h"
#include "CNullObject.h"
#include "CTextValue.h"
#include "CNumericValue.h"
#include "CArray.h"

namespace JSON::Parser
{
    class CLogger;

    /// Base class for drivers
    class CDriver
    {
    public:
        /// Preprocessing token
        using tToken = JSON::Scanner::CToken;

        /// Constructor
        CDriver() : m_object(nullptr) {}

        /// Destructor
        ~CDriver() { delete m_object; }

        // Objects
        // -------

        /// The function is called at the end of the input stream.
        /// 
        /// The function keep the object and the last token as
        /// the reference to the end of the file.
        void setContents(const tToken& tok, CObject* object);

        /// Create an object that holds a character string literal
        /// 
        /// \param tok reference to a position in the script
        /// \param str value
        /// \return new instance
        CTextValue* primitiveStringValue(const tToken& tok, const QString& str) {
            return new JSON::CTextValue(tok, str);
        }

        /// Create an object that holds a numeric literal
        /// 
        /// \param tok reference to a position in the script
        /// \param str value as a string
        /// \return new instance
        CNumericValue* primitiveNumericValue(const tToken& tok, const QString& str) {
            return new JSON::CNumericValue(tok, str);
        }

        /// Create an object that holds a logic literal
        /// 
        /// \param tok reference to a position in the script
        /// \param val value
        /// \return new instance
        CLogicValue* primitiveBooleanValue(const tToken& tok, bool val) {
            return new JSON::CLogicValue(tok, val);
        }

        /// Create an object that holds an ordered list of other objects
        /// 
        /// \param tok reference to a position in the script
        /// \return new instance, an empty list
        CArray* list(const tToken& tok) {
            return new JSON::CArray(tok);
        }

        /// Create an object that holds an associative list of other objects
        /// 
        /// \param tok reference to a position in the script
        /// \return new instance, an empty list
        CObject* map(const tToken& tok) {
            return new JSON::CObject(tok);
        }

        /// Create an object that represents a special 'null' object
        /// 
        /// \param tok reference to a position in the script
        /// \return new instance, an empty list
        CNullObject* null(const tToken& tok) {
            return new JSON::CNullObject(tok);
        }

        CObject* parse(QTextStream* stream, const QString& filePath, CLogger* logger);

    protected:
        tToken m_endToken;
        CObject* m_object;

        /// Initialization before parsing the input
        ///
        /// The function deletes the current (internal) object 
        /// and sets the m_object to nullptr.
        void beginParse();

        /// Finalization after parsing the input
        ///
        /// The function releases ownership of the object and
        /// returns pointer to the object. The m_object is set 
        /// to nullptr, so the object is not deleted in the
        /// destructor.
        ///
        CObject* endParse(bool success);
    };
}
