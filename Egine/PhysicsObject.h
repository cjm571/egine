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
	PhysicsObject(AABB, D2D1::ColorF::Enum, Shape);
	~PhysicsObject();

// Public Methods
public:
	AABB GetAABB() {return m_aabb;};
	double GetMass() {return m_mass;};
	D2D1::ColorF::Enum GetColor() {return m_color;};
	Shape GetShape() {return m_shape;};
	ULONG GetUID() {return m_UID;};

// Properties
private:
	// Axis-Aligned Bounding Box for use in collision detection
	AABB m_aabb;

	// Mass of object in kg
	double m_mass;

	// Display attributes
	D2D1::ColorF::Enum m_color;
	Shape m_shape;
	
	// Unique identifier of object
	ULONG m_UID;

	// Tracks previously-assigned UID to avoid collisions
	static ULONG prevUID;
};