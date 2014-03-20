/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-13 *
*************************/
#pragma once

#include "StdAfx.h"
#include "PhysicsObject.h"

#include <vector>
#include <utility>

class Scene
{
// Ctors
public:
	// Default Constructor
	// Creates Scene with 9.8m/s^2 gravity
	Scene();

	// Creates zero-gravity Scene
	Scene(UINT _creationFlags);

	// Default destructor
	~Scene();

// Static data members
public:
	// Margin for determining corner-hits
	static const double CornerHitMargin;

// Helper Functions
private:
	// Checks two AABBs for overlap
	bool CheckOverlap(AABB, AABB);

	// Checks two PhysicsObjects for overlap based on AABBs
	bool CheckOverlap(PhysicsObject*, PhysicsObject*);

	// Check scene for possible collisions based on AABBs
	// Returns vector of possibly-colliding pairs
	std::vector<std::pair<PhysicsObject*,PhysicsObject*>> CheckCollisions();
	
	// Check scene for out-of-bounds objects based on type param
	// Returns vector of out-of-bounds objects
	std::vector<PhysicsObject*> CheckOutOfBounds(eAxis);

	// Determine collision axis of a pair of physics objects
	// Returns axis enum value
	eAxis GetCollisionAxis(std::pair<PhysicsObject*,PhysicsObject*>);

// Public Methods
public:
	// Returns scene gravity in m/s^2
	double GetGravity() {return m_gravity;};

	// Returns vector of physics objects
	std::vector<PhysicsObject*> GetObjects() {return m_physicsObjects;};

	// Add object to the scene
	// Returns S_OK on success, E_FAIL on failure
	HRESULT AddObject(PhysicsObject*);

	// Step physics scene forward
	// NOTE: Until multithreading implemented, steps forward 1s
	void Step();

// Properties
private:
	// List of all objects existing in the scene
	std::vector<PhysicsObject*> m_physicsObjects;

	// Gravity in the scene in m/s^2
	double m_gravity;
};
