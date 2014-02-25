/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-13 *
*************************/
#pragma once

#include "StdAfx.h"

class AABB
{
// Ctors
public:
	AABB();
	AABB(PhysPoint, PhysPoint);
	AABB(PhysPoint, UINT, UINT);
	~AABB();

// Public methods
public:
	// ***For physics functions***
	// Returns bottom-left corner point
	PhysPoint GetMin() {return m_min;};
	// ***For physics functions***
	// Returns top-right corner point
	PhysPoint GetMax() {return m_max;};
	// ***For physics functions***
	// Returns center point
	PhysPoint GetMiddle() {return m_center;};
	
	// ***For drawing functions***
	// Returns top-left corner point
	PhysPoint GetTL();
	// ***For drawing functions***
	// Returns bottom-right corner point
	PhysPoint GetBR();
	// ***For drawing functions***
	// Returns center point
	PhysPoint GetCenter();

// Public fields
private:
	// Bottom-Left-0-based X, Y coordinates of AABB
	PhysPoint m_min;
	PhysPoint m_max;
	PhysPoint m_center;
};