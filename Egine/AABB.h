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
	// Default Constructor
	// Creates 20x20 AABB at Physics (10,10) 
	AABB();

	// Creates 20x20 AABB at Physics _center
	AABB(CartPoint _center);

	// Creates _widthx_height AABB at Physics _center
	AABB(CartPoint _center, double _width, double _height);
	~AABB();

// Public Accessor Methods
public:
	double GetWidth() {return m_width;};
	double GetHeight() {return m_height;};

	// Returns physics or drawing center coords, based on flag
	CartPoint GetCenter(eCoordSys flag=Physics);

	// Returns physics or drawing bottom-left coords, based on flag
	CartPoint GetBottomLeft(eCoordSys flag=Physics);
	
	// Returns physics or drawing bottom-right coords, based on flag
	CartPoint GetBottomRight(eCoordSys flag=Physics);
	
	// Returns physics or drawing top-left coords, based on flag
	CartPoint GetTopLeft(eCoordSys flag=Physics);
	
	// Returns physics or drawing top-right coords, based on flag
	CartPoint GetTopRight(eCoordSys flag=Physics);

	// Returns physcs or drawing upper boundary position, based on flag
	double GetUpperBound(eCoordSys flag=Physics);
	
	// Returns physcs or drawing lower boundary position, based on flag
	double GetLowerBound(eCoordSys flag=Physics);

	// Returns left boundary position
	double GetLeftBound();

	// Returns right boundary position
	double GetRightBound();

// Public Mutator Methods
public:
	// Sets the centerpoint, Bottom-Left-0-based
	void SetCenter(CartPoint);

	// Sets width of bounding-box
	void SetWidth(double);

	// Sets height of bounding-box
	void SetHeight(double);

// Public statics
public:
	// Checks two AABBs for overlap
	static bool CheckOverlap(AABB a, AABB b);

// Private data members
private:
	// Bottom-Left-0-based X, Y coordinates of AABB centerpoint
	CartPoint m_center;

	// Width in meters
	double m_width;

	// Height in meters
	double m_height;
};