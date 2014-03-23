/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-03-22 *
*************************/
#pragma once

#include <math.h>
#include <utility>

class Quadratic
{
// Ctors
public:
	// Default Constructor
	// Defines a quadratic with 1 for all coefficients
	Quadratic();

	// Defines quadratic with given coefficients
	Quadratic(double _a, double _b, double _c);

// Public Methods
public:
	// Solves quadratic for its real-number roots
	std::pair<double,double> GetRoots();

	// Returns slope of the tangent line (in radians between 0,2pi) at the given point
	double GetTangentSlope(double x);

// Coefficients
private:
	double m_a;
	double m_b;
	double m_c;
};