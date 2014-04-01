/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-04-01 *
*************************/

#include "Linear.h"

/********** CTORS **********/
Linear::Linear()
	: m_a(0.0), m_b(0.0)
{
}

Linear::Linear(double _a, double _b)
	: m_a(_a), m_b(_b)
{
}


/********** PUBLIC METHODS **********/
void Linear::SetA(double newA)
{
	m_a = newA;
}

void Linear::SetB(double newB)
{
	m_b = newB;
}

double Linear::GetRoot()
{
	double root = 0.0;

	root = (-1*m_b)/m_a;

	return root;
}

double Linear::Solve(double x)
{
	double solution = 0.0;

	solution = m_a*x + m_b;

	return solution;
}
