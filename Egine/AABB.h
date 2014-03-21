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
	CartPoint GetCenter(eCoordSys);

	// Returns physics or drawing bottom-left coords, based on flag
	CartPoint GetBottomLeft(eCoordSys);
	
	// Returns physics or drawing bottom-right coords, based on flag
	CartPoint GetBottomRight(eCoordSys);
	
	// Returns physics or drawing top-left coords, based on flag
	CartPoint GetTopLeft(eCoordSys);
	
	// Returns physics or drawing top-right coords, based on flag
	CartPoint GetTopRight(eCoordSys);

	// Returns physcs or drawing upper boundary position, based on flag
	double GetUpperBound(eCoordSys);
	
	// Returns physcs or drawing lower boundary position, based on flag
	double GetLowerBound(eCoordSys);

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

// Private data members
private:
	// Bottom-Left-0-based X, Y coordinates of AABB centerpoint
	CartPoint m_center;

	// Width in meters
	double m_width;

	// Height in meters
	double m_height;
};