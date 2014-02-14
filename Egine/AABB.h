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
	~AABB();

// Public methods
public:
	Point getMin() {return m_min;};
	Point getMax() {return m_max;};
	Point getCenter() {return m_center};

// Public fields
private:
	// X, Y coordinates of AABB
	Point m_min;
	Point m_max;
	Point m_center;

	// Measurements
	double m_width;
	double m_height;
};