/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-03-22 *
*************************/

#include "Quadratic.h"

/********** CTORS **********/
Quadratic::Quadratic()
	: m_a(0.0), m_b(0.0), m_c(0.0)
{
}
Quadratic::Quadratic(double _a, double _b, double _c)
	: m_a(_a), m_b(_b), m_c(_c)
{
}


/********** PUBLIC METHODS **********/
void Quadratic::SetA(double newA)
{
	m_a = newA;
}
void Quadratic::SetB(double newB)
{
	m_b = newB;
}
void Quadratic::SetC(double newC)
{
	m_c = newC;
}

std::pair<double,double> Quadratic::GetRoots(double fx)
{
	// Solve for quadratic roots
	double c = m_c - fx;
	double posRoot = ((-1*m_b) + sqrt(pow(m_b,2) - 4*m_a*c)) / (2*m_a);
	double negRoot = ((-1*m_b) - sqrt(pow(m_b,2) - 4*m_a*c)) / (2*m_a);
	
	// Make and return pair of roots
	std::pair<double,double> roots = std::make_pair(posRoot, negRoot);

	return roots;
}

double Quadratic::GetTangentAngle(double x)
{
	double angle = -1.0;

	// f'(x) = 2ax + b
	double m = 2*m_a;
	double b = m_b;
	double slope = m*x + b;

	// Convert to angle and wrap
	angle = atan(slope);
	return angle;
}

double Quadratic::Solve(double x)
{
	double solution = 0.0;

	solution = m_a*pow(x,2) + m_b*x + m_c;

	return solution;
}

Linear Quadratic::Derive()
{
	return Linear(2*m_a, m_b);
}