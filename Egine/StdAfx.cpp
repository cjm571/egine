/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-07 *
*************************/

// Inludes just standard includes and globals
// Generates Egine.pch precompiled header and StdAfx.obj for precompiled type info
#include "stdafx.h"

/***** GLOBAL HELPER FUNCTIONS *****/
PolarPoint CartToPolar(CartPoint cPoint)
{
	double r = 0.0;
	double theta = 0.0;

	r = sqrt((cPoint.x*cPoint.x) + (cPoint.y*cPoint.y));
	theta = atan(cPoint.y / cPoint.x);

	PolarPoint pPoint = {r, theta};

	return pPoint;
}
CartPoint PolarToCart(PolarPoint pPoint)
{
	double x = 0.0;
	double y = 0.0;

	x = pPoint.r * cos(pPoint.theta);
	y = pPoint.r * sin(pPoint.theta);

	CartPoint cPoint = {x, y};

	return cPoint;
}
double WrapAngle(double angle)
{
	// Wrap around at 2pi
	while (angle >= 2*M_PI)
	{
		angle -= 2*M_PI;
	}

	// Wrap around at 0
	while (angle < 0)
	{
		angle += 2*M_PI;
	}

	return angle;
}

/***** SCENE PARAMETERS *****/
double SCENE_WIDTH =	640.0;
double SCENE_HEIGHT =	480.0;


/***** SCENE CREATION MASKS *****/
UINT const SC_GRAVITY_MASK =	0x00000001;


/***** CONSTANTS *****/
UINT const C = 299792458;
double ERR_COLLISION = 0.0001;