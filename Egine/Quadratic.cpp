/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-03-22 *
*************************/

#include "Quadratic.h"

/********** CTORS **********/
Quadratic::Quadratic()
	: m_a(1), m_b(1), m_c(1)
{
}

Quadratic::Quadratic(double _a, double _b, double _c)
	: m_a(_a), m_b(_b), m_c(_c)
{
}


/********** PUBLIC METHODS **********/
std::pair<double,double> Quadratic::GetRoots()
{
	// Solve for quadratic roots
	double posRoot = ((-1*m_b) + sqrt(pow(m_b,2) - 4*m_a*m_c)) / (2*m_a);
	double negRoot = ((-1*m_b) - sqrt(pow(m_b,2) - 4*m_a*m_c)) / (2*m_a);
	
	// Make and return pair of roots
	std::pair<double,double> roots = std::make_pair(posRoot, negRoot);

	return roots;
}

double Quadratic::GetTangentSlope(double x)
{
	double slope = 0.0;

	// f'(x) = ax + b
	double a = 2*m_a;
	double b = m_b;

	// Convert slope to angle in radians
	slope = atan(a*x + b);

	return slope;
}