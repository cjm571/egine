// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

// Headers for CppUnitTest
#include "CppUnitTest.h"

// Headers from library
#include "..\..\Egine\Scene.h"

/*** CONSTANTS ***/
// Error bounds for distance measurements
extern const double DISTANCE_ERROR;
// Error bounds for angle measurements
extern const double ANGLE_ERROR;
// Error bounds for velocity measurements
extern const double VELOCITY_ERROR;
// Collision epicenter in Cartesian (x,y) coordinates
extern const CartPoint EPICENTER;
// Collision epicenter in Polar (r, theta) coordinates
extern const PolarPoint EPICENTER_POLAR;
// Distance (in meters) from collision epicenter
extern const double EPICENTER_OFFSET;
// Velocity of colliding object in m/s
extern const double DEFAULT_VELOCITY;
// Distance (in meters) between centerpoints when separation check is performed
extern const double SEPARATION_DISTANCE;

/*** TEST SCENE OBJECT ***/
// Scene object in which unit tests will occur
extern Scene testScene;