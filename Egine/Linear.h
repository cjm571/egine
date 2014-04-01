/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-04-01 *
*************************/
#pragma once

class Linear
{
// Ctors
public:
	// Default constructor
	// Coefficients initialized to 0.0
	Linear();

	// Defines Linear function with given coefficients
	Linear(double _a, double _b);
	
// Public Methods
public:
	double GetA() {return m_a;};
	double GetB() {return m_b;};
	void SetA(double newA);
	void SetB(double newB);

	// Returns real-number root of the function
	double GetRoot();

	// Solves given the value of x
	double Solve(double x);
	
// Coefficients
// Form: f(x) = ax + b
private:
	double m_a;
	double m_b;
};
