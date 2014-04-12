/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-03-25 *
*************************/
#pragma once

#include "Quadratic.h"

class Parametric
{
// Ctors
public:
	// Default Constructor
	// x(t), y(t) initialized to default (empty) quadratic
	Parametric();

	// _x and _y represent the quadratic parametric functions x(t) and y(t)
	Parametric(Quadratic _x, Quadratic _y);

// Public Methods
public:	
	Quadratic GetXQuadratic() {return m_x;};
	Quadratic GetYQuadratic() {return m_y;};

	// Returns angle of the tangent line (in radians) at the given time
	double GetTangentAngle(double t);
	
	// Solve for value of x(t) given t
	double SolveX(double t);
	// Solve for value of y(t) given t
	double SolveY(double t);
	
	// Return real-number roots of x(t)
	std::pair<double,double> GetXRoots(double xt=0.0);
	// Return real-number roots of y(t)
	std::pair<double,double> GetYRoots(double yt=0.0);

	// Calculates X-intercept given offset from initial position
	std::pair<double,double> CalcXIntercepts(double offset=0.0);
	// Calculates Y-intercept given offset from initial position
	std::pair<double,double> CalcYIntercepts(double offset=0.0);

// Data Members
protected:
	// Quadratic equation representing x(t)
	Quadratic m_x;

	// Quadratic equation representing y(t)
	Quadratic m_y;
};