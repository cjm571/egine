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
	AABB(PhysPoint);
	AABB(PhysPoint, double, double);
	~AABB();

public:
	// Flag indicating desired coordinate system
	static enum CoordFlag
	{
		Physics = 0,
		Drawing = 1
	};

// Public Accessor Methods
public:
	// Returns physics or drawing center coords, based on flag
	PhysPoint GetCenter(CoordFlag);

	// Returns physics or drawing bottom-left coords, based on flag
	PhysPoint GetBottomLeft(CoordFlag);
	
	// Returns physics or drawing bottom-right coords, based on flag
	PhysPoint GetBottomRight(CoordFlag);
	
	// Returns physics or drawing top-left coords, based on flag
	PhysPoint GetTopLeft(CoordFlag);
	
	// Returns physics or drawing top-right coords, based on flag
	PhysPoint GetTopRight(CoordFlag);

	// Returns physcs or drawing upper boundary position, based on flag
	double GetUpperBound(CoordFlag);
	
	// Returns physcs or drawing lower boundary position, based on flag
	double GetLowerBound(CoordFlag);

	// Returns left boundary position
	double GetLeftBound();

	// Returns right boundary position
	double GetRightBound();

// Public Mutator Methods
public:
	// Sets the centerpoint, Bottom-Left-0-based
	void SetCenter(PhysPoint);

	// Sets width of bounding-box
	void SetWidth(double);

	// Sets height of bounding-box
	void SetHeight(double);

// Private data members
private:
	// Bottom-Left-0-based X, Y coordinates of AABB centerpoint
	PhysPoint m_center;

	// Width in meters
	double m_width;

	// Height in meters
	double m_height;
};