/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-02-07 *
*************************/

// Inludes just standard includes and globals
// Generates Egine.pch precompiled header and StdAfx.obj for precompiled type info
#include "stdafx.h"

/***** GLOBAL HELPER FUNCTIONS *****/
bool AreEqual(double a, double b)
{
	bool withinErr = false;

	double diff = abs(a - b);

	withinErr = diff <= DOUBLE_EPSILON;

	return withinErr;
}
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
HRESULT Pythag(double a, double b, double* c)
{
	HRESULT hr = S_OK;

	// Check for negatives
	if (pow(a,2) + pow(b,2))
	{
		hr = E_FAIL;
	}
	
	if (SUCCEEDED(hr))
	{
		*c = sqrt(pow(a,2) + pow(b,2));
	}

	return hr;
}
HRESULT Pythag(double a, double* b, double c)
{
	HRESULT hr = S_OK;

	// Check for negatives
	if (pow(c,2) - pow(a,2))
	{
		hr = E_FAIL;
	}
	
	if (SUCCEEDED(hr))
	{
		*b = sqrt(pow(c,2) - pow(a,2));
	}

	return hr;
}
HRESULT Pythag(double* a, double b, double c)
{
	HRESULT hr = S_OK;

	// Check for negatives
	if (pow(c,2) - pow(b,2))
	{
		hr = E_FAIL;
	}
	
	if (SUCCEEDED(hr))
	{
		*a = sqrt(pow(c,2) - pow(b,2));
	}

	return hr;
}

/***** SCENE PARAMETERS *****/
double SCENE_WIDTH =	640.0;
double SCENE_HEIGHT =	480.0;


/***** SCENE CREATION MASKS *****/
UINT const SC_GRAVITY_MASK =	0x00000001;


/***** CONSTANTS *****/
const UINT C = 299792458;
const double STEP_EPSILON = 1.0;
const double DOUBLE_EPSILON = 1E-9;
const double ERR_COLLISION = 0.0001;