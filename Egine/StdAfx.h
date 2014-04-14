/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-07 *
*************************/
#pragma once

// Allow use of math.h #defines
#define _USE_MATH_DEFINES

// C Runtime header files
#include <stdlib.h>
#include <math.h>

// C++ Standard Library
#include <utility>
#include <vector>
#include <algorithm>

// Homegrown Multi-platform utilities
#include "MPUtils.h"


/***** GLOBAL TYPES *****/
// Represents Cartesian (x,y) coordinates of a physics object
typedef struct
{
	double x;
	double y;
} CartPoint;

// Represents Polar (r,theta) coordinates of a physics object
typedef struct
{
	double r;
	double theta;
} PolarPoint;


/***** GLOBAL HELPER FUNCTIONS *****/
// Returns true if doubles are within DOUBLE_EPSILON of each other
// Returns false otherwise
extern bool AreEqual(double a, double b);
// Converts Cartesian coordinates to Polar
extern PolarPoint CartToPolar(CartPoint cPoint);
// Converts Polar coordinates to Cartesian
extern CartPoint PolarToCart(PolarPoint pPoint);
// Wraps angles between 0 and 2pi
extern double WrapAngle(double angle);
// Returns roots of a quadratic function ax^2 + bx + c = 0
extern std::pair<double,double> SolveQuadratic(double a, double b, double c);
// Sets value of c (pointer parameter) by solving Pythagorean Theorem
extern PHRESULT Pythag(double a, double b, double* c);
// Sets value of b (pointer parameter) by solving Pythagorean Theorem
extern PHRESULT Pythag(double a, double* b, double c);
// Sets value of a (pointer parameter) by solving Pythagorean Theorem
extern PHRESULT Pythag(double* a, double b, double c);

// Enumeration of valid physics object Shapes
enum eShape
{
	PhysCircle = 0,
	PhysTriangle = 1,
	PhysRectangle = 2
};

// Denotes axis of collision
enum eAxis
{
	XAxis = 0,
	YAxis = 1,
	BothAxes = 2,
	AxisErr = -1
};

// Flag indicating desired coordinate system
enum eCoordSys
{
	Physics = 0,
	Drawing = 1
};


/***** SCENE PARAMETERS *****/
// Scene width in meters
// 03/07/14: currently 1m = 1px
extern double SCENE_WIDTH;
// Scene height in meters (03/07/14 currently 1m = 1px)
extern double SCENE_HEIGHT;


/***** SCENE CREATION FLAGS *****/
enum SceneGravityFlags
{
	// Created Scene will have 0 gravity
	SC_GRAVITY_OFF		= 0x00000000,
	// Created Scene will have Earth gravity
	SC_GRAVITY_EARTH	= 0x00000001,
	// Created Scene will have Moon gravity
	SC_GRAVITY_MOON		= 0x00000002
};


/***** SCENE CREATION MASKS *****/
// Gravity on/off mask
extern const UINT SC_GRAVITY_MASK;

/***** CONSTANTS *****/
// Speed of light in m/s
extern const UINT C;
// Amount of time (in seconds) between each physics calculation
extern const double STEP_EPSILON;
// Epsilon between distinct 'double's
// All doubles within this delta from each other are considered the same value;
extern const double DOUBLE_EPSILON;
// Acceptable error for collision detection
extern const double ERR_COLLISION;