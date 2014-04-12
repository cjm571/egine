/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-13 *
*************************/
#pragma once

#include "StdAfx.h"
#include "AABB.h"
#include "Trajectory.h"

class PhysicsObject
{
// Ctors
public:
	// Default constructor
	// Creates a 1kg black circle at bottom-left corner of containing Scene
	PhysicsObject();

	// Creates a 1kg black circle w/ 10m radius at centerpoint _center
	PhysicsObject(CartPoint _center);

	// Creates a 1kg black circle contained in boundaries of _aabb
	PhysicsObject(AABB _aabb);

	// Creates a 1kg object with specified attributes
	PhysicsObject(AABB _aabb, D2D1::ColorF::Enum _color, eShape _eShape);
	
	// Destructor
	~PhysicsObject();

// Public Methods
public:
	AABB GetAABB()					{return m_aabb;};
	Trajectory GetTrajectory()		{return m_trajectory;};
	double GetMass()				{return m_mass;};
	D2D1::ColorF::Enum GetColor()	{return m_color;};
	eShape GeteShape()				{return m_shape;};
	ULONG GetUID()					{return m_UID;};
	
	// Returns initial Cartesian position of object
	CartPoint GetInitialPosition();

	// Sets initial position of the PhysicsObject
	HRESULT SetInitialPosition(CartPoint newP0);

	// Changes trajectory of object
	HRESULT SetTrajectory(Trajectory);

	// Moves object forward in time to given time
	void Move(double t);

	// Resets an object's trajectory after collision on the given axis
	// NOTE: does NOT perform the subsequent Move()
	HRESULT Rebound(eAxis axis, double reboundTime);


// Public Static
public:
	// Checks two PhysicsObjects for overlap based on AABBs
	static bool CheckOverlap(PhysicsObject a, PhysicsObject b);
	
	// Calculates intra-step collisions position of 2 PhysicsObjects
	static std::pair<CartPoint,CartPoint> CalcActualCollisionPosition(PhysicsObject a, PhysicsObject b);

// Properties
private:
	// Axis-Aligned Bounding Box for use in collision detection
	AABB m_aabb;
		
	// Trajectory of object, will be acted on by physics operations
	Trajectory m_trajectory;

	// Mass of object in kg
	double m_mass;

	// Display attributes
	D2D1::ColorF::Enum m_color;
	eShape m_shape;
	
	// Unique identifier of object
	ULONG m_UID;

	// Tracks previously-assigned UID to avoid collisions
	static ULONG prevUID;
};