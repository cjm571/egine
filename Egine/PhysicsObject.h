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

// Public Methods
public:
	AABB getAABB() {return m_aabb;};
	double getMass() {return m_mass;};
	int getUID() {return m_UID;};

// Properties
private:
	// Axis-Aligned Bounding Box for use in collision detection
	AABB m_aabb;

	// Mass of object in kg
	double m_mass;

	// Display attributes
	D2D1::ColorF color;
	Shape m_shape;
	
	// Unique identifier of object
	int m_UID;
};