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
double Parametric::GetTangentAngle(double t)
{
	double angle = -1.0;

	// Get derivatives of quadratics
	Linear dx_dt = m_x.Derive();
	Linear dy_dt = m_y.Derive();

	// m = dy/dx
	double dx = dx_dt.Solve(t);
	double dy = dy_dt.Solve(t);
	angle = atan2(dy, dx);

	return angle;
}

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

std::pair<double,double> Parametric::GetXRoots(double xt)
{
	std::pair<double,double> roots;

	roots = m_x.GetRoots(xt);

	return roots;
}

std::pair<double,double> Parametric::GetYRoots(double yt)
{
	std::pair<double,double> roots;

	roots = m_y.GetRoots(yt);

	return roots;
}