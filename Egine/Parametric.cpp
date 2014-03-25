/*************************
* Author: CJ McAllister  *
*                        *
* Created on: 2014-03-25 *
*************************/

#include "Parametric.h"

/********** CTORS **********/
Parametric::Parametric()
{
}
Parametric::Parametric(Quadratic _x, Quadratic _y)
{
	m_x = _x;
	m_y = _y;
}


/********** PUBLIC METHODS **********/
double Parametric::SolveX(double t)
{
	double solution = 0.0;

	solution = m_x.Solve(t);

	return solution;
}

double Parametric::SolveY(double t)
{
	double solution = 0.0;

	solution = m_y.Solve(t);

	return solution;
}