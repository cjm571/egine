/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-07 *
*************************/
#pragma once

// C Runtime header files
#include <stdlib.h>

// Maths stuffs
#include <cmath>
#ifdef M_PI
#undef M_PI // undefine M_PI so my type-safe global M_PI can be used
#endif

// C++ Standard Library
#include <utility>
#include <vector>
#include <algorithm>

// Home-grown Multi-platform utilities
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
enum GravityFlag
{
	// Created Scene will have 0 gravity
	Off		= 0x00000000,
	// Created Scene will have Earth gravity
	Earth	= 0x00000001,
	// Created Scene will have Moon gravity
	Luna	= 0x00000002
};

// Log output mode
enum LogModeFlag
{
	Silent	= 0x00000000,
	StdOut	= 0x00000010,
	File	= 0x00000020,
	Both	= 0x00000030
};

/***** SCENE CREATION MASKS *****/
extern const UINT GRAV_MASK;
extern const UINT LOGMODE_MASK;

/***** CONSTANTS *****/
// pi!
extern const double M_PI;
// Speed of light in m/s
extern const UINT C;
// Zero gravity in m/s^2
extern const double GRAV_ZERO;
// Earth gravity in m/s^2
extern const double GRAV_EARTH;
// Luna gravity in m/s^2
extern const double GRAV_LUNA;
// Simulation start time
extern const double TIME_SIM_START;
// Amount of time (in seconds) between each physics calculation
extern const double TIME_SIM_EPSILON;
// Epsilon between distinct 'double's
// All doubles within this delta from each other are considered the same value;
extern const double DOUBLE_EPSILON;
// Acceptable error for collision detection
extern const double ERR_COLLISION;
