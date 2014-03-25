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
	// All coefficients initialized to 0
	Quadratic();
	// Defines quadratic with given coefficients
	Quadratic(double _a, double _b, double _c);

// Public Methods
public:
	void SetA(double newA);
	void SetB(double newB);
	void SetC(double newC);

	// Calculates real-number roots of the quadratic
	std::pair<double,double> GetRoots();

	// Returns slope of the tangent line (in radians between 0,2pi) at the given point
	double GetTangentSlope(double x);

	// Solves quadratic given the value of x
	double Solve(double x);

// Coefficients
private:
	double m_a;
	double m_b;
	double m_c;
};