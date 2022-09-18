/*!
*  \file      CObject.h
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
    /// JSON object (associative list of objects)
    ///
    /// The CObject class holds an associative list of objects. The keys are character strings, the values
    /// are of CNode type, so they can be either primitive values or compounds.
    ///
    class CObject : public CNode
    {
    public:
        /// Default constructor
        ///
        /// The constructor creates an empty object
        CObject() {}

        /// Constructor
        /// \param token position in the script
        CObject(const tToken& token) : CNode(token) {}

        /// Insert or update an item.
        ///
        /// The container takes owership of the given value. It is possible to store
        /// multiple values associated with one key, the order of the values is undefined.
        /// \param key key
        /// \param value value
        void insert(const QString& key, CNode* value) { appendChildObject(value, key); }

        // Overridables:
        // -------------

        /// Node type
        tValueType valueType(void) const override { return tValueType::Map; }

        /// Returns true if this is a "null" value
        bool isNull(void) const override { return false; }

        /// Get value as a map, returns NULL if the node is not a map.
        const CObject* toMap(void) const override { return this; }

        /// Get first value by key (this node should be the map node)
        ///
        /// The function returns pointer to the first item in the list. The function returns
        /// a pointer to the internal object, the caller should not modify or free the object.
        /// \param key key
        const CNode* firstValue(const QString& key) const;

        /// Get first value by key (this node should be the map node)
        ///
        /// Same as firstValue(const QString&)
        /// \param key key
        const CNode* operator[](const QString& key) const { return firstValue(key); }

        /// Returns a true if the list contains a value for a specified key
        ///
        /// The function returns true if there is at least one item associated
        /// with specified key
        bool contains(const QString& key) const;

        /// Get list of keys (does not remove duplicates)
        ///
        /// The function returns a list of keywords. The keywords are sorted in the
        /// order of appearance. If a key is used more than once, the returned list
        /// contains duplicate entries.
        QStringList keys(void) const;

        /// Get list of unique keys
        ///
        /// The function returns a sorted list of unique keyword. The keys are sorted
        /// alphabetically. If a key is used more than once, the returned list
        /// contains a single entry only.
        QStringList uniqueKeys(void) const;

        /// Get list of values for a given key
        ///
        /// The function returns a list of values that are associated with a given key.
        /// The values are sorted in order of appearance.
        QList<const CNode*> values(const QString& key) const;
    };
}
