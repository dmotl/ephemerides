/*!
*  \file      CNode.h
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

namespace JSON
{
    class CArray;
    class CObject;

    /// Type of a value
    enum class tValueType
    {
        /// 'Null' value
        Null,

        /// Text value
        Text,

        /// Numeric value
        Numeric,

        /// Boolean value
        Logic,

        /// Map (associative list)
        Map,

        /// List (ordered list)
        List,

        /// Function-like object
        Function
    };

    /// Node
    ///
    /// The CNode class provides an common interface for all primitive values (string, numeric and
    /// logic literals, the null object) and compounds (lists and objects) in the JSON tree.
    ///
    /// The values nodes constitutes a hierarchical structure. Each node holds a list
    /// of child nodes. The child nodes can be accesses sequentially, using firstChildNode()
    /// and nextSiblingNode() methods.
    /// 
    class CNode
    {
        /// Disable copy constructor and assignment operator
        CNode(const CNode&) = delete;
        CNode& operator=(const CNode&) = delete;

    public:
        /// Preprocessing token
        using tToken = JSON::Scanner::CToken;

        /// Default constructor
        ///
        /// The constructor creates an empty node
        CNode() : m_parent(NULL), m_nextSibling(NULL), m_previousSibling(NULL), m_firstChild(NULL), m_lastChild(NULL) {}

        /// Constructor
        /// \param token token that generated the node
        explicit CNode(const tToken& token) : m_token(token), m_parent(NULL), m_previousSibling(NULL), m_nextSibling(NULL), m_firstChild(NULL), m_lastChild(NULL) {}

        /// Destructor
        virtual ~CNode();

        /// Position of a token
        const tToken& token(void) const { return m_token; }

        /// Parent node
        CNode* parent() const { return m_parent; }

        /// First child node
        CNode* firstChildNode() const { return m_firstChild; }

        /// Next sibling node
        CNode* nextSiblingNode() const { return m_nextSibling; }

        /// Next sibling node
        CNode* previousSiblingNode() const { return m_previousSibling; }

        /// Value type
        virtual tValueType valueType(void) const = 0;

        /// Returns true if the list is empty
        bool isEmpty(void) const { return firstChildNode() == nullptr; }

        /// Remove a node (including its all child nodes) and releases the allocated
        /// memory. Please note, that the pointer is not longer valid after calling this function.
        /// The specified node must be a direct member of this node.
        /// \param node node to be removed
        void removeChildNode(CNode* node) { delete takeChildNode(node); }

        /// Remove a node (including its all child nodes) without releasing the memory.
        /// After calling this function, the pointer refers to a "free" node, the caller is responsible
        /// to insert it somewhere or delete it. The specified node must be a direct member of this node.
        /// The function returns the value of the node parameter
        /// \param node node to be removed
        /// \return Returns pointer to a removed node
        CNode* takeChildNode(CNode* node);

        /// Remove all child nodes (including their child nodes) and releases the allocated
        /// memory.
        void removeAllChildNodes();

        /// Check if a specified node is (direct or indirect) parent of this item.
        /// The function returns true if the specified node is item's parent, if not the function continues
        /// recusively up in the structure up to the top level item.
        /// \param node node that shall be self's parent
        bool isParentOf(const CNode* node) const;

        // Support for lists
        // -----------------

        /// First value in the list (synonym for firstChildObject())
        const CNode* firstValue() const { return firstChildNode(); }

        /// Next sibling node (synonym for getNextSiblingNode())
        const CNode* nextValue(void) const { return nextSiblingNode(); }

        /// Number of items (including any `null` entries).
        ///
        /// Counts only direct child nodes, compound entries are counted as one.
        int size(void) const;


        // Support for maps
        // ----------------

        /// Key for this item
        ///
        /// This field is valid only for members of an associative list (map)
        const QString& key(void) const { return m_key; }

        /// Next map item by key
        ///
        /// This method is valid only for members of an associative list (map)
        const CNode* nextValue(const QString& key) const;


        // Getters (conversion functions)
        // ------------------------------
        // The functions retrieve value stored in 'this' node.

        /// Returns _true_ if this is a _null_ value. It is a special value denoted by `null` keyword.
        virtual bool isNull(void) const = 0;

        /// Get value as a string
        ///
        /// If the node value represents a primitive value that can be converted to a string,
        /// it returns the string, otherwise sets _ok_ to false and returns an empty string.
        /// \param[out] ok set to true on success, false on failure
        /// \return value as a string or an empty string
        virtual QString toString(bool* ok = NULL) const { if (ok) *ok = false; return QString(); }

        /// Get integer value
        ///
        /// If the node value represents a primitive value that can be converted to an integer value,
        /// it returns the value, otherwise sets _ok_ to false and returns zero
        /// \param[out] ok set to true on success, false on failure
        /// \return value as an integer number or zero 
        virtual int toInt(bool* ok = NULL) const { if (ok) *ok = false; return 0; }

        /// Get numeric value
        ///
        /// If the node value represents a primitive value that can be converted to a numeric value,
        /// it returns the value, otherwise sets _ok_ to false and returns zero
        /// \param[out] ok set to true on success, false on failure
        /// \return value as a number or zero 
        virtual double toDouble(bool* ok = NULL) const { if (ok) *ok = false; return 0; }

        /// Get logic value
        ///
        /// If the node value represents a primitive value that can be converted to a logic value,
        /// it returns the value, otherwise sets _ok_ to false and returns zero
        /// \param[out] ok set to true on success, false on failure
        /// \return value as a logic value or zero 
        virtual bool toBool(bool* ok = NULL) const { if (ok) *ok = false; return false; }

        /// Get value as a list
        ///
        /// If the node value represents an ordered list, it returns pointer to self. Otherwise,
        /// returns NULL.
        /// \return value as an ordered list or NULL
        virtual const CArray* toList(void) const { return NULL; }

        /// Get value as a map
        ///
        /// If the node value represents an associative list, it returns pointer to self. Otherwise,
        /// returns NULL.
        /// \return value as an associative list or NULL
        virtual const CObject* toMap(void) const { return NULL; }

    protected:
        /// Add a node after the last child node
        ///
        /// The function inserts specified node (and its child nodes) to this node after the last item. The functions modifies 
        /// the specified node and sets the reference to the parent node. If the specified 
        /// node is already member of another node, it is removed from its current parent node first.
        /// \param node node to be added
        /// \param key associated key in the associative list
        void appendChildObject(CNode* node, const QString& key);

        /// Add a node before the first child node
        ///
        /// The function prepends specified node (and its child nodes) to this node before the first item. The functions modifies 
        /// the specified node and sets the reference to the parent node. If the specified 
        /// node is already member of another node, it is removed from its current parent node first.
        /// \param node node to be added
        /// \param key associated key in the associative list
        void prependChildObject(CNode* node, const QString& key);

    private:
        /// Associated key (for members of an associative list)
        QString m_key;

        /// Token that generated the node
        tToken m_token;

        /// Parent node
        CNode* m_parent;

        /// Next sibling node
        CNode* m_nextSibling;

        /// Previous sibling nde
        CNode* m_previousSibling;

        /// Find child node
        CNode* m_firstChild;

        /// Last child node
        CNode* m_lastChild;

        /// Add a child node
        ///
        /// The function appends specified node and its child nodes to this node. The functions modifies 
        /// the specified node and sets the reference to the parent node. If the specified 
        /// node is already member of another node, it is removed from its current parent node first.
        /// \param node node to be appended
        void appendChildNode(CNode* node);

        /// Add a child node
        ///
        /// The function appends specified node and its child nodes to this node. The functions modifies 
        /// the specified node and sets the reference to the parent node. If the specified 
        /// node is already member of another node, it is removed from its current parent node first.
        /// \param node node to be appended
        void prependChildNode(CNode* node);
    };
}
