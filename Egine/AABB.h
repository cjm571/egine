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
	// Accessors for physics functions
	PhysPoint GetMin() {return m_min;};
	PhysPoint GetMax() {return m_max;};
	PhysPoint GetCenter() {return m_center;};

	// Accessors for drawing functions
	PhysPoint GetTL();
	PhysPoint GetBR();
	PhysPoint GetTL0Center();

// Public fields
private:
	// Bottom-Left-0-based X, Y coordinates of AABB
	PhysPoint m_min;
	PhysPoint m_max;
	PhysPoint m_center;
};