/*!
*  \file      CArray.h
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
    /// Ordered list of objects
    /// 
    /// The CArray class holds an ordered list of values of CNode type. The list items
    /// can be either primitive values or compound values.
    ///
    class CArray : public CNode
    {
    public:
        /// Default constructor
        CArray() {}

        /// Constructor
        /// 
        /// \param token position in the script
        explicit CArray(const tToken& token) : CNode(token) {}

        /// Append an item
        ///
        /// The methods inserts an item to the list after the last item.
        /// The container takes ownership of the item.
        /// \param item list item
        void append(CNode* item) { appendChildObject(item, QString()); }

        /// Prepend an item
        ///
        /// The methods inserts an item to the list before the first item.
        /// The container takes ownership of the item.
        /// \param item list item
        void prepend(CNode* item) { prependChildObject(item, QString()); }


        // Overridables:
        // -------------

        /// Node type
        tValueType valueType(void) const override { return tValueType::List; }

        /// Returns true if this is a "null" value
        bool isNull(void) const override { return false; }

        /// Get value as a list, returns NULL if the node is not a list.
        const CArray* toList(void) const override { return this; }
    };
}
