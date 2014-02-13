/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-13 *
*************************/
#pragma once

#include "StdAfx.h"
#include "PhysicsObject.h"

#include <vector>

class PhysicsScene
{
// Ctors
public:
	PhysicsScene();
	~PhysicsScene();

// Methods
private:
	

// Properties
private:
	// List of all objects existing in the scene
	std::vector<PhysicsObject *> PhysicsObjects;

	// Scene size
	int width;
	int height;
};
