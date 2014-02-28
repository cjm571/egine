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
	Scene();
	~Scene();

// Bounds-check flag
public:
	static enum BoundsType
	{
		XBounds = 0,
		YBounds = 1
	};

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
	std::vector<PhysicsObject*> CheckOutOfBounds(BoundsType);

// Public Methods
public:
	// Returns vector of physics objects
	std::vector<PhysicsObject*> GetObjects() {return m_physicsObjects;};

	// Add object to the scene at specified coords
	// Returns S_OK on success, E_FAIL on failure
	HRESULT AddObject(PhysicsObject*);

	// Step physics scene forward
	// NOTE: Until multithreading implemented, steps forward 0.1s
	void Step();

// Properties
private:
	// List of all objects existing in the scene
	std::vector<PhysicsObject*> m_physicsObjects;
};
