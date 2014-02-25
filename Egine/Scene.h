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

// Public Methods
public:
	// Returns vector of physics objects
	std::vector<PhysicsObject*> GetObjects() {return m_physicsObjects;};

	// Add object to the scene at specified coords
	// Returns S_OK on success, E_FAIL on failure
	HRESULT AddObject(PhysicsObject*);

	// Check scene for possible collisions based on AABBs
	// Returns vector of UIDs of possibly-colliding pairs
	std::vector<std::pair<ULONG/*UID*/,ULONG/*UID*/>> CheckCollisions();

	// Imposes gravitational effects on physics objects
	HRESULT ImposeGravity();

// Properties
private:
	// List of all objects existing in the scene
	std::vector<PhysicsObject*> m_physicsObjects;
};
