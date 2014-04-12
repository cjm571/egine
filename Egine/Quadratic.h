/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-03-22 *
*************************/
#pragma once

#include <math.h>
#include <utility>
#include "Linear.h"

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
	double GetA() {return m_a;};
	double GetB() {return m_b;};
	double GetC() {return m_c;};
	void SetA(double newA);
	void SetB(double newB);
	void SetC(double newC);

	// Calculates real-number roots of the quadratic
	std::pair<double,double> GetRoots(double fx = 0.0);

	// Returns angle of the tangent line (in radians) at the given point
	double GetTangentAngle(double x);

	// Solves quadratic given the value of x
	double Solve(double x);

	// Returns derivative as Linear function object
	Linear Derive();

	// Returns solution to the derivative at the given point
	double Derive(double x);

// Public Statics
public:
	// Calculates intersections of Quadratics f(x) and g(x)
	static std::pair<double,double> CalcIntersects(Quadratic f, Quadratic g);

// Coefficients
// Form f(x) = ax^2 + bx + c
private:
	double m_a;
	double m_b;
	double m_c;
};