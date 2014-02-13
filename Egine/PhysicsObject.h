/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-13 *
*************************/
#pragma once

#include "StdAfx.h"
#include "AABB.h"

class PhysicsObject
{
// Ctors
public:
	PhysicsObject();
	~PhysicsObject();

// Methods
private:


// Properties
private:
	// Axis-Aligned Bounding Box for use in collision detection
	AABB aabb;

	// Mass of object in kg
	double mass;

	// Display attributes
	D2D1::ColorF color;
	Shape shape;
	
	// Unique identifier of object
	int UID;
};