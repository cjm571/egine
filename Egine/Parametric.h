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
	// Solve for value of x(t) given t
	double SolveX(double t);
	// Solve for value of y(t) given t
	double SolveY(double t);

// Data Members
protected:
	// Quadratic equation representing x(t)
	Quadratic m_x;

	// Quadratic equation representing y(t)
	Quadratic m_y;
};