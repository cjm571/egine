// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

// Headers for CppUnitTest
#include "CppUnitTest.h"

// Headers from library
#include "..\Egine\Scene.h"

/*** CONSTANTS ***/
// Error bounds
extern const double ALLOWABLE_ERROR;
// Collision epicenter in Cartesian (x,y) coordinates
extern const CartPoint EPICENTER;
// Collision epicenter in Polar (r, theta) coordinates
extern const PolarPoint EPICENTER_POLAR;
// Distance in meters from collision epicenter
extern const double EPICENTER_OFFSET;
// Velocity of colliding object in m/s
extern const double OBJECT_VELOCITY;

/*** TEST SCENE OBJECT ***/
// Scene object in which unit tests will occur
extern Scene testScene;