/****************************************************************************/
/// @file    NamedRTree.h
/// @author  Daniel Krajzewicz
/// @date    27.10.2008
/// @version $Id$
///
// A RT-tree for efficient storing of SUMO's Named objects
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo-sim.org/
// Copyright (C) 2001-2013 DLR (http://www.dlr.de/) and contributors
/****************************************************************************/
//
//   This file is part of SUMO.
//   SUMO is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/
#ifndef NamedRTree_h
#define NamedRTree_h


// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#include <set>
#include <foreign/rtree/RTree.h>
#include <utils/common/Named.h>

//#include "RTree.h"


// specialized implementation for speedup and avoiding warnings
template<>
inline float RTree<Named*, Named, float, 2, Named::StoringVisitor, float, 8, 4>::RectSphericalVolume(Rect* a_rect) {
    ASSERT(a_rect);
    const float extent0 = a_rect->m_max[0] - a_rect->m_min[0];
    const float extent1 = a_rect->m_max[1] - a_rect->m_min[1];
    return .78539816f * (extent0 * extent0 + extent1 * extent1);
}


// ===========================================================================
// class definitions
// ===========================================================================
/** @class NamedRTree
 * @brief A RT-tree for efficient storing of SUMO's Named objects
 *
 * This class specialises the used RT-tree implementation from "rttree.h".
 * It stores names of "Named"-objects.
 * @see Named
 */
class NamedRTree : private RTree<Named*, Named, float, 2, Named::StoringVisitor > {
public:
    /// @brief Constructor
    NamedRTree()
        : RTree<Named*, Named, float, 2, Named::StoringVisitor, float>(&Named::addTo) {
    }


    /// @brief Destructor
    ~NamedRTree() {
    }


    /** @brief Insert entry
     * @param a_min Min of bounding rect
     * @param a_max Max of bounding rect
     * @param a_data The instance of a Named-object to add (the ID is added)
     * @see RTree::Insert
     */
    void Insert(const float a_min[2], const float a_max[2], Named* a_data) {
        RTree<Named*, Named, float, 2, Named::StoringVisitor, float>::Insert(a_min, a_max, a_data);
    }


    /** @brief Remove entry
     * @param a_min Min of bounding rect
     * @param a_max Max of bounding rect
     * @param a_data The instance of a Named-object to remove
     * @see RTree::Remove
     */
    void Remove(const float a_min[2], const float a_max[2], Named* a_data) {
        RTree<Named*, Named, float, 2, Named::StoringVisitor, float>::Remove(a_min, a_max, a_data);
    }


    /** @brief Find all within search rectangle
     * @param a_min Min of search bounding rect
     * @param a_max Max of search bounding rect
     * @param a_searchResult Search result array.  Caller should set grow size. Function will reset, not append to array.
     * @param a_resultCallback Callback function to return result.  Callback should return 'true' to continue searching
     * @param a_context User context to pass as parameter to a_resultCallback
     * @return Returns the number of entries found
     * @see RTree::Search
     */
    int Search(const float a_min[2], const float a_max[2], const Named::StoringVisitor& c) const {
        return RTree<Named*, Named, float, 2, Named::StoringVisitor, float>::Search(a_min, a_max, c);
    }


};


#endif

/****************************************************************************/

